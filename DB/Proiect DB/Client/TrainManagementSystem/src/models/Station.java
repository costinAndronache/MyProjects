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
public class Station 
{
    private String name;
    private String address;
    private int id;
    
    
    public int getID()
    {
        return this.id;
    }
    
    public String getName()
    {
        return this.name;
    }
    
    public String getAddress()
    {
        return this.address;
    }
    
    public void setID(int id)
    {
        this.id = id;
    }
    
    public void setName(String name)
    {
        this.name = name;
    }
    
    public void setAddress(String address)
    {
        this.address = address;
    }
    
    @Override
    public String toString()
    {
        return "" + this.id + ", " + this.name + ", " + this.address;
    }
    
}
