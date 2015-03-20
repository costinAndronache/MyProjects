package mainApp;

import javax.swing.JDialog;

import View.View;
import cjFastChatClient.AppModel;
import cjFastChatCommon.UserLogin;

public class MainApp {

	String hostName,userName;
	int port;
	Dialog d;
	AppModel appModel;
	View appView;
	boolean canStart=false;
	public void receiveParameters(String hostName, int port, String userName)
	{
		this.port=port;
		this.hostName=hostName;
		this.userName=userName;
		canStart=true;
		d.setVisible(false);
	}
	
	public MainApp()
	{
		
		d = new Dialog();
		d.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
		d.setVisible(true);
		d.setMainApp(this);
		
		while(!canStart)
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		appView = new View();
		appModel=new AppModel(appView,hostName,port);
		appView.setAppModel(appModel);
		
		appModel.makeLoginRequest(new UserLogin(userName));
		
	}
	
	public static void main(String[] args)
	{
		MainApp mainApp = new MainApp();
	}
}
