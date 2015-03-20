package com.PA.MusicApp;

import java.util.*;
import java.io.*;

public class FindCommand extends Command {

	@Override
	public String executeWithString(String arg) 
	{
		
		StringBuilder result = new StringBuilder();
		
		String currentDir = UserSettings.getSharedInstance().getCurrentDirectory();
		
		if(currentDir == null)
		{
			return "Please set the current directory using the SET command";
		}
		

		String regex = arg.replaceAll("FIND ", "");
		
		String allFileList = new ListCommand().executeWithString("LIST " + currentDir);
		
		StringTokenizer tok = new StringTokenizer(allFileList);
		
		while(tok.hasMoreTokens())
		{
			String aFile = tok.nextToken("\n");
			try
			{
				int lastIndexOfSeparator = aFile.lastIndexOf(File.separator);
				String substr = aFile.substring(lastIndexOfSeparator + 1);
				
				if(substr.matches(regex))
				{
					result.append(aFile + "\n");
				}
			}catch(Exception e)
			{
				return "Error: the regex provided is not valid, " + e.getMessage();
			}
		}
		
		String str = result.toString();
		if(str.length() == 0)
			return "No files found matching your criteria " + regex;
		
		return result.toString();
	}

}
