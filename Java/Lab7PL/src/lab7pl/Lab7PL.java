/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab7pl;
import java.io.BufferedInputStream;
import jpl.*;
import java.util.*;
/**
 *
 * @author Costinel
 */
public class Lab7PL {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        // TODO code application logic here
        
        String[] predicatesList = new String[]{"mama", "tata", "frate", "sora", "bunic", "bunica", 
                                                           "unchi", "matusa", "nepot", "soti"};
        
        new Query("consult('arboreLab4.pl')").oneSolution();
        
        
        Scanner s = new Scanner(new BufferedInputStream(System.in));
        
        String firstName, secondName;
        System.out.println("First name: "); firstName = s.nextLine();
        System.out.println("Second name: ");secondName = s.nextLine();
        
        String arguments = "(" + firstName + ", " + secondName + ").";
        
        
        Hashtable res = null;
        for(int i=0; i<predicatesList.length; i++)
        {
            String query = predicatesList[i] + arguments;
            res = new Query(query).oneSolution();
            
            if(res != null)
            {
                System.out.println("Found predicate: " + predicatesList[i]);
                break;
            }
        }
        
        if(res == null)
        {
            System.out.print("Found nothing.");
        }
        
    }
    
}
