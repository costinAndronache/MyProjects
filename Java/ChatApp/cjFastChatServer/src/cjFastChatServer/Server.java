package cjFastChatServer;

import static cjFastChatCommon.FromClientMessage.USR_LOGIN;
import static cjFastChatCommon.FromClientMessage.USR_MSG;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.ArrayList;

import cjFastChatCommon.FromClientMessage;
import cjFastChatCommon.FromServerMessage;
import cjFastChatCommon.SvLoginOk;
import cjFastChatCommon.SvLoginUsed;
import cjFastChatCommon.SvUserMessage;
import cjFastChatCommon.UserLogin;
import cjFastChatCommon.UsrMessage;
public class Server {

	final int port = 8556;
	ServerSocket serverSocket;
	Socket clientSocket;
	
	ArrayList<ServerClientConnection> clientConnections = new ArrayList<ServerClientConnection>();
	public Server()
	{
		try {
			serverSocket = new ServerSocket(port);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		while(true)
		{
			try {
				clientSocket = serverSocket.accept();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			clientConnections.add(new ServerClientConnection(this,clientSocket));
			
		}
	}
	
	

	
	
	
	
	
	
	
	
	
	
	private class ServerClientConnection extends Thread
	{
		Server server;
		String clientID;
		ObjectInputStream ois;
		ObjectOutputStream oos;
		Socket clientSocket;
		
		public ServerClientConnection(Server server, Socket clientSocket)
		{
			this.server=server;
			this.clientSocket=clientSocket;
			start();
		}
		
		@Override
		public void run()
		{
			try {
				oos = new ObjectOutputStream(clientSocket.getOutputStream());
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			try {
				ois  = new ObjectInputStream(clientSocket.getInputStream());
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			

			boolean done=false;
			while(!done)
			{
				FromClientMessage message=null;
				try {
					message=(FromClientMessage)ois.readObject();
				}
				 catch(SocketException e)
				 {
					 done=true;
					 server.clientConnections.remove(this);
				 }
				catch (ClassNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} 

				
				if(message!=null)
					handleMessage(message);
				
			}
		}
		
		public void handleUserLogin(UserLogin loginInfo)
		{

			
			String name = loginInfo.loginID();
			
			for(int i=0;i<server.clientConnections.size();i++)
			{
				ServerClientConnection con=server.clientConnections.get(i);
				if(name.equals(con.clientID))
				{
					
					sendMessage(new SvLoginUsed());
					return;
					
				}
				
			}
			
			clientID=name;
			sendMessage(new SvLoginOk());
		}
		
		public void handleUserMessage(UsrMessage message)
		{
			FromServerMessage svMessage = new SvUserMessage(clientID,message.getMessage());
			for(int i=0;i<server.clientConnections.size();i++)
			{
				ServerClientConnection con = server.clientConnections.get(i);
				con.sendMessage(svMessage);
			}
		}
		public void handleMessage(FromClientMessage message)
		{
			switch(message.getType())
			{
			case USR_LOGIN:
				handleUserLogin((UserLogin)message);
				break;
			case USR_MSG:
				handleUserMessage((UsrMessage)message);
				break;
			default:
				break;
				
			}
		}
		
		
		public void sendMessage(FromServerMessage message)
		{
			
			try {
				oos.writeObject(message);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		
	}
	
	public static void main(String[] args)
	{
		Server s = new Server();
	}
}
