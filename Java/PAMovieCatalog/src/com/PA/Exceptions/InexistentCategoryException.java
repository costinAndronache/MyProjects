package com.PA.Exceptions;

public class InexistentCategoryException extends Exception 
{
	public InexistentCategoryException(String msg)
	{
		super("Inexistent category exception: " + msg);
	}
}
