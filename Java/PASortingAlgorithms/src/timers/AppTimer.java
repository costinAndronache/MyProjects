/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package timers;
import java.util.logging.Level;
import java.util.logging.Logger;
import views.AppTimerView;
/**
 *
 * @author Costinel
 */
public class AppTimer implements Runnable
{
    
    private AppTimerView view;
    
    private long totalTime;
    private long start;
    private boolean shouldStop = false;
    
    private int count = 0;
    
    public void setView(AppTimerView view)
    {
        this.view = view;
    }
    
    public void stop()
    {
        this.shouldStop = true;
    }
    
    @Override
    public void run() 
    {
        totalTime = 0;
        this.shouldStop = false;
        this.start = System.currentTimeMillis();
        while(this.shouldStop == false)
        {
            try {
                this.totalTime = System.currentTimeMillis() - this.start;
                if(this.view != null)
                {
                    this.view.updateTotalTime((float)totalTime / (float)1000.);
                }
                
                Thread.sleep(50);
            } catch (InterruptedException ex) {
                Logger.getLogger(AppTimer.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
    
    
    public void bubbleSortStopped()
    {
        count ++;
        long time = System.currentTimeMillis() - this.start;
        float seconds = (float)time / (float)1000.;
        if(this.view != null)
                {
                   this.view.updateBubbleSortTime(seconds);
                }
        
        if(count > 3)
            this.shouldStop = true;
    }
    
    public void heapSortStopped()
    {
        count++;
        if(count > 3)
            this.shouldStop = true;
        
        long time = System.currentTimeMillis() - this.start;
        float seconds = (float)time / (float)1000.;
        if(this.view != null)
                {
                   this.view.updateHeapSortTime(seconds);
                }
        
        
                count++;
        if(count > 3)
            this.shouldStop = true;
    }
    
    public void mergeSortStopped()
    {
                long time = System.currentTimeMillis() - this.start;
        float seconds = (float)time / (float)1000.;
        if(this.view != null)
                {
                   this.view.updateMergeSortTime(seconds);
                }
        
                count++;
        if(count > 3)
            this.shouldStop = true;
    }
    
}
