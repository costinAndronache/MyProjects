package com.PA.Exceptions;

public class InvalidDirectorNameException extends Exception 
{
	public InvalidDirectorNameException(String directorName)
	{
		super("Invalid director name: " + directorName + ". Director names should contain only alfanumeric characters.");
	}
}
