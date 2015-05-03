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
public class Track 
{
    private int id;
    private int fromStationID;
    private int toStationID;
    private int length;
    
    public int getID()
    {
        return this.id;
    }
    
    public int getSourceStation()
    {
        return this.fromStationID;
    }
    
    public int getDestinationStation()
    {
        return this.toStationID;
    }
    
    public int getLength()
    {
        return this.length;
    }
    
    
    public void setLength(int length)
    {
        this.length = length;
    }
    
    public void setSourceID(int id)
    {
        this.fromStationID = id;
    }
            
    public void setDestinationID(int id)
    {
        this.toStationID = id;
    }
    
    public void setID(int id)
    {
        this.id = id;
    }
    
    @Override
    public String toString()
    {
        return "" + this.id + ", " + this.length + ", " +this.fromStationID + 
                ", " + this.toStationID;
    }
    
}
