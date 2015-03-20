package cjFastChatCommon;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;

public class Utilities {

	public static String getExternalIP()
	
		   {
			    URL connection = null;
				try {
					connection = new URL("http://checkip.amazonaws.com/");
				} catch (MalformedURLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			    URLConnection con = null;
				try {
					con = connection.openConnection();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			    String str = null;
			    BufferedReader reader = null;
				try {
					reader = new BufferedReader(new InputStreamReader(con.getInputStream()));
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			    try {
					str = reader.readLine();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			    return str;
			     }
	
}
