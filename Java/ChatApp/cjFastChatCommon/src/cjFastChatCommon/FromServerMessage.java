package cjFastChatCommon;

import java.io.Serializable;

public interface FromServerMessage extends Serializable{

	final int SV_CLOSING=0;
	final int SV_USRMSG=1;
	final int SV_LOGINOK=2;
	final int SV_LOGINUSED=3;
	
	public int getType();
	
}
