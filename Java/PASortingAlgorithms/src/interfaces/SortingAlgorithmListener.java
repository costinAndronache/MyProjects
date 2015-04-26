/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package interfaces;
import algorithms.*;
/**
 *
 * @author Costinel
 */
public interface SortingAlgorithmListener 
{
    public void sortingAlgorithmDidUpdateArray(SortingAlgorithm alg, int[] array);
    public void sortingAlgorithmDidFinish(SortingAlgorithm alg);
}
