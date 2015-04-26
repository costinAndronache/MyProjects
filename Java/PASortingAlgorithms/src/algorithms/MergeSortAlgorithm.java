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
public class MergeSortAlgorithm extends SortingAlgorithm {
     
    
    private int[] tempMergArr;
    private int length;
 
     
    public void sort(int inputArr[]) {
        this.array = inputArr;
        this.length = inputArr.length;
        this.tempMergArr = new int[length];
        doMergeSort(0, length - 1);
    }
 
    private void doMergeSort(int lowerIndex, int higherIndex) {
         
        if (lowerIndex < higherIndex) {
            int middle = lowerIndex + (higherIndex - lowerIndex) / 2;
            // Below step sorts the left side of the array
            doMergeSort(lowerIndex, middle);
            // Below step sorts the right side of the array
            doMergeSort(middle + 1, higherIndex);
            // Now merge both sides
            mergeParts(lowerIndex, middle, higherIndex);
        }
    }
 
    private void mergeParts(int lowerIndex, int middle, int higherIndex) {
 
        for (int i = lowerIndex; i <= higherIndex; i++) {
            tempMergArr[i] = array[i];
        }
        int i = lowerIndex;
        int j = middle + 1;
        int k = lowerIndex;
        while (i <= middle && j <= higherIndex) {
            if (tempMergArr[i] <= tempMergArr[j]) {
                array[k] = tempMergArr[i];
                i++;
            } else {
                array[k] = tempMergArr[j];
                j++;
            }
            k++;
            
             if(this.listener != null)
            {
                this.listener.sortingAlgorithmDidUpdateArray(this, array);
            }
            
            try {
                Thread.sleep(sleepTime);
            } catch (InterruptedException ex) {
                Logger.getLogger(MergeSortAlgorithm.class.getName()).log(Level.SEVERE, null, ex);
            }
            
        }
        while (i <= middle) {
            array[k] = tempMergArr[i];
            k++;
            i++;
            
            if(this.listener != null)
            {
                this.listener.sortingAlgorithmDidUpdateArray(this, array);
            }
            
            try {
                Thread.sleep(sleepTime);
            } catch (InterruptedException ex) {
                Logger.getLogger(MergeSortAlgorithm.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
 
    }

    @Override
    public void run() 
    {
        this.sort(this.array);
        
        if(this.listener != null)
        {
            this.listener.sortingAlgorithmDidFinish(this);
        }
    }
}

