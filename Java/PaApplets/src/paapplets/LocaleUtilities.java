package paapplets;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.text.*;
import java.util.*;

/**
 *
 * @author Costinel
 */
public class LocaleUtilities 
{
    
 public static String printCurrency(Locale locale, double dbl)
 {  
    NumberFormat formatter=NumberFormat.getCurrencyInstance(locale);  
    return formatter.format(dbl);  
 }  
    
 public static String printTime(Locale locale, Date date)
 {
     DateFormat formatter=DateFormat.getTimeInstance(DateFormat.DEFAULT,locale);  
     Date currentDate=new Date();  
     return formatter.format(currentDate);    
 }
 
 public static String printDate(Locale locale, Date date)
 {
     DateFormat formatter=DateFormat.getDateInstance(DateFormat.DEFAULT,locale);  
     Date currentDate=new Date();  
     return formatter.format(currentDate);
 }
 
}