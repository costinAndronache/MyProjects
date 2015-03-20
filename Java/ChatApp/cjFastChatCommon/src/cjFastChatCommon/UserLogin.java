package cjFastChatCommon;

public class UserLogin implements FromClientMessage {

	String loginID;
	public int getType()
	{
		return FromClientMessage.USR_LOGIN;
	}
	
	public UserLogin(String loginID)
	{
		this.loginID=loginID;
	}
	
	public String loginID()
	{
		return loginID;
	}
}
