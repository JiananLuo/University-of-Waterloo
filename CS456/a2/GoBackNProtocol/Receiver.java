package GoBackNProtocol;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class Receiver
{
	private static final String arrivalLogName = "arrival.log";

	static String networkEmulatorHostName, fileName;
	static int UDPPortSendACKs;
	static int UDPPortReceiveData;
	static InetAddress networkEmulatorAddress;
	static FileWriter destFile;
	static FileWriter arrivalLogFile;

	static byte[] packetDataBytes;
	static DatagramSocket UDPSocketReceiveData;
	static DatagramSocket UDPSocketSendACK;

	static int expectedSeqNum;
	static DatagramPacket uPacket_ACK;

	public static void main(String argv[]) throws Exception
	{
		// check argument if there are errors
		commandLineArgumentCheck(argv);
		// initiate other receiver static field
		initReceiver(argv);
		// start listen for any packets arrival
		listenLoop();
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
			UDPPortSendACKs = Integer.valueOf(argv[1]);
			UDPPortReceiveData = Integer.valueOf(argv[2]);
			fileName = argv[3];
			networkEmulatorAddress = InetAddress.getByName(networkEmulatorHostName);

			// clear destination file if already exist
			PrintWriter tempWriter = new PrintWriter(fileName);
			tempWriter.print("");
			tempWriter.close();
			destFile = new FileWriter(fileName, true);
			// clear logFile if already exist
			tempWriter = new PrintWriter(arrivalLogName);
			tempWriter.print("");
			tempWriter.close();
			arrivalLogFile = new FileWriter(arrivalLogName, true);
		}
		catch (Exception e)
		{
			System.err.println("Command line argument type error.");
			System.exit(1);
		}
	}

	private static void initReceiver(String[] argv) throws SocketException
	{
		// generate UPD socket to receive packet from sender
		UDPSocketReceiveData = new DatagramSocket(UDPPortReceiveData);
		// generate UPD socket to send ACK/EOT to sender
		UDPSocketSendACK = new DatagramSocket();
		// generate a byte with space as 512
		packetDataBytes = new byte[512];
		// first expected seqNum should be 0
		expectedSeqNum = 0;
	}

	private static void listenLoop() throws IOException, Exception
	{
		// keep listen
		while (true)
		{
			// create unreliable data packet
			DatagramPacket uPacketData = new DatagramPacket(packetDataBytes,
					packetDataBytes.length);
			// get the unreliable from UDPSocketReceiveData socket
			UDPSocketReceiveData.receive(uPacketData);
			// parse the unreliable packet to reliable packet
			Packet rPacketData = Packet.parseUDPdata(packetDataBytes);
			// get the received packet seqNum
			int rPacketSeqNum = rPacketData.getSeqNum();
			// write received packet seqNum to arrivalLog file
			arrivalLogFile.write(rPacketSeqNum + "\n");
			// case when the received packet type is DATA type
			if (rPacketData.getType() == Packet.PACKET_TYPE_DATA)
			{
				// case when the packetSeqNum is what we expected
				if (rPacketSeqNum == expectedSeqNum)
				{
					// if seqNum in order, generate a new ACK packet & send it
					sendACK(expectedSeqNum);
					// write data to file
					writeTofile(rPacketData.getData());
					// increment expected seqNum by 1 && do mod by 32
					expectedSeqNum++;
					expectedSeqNum %= 32;
				}
				// case when the packetSeqNum is NOT what we expected
				else
				{
					// if seqNum out of order, resends last good ACK packet
					if (uPacket_ACK != null)
					{
						UDPSocketSendACK.send(uPacket_ACK);
					}
				}
			}
			// case when the received packet type is EOT type
			else if (rPacketData.getType() == Packet.PACKET_TYPE_EOT)
			{
				// send a EOT packet back when receive a EOT packet
				sendEOT(rPacketSeqNum);
				break;
			}
		}
	}

	private static void sendACK(int seqNum) throws Exception
	{
		// create ACK packet
		Packet rPacket_ACK = Packet.createACK(seqNum);
		// convert ACK packet to bytes
		byte[] packetACKBytes = rPacket_ACK.getUDPdata();
		// generate unreliable ACK packet which will be send
		uPacket_ACK = new DatagramPacket(packetACKBytes, packetACKBytes.length,
				networkEmulatorAddress, UDPPortSendACKs);
		// send unreliable ACK packet
		UDPSocketSendACK.send(uPacket_ACK);
	}

	private static void sendEOT(int seqNum) throws Exception
	{
		// create EOT packet
		Packet rPacket_EOT = Packet.createEOT(seqNum);
		// convert EOT packet to bytes
		byte[] packetEOTBytes = rPacket_EOT.getUDPdata();
		// generate real EOT packet which will be send
		DatagramPacket uPacket_EOT = new DatagramPacket(packetEOTBytes, packetEOTBytes.length,
				networkEmulatorAddress, UDPPortSendACKs);
		// send real EOT packet
		UDPSocketSendACK.send(uPacket_EOT);
		// close destination file
		destFile.close();
		// close log file
		arrivalLogFile.close();
		// after send EOT packet, receiver should exit
		return;
	}

	private static void writeTofile(byte[] rData) throws IOException
	{
		// cast rData from byte to String
		String textData = new String(rData);
		// write rData to the destFile
		destFile.write(textData);
	}

}
