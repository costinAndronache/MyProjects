/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.PA.Interfaces;
import com.PA.Views.*;
import com.PA.MovieCatalog.*;

/**
 *
 * @author Costinel
 */
public interface MovieDbTreeListener 
{
    public void movieDbTreeDidSelectMovie(MovieDbTreePanel dbTreePanel, Movie m);
    public void movieDbTreeDidSelectCategory(MovieDbTreePanel dbTreePanel, MovieCategory mc);
    public void movieDbTreeDidSelectRootCategoryNode(MovieDbTreePanel dbTreePanel);
    public void movieDbTreeDidSelectRootMoviesNode(MovieDbTreePanel dbTreePanel);
    public void movieDbTreeDidSelectRootNode(MovieDbTreePanel dbTreePanel);
}
