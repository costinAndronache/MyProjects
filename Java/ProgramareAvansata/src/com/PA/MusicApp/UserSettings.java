package com.PA.MusicApp;

import java.io.*;
public class UserSettings 
{
	private static UserSettings sharedInstance = new UserSettings();
	
    private String currentDirectoryPath;
    
    public  String getCurrentDirectory()
    {
    	return this.currentDirectoryPath;
    }
    
    public void setCurrentDirectoryPath(String newPath) throws InvalidDirectoryException
    {
    	File file = new File(newPath);
    	if(file.isDirectory() == false)
    	{
    		throw new InvalidDirectoryException(newPath);
    	}
    	this.currentDirectoryPath = newPath;
    }
    
    private UserSettings()
    {
    	
    }
    
    public static UserSettings getSharedInstance()
    {
    	return sharedInstance;
    }
}
