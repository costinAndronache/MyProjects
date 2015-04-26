/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package algorithms;
import interfaces.SortingAlgorithmListener;
import java.util.logging.Level;
import java.util.logging.Logger;
/**
 *
 * @author Costinel
 */
public class BubbleSortAlgorithm extends SortingAlgorithm 
{

    @Override
    public void sortArrayWith(int[] array) 
    {
        this.array = array;
    }
    
    @Override
    public void run()
    {
        System.out.print(Thread.currentThread().getName());
               
        for(int i=0; i<array.length-1; i++)
            for(int j=i+1; j<array.length;j++)
            {
                if(array[i] > array[j])
                {
                    int aux = array[i];
                    array[i] = array[j];
                    array[j] = aux;
                    
                    if(this.listener != null)
                    {
                        
                        this.listener.sortingAlgorithmDidUpdateArray(this, array);
                    }
                }
                
                try {
                                             Thread.sleep(sleepTime);
                                            } 
                                                catch (InterruptedException ex) {
                        Logger.getLogger(BubbleSortAlgorithm.class.getName()).log(Level.SEVERE, null, ex);
                            }
            }
      
        if(this.listener != null)
        {
            this.listener.sortingAlgorithmDidFinish(this);
        }
    }
}
