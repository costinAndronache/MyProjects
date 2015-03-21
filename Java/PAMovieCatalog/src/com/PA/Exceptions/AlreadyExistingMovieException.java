package com.PA.Exceptions;

public class AlreadyExistingMovieException extends Exception 
{
	public AlreadyExistingMovieException(String movieName)
	{
		super("Exception! Movie already exists : " + movieName);
	}
}
