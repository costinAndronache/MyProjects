package com.PA.Exceptions;

public class InvalidDateException extends Exception 
{
	public InvalidDateException(String date, String format)
	{
		super("Invalid date! The date " + date + " is not in the specified format: " + format);
	}
}
