/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.PA.Interfaces;
import com.PA.MovieCatalog.Movie;

/**
 *
 * @author Costinel
 */
public interface MovieSupplierListener {
    public void movieSupplierDidCreateMovie(MovieSupplier controller, Movie movie);
    public void movieSupplierDidEditMovie(MovieSupplier supplier, Movie movie);
}
