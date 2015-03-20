package com.PA.MusicApp;

import java.util.*;
public class SetCommand extends Command
{
	public String executeWithString(String arg)
	{
		String result = "Succes";
		
		StringTokenizer tokenizer = new StringTokenizer(arg);
		
		tokenizer.nextToken();
		String path = tokenizer.nextToken();
		
		System.out.print("path = " + path);
		
		try
		{
			UserSettings.getSharedInstance().setCurrentDirectoryPath(path);
		}catch(InvalidDirectoryException e)
		{
			return e.getMessage();
		}
		
		return result;
	}
}
