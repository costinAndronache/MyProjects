package com.PA.MusicApp;

import java.util.*;
import java.awt.Desktop;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class PlayCommand extends Command {

	@Override
	public String executeWithString(String arg) 
	{
		// TODO Auto-generated method stub
		
		String filePath;
		StringTokenizer tok  = new StringTokenizer(arg);
		
		
		tok.nextToken();
		filePath = tok.nextToken();
		filePath = arg.replaceAll("PLAY ", "");
		
		File file = new File(filePath);
		if(file.isFile() == false)
		{
			return "Error " + filePath + " is not a valid file in the filesystem.";
		}
		
		Path p = Paths.get(filePath);
		String probe = null;
		try {
			probe = Files.probeContentType(p);
		} catch (IOException e) {
			return "Something unexpected happened. Sorry, the reason is: " + e.getMessage();
		}
		
		if(probe == null || probe.indexOf("audio") < 0)
		{
			return "Error " + filePath + " is not a valid audio file.";
		}
		
		try {
			Desktop.getDesktop().open(file);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			return "Something unexpected happened. Sorry, the reason is: " + e.getMessage();
		}
		
		return "Succes";
	}

}
