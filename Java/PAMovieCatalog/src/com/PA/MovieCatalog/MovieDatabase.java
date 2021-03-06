package com.PA.MovieCatalog;

import java.util.*;
import java.io.*;

import com.PA.Exceptions.*;
import java.util.logging.Level;
import java.util.logging.Logger;

public class MovieDatabase 
{
	private List<Movie> moviesList;
	private List<MovieCategory> categoriesList;
	
        
              public static MovieDatabase createDummyDatabase()
              {
                  MovieDatabase db = new MovieDatabase();
                  
                  MovieCategory adv = new MovieCategory("Adventure");
                  MovieCategory action = new MovieCategory("Action");
                  
                  db.addNewCategory(adv);
                  db.addNewCategory(action);
                  
                  for(int i=1; i<=5; i++)
                  {
                      Movie m1 = new Movie();
                      Movie m2 = new Movie();
                      
                      m1.setName("Action " + i);
                      m2.setName("Adventure " + i);
                      
                      
                      m1.addToCategory(action);
                      m2.addToCategory(adv);
                      
                      adv.addNewMovie(m2);
                      action.addNewMovie(m1);
                      
                      try {
                          db.addNewMovie(m2);
                          db.addNewMovie(m1);
                      } catch (InexistentCategoryException ex) {
                          Logger.getLogger(MovieDatabase.class.getName()).log(Level.SEVERE, null, ex);
                      } catch (AlreadyExistingMovieException ex) {
                          Logger.getLogger(MovieDatabase.class.getName()).log(Level.SEVERE, null, ex);
                      }
                      
                  }
                  
                  return db;
              }
        
	public MovieDatabase() 
	{
		// TODO Auto-generated constructor stub
		this.moviesList = new ArrayList<Movie>();
		this.categoriesList = new ArrayList<MovieCategory>();
	}
	
	public void addNewMovie(Movie m) throws InexistentCategoryException, AlreadyExistingMovieException
	{
		this.validateMovie(m);
		this.moviesList.add(m);
	}
	
	public void validateAlteredMovie(Movie m) throws InexistentCategoryException, 
                                                                             AlreadyExistingMovieException
	{
		this.validateMovie(m);
	}
	
	
	public void addNewCategory(MovieCategory mc) 
	{
		if(this.findCategoryForName(mc.getName()) == null)
		{
			this.categoriesList.add(mc);
		}
	}
	
	public void addNewCategory(String categoryName)
	{
		if(this.findCategoryForName(categoryName) == null)
		{
			MovieCategory mc = new MovieCategory(categoryName);
			this.categoriesList.add(mc);
		}
	}
	
              public List<MovieCategory> getCategoriesList()
              {
                  return this.categoriesList;
              }
        
	public void removeMovieWithName(String name)
	{
		Movie m = this.findMovieWithName(name);
		if(m != null)
		{
			this.moviesList.remove(m);
		}
	}
	
	public Movie findMovieWithName(String name)
	{
		
		for(int i=0; i<this.moviesList.size(); i++)
		{
			Movie m = this.moviesList.get(i);
			if(m.getName().equals(name) == true)
			{
				return m;
			}
		}
		
		return null;
	}
	
	
	public void serializeToFile(String filename) throws Exception
	{
		File file = new File(filename);
		ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(file));
		
		oos.writeInt(this.moviesList.size());
		
		for(Movie m : this.moviesList)
		{
			oos.writeObject(m);
		}

		oos.close();
	}
	
	@SuppressWarnings("unchecked")
	public void deserializeFromFile(String filename) throws Exception
	{
		File file = new File(filename);
		ObjectInputStream ois = new ObjectInputStream(new FileInputStream(file));
		
		int numOfMovies = ois.readInt();
		
		for(int i=1; i<=numOfMovies; i++)
		{
			Movie m = (Movie)ois.readObject();
			this.moviesList.add(m);
		}
		ois.close();
	}
	
	public List<Movie> getListOfMovies()
	{
		return this.moviesList;
	}
	
	
	
	private boolean stringExistsInList(List<String> list, String s)
	{
		for(String ss : list)
		{
			if(ss.equals(s))
				return true;
		}
		
		return false;
	}
	
	@Override
	public String toString()
	{
		String res = "";
		for(Movie m : this.moviesList)
		{
			res += m.toString() + "\n";
		}
		return res;
	}
	
	public MovieCategory findCategoryForName(String name)
	{
		
		for(MovieCategory mc : this.categoriesList)
		{
			if(mc.getName().equals(name))
				return mc;
		}
		return null;
	}
	
	private boolean validateCategoriesForMovie(Movie m)
	{
		MovieCategory[] cats = m.getCategoriesList();
		for(int i=0; i<cats.length; i++)
		{
			if(this.categoriesList.contains(cats[i]) == false)
			{
				return false;
			}
		}
		
		return true;
	}
	
	private boolean validateMovieNameForMovie(Movie m)
	{
                    
                    
		for(Movie aMovie : this.moviesList)
		{
			if(aMovie.getName().equals(m.getName()))
			{
				return false;
			}
		}
		
		return true;
	}
	
	private void validateMovie(Movie m) throws InexistentCategoryException, AlreadyExistingMovieException
	{
		if(this.validateCategoriesForMovie(m) == false)
			throw new InexistentCategoryException("One or more categories are not found for the"
					+ " movie " + m);
		
		if(this.validateMovieNameForMovie(m) == false)
		 throw new AlreadyExistingMovieException(m.getName());
	}
	
}
