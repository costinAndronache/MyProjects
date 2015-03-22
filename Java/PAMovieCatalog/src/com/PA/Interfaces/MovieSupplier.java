/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.PA.Interfaces;
import com.PA.MovieCatalog.*;
import java.util.*;

/**
 *
 * @author Costinel
 */
public interface MovieSupplier 
{
    public void setListOfCategories(List<MovieCategory> categoriesList);
    void addListener(MovieSupplierListener listener);
    void removeListener(MovieSupplierListener listener);
}
