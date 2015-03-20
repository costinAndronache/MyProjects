package cjFastChatClient;

import cjFastChatCommon.SvUserMessage;


public interface AppModelListener {

	public void messageReceived(SvUserMessage message);
	public void needNewLogin();
	public void loginOk();
}
