package cjFastChatCommon;

import java.io.Serializable;

public interface FromClientMessage extends Serializable{

	final int USR_MSG=0, USR_CLOSING=1,USR_LOGIN=2;
	public int getType();
}
