/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package models;

/**
 *
 * @author costin
 */
public class Train 
{
    private int id;
    private String name;
    private int type;
    private int numOfWagons;
    
    public int getNumOfWagons()
    {
        return this.numOfWagons;
    }
    
    public void setNumOfWagons(int n)
    {
        this.numOfWagons = n;
    }
    
    public int getID()
    {
        return this.id;
    }
    
    public String getName()
    {
        return this.name;
    }
    
    public int getType()
    {
        return this.type;
    }
    
    public void setType(int t)
    {
        this.type = t;
    }
    public void setName(String name)
    {
        this.name = name;
    }
    
    public void setID(int id)
    {
        this.id = id;
    }
    
    @Override
    public String toString()
    {
        return "" + this.id + ", " + this.name + ", " + this.type;
    }
    
}
