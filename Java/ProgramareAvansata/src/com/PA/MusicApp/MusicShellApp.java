package com.PA.MusicApp;

import java.util.*;
import java.io.*;
public class MusicShellApp 
{
	
	Map<String, Command> commandMap;
	
	public MusicShellApp()
	{
		this.commandMap = new HashMap<String, Command>();
		this.commandMap.put("SET", new SetCommand());
		this.commandMap.put("LIST", new ListCommand());
		this.commandMap.put("PLAY", new PlayCommand());
		this.commandMap.put("FIND", new FindCommand());
		this.commandMap.put("PREFIX", new PrefixCommand());
	}
	
	public void run()
	{
		Scanner s = new Scanner(System.in);
		while(true)
		{
			System.out.println("Available commands: ");
			int i=0;
			for(String key : this.commandMap.keySet())
			{
				System.out.println((i+1) + ". " +  key);
				i++;
			}
			System.out.println( (i+1) +". QUIT");
			
			
			System.out.print("Please insert a command along with its arguments: ");
			String command = s.nextLine();
			
			StringTokenizer tok = new StringTokenizer(command);
			String cName = tok.nextToken();
			if(cName.equals("QUIT"))
			{
				System.out.print("Will exit.");
				return;
			}
			
			Command actualCommand = this.commandMap.get(cName);
			if(actualCommand == null)
			{
				System.out.println("Unrecognized command name. Please try again\n");
			}
			else
			{
				String res = actualCommand.executeWithString(command);
				System.out.println("\n\n Result: " + res);
			}
			
			System.out.println("\n------------------------------\n");
			
		} // end while
		
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		MusicShellApp app = new MusicShellApp();
		app.run();
		
	}

}
