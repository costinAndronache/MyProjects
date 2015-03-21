package com.PA.Exceptions;

public class InvalidRatingException extends Exception 
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public InvalidRatingException(float rating)
	{
		super("Invalid movie rating: " + rating + ", ratins should lie between 1 and 10. ");
	}
}
