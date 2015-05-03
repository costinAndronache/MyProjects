/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gobangServer;

import java.net.*;
import org.json.simple.*;
import org.json.simple.parser.*;
import gobangpa.*;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.io.*;


/**
 *
 * @author Costinel
 */
public class GameServerRoom implements ReadingThreadListener, Runnable
{
    
    private final ServerSocket serverSocket;
    private Socket player1Socket, player2Socket;
    private ReadingThread player1Thread, player2Thread;
    
    private BufferedWriter player1BW, player2BW;
    
    public GameServerRoom() throws IOException
    {
        this.serverSocket = new ServerSocket(8822);
    }
    
    public int getPort()
    {
        return this.serverSocket.getLocalPort();
    }
    
    
    
    @Override
    public void readingThreadDidReadString(ReadingThread rt, String s) 
    {
        synchronized(this)
        {
            System.out.println("Received stuff " + s + ", from player " + rt.getID());
            if(s == null)
            {
                rt.stop();
            }
        }
    }

    @Override
    public void readingThreadFailedWithException(ReadingThread rt, Exception ex) 
    {
        synchronized(this)
        {
            System.out.println("Player " + rt.getID() + ", crashed zzz");
            rt.stop();
        }
    }

    @Override
    public void run() 
    {
        try {
            try {
                try {
                    this.player1Socket = this.serverSocket.accept();
                } catch (IOException ex) {
                    Logger.getLogger(GameServerRoom.class.getName()).log(Level.SEVERE, null, ex);
                    System.out.println("Could not accept the first player's socket!");
                    System.exit(-1);
                }
                
                System.out.println("Accepted player 1 socket");
                
                
                DataOutputStream outStream = null;
                try {
                    this.player1BW = new BufferedWriter(new OutputStreamWriter(player1Socket.getOutputStream()));
//           outStream = new DataOutputStream(player1Socket.getOutputStream());
                } catch (IOException ex) {
                    Logger.getLogger(GameServerRoom.class.getName()).log(Level.SEVERE, null, ex);
                    System.out.println("Could not read the first player's socket!");
                    System.exit(-1);
                }
                
                
                
                String s = this.createSetupForPlayerAndColor(1, JsonUtilties.kWhiteColorValue);
                try {
                    this.player1BW.write(s + "\n");
                    this.player1BW.flush();
                } catch (IOException ex) {
                    Logger.getLogger(GameServerRoom.class.getName()).log(Level.SEVERE, null, ex);
                    System.out.println("Could not send the setup to the first player's socket!");
                    System.exit(-1);
                }
                
                System.out.println("Sent " + s + ", to player 1");
                
                try {
                    this.player2Socket = this.serverSocket.accept();
                } catch (IOException ex)
                {
                    System.out.println("Could not accept the second player's socket!");
                    System.exit(-1);
                    Logger.getLogger(GameServerRoom.class.getName()).log(Level.SEVERE, null, ex);
                }
                
                System.out.println("Accepted player 2 socket");
                
                try {
                    this.player2BW = new BufferedWriter(new OutputStreamWriter(player2Socket.getOutputStream()));
                } catch (IOException ex)
                {
                    Logger.getLogger(GameServerRoom.class.getName()).log(Level.SEVERE, null, ex);
                    
                    System.out.println("Could not get the output stream of the second player");
                    System.exit(-1);
                }
                
                String s2 = this.createSetupForPlayerAndColor(2, JsonUtilties.kBlackColorValue);
                
                try {
                    this.player2BW.write(s2 + "\n");
                    this.player2BW.flush();
                } catch (IOException ex) {
                    Logger.getLogger(GameServerRoom.class.getName()).log(Level.SEVERE, null, ex);
                    System.out.println("Could not write to the output stream of the second player");
                    System.exit(-1);
                    
                }
                
                System.out.println("Sent " + s2 + ", to player 2");
                
                String startMessage = this.createStartMessage();
                
                this.player1BW.write(startMessage + "\n");
                 this.player1BW.flush();
                this.player2BW.write(startMessage + "\n");
                this.player2BW.flush();
                
                
                String waitMessage = this.buildWaitMessageForPlayer();
                String moveMessage = this.buildMoveMessage();
                
                this.player2BW.write(waitMessage + "\n");
                this.player1BW.write(moveMessage + "\n");
                this.player2BW.flush();
                this.player1BW.flush();
                
            
            } catch (IOException ex) {
                Logger.getLogger(GameServerRoom.class.getName()).log(Level.SEVERE, null, ex);
                System.out.println("Could not send start to both players.");
            }
            
            player1Thread = new ReadingThread(1, player1Socket.getInputStream(), this);
            player2Thread = new ReadingThread(2, player2Socket.getInputStream(), this);
            
            Thread t1 = new Thread(player1Thread);
            t1.start();
            Thread t2 = new Thread(player2Thread);
            t2.start();
            
            System.out.println("Started both listening threads ... ");
            
            while(player1Thread.isStopped() == false && player2Thread.isStopped() == false)
            {
                try {
                    Thread.sleep(200);
                } catch (InterruptedException ex) {
                    Logger.getLogger(GameServerRoom.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
            
        } catch (IOException ex) {
            Logger.getLogger(GameServerRoom.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
    
    
    private String createSetupForPlayerAndColor(int player, String color)
    {
        JSONObject obj = new JSONObject();
        obj.put(JsonUtilties.kPlayerIdKey, player);
        obj.put(JsonUtilties.kColorKey, color);
        JSONObject obj2 = new JSONObject();
        obj2.put(JsonUtilties.kSetupKey, obj);
        JSONObject message = new JSONObject();
        message.put(JsonUtilties.kServerMessageKey, obj2);
        
        return message.toJSONString();
    }
    
    private String createStartMessage()
    {
        JSONObject obj = new JSONObject();
        obj.put(JsonUtilties.kRequestKey, JsonUtilties.kRequestValueStart);
        JSONObject message = new JSONObject();
        message.put(JsonUtilties.kServerMessageKey, obj);
        return message.toJSONString();
    }
    
    private String buildMoveMessageForLineAndColumnAndColor(int i, int j, String color)
    {
        JSONObject obj = new JSONObject();
        obj.put(JsonUtilties.kLineKey, i);
        obj.put(JsonUtilties.kColumnKey, j);
        obj.put(JsonUtilties.kColorKey, color);
        
        JSONObject message = new JSONObject();
        message.put(JsonUtilties.kServerMessageKey, obj);
        
        return message.toJSONString();
    }
    
    private String buildWaitMessageForPlayer()
    {
        JSONObject obj = new JSONObject();
        obj.put(JsonUtilties.kRequestKey, JsonUtilties.kRequestValueWait);
        
        JSONObject message = new JSONObject();
        message.put(JsonUtilties.kServerMessageKey, obj);
        return message.toJSONString();
    }
    
    private String buildMoveMessage()
    {
        JSONObject obj = new JSONObject();
        obj.put(JsonUtilties.kRequestKey, JsonUtilties.kRequestValueMove);
        
        JSONObject message = new JSONObject();
        message.put(JsonUtilties.kServerMessageKey, obj);
        return message.toJSONString();
    }
    
    public static void main(String[] args)
    {
        GameServerRoom room = null;
        try {
            System.out.print("Creating a room" + "\n");
            room = new GameServerRoom();
            room.run();
        } catch (IOException ex) {
            Logger.getLogger(GameServerRoom.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
    
    
    private void analyzeMessage(String message) throws ParseException
    {
        JSONParser parser = new JSONParser();
        JSONObject obj = (JSONObject)parser.parse(message);
        obj = (JSONObject)obj.get(JsonUtilties.kPlayerMessageKey);
        
        if(obj.containsKey(JsonUtilties.kMoveKey))
        {
            long playerID = (Long)obj.get(JsonUtilties.kPlayerIdKey);
            
            JSONObject moveObj = (JSONObject)obj.get(JsonUtilties.kMoveKey);
            long i = (Long)moveObj.get(JsonUtilties.kLineKey);
            long j = (Long)moveObj.get(JsonUtilties.kColumnKey);
            
            String color = playerID == 1 ? JsonUtilties.kWhiteColorValue : JsonUtilties.kBlackColorValue;
            
            String moveMessage = this.buildMoveMessageForLineAndColumnAndColor((int)i, (int)j, color);
            
            try
            {
            this.player1BW.write(moveMessage + "\n");
            this.player2BW.write(message + "\n");
            this.player1BW.flush();
            this.player2BW.flush();
            
            
            String moveReq = this.buildMoveMessage();
            String waitReq = this.buildWaitMessageForPlayer();
            
            if(playerID == 1)
            {
                this.player1BW.write(waitReq + "\n");
                this.player2BW.write(moveReq + "\n");
            }
            else
            {
                this.player1BW.write(moveReq + "\n");
                this.player2BW.write(waitReq + "\n");
            }
            
            this.player1BW.flush();
            this.player2BW.flush();
            
            }catch(Exception e)
            {
                System.out.println("Could not send move message to both players");
            }
            
        }
        
    }
    
}
