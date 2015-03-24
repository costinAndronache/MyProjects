package com.PA.MovieCatalog;

import java.io.Serializable;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

import java.io.*;

import com.PA.Exceptions.*;

public class Movie implements Serializable 
{
             
	private String name;
	private String filePath;
	private List<MovieCategory> categoriesList;
	private String directorName;
	private String imdbID;
	private String releaseDate;
	private float rating;
	
	
	
	public Movie()
	{
		this.categoriesList = new ArrayList<MovieCategory>();
	}
	
	public void setName(String name)
	{
		this.name = name;
	}
	
	public String getName()
	{
		return name;
	}
	
	public void setFilePath(String path) throws InvalidMoviePathException
	{
                    File f = new File(path);
                    
                    if(f.isFile() == false)
                    {
                        throw new InvalidMoviePathException(path);
                    }
                    
                    this.filePath = path;
	}
	
	public String getFilePath()
	{
		return this.filePath;
	}
	
	public void addToCategory(MovieCategory category)
	{
		this.categoriesList.add(category);
	}
	
	public void removeFromCategory(MovieCategory category)
	{
		if(this.categoriesList.contains(category))
		{
			this.categoriesList.remove(category);
			return;
		}
		
		for(int i=0; i<this.categoriesList.size(); i++)
		{
			MovieCategory mc = this.categoriesList.get(i);
			if(mc.equals(category))
			{
				this.categoriesList.remove(i);
				return;
			}
		}
		
	}
	
	public MovieCategory[] getCategoriesList()
	{
		MovieCategory[] a = new MovieCategory[this.categoriesList.size()];
		return this.categoriesList.toArray(a);
	}
	
	public void setDirectorName(String dName) throws InvalidDirectorNameException
	{
		
		System.out.println("Received: " + dName + "--");
		if( dName.matches("[a-zA-Z]+") == false)
		{
			throw new InvalidDirectorNameException(dName);
		}
		
		this.directorName = dName;
		
	}
	
	public String getDirectorName()
	{
		return this.directorName;
	}
	
	public String getImdbID()
	{
		return this.imdbID;
	}
	
	public void setImdbID(String imdbID)
	{
		this.imdbID = imdbID;
	}
	
	public float getRating()
	{
		return this.rating;
	}
	
	public void setRating(float rating) throws InvalidRatingException
	{
		if(rating < 1 || rating > 10)
		{
			throw new InvalidRatingException(rating);
		}
		this.rating = rating;
	}
	
              

        
       
	public String getReleaseDate()
	{
		return this.releaseDate;
	}
	
	public void setReleaseDate(String date) throws InvalidDateException
	{
		String format = "dd-MM-yyyy";
		SimpleDateFormat df = new SimpleDateFormat(format);
		try {
			Date d = df.parse(date);
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			throw new InvalidDateException(date, format);
		}
		
		this.releaseDate = date;
	}
	
	public boolean belongsToCategory(MovieCategory category)
	{
		for(MovieCategory cat : this.categoriesList)
		{
			if(cat.equals(category) == true)
			{
				return true;
			}
		}
		
		return false;
	}
	
	
	@Override
	public String toString()
	{
		String res = "";
		res += "Name: " + this.name + "\n";
		res += "IMDB id: " + this.imdbID + "\n";
		res += "Rating : " + this.rating + "\n";
		res += "Director name: " + this.directorName;
		res += "Categories: ";
		
		for(MovieCategory cat : this.categoriesList)
		{
			res += cat + " ";
		}
		
		return res;
	}
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

}
