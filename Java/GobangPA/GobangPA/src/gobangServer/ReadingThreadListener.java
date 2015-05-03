/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gobangServer;

/**
 *
 * @author Costinel
 */
public interface ReadingThreadListener 
{
    public void readingThreadDidReadString(ReadingThread rt, String s);
    public void readingThreadFailedWithException(ReadingThread rt, Exception ex);
}
