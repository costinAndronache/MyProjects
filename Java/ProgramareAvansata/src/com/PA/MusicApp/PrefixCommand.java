package com.PA.MusicApp;

import java.util.*;
import java.io.*;

public class PrefixCommand extends Command {

	@Override
	public String executeWithString(String arg) {
		// TODO Auto-generated method stub
		
		StringTokenizer tok  = new StringTokenizer(arg);
		tok.nextToken();
		String prefix = tok.nextToken();
		String filePath = arg.replaceAll("PREFIX " + prefix + " ", "");
		
		File file = new File(filePath);
		if(file.isFile() == false)
		{
			return "Error: " + filePath + " does not point to a valid file.";
		}
		
		String fileName = filePath.substring(filePath.lastIndexOf(File.separator) + 1 );
		String newFilePathWithPrefix = filePath.substring(0, filePath.lastIndexOf(File.separator)+1) + prefix + fileName;
		
		System.out.println(newFilePathWithPrefix);
		File renamedFile = new File(newFilePathWithPrefix);
		
		if(file.renameTo(renamedFile))
		return "Succesfull";
		else
			return "Sorry, could not rename it.";
	}

}
