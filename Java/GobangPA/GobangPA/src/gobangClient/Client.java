/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gobangClient;
import gobangpa.*;
/**
 *
 * @author Costinel
 */

import gobangServer.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.UnsupportedLookAndFeelException;

import org.json.simple.*;
import org.json.simple.parser.*;

public class Client implements ReadingThreadListener, GameboardPanelListener
{
    private final Gameboard gameBoard = new Gameboard(10, 10);
  
    private ReadingThread readingThread;
    private Socket socket;
    private GobangFrame frame;
    private GameboardPanel gameboardPanel;
    private long myID;
    private CircleType myCircleType;
    
    public void run() throws IOException
    {
        
        try {
            this.gameBoard.setCircleAt(CircleType.CircleTypeBlack, 0, 0);
        } catch (Exception ex) {
            Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        String host = null;
      
        System.out.println("Connecting to the server");
        
        this.socket = new Socket(host, 8822);
        
        BufferedReader br = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
        String message = br.readLine();
        
        try {
            this.analyzeServerMessage(message);
        } catch (ParseException ex) {
            Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        this.readingThread = new ReadingThread(0, this.socket.getInputStream(), this);
        Thread t = new Thread(this.readingThread);
        t.start();
        
        while(this.readingThread.isStopped() == false)
        {
            try {
                Thread.sleep(500);
            } catch (InterruptedException ex) {
                Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
    }
    
    public static void main(String[] args)
    {
        Client c = new Client();
        try {
            c.run();
        } catch (IOException ex) {
            Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    
    private void analyzeServerMessage(String message) throws ParseException
    {
        JSONParser parser = new JSONParser();
        JSONObject obj = (JSONObject)parser.parse(message);
        
        JSONObject serverMessage = (JSONObject)obj.get(JsonUtilties.kServerMessageKey);
        
        System.out.println("Received from the server " + message);
        
        if(serverMessage.containsKey(JsonUtilties.kSetupKey))
        {
            JSONObject setupObj = (JSONObject)serverMessage.get(JsonUtilties.kSetupKey);
            this.myID = (Long)setupObj.get(JsonUtilties.kPlayerIdKey);
            String color = (String)setupObj.get(JsonUtilties.kColorKey);
            
            if(color.equalsIgnoreCase(JsonUtilties.kWhiteColorValue))
                this.myCircleType = CircleType.CircleTypeWhite;
            
            if(color.equalsIgnoreCase(JsonUtilties.kBlackColorValue))
                this.myCircleType = CircleType.CircleTypeBlack;
            
            System.out.println("Received setup from the server " + setupObj);
        }
        
        if(serverMessage.containsKey(JsonUtilties.kRequestKey))
        {
            
            String what = (String)serverMessage.get(JsonUtilties.kRequestKey);
            
            if(what.equalsIgnoreCase(JsonUtilties.kRequestValueStart))
            {
                System.out.println("Received start request");
                // setup ui here
                
                GameboardPanelListener listener = this;
                final Client client = this;
                
                java.awt.EventQueue.invokeLater(new Runnable() {

                    @Override
                    public void run() 
                    {
                        
                        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(GobangFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(GobangFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(GobangFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(GobangFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
                        
                        
                        frame = new GobangFrame();
                        client.gameboardPanel = frame.getGameboardPanel();
                        client.gameboardPanel.setListener(client);
                        
                        Gameboard gb = new Gameboard(10, 10);
                        
                        client.gameboardPanel.setGameboard(gb);
                        client.gameboardPanel.repaint();
                        frame.setVisible(true);
                    }
                });
            }    
        }
        
    }
    
    @Override
    public void readingThreadDidReadString(ReadingThread rt, String s) 
    {
        try {
            this.analyzeServerMessage(s);
        } catch (ParseException ex) {
            Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @Override
    public void readingThreadFailedWithException(ReadingThread rt, Exception ex) 
    {
        rt.stop();
        System.out.println("Reading thread stopped zzz....");
    }

    @Override
    public void gameboardPanelDidClickAt(GameboardPanel gbp, int i, int j) 
    {
        
        System.out.println("Detected click from the gameboard panel");
        
        try {
            this.gameBoard.setCircleAt(CircleType.CircleTypeBlack, i, j);
        } catch (Exception ex) {
            Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
        gbp.repaint();
    }
    
}
