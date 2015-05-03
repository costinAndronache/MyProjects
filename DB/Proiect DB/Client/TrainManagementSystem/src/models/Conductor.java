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
public class Conductor {
    private int id;
    private String firstName;
    private String lastName;
    
    public int getID()
    {
        return this.id;
    }
    
    public String getFirstName()
    {
        return this.firstName;
    }
    
    public String getLastName()
    {
        return this.lastName;
    }
    
    public void setLastName(String name)
    {
        this.lastName = name;
    }
    
    public void setFirstName(String name)
    {
        this.firstName = name;
    }
    
    public void setID(int id)
    {
        this.id = id;
    }
    
    @Override
    public String toString()
    {
        return "" + this.id + ", " + this.firstName + ", " + this.lastName;
    }
}
