package cjFastChatCommon;

public class SvUserMessage implements FromServerMessage{

	public int getType()
	{
		return FromServerMessage.SV_USRMSG;
	}
	
	String userID,userMessage;
	public SvUserMessage(String userID,String userMessage)
	{
		this.userID=userID;
		this.userMessage=userMessage;
	}
	
	public String userID()
	{
		return userID;
	}
	
	public String userMessage()
	{
		return userMessage;
	}
}
