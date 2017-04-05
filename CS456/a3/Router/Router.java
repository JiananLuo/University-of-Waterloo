import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;

class pkt_INIT
{
	// size 4
	int router_id; /* id of the router that send the INIT PDU */

	pkt_INIT(int router_id)
	{
		this.router_id = router_id;
	}

	public byte[] getUDPdata()
	{
		ByteBuffer buffer = ByteBuffer.allocate(4);
		buffer.order(ByteOrder.LITTLE_ENDIAN);
		buffer.putInt(router_id);
		return buffer.array();
	}
}

class pkt_HELLO
{
	// size 8
	int router_id; /* id of the router who sends the HELLO PDU */
	int link_id; /* id of the link through which it is sent */

	pkt_HELLO(int router_id, int link_id)
	{
		this.router_id = router_id;
		this.link_id = link_id;
	}

	public byte[] getUDPdata()
	{
		ByteBuffer buffer = ByteBuffer.allocate(8);
		buffer.order(ByteOrder.LITTLE_ENDIAN);
		buffer.putInt(router_id);
		buffer.putInt(link_id);
		return buffer.array();
	}

	public static pkt_HELLO parseUDPdata(byte[] UDPdata) throws Exception
	{
		ByteBuffer buffer = ByteBuffer.wrap(UDPdata);
		buffer.order(ByteOrder.LITTLE_ENDIAN);
		int router_id = buffer.getInt();
		int link_id = buffer.getInt();
		return new pkt_HELLO(router_id, link_id);
	}
}

class pkt_LSPDU
{
	// size 20
	int source_router_id; /* sender of the LS PDU */
	int dest_router_id; /* router id */
	int link_id; /* link id */
	int cost; /* cost of the link */
	int via; /* id of the link through which the LS PDU is sent */

	pkt_LSPDU(int router_id, int link_id, int cost)
	{
		this.source_router_id = 0;
		this.dest_router_id = router_id;
		this.link_id = link_id;
		this.cost = cost;
		this.via = 0;
	}

	pkt_LSPDU(int sender, int router_id, int link_id, int cost, int via)
	{
		this.source_router_id = sender;
		this.dest_router_id = router_id;
		this.link_id = link_id;
		this.cost = cost;
		this.via = via;
	}

	public byte[] getUDPdata()
	{
		ByteBuffer buffer = ByteBuffer.allocate(20);
		buffer.order(ByteOrder.LITTLE_ENDIAN);
		buffer.putInt(source_router_id);
		buffer.putInt(dest_router_id);
		buffer.putInt(link_id);
		buffer.putInt(cost);
		buffer.putInt(via);
		return buffer.array();
	}

	public static pkt_LSPDU parseUDPdata(byte[] UDPdata) throws Exception
	{
		ByteBuffer buffer = ByteBuffer.wrap(UDPdata);
		buffer.order(ByteOrder.LITTLE_ENDIAN);
		int sender = buffer.getInt();
		int router_id = buffer.getInt();
		int link_id = buffer.getInt();
		int cost = buffer.getInt();
		int via = buffer.getInt();
		return new pkt_LSPDU(sender, router_id, link_id, cost, via);
	}
}

class link_cost
{
	// size 8
	int link; /* link id */
	int cost; /* associated cost */

	link_cost(int link, int cost)
	{
		this.link = link;
		this.cost = cost;
	}
}

class circuit_DB
{
	// max size: 4+ 5*8 = 44
	int nbr_link; /* number of links attached to a router */
	ArrayList<link_cost> linkcosts = new ArrayList<link_cost>();

	/* we assume that at most NBR_ROUTER links are attached to each router */
	circuit_DB(int nbr_link, ArrayList<link_cost> linkcost)
	{
		this.nbr_link = nbr_link;
		this.linkcosts = linkcost;
	}

	// convert data in bytes to circuit_DB
	public static circuit_DB parseUDPdata(byte[] UDPdata) throws Exception
	{
		ByteBuffer buffer = ByteBuffer.wrap(UDPdata);
		buffer.order(ByteOrder.LITTLE_ENDIAN);
		int nbr_link = buffer.getInt();

		ArrayList<link_cost> linkcosts = new ArrayList<link_cost>();
		for (int i = 0; i < nbr_link; i++)
		{
			int link = buffer.getInt();
			int cost = buffer.getInt();
			link_cost linkcost = new link_cost(link, cost);
			linkcosts.add(linkcost);
		}
		return new circuit_DB(nbr_link, linkcosts);
	}
}

class Neighbor
{
	int link_id;
	int cost;
	int neighbor_id;

	Neighbor(int link_id, int cost)
	{
		this.link_id = link_id;
		this.cost = cost;
		this.neighbor_id = -1;
	}
}

public class Router
{
	static final int NBR_ROUTER = 5;

	static int routerID;
	static String networkEmulatorHostName;
	static int UDPPortSend;
	static int UDPPortReceive;

	static String logFileName;
	static FileWriter routerLogFile;
	static InetAddress networkEmulatorAddress;

	static DatagramSocket UDPSocket;
	ArrayList<pkt_LSPDU> topologyDB;
	ArrayList<Neighbor> neighbor;
	int ShortestPathTable[][];
	HashMap<Integer, Integer> neighborMap;
	Queue<Integer>[] roadMap = new Queue[NBR_ROUTER];

	public Router() throws SocketException
	{
		// generate UPD socket to send & receive packets
		UDPSocket = new DatagramSocket();
		// init Topology Database
		topologyDB = new ArrayList<pkt_LSPDU>();
		// init neighbor
		neighbor = new ArrayList<Neighbor>();
		// init ShortestPathTable
		ShortestPathTable = new int[NBR_ROUTER][NBR_ROUTER];
		for (int i = 0; i < NBR_ROUTER; i++)
		{
			for (int j = 0; j < NBR_ROUTER; j++)
			{
				ShortestPathTable[i][j] = 0;
			}
		}
		// init neighbor hashMap
		neighborMap = new HashMap<Integer, Integer>();
		for (int i = 0; i < NBR_ROUTER; i++)
		{
			roadMap[i] = new LinkedList<Integer>();
		}
	}

	public static void main(String argv[]) throws Exception
	{
		// check argument if there are errors
		commandLineArgumentCheck(argv);
		// new a router object
		Router router = new Router();
		// generate init packet
		pkt_INIT pkt_Init = new pkt_INIT(routerID);
		// send init packet
		router.sendINIT(pkt_Init);
		// listen to circuit database
		router.listenCircuitDatabase();
		// send hello packets to neighbors
		router.sendHELLOS();
		// keep listen for HELLO & LSPDU packets
		router.listenLoop();
	}

	private static void commandLineArgumentCheck(String[] argv)
	{
		// if # of argument is not 4, terminate
		if (argv.length != 4)
		{
			System.err.println("Wrong number of command line argument.");
			System.exit(1);
		}
		try
		{
			routerID = Integer.valueOf(argv[0]);
			networkEmulatorHostName = argv[1];
			UDPPortSend = Integer.valueOf(argv[2]);
			UDPPortReceive = Integer.valueOf(argv[3]);
			logFileName = "router" + routerID + ".log";
			networkEmulatorAddress = InetAddress.getByName(networkEmulatorHostName);

			// clear logFile if already exist
			PrintWriter tempWriter = new PrintWriter(logFileName);
			tempWriter.print("");
			tempWriter.close();
			routerLogFile = new FileWriter(logFileName, true);
		}
		catch (Exception e)
		{
			System.err.println("Command line argument type error.");
			System.exit(1);
		}
	}

	private void sendPacket(byte[] pkt_send_data) throws IOException
	{
		// create the DatagramPacket to send
		DatagramPacket sendPacket = new DatagramPacket(pkt_send_data, pkt_send_data.length,
				networkEmulatorAddress, UDPPortSend);
		// send the DatagramPacket
		UDPSocket.send(sendPacket);
	}

	private void sendINIT(pkt_INIT pkt) throws IOException
	{
		// convert INIT to data in bytes and send it
		byte[] pkt_send_data = pkt.getUDPdata();
		sendPacket(pkt_send_data);

		// write to log file
		routerLogFile.write("R" + routerID + " sends an INIT: router_id" + pkt.router_id + "\n");
		routerLogFile.flush();
	}

	private void sendHELLO(pkt_HELLO pkt) throws IOException
	{
		// convert HELLO to data in bytes and send it
		byte[] pkt_send_data = pkt.getUDPdata();
		sendPacket(pkt_send_data);

		// write to log file
		routerLogFile.write("R" + routerID + " sends an HELLO: router_id" + pkt.router_id
				+ ", link_id " + pkt.link_id + "\n");
		routerLogFile.flush();
	}

	private void sendLSPDU(pkt_LSPDU pkt) throws IOException
	{
		// convert LSPDU to data in bytes and send it
		byte[] pkt_send_data = pkt.getUDPdata();
		sendPacket(pkt_send_data);

		// write to log file
		routerLogFile.write("R" + routerID + " sends an LS PDU: sender " + pkt.source_router_id
				+ ", router_id " + pkt.dest_router_id + ", link_id " + pkt.link_id + ", cost "
				+ pkt.cost + ", via " + pkt.via + "\n");
		routerLogFile.flush();
	}

	private void sendHELLOS() throws IOException
	{
		// send hello pakcets to all known neighbor
		for (Neighbor neighbour : this.neighbor)
		{
			pkt_HELLO pkt_HELLO = new pkt_HELLO(routerID, neighbour.link_id);
			this.sendHELLO(pkt_HELLO);
		}
	}

	private void listenCircuitDatabase() throws Exception
	{
		byte[] packetDataBytes = new byte[88];
		// create unreliable data packet
		DatagramPacket uPacketData = new DatagramPacket(packetDataBytes, packetDataBytes.length);
		// get the unreliable from UDPSocketReceiveData socket
		UDPSocket.receive(uPacketData);
		// parse the unreliable packet to reliable packet
		circuit_DB circuitDB = circuit_DB.parseUDPdata(packetDataBytes);
		// parse to TopologyDatabase
		ArrayList<link_cost> linkcosts = circuitDB.linkcosts;
		for (int i = 0; i < circuitDB.nbr_link; i++)
		{
			link_cost linkcost = linkcosts.get(i);
			pkt_LSPDU pktLSPDU = new pkt_LSPDU(routerID, linkcost.link, linkcost.cost);
			neighbor.add(new Neighbor(linkcost.link, linkcost.cost));
			topologyDB.add(pktLSPDU);
			writeToTDB();
		}
	}

	private void listenLoop() throws Exception
	{
		while (true)
		{
			byte[] packetDataBytes = new byte[1024];
			// create unreliable data packet
			DatagramPacket uPacketData = new DatagramPacket(packetDataBytes,
					packetDataBytes.length);
			// get the unreliable from UDPSocketReceiveData socket
			UDPSocket.receive(uPacketData);
			// hello packet
			if (uPacketData.getLength() == 8)
			{
				receivedHELLO(packetDataBytes);
			}
			// LSPDU packet
			else if (uPacketData.getLength() == 20)
			{
				receivedLSDPU(packetDataBytes);
			}
		}
	}

	private void receivedHELLO(byte[] packetDataBytes) throws Exception
	{
		pkt_HELLO pkt = pkt_HELLO.parseUDPdata(packetDataBytes);

		// write to log file
		routerLogFile.write("R" + routerID + " receives an HELLO: router_id" + pkt.router_id
				+ ", link_id " + pkt.link_id + "\n");
		routerLogFile.flush();

		// respond to each HELLO packet by a set of LS PDUs containing its
		// circuit database
		for (pkt_LSPDU neighbor : topologyDB)
		{
			neighbor.source_router_id = routerID;
			neighbor.via = pkt.link_id;
			sendLSPDU(neighbor);
		}
		// add information to its neighbors
		for (Neighbor neighbor : this.neighbor)
		{
			if (neighbor.link_id == pkt.link_id)
			{
				neighbor.neighbor_id = pkt.router_id;
				neighborMap.put(neighbor.link_id, neighbor.neighbor_id);
				updateSPT(neighbor);
			}
		}
	}

	private void receivedLSDPU(byte[] packetDataBytes) throws Exception
	{
		pkt_LSPDU pkt = pkt_LSPDU.parseUDPdata(packetDataBytes);
		int pkt_id = pkt.dest_router_id;
		int pkt_link = pkt.link_id;
		// if we already know this neighbor skip
		for (pkt_LSPDU lspdu : topologyDB)
		{
			if (lspdu.dest_router_id == pkt_id && lspdu.link_id == pkt_link)
			{
				return;
			}
		}
		// add LSPDU to TopologyDB
		topologyDB.add(pkt);
		// write to log file
		routerLogFile.write("R" + routerID + " receives an LS PDU: sender " + pkt.source_router_id
				+ ", router_id " + pkt.dest_router_id + ", link_id " + pkt.link_id + ", cost "
				+ pkt.cost + ", via " + pkt.via + "\n");
		routerLogFile.flush();
		updateSPT(pkt);

		// send to all its neighbors
		for (Neighbor neighbor : this.neighbor)
		{
			// skip the one that send the LS PDU
			if (neighbor.link_id == pkt_link)
			{
				continue;
			}
			// resigning the sender and through which link
			pkt.source_router_id = routerID;
			pkt.via = neighbor.link_id;
			// send the LSPDU packet
			sendLSPDU(pkt);
		}

		writeToTDB();
	}

	/*
	 * those function are found online to solve the shortest path using dijkstra
	 * algorithm
	 */
	int minDistance(int dist[], Boolean sptSet[])
	{
		int min = Integer.MAX_VALUE, min_index = -1;

		for (int v = 0; v < NBR_ROUTER; v++)
			if (sptSet[v] == false && dist[v] <= min)
			{
				min = dist[v];
				min_index = v;
			}

		return min_index;
	}

	private void dijkstra(int graph[][], int src) throws IOException
	{
		int dist[] = new int[NBR_ROUTER];
		ArrayList<Integer> nextVisited = new ArrayList<Integer>();
		Boolean sptSet[] = new Boolean[NBR_ROUTER];
		for (int i = 0; i < NBR_ROUTER; i++)
		{
			dist[i] = Integer.MAX_VALUE;
			sptSet[i] = false;
		}
		dist[src] = 0;
		for (int count = 0; count < NBR_ROUTER; count++)
		{
			int u = minDistance(dist, sptSet);
			sptSet[u] = true;
			nextVisited.add(u);
			for (int v = 0; v < NBR_ROUTER; v++)
			{
				if (!sptSet[v] && graph[u][v] != 0 && dist[u] != Integer.MAX_VALUE
						&& dist[u] + graph[u][v] < dist[v])
				{
					dist[v] = dist[u] + graph[u][v];
					roadMap[v] = new LinkedList(roadMap[u]);
					roadMap[v].add(v);
				}
				// visited.set(v, new Vector<Integer>(visited.get(u)));
				// visited.get(v).add(v);
			}
		}
		writeToRIB(dist, NBR_ROUTER, nextVisited);
	}

	private void updateSPT(pkt_LSPDU pktLSPDU) throws IOException
	{
		// update the Shortest Path Table which needs to get maintain which
		// takes a pktLSPDU
		if (neighborMap.containsKey(pktLSPDU.link_id))
		{
			int a = pktLSPDU.dest_router_id - 1;
			int b = neighborMap.get(pktLSPDU.link_id) - 1;
			if (ShortestPathTable[a][b] != pktLSPDU.cost && a != b)
			{
				ShortestPathTable[a][b] = pktLSPDU.cost;
				ShortestPathTable[b][a] = pktLSPDU.cost;
				dijkstra(ShortestPathTable, this.routerID - 1);
			}
		}
		else
		{
			neighborMap.put(pktLSPDU.link_id, pktLSPDU.dest_router_id);
		}
	}

	private void updateSPT(Neighbor neighbor) throws IOException
	{
		// update the Shortest Path Table which needs to get maintain which
		// takes a Neighbor
		int a = neighbor.neighbor_id - 1;
		int b = this.routerID - 1;
		if (ShortestPathTable[a][b] != neighbor.cost)
		{
			ShortestPathTable[a][b] = neighbor.cost;
			ShortestPathTable[b][a] = neighbor.cost;
			dijkstra(ShortestPathTable, this.routerID - 1);
		}
	}

	private void writeToTDB() throws Exception
	{
		// write Topology database info to log file
		routerLogFile.write("# Topology database" + "\n");
		routerLogFile.flush();

		int rLog[] = { 0, 0, 0, 0, 0 };

		// calculate how many entry for each router
		for (pkt_LSPDU neighbor : topologyDB)
		{
			rLog[neighbor.dest_router_id - 1]++;
		}

		// write them into log file in order
		for (int i = 0; i < NBR_ROUTER; i++)
		{
			if (rLog[i] != 0)
			{
				routerLogFile.write("R" + this.routerID + " -> " + "R" + (i + 1) + " nbr link "
						+ rLog[i] + "\n");
				routerLogFile.flush();
			}
			for (pkt_LSPDU neighbor : topologyDB)
			{
				if (neighbor.dest_router_id == i + 1)
				{
					routerLogFile.write("R" + neighbor.source_router_id + " -> " + "R"
							+ neighbor.dest_router_id + " link " + neighbor.link_id + " cost "
							+ neighbor.cost + "\n");
					routerLogFile.flush();
				}
			}
		}
	}

	private void writeToRIB(int dist[], int n, ArrayList<Integer> nV) throws IOException
	{
		// write RIB info to the log file
		for (int i = 0; i < NBR_ROUTER; i++)
		{
			int a = i + 1;
			int from = nV.get(i) + 1;

			int goOut;
			if (roadMap[i].isEmpty())
				goOut = 0;
			else
				goOut = roadMap[i].peek() + 1;
			routerLogFile.write(R(routerID) + " -> " + R(a) + " -> "
					+ ((routerID == a) ? "local" : R(goOut)) + ", " + dist[i] + "\n");
			routerLogFile.flush();
		}
	}

	String R(int routerID)
	{
		// helper for add R in from the router ID
		return "R" + routerID;
	}
}

