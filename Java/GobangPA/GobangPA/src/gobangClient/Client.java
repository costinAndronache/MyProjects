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
import java.io.*;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;

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
    
    private BufferedWriter bw;
    
    public void run() throws IOException
    {
        
        String host = null;
      
        System.out.println("Connecting to the server");
        
        this.socket = new Socket(host, 8822);
        
        BufferedReader br = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
        String message = br.readLine();
        
        this.bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        
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
        

        
        System.out.println("Received from the server " + message);
        
         JSONObject serverMessage = (JSONObject)obj.get(JsonUtilties.kServerMessageKey);
  
         
         if(serverMessage.containsKey(JsonUtilties.kStatusKey))
         {
             String statusValue = (String)serverMessage.get(JsonUtilties.kStatusKey);
             
             if(statusValue.equalsIgnoreCase(JsonUtilties.kStatusValueWin))
             {
                 frame.presentStatusWin();
             }
             else
             {
                 frame.presentStatusLose();
             }
             
             
         }
         
         
         if(serverMessage.containsKey(JsonUtilties.kMoveKey))
         {
             JSONObject moveObj = (JSONObject)serverMessage.get(JsonUtilties.kMoveKey);
             long i = (Long)moveObj.get(JsonUtilties.kLineKey);
             long j = (Long)moveObj.get(JsonUtilties.kColumnKey);
             String color = (String)moveObj.get(JsonUtilties.kColorKey);
             
             CircleType ctype;
             if(color.equalsIgnoreCase(JsonUtilties.kWhiteColorValue))
                 ctype = CircleType.CircleTypeWhite;
             else
                 ctype = CircleType.CircleTypeBlack;
             
            try {
                this.gameBoard.setCircleAt(ctype, (int)i, (int)j);
                this.gameboardPanel.repaint();
            } catch (Exception ex) 
            {
                Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
            }
             
         }
         
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
            
            
            if(what.equalsIgnoreCase(JsonUtilties.kRequestValueMove))
            {
                if(this.frame == null)
                    return;
                
                this.frame.presentStatusMove();
                this.gameboardPanel.presentWaitForInput();
            }
            
            if(what.equalsIgnoreCase(JsonUtilties.kRequestValueWait))
            {
                if(this.frame == null)
                    return;
                
                this.frame.presentStatusWait();
                this.gameboardPanel.presentWaitForOtherPlayer();
            }
            
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
                        
                        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
                        
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
                        //</editor-fold>
                    
                        frame = new GobangFrame();
                        client.gameboardPanel = frame.getGameboardPanel();
                        client.gameboardPanel.setListener(client);
                    
                        client.gameboardPanel.setGameboard(client.gameBoard);
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
        if(this.gameBoard.isCellFree(i, j) == false)
            return;
        
        String message = this.createMoveMessageForPosition(i, j);
        try {
            this.bw.write(message + "\n");
        } catch (IOException ex) {
            Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
        try {
            this.bw.flush();
        } catch (IOException ex) {
            Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
    
    
    
    private String createMoveMessageForPosition(int i, int j)
    {
        
        JSONObject moveObj = new JSONObject();
        moveObj.put(JsonUtilties.kLineKey, i);
        moveObj.put(JsonUtilties.kColumnKey, j);
        
        JSONObject body = new JSONObject();
        body.put(JsonUtilties.kMoveKey, moveObj);
        body.put(JsonUtilties.kPlayerIdKey, this.myID);
        
        JSONObject message = new JSONObject();
        message.put(JsonUtilties.kPlayerMessageKey, body);
        
        return message.toJSONString();
    }
    
}
