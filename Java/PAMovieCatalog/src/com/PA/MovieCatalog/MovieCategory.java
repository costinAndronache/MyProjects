package com.PA.MovieCatalog;

import java.util.*;

public class MovieCategory 
{
	private String name;
	private Set<Movie> moviesSet;
	
	public MovieCategory(String name)
	{
		this.name = name;
		this.moviesSet = new HashSet<Movie>();
	}
	
	public String getName()
	{
		return this.name;
	}
	
	public void addNewMovie(Movie m)
	{
		this.moviesSet.add(m);
	}
	
	public void removeMovie(Movie m)
	{
		this.moviesSet.remove(m);
	}
	
	public Movie[] getAllMoviesList()
	{
		Movie[] array = new Movie[this.moviesSet.size()];
		return this.moviesSet.toArray(array);
	}
	
	@Override
	public boolean equals(Object o)
	{
		if(o == this)
		{
			return true;
		}
		if(o instanceof MovieCategory == false)
		{
			return false;
		}
		
		MovieCategory other = (MovieCategory)o;
		if(other.getName().equals(this.getName()))
		{
			return true;
		}
		
		return false;
	}
	
	@Override
	public String toString()
	{
		return this.name;
	}
	
}
