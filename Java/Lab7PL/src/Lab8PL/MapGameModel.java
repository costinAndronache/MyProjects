/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Lab8PL;


import jpl.*;
import java.util.*;

/**
 *
 * @author Costinel
 */
public class MapGameModel 
{
    
    private Variable X, Y;
    private Query explorerQuery;
    private Query startQuery, teleportQuery;
    private Query northQuery, southQuery, eastQuery, westQuery;
    
    public MapGameModel()
    {
        
       this.X = new Variable("X");
       this.Y = new Variable("Y");
       
       Hashtable t = new Query("consult('Lab6Map.pl')").oneSolution();
              
        explorerQuery = new Query(new Compound("explorer", new Term[]{X, Y}));
        
        startQuery = new Query("start");
        teleportQuery  = new Query("teleport");
        
        northQuery = new Query("north");
        southQuery = new Query("south");
        eastQuery = new Query("east");
        westQuery = new Query("west");
        
    }
    
    
    public boolean start()
    {
        return startQuery.hasSolution();
    }
    
    public boolean teleport()
    {
        return teleportQuery.hasSolution();
    }
    
    public boolean moveNorth()
    {
        
        return northQuery.hasSolution();
    }
    
    public boolean moveSouth()
    {
        
        return southQuery.hasSolution();
    }
    
    public boolean moveEast()
    {
        
        return eastQuery.hasSolution();
    }
    
    public boolean moveWest()
    {
        return westQuery.hasSolution();
    }
    
    public int getCurrentLine()
    {
        
        
       Hashtable t = this.explorerQuery.oneSolution();
       
       if(t == null)
           return 1;
       
       jpl.Integer i = (jpl.Integer)t.get("X");
       
       
       System.out.println(i);
       
       return i.intValue();
       

    }
    
    
    public int getCurrentColumn()
    {
       Hashtable t = this.explorerQuery.oneSolution();
       
       if(t == null)
           return 1;
 
       jpl.Integer i = (jpl.Integer)t.get("Y");
       
       System.out.println(i);
       
       return i.intValue();
    }
    
}
