/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.PA.Exceptions;

/**
 *
 * @author Costinel
 */
public class InvalidMoviePathException extends Exception
{
    public InvalidMoviePathException(String path)
    {
        super("The following is not a valid path in the system : " + path);
    }
}
