package GoBackNProtocol;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;

public class Sender
{
	private static final String seqLogName = "seqnum.log";
	private static final String ackLogName = "ack.log";
	private static final int TIME_OUT_VALUE = 200;

	static int WINDOW_SIZE = 10;

	static String networkEmulatorHostName, fileName;
	static int UDPPortSendData;
	static int UDPPortReceiveACKs;
	static InetAddress networkEmulatorAddress;
	static FileWriter seqLogFile;
	static FileWriter ackLogFile;

	static byte[] packetDataBytes;
	static DatagramSocket UDPSocketSendData;
	static DatagramSocket UDPSocketReceiveACK;
	static Timer timer;
	static ArrayList<DatagramPacket> uPackets;
	static DatagramPacket uPacket_ACK;
	static DatagramPacket uPacket_EOT;
	static int seqNumCounter;
	static int numOfPackets;

	public static void main(String argv[]) throws Exception
	{
		// check argument if there are errors
		commandLineArgumentCheck(argv);
		// initiate other sender static field
		initSender(argv);
		// generate all packets will be send
		initPackets();
		// send first # of window size packets
		sendFirstNPackets(seqNumCounter, WINDOW_SIZE);
		// start listen for any packets arrival
		listenLoop();
		// after all packets are ACKed, stop the timer
		timer.cancel();
		// send EOT packet to receiver
		sendEOT();
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
			networkEmulatorHostName = argv[0];
			UDPPortSendData = Integer.valueOf(argv[1]);
			UDPPortReceiveACKs = Integer.valueOf(argv[2]);
			fileName = argv[3];
			networkEmulatorAddress = InetAddress.getByName(networkEmulatorHostName);
			// clear logFile if already exist
			PrintWriter writer = new PrintWriter(seqLogName);
			writer.print("");
			writer.close();
			seqLogFile = new FileWriter(seqLogName, true);
			// clear logFile if already exist
			writer = new PrintWriter(ackLogName);
			writer.print("");
			writer.close();
			ackLogFile = new FileWriter(ackLogName, true);
		}
		catch (Exception e)
		{
			System.err.println("Command line argument type error.");
			System.exit(1);
		}
	}

	private static void initSender(String[] argv) throws SocketException, UnknownHostException
	{
		// Create UDP Socket to send DATA packets
		UDPSocketSendData = new DatagramSocket();
		// Create UDP Socket to receive ACK/EOT packets
		UDPSocketReceiveACK = new DatagramSocket(UDPPortReceiveACKs);
		// generate a byte with space as 512
		packetDataBytes = new byte[512];
		// generate unreliable ACK packet which will be received
		uPacket_ACK = new DatagramPacket(packetDataBytes, packetDataBytes.length);
		// initiate the unreliable array
		uPackets = new ArrayList<DatagramPacket>();
		// seqNumCounter should be 0 in the beginning
		seqNumCounter = 0;
		// numOfPackets should be 0 in the beginning
		numOfPackets = 0;
	}

	private static void startTimer()
	{
		// if timer exists, cancel the timer schedule
		if (timer != null)
		{
			timer.cancel();
		}
		// set/reset the timer
		timer = new Timer();
		// the timer will call sendFirstNPackets after time out
		timer.schedule(new TimerTask() {
			@Override
			public void run()
			{
				try
				{
					// resends # of WINDOW_SIZE packets start from seqNumCounter
					sendFirstNPackets(seqNumCounter, WINDOW_SIZE);
				}
				catch (IOException e)
				{
					e.printStackTrace();
				}
			}
		}, TIME_OUT_VALUE);
	}

	private static void initPackets() throws FileNotFoundException, IOException, Exception
	{
		// get source file
		FileReader sourceFile = new FileReader(fileName);
		// use to store temp char to read file
		int tempChar;
		// initiate temp string to store file data
		String packetData = "";
		// read file char by char
		for (int charCounter = 0; (tempChar = sourceFile.read()) != -1; charCounter++)
		{
			// append temp char to temp string
			packetData += (char) (tempChar);
			// if string size is full build unreliable packets
			if (charCounter == 499)
			{
				// build the unreliable packet
				createUPacketData(packetData, numOfPackets);
				// reset the charCounter
				charCounter = 0;
				// clear the temp string
				packetData = "";
			}
		}
		// create the last packet for the source file
		createUPacketData(packetData, numOfPackets);
		// generate the reliable EOT packet
		Packet rPacket_EOT = Packet.createEOT(numOfPackets);
		// convert EOT packet to bytes
		byte[] packetEOTBytes = rPacket_EOT.getUDPdata();
		// generate unreliable EOT packet will be send from reliable EOT packet
		uPacket_EOT = new DatagramPacket(packetEOTBytes, packetEOTBytes.length,
				networkEmulatorAddress, UDPPortSendData);
	}

	private static void createUPacketData(String packetData, int seqCount) throws Exception
	{
		// create reliable packet using the data & seqNum from parameter
		Packet rPacketData = Packet.createPacket(seqCount, packetData);
		// convert the reliable packet to byte
		byte[] packetDataBytes = rPacketData.getUDPdata();
		// create the unreliable packet using the reliable packet
		DatagramPacket uPacket_DATA = new DatagramPacket(packetDataBytes, packetDataBytes.length,
				networkEmulatorAddress, UDPPortSendData);
		// add the unreliable packet to the packet array
		uPackets.add(uPacket_DATA);
		// increment total number of packets by 1
		numOfPackets++;
	}

	private static void sendNextPacket() throws UnknownHostException, IOException
	{
		// call sendFirstNPackets with 1 to be the N
		sendFirstNPackets(seqNumCounter, 1);
	}

	private static void sendFirstNPackets(int startFromIndex, int N)
			throws UnknownHostException, IOException
	{
		// start the timer
		startTimer();
		for (int i = startFromIndex; i < startFromIndex + N; i++)
		{
			// check if the packet is within the range
			if (i == numOfPackets)
			{
				break;
			}
			// get the corresponding datagram to send
			DatagramPacket sendPacket = uPackets.get(i);
			// Send datagram to server
			UDPSocketSendData.send(sendPacket);
			// write sent packet seq to seqLog file
			seqLogFile.write(i % 32 + "\n");
		}
	}

	private static void sendEOT() throws Exception
	{
		// send real EOT packet
		UDPSocketSendData.send(uPacket_EOT);
		// close UDPSocketSendData socket, no need to send Data anymore
		UDPSocketSendData.close();
		// wait for the EOT packet from receiver
		while (true)
		{
			// get unreliable packet from UDPSocketReceiveACK
			UDPSocketReceiveACK.receive(uPacket_ACK);
			// parse the unreliable packet to reliable packet
			Packet rPacket = Packet.parseUDPdata(uPacket_ACK.getData());
			// case when received packet is the EOT packet
			if (rPacket.getType() == Packet.PACKET_TYPE_EOT)
			{
				// close the UDPSocketReceiveACK connection
				UDPSocketReceiveACK.close();
				// close seqLog file
				seqLogFile.close();
				// close ackLog file
				ackLogFile.close();
				break;
			}
			// case when received packet is the ACK packet
			else if(rPacket.getType() == Packet.PACKET_TYPE_ACK)
			{
				//write the ack seq to the ackLog file
				ackLogFile.write(rPacket.getSeqNum()+"\n");
			}
		}
	}

	private static void listenLoop() throws IOException, Exception, UnknownHostException
	{
		// this variable is reserved for convert seqNumCounter to mod 32
		int baseSeqNum;
		// this listen while loop will break only when we got all packets ACKed
		while (seqNumCounter < numOfPackets)
		{
			// calculate baseSeqNum
			baseSeqNum = seqNumCounter % 32;
			// get unreliable packet from UDPSocketReceiveACK
			UDPSocketReceiveACK.receive(uPacket_ACK);
			// parse the unreliable packet to reliable packet
			Packet rPacket = Packet.parseUDPdata(uPacket_ACK.getData());
			// case when the received packet type is ACK type
			if (rPacket.getType() == Packet.PACKET_TYPE_ACK)
			{
				// get the received packet seqNum
				int rPacketSeqNum = rPacket.getSeqNum();
				// case when the packetSeqNum is what we expected
				if (rPacketSeqNum == baseSeqNum)
				{
					// update seqNumCounter, increment by 1
					seqNumCounter++;
					// send next 1 packet
					sendNextPacket();
				}
				// case when the packetSeqNum is NOT what we expected
				else
				{
					// check if the received seqNum is with the window range
					checkSeqNumInWindow(rPacketSeqNum, baseSeqNum);
				}
				// write received ACK seqNum to ackLog
				ackLogFile.write(rPacketSeqNum + "\n");
			}
		}
	}

	private static void checkSeqNumInWindow(int packetSeq, int baseWindowSeqNum)
			throws UnknownHostException, IOException
	{
		// case where there will be only 1 window
		if (baseWindowSeqNum < 22)
		{
			// calculate window bounds
			int windowLowerBound = baseWindowSeqNum;
			int windowUpperBound = baseWindowSeqNum + WINDOW_SIZE - 1;
			// case when packetSeq is between the window range
			if (packetSeq >= windowLowerBound && packetSeq <= windowUpperBound)
			{
				// calculate # of packet will skip in total
				int numOfPacketShouldSkip = packetSeq - windowLowerBound + 1;
				// update seqNumCounter with packets skipped
				seqNumCounter += numOfPacketShouldSkip;
				// send next # of packets which # equals to packets we skipped
				sendFirstNPackets(seqNumCounter, numOfPacketShouldSkip);
			}
			// case when packetSeq is out of the window range
			else
			{
				// not in window range, do nothing
			}
		}
		// case where the window will be break to 2 parts
		else
		{
			// calculate window bounds
			int window1LowerBound = baseWindowSeqNum;
			int window1UpperBound = 31;
			int window2LowerBound = 0;
			int window2UpperBound = baseWindowSeqNum + WINDOW_SIZE - 33;

			// case when packetSeq is between the first window range
			if (packetSeq >= window1LowerBound && packetSeq <= window1UpperBound)
			{
				// calculate # of packet will skip in total
				int numOfPacketShouldSkip = packetSeq - window1LowerBound + 1;
				// update seqNumCounter with packets skipped
				seqNumCounter += numOfPacketShouldSkip;
				// send next # of packets which # equals to packets we skipped
				sendFirstNPackets(seqNumCounter, numOfPacketShouldSkip);
			}
			// case when packetSeq is between the second window range
			else if (packetSeq >= window2LowerBound && packetSeq <= window2UpperBound)
			{
				// calculate # of packet will skip in first window
				int numPacketInFirstWindow = 31 - baseWindowSeqNum + 1;
				// calculate # of packet will skip in second window
				int numPacketInSecondWindow = packetSeq - window2LowerBound + 1;
				// calculate # of packet will skip in total
				int numOfPacketShouldSkip = numPacketInFirstWindow + numPacketInSecondWindow;
				// update seqNumCounter with packets skipped
				seqNumCounter += numOfPacketShouldSkip;
				// send next # of packets which # equals to packets we skipped
				sendFirstNPackets(seqNumCounter, numOfPacketShouldSkip);
			}
			// case when packetSeq is out of the window range
			else
			{
				// not in window range, do nothing
			}
		}
	}
}
