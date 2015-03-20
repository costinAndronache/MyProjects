package cjFastChatClient;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketException;

import cjFastChatCommon.FromClientMessage;
import cjFastChatCommon.FromServerMessage;

public class ClientServerConnection {

	Socket serverSocket;
	ObjectOutputStream oos;
	ClientListener clientListener;
	ListeningThread listeningThread=null;
	
	public ClientServerConnection(InetAddress hostAddress,int port, ClientListener clientListener)
	{
		try {
			serverSocket = new Socket(hostAddress,port);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.out.println("Could not connect to the server. Maybe the ip address is wrong ... ");
			System.exit(1);
		}
		
		try {
			oos = new ObjectOutputStream(serverSocket.getOutputStream());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		this.clientListener=clientListener;
		listeningThread=new ListeningThread(this);
		}
	
	
	public void sendMessage(FromClientMessage message)
	{
		try {
			oos.writeObject(message);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	
	class ListeningThread extends Thread
	{
		ClientServerConnection con;
		ObjectInputStream ois;
		
		public ListeningThread(ClientServerConnection con)
		{
			this.con=con;
			try {
				ois = new ObjectInputStream(con.serverSocket.getInputStream());
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				System.out.println("Could not get inputStream from serverSocket");
			}
			
			start();
		}
		
		@Override
		public void run()
		{
			FromServerMessage svMessage=null;
			while(con.serverSocket.isConnected())
			{
				
				try {
					Thread.sleep(10);
				} catch (InterruptedException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				
				try {
					svMessage=(FromServerMessage)ois.readObject();
				} catch (ClassNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
					
				}
				  catch(SocketException e)
				  {
					  System.out.println("The server has closed.");
					  System.exit(0);
				  }
				catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
					  System.out.println("The server has closed.");
					  System.exit(0);
				}
				
				if(svMessage!=null)
				{
					con.clientListener.update(svMessage);
				}
				
				
			}
		}
	}

	
	
	

}

