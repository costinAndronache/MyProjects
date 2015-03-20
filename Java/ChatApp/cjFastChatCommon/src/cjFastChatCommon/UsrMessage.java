package cjFastChatCommon;

public class UsrMessage implements FromClientMessage {

	public int getType()
	{
		return USR_MSG;
	}
	
	String message;
	
	public UsrMessage(String message)
	{
		this.message=message;
	}
	
	public String getMessage()
	{
		return message;
	}
}
