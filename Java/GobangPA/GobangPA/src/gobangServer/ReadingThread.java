/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gobangServer;
import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Costinel
 */
public class ReadingThread implements Runnable
{
    
    private ReadingThreadListener listener;
    private final InputStream is;
    private final int id;
    boolean shouldStop;
    
    public ReadingThread(int id, InputStream is, ReadingThreadListener listener)
    {
        this.id = id;
        this.is = is;
        this.listener = listener;
        this.shouldStop = false;
    }
    
    public boolean isStopped()
    {
        return this.shouldStop;
    }
    
    public int getID()
    {
        return this.id;
    }
    
    public void setListener(ReadingThreadListener listener)
    {
        this.listener = listener;
    }
    
    public void stop()
    {
        this.shouldStop = true;
    }
    
    @Override
    public void run() 
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        while(!this.shouldStop)
        {
            try {
                String s = br.readLine();
                
                System.out.println(s);
                
                if(this.listener != null)
                {
                    this.listener.readingThreadDidReadString(this, s);
                }
                
            } catch (IOException ex) {
                Logger.getLogger(ReadingThread.class.getName()).log(Level.SEVERE, null, ex);
                
                if(this.listener != null)
                {
                    this.listener.readingThreadFailedWithException(this, ex);
                }
                
            }
        }
    }
    
    
}
