package com.PA.MusicApp;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class ListCommand extends Command {

	@Override
	public String executeWithString(String arg) 
	{
		StringBuilder result = new StringBuilder();
		StringTokenizer tok = new StringTokenizer(arg);
		tok.nextToken();
		String argrument = tok.nextToken();
		
		if(argrument.equals("!"))
		{
			String currentDir = UserSettings.getSharedInstance().getCurrentDirectory();
			if(currentDir == null)
			{
				return "The  current directory is not set.";
			}
			try {
				result.append( this.buildListOfAudioFilesFrom( UserSettings.getSharedInstance().getCurrentDirectory()));
			} catch (Exception e) {
				
				return e.getMessage();
			}
		}
		else
		{
			try {
				result.append(this.buildListOfAudioFilesFrom(argrument));
			} catch (Exception e) {
				// TODO Auto-generated catch block
				return e.getMessage();
			}
		}
		
		return result.toString();
	}

	
	private String buildListOfAudioFilesFrom(String path) throws Exception
	{
		StringBuilder fileList = new StringBuilder();
		File file = new File(path);
		if(file.isDirectory() == false)
		{
			throw new InvalidDirectoryException(path);
		}
		
		String[] fileListStrings = file.list();
		
		
		if(fileListStrings != null && fileListStrings.length > 0)
		{
			for(String aFileString : fileListStrings)
			{
				String dirPath = path + File.separator + aFileString;
				File newPossibleDir = new File(dirPath);
				
				if(newPossibleDir.isDirectory())
				{
					System.out.println("IS A DIR: " + aFileString);
					fileList.append(this.buildListOfAudioFilesFrom(dirPath));
					}
				else
				{
					Path p = Paths.get(aFileString);
					String probe = Files.probeContentType(p);
					if(probe != null && probe.indexOf("audio") >=0)
					{
						fileList.append(path + File.separator + aFileString + "\n");
					}
					
					}
				}
		}
		
		return fileList.toString();
	}

}
