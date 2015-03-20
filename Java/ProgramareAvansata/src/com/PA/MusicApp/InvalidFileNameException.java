package com.PA.MusicApp;

public class InvalidFileNameException extends Exception 
{
	public InvalidFileNameException(String fileName)
	{
		super("The file path " + fileName + " does not point to an existent file in the filesystem.");
	}
}
