/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.PA.MovieCatalog;
import org.jdom2.*;
import org.jdom2.input.SAXBuilder;
import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.*;
import org.jdom2.output.Format;
import org.jdom2.output.XMLOutputter;
/**
 *
 * @author Costinel
 */
public class MovieDatabaseSerializer 
{
  
    private static String kRootElement = "MovieApp";
    private static String kCategoryListElement = "categoryList";
    private static String kCategoryElement = "category";
    private static String kCategoryNameElement = "categoryName";
    private static String kMovieListElement = "movieList";
    
    private static String kMovieCatListElement = "movieCatList";
    
    private static String kMovieElement = "movie";
    private static String kMovieNameElement = "movieName";
    private static String kMovieRatingElement = "movieRating";
    private static String kMovieIMDBIDElement = "movieIMDB";
    private static String kMoviePathElement = "moviePath";
    private static String kMovieDirectorElement = "movieDirector";
    private static String kMovieReleaseDateElement = "movieReleaseDate";
    
    public MovieDatabase deserializeFromXMLFile(File xmlFile) throws Exception
    {
        MovieDatabase db = new MovieDatabase();
        
        SAXBuilder builder = new SAXBuilder();
        Document doc = null;
        try {
            doc = builder.build(xmlFile);
        } catch (Exception ex) {
            Logger.getLogger(MovieDatabaseSerializer.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
        
        Element catList = doc.getRootElement().getChild(kCategoryListElement);
        List<Element> categories = catList.getChildren();
        for(Element e : categories)
        {
            MovieCategory cat = new MovieCategory(
                    e.getChild(kCategoryNameElement).getText());
            
            db.addNewCategory(cat);
            
        }
        
        Element movieList = doc.getRootElement().getChild(kMovieListElement);
        List<Element> movies = movieList.getChildren();
        for(Element e : movies)
        {
            Movie m = new Movie();
            
            m.setName(e.getChildText(kMovieNameElement));
            m.setDirectorName(e.getChildText(kMovieDirectorElement));
            m.setRating(Float.parseFloat(e.getChildText(kMovieRatingElement)));
            m.setReleaseDate(e.getChildText(kMovieReleaseDateElement));
            m.setImdbID(e.getChildText(kMovieIMDBIDElement));
            m.setFilePath(e.getChildText(kMoviePathElement));
            
            Element movieCatList = e.getChild(kMovieCatListElement);
            List<Element> movieCategories = movieCatList.getChildren();
            
            for(Element c : movieCategories)
            {
                String name = c.getChildText(kCategoryNameElement);
                MovieCategory mc = db.findCategoryForName(name);
                if(mc == null)
                {
                    throw new Exception("No category deserialized for name " + name);
                }
                
                mc.addNewMovie(m);
                m.addToCategory(mc);
                
            }
            
             db.addNewMovie(m);
        }
        
        
        return db;
    }
    
    public void serializeDatabaseToXML(MovieDatabase db, String filename)
    {
        File f = new File(filename);
        try {
            f.createNewFile();
        } catch (IOException ex) {
            Logger.getLogger(MovieDatabaseSerializer.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        
        Element root = new Element(kRootElement);
        Element catList = new Element(kCategoryListElement);
        Element movieListElement = new Element(kMovieListElement);
        
        
        for(MovieCategory cat : db.getCategoriesList())
        {
            Element catElement = new Element(kCategoryElement);
            
            Element catNameElement = new Element(kCategoryNameElement);
            catNameElement.setText(cat.getName());
            catElement.addContent(catNameElement);
            catList.addContent(catElement);
        }
        
        
        List<Movie> allMovies = db.getListOfMovies();
            for(Movie m : allMovies)
            {
                Element movieElement = new Element(kMovieElement);
                
                Element movieNameElement = new Element(kMovieNameElement);
                movieNameElement.setText(m.getName());
                
                Element movieRatingElement = new Element(kMovieRatingElement);
                movieRatingElement.setText("" + m.getRating());
                
                Element movieRelease = new Element(kMovieReleaseDateElement);
                movieRelease.setText(m.getReleaseDate());
                
                Element movieID = new Element(kMovieIMDBIDElement);
                movieID.setText(m.getImdbID());
                
                Element movieDirector = new Element(kMovieDirectorElement);
                movieDirector.setText(m.getDirectorName());
                
                Element moviePath = new Element(kMoviePathElement);
                moviePath.setText(m.getFilePath());
                
                Element movieCatListElement = new Element(kMovieCatListElement);
                
                MovieCategory[] categories = m.getCategoriesList();
                
                for(MovieCategory mc : categories)
                {
                 Element catElement = new Element(kCategoryElement);
                 Element catNameElement = new Element(kCategoryNameElement);
                 catNameElement.setText(mc.getName());
                 catElement.addContent(catNameElement);
                 movieCatListElement.addContent(catElement);
                 
                }
                
                List<Element> list = Arrays.asList(movieNameElement,
                                                            movieRatingElement,
                                                            movieRelease,
                                                            movieID,
                                                            movieDirector,
                                                            moviePath,
                                                            movieCatListElement);
                
                movieElement.addContent(list);
                
                movieListElement.addContent(movieElement);
            }
        
        
        root.addContent(catList);
        root.addContent(movieListElement);
        Document doc = new Document(root);
        
        XMLOutputter out = new XMLOutputter(Format.getPrettyFormat());
        FileWriter fw = null;
        try {
             fw = new FileWriter(f);
        } catch (IOException ex) {
            Logger.getLogger(MovieDatabaseSerializer.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        try {
            out.output(doc, fw);
        } catch (IOException ex) {
            Logger.getLogger(MovieDatabaseSerializer.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
    
    public static void main(String[] args)
    {
        MovieDatabase db = MovieDatabase.createDummyDatabase();
        MovieDatabaseSerializer ser = new MovieDatabaseSerializer();
        ser.serializeDatabaseToXML(db, "testXML.xml");
    }
    
}
