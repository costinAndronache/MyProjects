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
    
    private Gameboard gameboard;
    
    public GameServerRoom() throws IOException
    {
        this.serverSocket = new ServerSocket(8822);
        
        this.gameboard = new Gameboard(10, 10);
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
            
            try {
                this.analyzeMessage(s);
            } catch (ParseException ex) {
                Logger.getLogger(GameServerRoom.class.getName()).log(Level.SEVERE, null, ex);
            }
            
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
                
                
                try {
                    Thread.sleep(500);
                } catch (InterruptedException ex) {
                    Logger.getLogger(GameServerRoom.class.getName()).log(Level.SEVERE, null, ex);
                }
                
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
        
        JSONObject moveObj = new JSONObject();
        
        moveObj.put(JsonUtilties.kMoveKey, obj);
        
        JSONObject message = new JSONObject();
        message.put(JsonUtilties.kServerMessageKey, moveObj);
        
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
    
    
    
    private String buildWinMessage()
    {
        JSONObject obj = new JSONObject();
        obj.put(JsonUtilties.kStatusKey, JsonUtilties.kStatusValueWin);
        
        JSONObject message = new JSONObject();
        message.put(JsonUtilties.kServerMessageKey, obj);
        return message.toJSONString();
    }
    
    private String buildLoseMessage()
    {
         JSONObject obj = new JSONObject();
        obj.put(JsonUtilties.kStatusKey, JsonUtilties.kStatusValueLose);
        
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
            
            CircleType type = playerID == 1 ? CircleType.CircleTypeWhite : CircleType.CircleTypeBlack;
            
            try {
                this.gameboard.setCircleAt(type, (int)i, (int)j);
            } catch (Exception ex) {
                System.out.println("ILLEGAL MOVE!!!");
            }
            
            try
            {
            this.player1BW.write(moveMessage + "\n");
            this.player2BW.write(moveMessage + "\n");
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
            
            
            boolean whiteWin = this.checkHorizontalWinForType(CircleType.CircleTypeWhite, 5) ||
                                      this.checkVerticalWinForType(CircleType.CircleTypeWhite, 5);
            
            boolean blackWin  = this.checkHorizontalWinForType(CircleType.CircleTypeBlack, 5) ||
                                      this.checkVerticalWinForType(CircleType.CircleTypeBlack, 5);
            
            String winMessage = this.buildWinMessage();
            String loseMessage = this.buildLoseMessage();
            
            if(whiteWin)
            {
                this.player1BW.write(winMessage + "\n");
                this.player2BW.write(loseMessage +"\n");
            }
            else
                if(blackWin)
                {
                    this.player1BW.write(loseMessage + "\n");
                    this.player2BW.write(winMessage + "\n");
                }
            
            if(whiteWin || blackWin)
            {
                this.player1BW.flush();
                this.player2BW.flush();
            }
            
            }catch(Exception e)
            {
                System.out.println("Could not send move message to both players");
            }
            
        }
        
    }
    
    private boolean checkGameOver()
    {
        CircleType[][] m = this.gameboard.getMatrixRepresentation();
        
        for(int i=0; i<m.length; i++)
        {
            
        }
        
        return false;
    }
    
    private boolean checkHorizontalWinForType(CircleType type, int number)
    {
        CircleType[][] m = this.gameboard.getMatrixRepresentation();
        for(int i=0; i<m.length; i++)
        {
            int count = 0;
            for(int j = 0; j<m[i].length; j++)
                if(m[i][j] == type)
                {
                    count++;
                    if(count == number)
                        return true;
                }
            else
                {
                    count = 0;
                }
        }
        
        return false;
    }
    
    
    private boolean checkVerticalWinForType(CircleType type, int number)
    {
        CircleType[][] m = this.gameboard.getMatrixRepresentation();
        for(int j=0; j<m[0].length; j++)
        {
            int count = 0;
            for(int i = 0; i<m.length; i++)
                if(m[i][j] == type)
                {
                    count++;
                    if(count == number)
                        return true;
                }
            else
                {
                    count = 0;
                }
        }
        
        return false;
    }
}
