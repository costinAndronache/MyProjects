package cjFastChatClient;

import cjFastChatCommon.FromServerMessage;

public interface ClientListener {

	public void update(FromServerMessage m);
}
