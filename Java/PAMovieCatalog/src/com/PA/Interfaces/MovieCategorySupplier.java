/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.PA.Interfaces;

import com.PA.MovieCatalog.*;

/**
 *
 * @author Costinel
 */
public interface MovieCategorySupplier 
{
    public void setMovieDatabase(MovieDatabase db);
    public void addListener(MovieCategorySupplierListener listener);
    public void removeListener(MovieCategorySupplierListener listener);
}
