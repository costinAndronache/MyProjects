package com.PA.ConsoleView;

import java.util.*;
import java.io.*;

import com.PA.MovieCatalog.Movie;
import com.PA.MovieCatalog.MovieDatabase;

public class DeleteController extends MenuController {

	@Override
	public void runWithDatabase(MovieDatabase db) 
	{
		System.out.println("Deleting a movie: ");
		String name;
		Scanner s = new Scanner(new InputStreamReader(System.in));
		System.out.println("Please insert the movie name: ");
		name = s.nextLine();
		Movie m = db.findMovieWithName(name);
		
		if(m != null)
		{
			System.out.println("Found the movie: " + m);
			db.removeMovieWithName(name);
			System.out.println("Deletion done.");
		}
		else
		{
			System.out.println("No such move found");
		}
		
	}
	
}
