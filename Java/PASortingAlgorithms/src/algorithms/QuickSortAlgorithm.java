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
public class QuickSortAlgorithm extends SortingAlgorithm {
 
 
    public  void quickSort(int[] arr, int low, int high) {
 
		if (arr == null || arr.length == 0)
			return;
 
		if (low >= high)
			return;
 
		//pick the pivot
		int middle = low + (high - low) / 2;
		int pivot = arr[middle];
 
		//make left < pivot and right > pivot
		int i = low, j = high;
		while (i <= j) {
			while (arr[i] < pivot) 
                        {
                            try {
                                Thread.sleep(sleepTime);
                            } catch (InterruptedException ex) {
                                Logger.getLogger(QuickSortAlgorithm.class.getName()).log(Level.SEVERE, null, ex);
                            }
				i++;
			}
 
			while (arr[j] > pivot) {
				j--;
                            try {
                                Thread.sleep(sleepTime);
                            } catch (InterruptedException ex) {
                                Logger.getLogger(QuickSortAlgorithm.class.getName()).log(Level.SEVERE, null, ex);
                            }
			}
 
			if (i <= j) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
				i++;
				j--;
                                
                                            if(this.listener != null)
                                            {
                                                this.listener.sortingAlgorithmDidUpdateArray(this, array);
                                            }
			}
		}
 
		//recursively sort two sub parts
		if (low < j)
			quickSort(arr, low, j);
 
		if (high > i)
			quickSort(arr, i, high);
	}
 
    @Override
    public void run() 
    {
        this.quickSort(this.array, 0, this.array.length - 1);
        
        if(this.listener != null)
        {
            this.listener.sortingAlgorithmDidFinish(this);
        }
    }
}