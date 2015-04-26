/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package algorithms;
import interfaces.*;
/**
 *
 * @author Costinel
 */
public abstract class SortingAlgorithm implements Runnable
{
    protected SortingAlgorithmListener listener;
    protected int[] array;
    protected long sleepTime;
    
    
    public void setListener(SortingAlgorithmListener listener)
    {
        this.listener = listener;
    }
    public void setSleepTime(long sleepTime)
    {
        this.sleepTime = sleepTime;
    }
    
    public void sortArrayWith(int[] array)
    {
        this.array = array;
    }
}
