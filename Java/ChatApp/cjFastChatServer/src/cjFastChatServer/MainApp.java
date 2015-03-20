package cjFastChatServer;

import java.net.UnknownHostException;

public class MainApp {

	public static void main(String[] args)
	{
		try {
			ServerDialog sd = new ServerDialog();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		Server server = new Server();
	}
}
