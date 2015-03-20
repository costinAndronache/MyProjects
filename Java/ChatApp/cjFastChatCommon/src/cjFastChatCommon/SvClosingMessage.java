package cjFastChatCommon;

public class SvClosingMessage implements FromServerMessage{

	public int getType()
	{
		return FromServerMessage.SV_CLOSING;
	}
}
