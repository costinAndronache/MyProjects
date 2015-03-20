package com.PA.MusicApp;

public class InvalidDirectoryException extends Exception 
{
	public InvalidDirectoryException(String dirPath)
	{
		super("The path " + dirPath + " does not point to a valid directory in the filesystem,");
	}
}
