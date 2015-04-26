/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package algorithms;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Costinel
 */

public class HeapSortAlgorithm extends SortingAlgorithm
{
    private  int[] a;
    private  int n;
    private  int left;
    private  int right;
    private  int largest;

    // Build-Heap Function
    public void buildheap(int []a){
    	n=a.length-1;
    	for(int i=n/2;i>=0;i--){
    		maxheap(a,i);
    	}
    }
    
    // Max-Heap Function
    public  void maxheap(int[] a, int i){
    	left=2*i;
    	right=2*i+1;
    	if(left <= n && a[left] > a[i]){
    		largest=left;
    	}
    	else{
    		largest=i;
    	}
    	
    	if(right <= n && a[right] > a[largest]){
    		largest=right;
    	}
    	if(largest!=i){
    		exchange(i,largest);
    		maxheap(a, largest);
    	}
        
           try {
                                             Thread.sleep(sleepTime);
                                            } 
                                                catch (InterruptedException ex) {
                        Logger.getLogger(BubbleSortAlgorithm.class.getName()).log(Level.SEVERE, null, ex);
                            }
    }
    
    // Exchange Function
    public  void exchange(int i, int j){
    	int t=a[i];
    	a[i]=a[j];
    	a[j]=t; 
        
        if(this.listener != null)
        {
            this.listener.sortingAlgorithmDidUpdateArray(this, a);

        }
        
   }
    
    // Sort Function
    public  void sort(int []a0){
    	a=a0;
    	buildheap(a);
    	
    	for(int i=n;i>0;i--){
    		exchange(0, i);
    		n=n-1;
    		maxheap(a, 0);
    	}
        
         if(this.listener != null)
         {
             this.listener.sortingAlgorithmDidFinish(this);
         }
         
    }
    
    @Override
    public void run() 
    {
        sort(this.array);
    }
} 

