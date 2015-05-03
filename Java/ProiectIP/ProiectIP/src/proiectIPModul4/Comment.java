/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package proiectIPModul4;

/**
 *
 * @author Costinel
 */
public class Comment {
    
    private String author;
    private String text;
    private String location;
    private String date;
    
    public void setAuthor(String author)
    {
        this.author = author;
    }
    
    public void setText(String text)
    {
        this.text = text;
    }
    
    public void setLocation(String location)
    {
        this.location = location;
    }
    
    public void setDate(String date)
    {
        this.date = date;
    }
    
    public String getDate()
    {
        return this.date;
    }
    
    public String getAuthor()
    {
        return this.author;
    }
    
    public String getText()
    {
        return this.text;
    }
    
    public String getLocation()
    {
        return this.location;
    }
}
