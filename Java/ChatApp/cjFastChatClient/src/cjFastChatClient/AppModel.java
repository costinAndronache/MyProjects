package cjFastChatClient;

import java.net.InetAddress;
import java.net.UnknownHostException;

import cjFastChatCommon.FromServerMessage;
import cjFastChatCommon.SvUserMessage;
import cjFastChatCommon.UserLogin;
import cjFastChatCommon.UsrMessage;
import static cjFastChatCommon.FromServerMessage.*;
public class AppModel implements ClientListener {

	AppModelListener appListener;
	ClientServerConnection con;
	String userID;
	
	public AppModel(AppModelListener appListener, String hostName,int port)
	{
		this.appListener=appListener;
		try {
			con = new ClientServerConnection(InetAddress.getByName(hostName),port,this);
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.out.println("Are you sure you typed the name/address correctly?");
		}
	}
	
	
	@Override
	public void update(FromServerMessage message)
	{
		switch(message.getType())
		{
		case FromServerMessage.SV_CLOSING:
			System.out.println("The server has closed.");
			System.exit(1);
			break;
		case SV_LOGINOK:
			appListener.loginOk();
			break;
		case SV_LOGINUSED:
			appListener.needNewLogin();
			break;
		case SV_USRMSG:
			SvUserMessage m=(SvUserMessage)message;
			appListener.messageReceived(m);
		default:
			break;
		}
	}
	
	public void makeLoginRequest(UserLogin loginInfo)
	{
		con.sendMessage(loginInfo);
		}
	
	public void sendMessage(String textLine)
	{
		UsrMessage message = new UsrMessage(textLine);
		con.sendMessage(message);
	}
	
}
