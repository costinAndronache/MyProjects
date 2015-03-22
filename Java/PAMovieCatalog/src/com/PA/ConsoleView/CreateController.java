package com.PA.ConsoleView;

import java.io.*;
import java.util.Scanner;

import com.PA.Exceptions.InvalidDateException;
import com.PA.Exceptions.InvalidDirectorNameException;
import com.PA.Exceptions.InvalidRatingException;
import com.PA.MovieCatalog.Movie;
import com.PA.MovieCatalog.MovieCategory;
import com.PA.MovieCatalog.MovieDatabase;
public class CreateController extends MenuController 
{

	@Override
	public void runWithDatabase(MovieDatabase db) 
	{
		Movie m = new Movie();
		print("Creating a new movie:\n");
		Scanner s = new Scanner(new InputStreamReader(System.in));
		
		print("Movie name: ");
		String name = s.nextLine();
		m.setName(name);
		print("Movie imdb id: ");
		String imdbID = s.nextLine();
		m.setImdbID(imdbID);

		
		boolean keepAsking = true;
		while(keepAsking)
		{
			keepAsking = false;
			print("Movie rating: ");
			float rating = s.nextFloat();
			try {
				m.setRating(rating);
			} catch (InvalidRatingException e) {
				// TODO Auto-generated catch block
				print(e.getMessage() + "\n");
				keepAsking = true;
			}
		}
		s.nextLine();
		keepAsking = true;
		while(keepAsking)
		{
			keepAsking = false;
			print("Director name: ");
			String dName = s.nextLine();
			try {
				m.setDirectorName(dName);
			} catch (InvalidDirectorNameException e) {
				// TODO Auto-generated catch block
				print(e.getMessage() + "\n");
				keepAsking = true;
			}
		}
		

		keepAsking = true;
		while(keepAsking)
		{
			keepAsking = false;
			print("Release date: ");
			String date = s.nextLine();
			try {
				m.setReleaseDate(date);
			} catch (InvalidDateException e) {
				// TODO Auto-generated catch block
				keepAsking = true;
				print(e.getMessage() + "\n");
			}
		}
		
		int numOfCategories;
		print("How many categories does this movie belong to?: ");
		numOfCategories = s.nextInt();
                           
		s.nextLine();
		for(int i=1; i<=numOfCategories; i++)
		{
			System.out.print("Category: ");
			String newCat = s.nextLine();
                                        MovieCategory cat = db.findCategoryForName(newCat);
                                        
                                        if(cat == null)
                                        {
                                            cat = new MovieCategory(newCat);
                                        }
                                        
			m.addToCategory(cat);
		}
		try
                    {
                        db.addNewMovie(m);
                    }catch(Exception e)
                    {
                        System.out.print(e);
                    }
		print("Thank you! \n");
	}
	
	private void print(String s)
	{
		System.out.print(s);
	}

}
