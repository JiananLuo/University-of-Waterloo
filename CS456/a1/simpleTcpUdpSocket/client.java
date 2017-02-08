import java.io.*;
import java.net.*;
import java.io.IOException;

public class Client {
	public static void main(String argv[]) throws Exception
	{
		//error checking for command line argument
		if(argv.length != 4)
		{
			System.err.println("Wrong number of command line argument.");
			return;
		}
		int nPort;
		try
		{
			InetAddress.getByName(argv[0]);
			nPort = Integer.valueOf(argv[1]);
			Integer.valueOf(argv[2]);
		}
		catch(Exception e)
		{
			System.err.println("Command line argument type error.");
			return;
		}

		//inputs are fine
	//TCP Socket to get the actual port for sending actual msg
		String serverAddress, reqCode, msg;
		serverAddress = argv[0];
		reqCode = argv[2];
		msg = argv[3];
		//Create client socket, connect to server
		Socket TCPClientSocket;
		try
		{
			TCPClientSocket = new Socket(serverAddress, nPort);
		}
		catch(ConnectException e)
		{
			System.err.println("Connection refused.");
			System.err.println("Connection to the address: " + serverAddress +  "  Port: " + nPort + " is Unreachable.");
			return;
		}
		catch(Exception e)
		{
			System.err.println("No route to host/ip");
			return;
		}

		//Create output stream attached to socket
		DataOutputStream outToServer = new DataOutputStream(TCPClientSocket.getOutputStream());
		//Send line to server
		outToServer.writeBytes(reqCode + '\n');

		//Create input stream attached to socket
		BufferedReader inFromServer = new BufferedReader(new InputStreamReader(TCPClientSocket.getInputStream()));
		//Read line from server
		String TCPResponseString = inFromServer.readLine();

		//Check if TCP connection is closed by server, if so, terminate client side
		if(TCPResponseString == null)
		{
			System.err.println("Unmatching reqCode, client terminate.");
			return;
		}
		//If not, parse r_port from server response
		int rPort = Integer.valueOf(TCPResponseString);
		//Close TCP connection
		TCPClientSocket.close();


	//UDP Socket to send & receive actual message
		//Create client socket
		DatagramSocket UDPClientSocket = new DatagramSocket();

		byte[] sendData = new byte[1024];
		sendData = msg.getBytes();
		//Translate IP type from String to InetAddress using DNS
		InetAddress IPAddress = InetAddress.getByName(serverAddress);
		//Create datagram with data-to-send, length, IP addr, port
		DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, rPort);
		//Send datagram to server
		UDPClientSocket.send(sendPacket);

		byte[] receiveData = new byte[1024];
		//Get packet from server
		DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
		//Read datagram from server
		UDPClientSocket.receive(receivePacket);
		String UDPResponseString = new String(receivePacket.getData());

		//Client prints out the reversed string
		System.out.println("FROM SERVER: " + UDPResponseString);
		//Client exit
		UDPClientSocket.close();
	}
}
