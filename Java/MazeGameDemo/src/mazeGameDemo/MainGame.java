package mazeGameDemo;

import static java.awt.event.KeyEvent.*;

import java.awt.*;
import java.awt.event.*;


public class MainGame extends Thread {

	
	enum RoundOverState{OverWon,OverLost,NULL};
	
	public static final int WIDTH = 1000;
	public static final int HEIGHT = 700;
	
	public static final int playerWIDTH = 12;
	public static final int playerHEIGHT = 12;
	
	public static final int minuteLimit = 2 ;
	public static final int secondLimit = 10;
	
	public static final int mazeDisplayWait=25;
	
	public static final String insertProperName = "Please insert a name";
	public static final String insertPlayerName = "Type your name here";
	
	
	GameCanvas gameCanvas;
	MazeCanvas mazeCanvas;
	MazeGenerator mazeGenerator;
	
	PlayerModel player;
	PlayerMovementInformation movementInfo;
	PlayerView playerView;
	TimerModel timerModel;
	TimerView timerView;
	
	int waitTimeToDisplay=0;
	
	int wonRounds;
	String playerName;
	RoundOverState lastRoundState;
	
	
	Dialog dInsertPlayerName, dBestOfLuck;
	TextField tfInsertPlayerName;
	Label lbBestOfLuck;
	
	Button btnOk, btnBestOfLuckOk;
	
	Frame gameFrame;
	
	boolean acceptInput;
	
	public MainGame()
	{
		
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		
		gameFrame = new Frame("theMaze");
		gameFrame.setBounds(new Rectangle((screenSize.width-WIDTH)/2,(screenSize.height-HEIGHT)/2,WIDTH,HEIGHT));
		gameFrame.setResizable(false);
		
		gameCanvas = new GameCanvas(WIDTH,HEIGHT);
		
		mazeGenerator = new MazeGenerator(60,40);
		
		mazeCanvas = new MazeCanvas();
		mazeCanvas.setCellHeight(16);
		mazeCanvas.setCellWidth(16);
		
		
		player = new PlayerModel(new Point(0,0), new Dimension(playerWIDTH,playerHEIGHT));
		
		movementInfo = new PlayerMovementInformation(2,2);
		playerView = new PlayerView("./TerraSheet.png",player);
		
		gameFrame.add(gameCanvas);
		gameFrame.addKeyListener(new KeyManager());
		
		
		timerModel = new TimerModel();
		timerView = new TimerView(timerModel,new Font("Arial", Font.BOLD, playerHEIGHT));
		
		gameFrame.addWindowListener(new WindowAdapter()
		{
			@Override
			public void windowClosing(WindowEvent e)
			{
				System.exit(0);
			}
		});
		
		
		dInsertPlayerName = new Dialog(gameFrame,"Hello",true);
		dInsertPlayerName.setLayout(null);
		dInsertPlayerName.addWindowListener(new WindowAdapter()
		{
			public void windowClosing(WindowEvent e)
			{
				System.exit(0);
			}
		});
		
		
		
		dInsertPlayerName.setBounds(screenSize.width/2 - 100,screenSize.height/2-150,300,150);
		
		
		tfInsertPlayerName = new TextField("Type your name here");
		tfInsertPlayerName.setPreferredSize(new Dimension(200,50));
		tfInsertPlayerName.addFocusListener(new FocusListener()
		{
			public void focusGained(FocusEvent e)
			{
				tfInsertPlayerName.setText("");
			}
			
			public void focusLost(FocusEvent e)
			{
				
			}
		});
		
		lbBestOfLuck = new Label("Best of luck!",Label.CENTER);
		lbBestOfLuck.setBounds(50,10,50,50);
		lbBestOfLuck.setFont(new Font("Arial", Font.BOLD,14));
		
		
		dBestOfLuck = new Dialog(dInsertPlayerName,"Best Of Luck",true);
		dBestOfLuck.setBounds(screenSize.width/2 - 100,screenSize.height/2-80,250,120);
		dBestOfLuck.setLayout(new FlowLayout());
		

		
		
		gameCanvas.addKeyListener(new KeyManager());
		
		Label insertRequest = new Label("Type in your name:");
		insertRequest.setFont(new Font("Arial",Font.BOLD,14));
		
		btnOk = new Button("Ok");
		btnOk.setPreferredSize(new Dimension(20,25));
		btnOk.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				playerName=tfInsertPlayerName.getText();
				
				if(playerName.length() == 0 || playerName.equals(insertPlayerName) || playerName.equals(insertProperName))
					tfInsertPlayerName.setText(insertProperName);
				else
				dBestOfLuck.setVisible(true);
			}
		});
		
		btnBestOfLuckOk = new Button("Ok");
		btnBestOfLuckOk.setPreferredSize(new Dimension(50,25));
		
		btnBestOfLuckOk.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				dBestOfLuck.setVisible(false);
				dInsertPlayerName.setVisible(false);
			}
		});
		
		Panel myPanel = new Panel();
		myPanel.setLayout(new GridLayout(0,1,10,10));
		myPanel.add(insertRequest);
		myPanel.add(tfInsertPlayerName);
		myPanel.add(btnOk);
		
		dInsertPlayerName.setLayout(new FlowLayout());
		dInsertPlayerName.add(myPanel);
		
		
		Panel mySecondPanel = new Panel();
		mySecondPanel.setLayout(new GridLayout(0,1,10,10));
		
		
		mySecondPanel.add(lbBestOfLuck);
		mySecondPanel.add(btnBestOfLuckOk);
		
		dBestOfLuck.add(mySecondPanel);
		
		
		dInsertPlayerName.setResizable(false);
		dBestOfLuck.setResizable(false);
		
		dInsertPlayerName.setVisible(true);
		
	}
		
	
	public static void main(String[] args)
	{
		MainGame mainGame = new MainGame();
		
		mainGame.start();
	
	}
	
	@Override
	public void run()
	{
		
		gameFrame.setVisible(true);
		
		Point destination;
		Rectangle destRect = new Rectangle();
				
		while(lastRoundState!=RoundOverState.OverLost)
		{
		byte[][] maze;
		mazeGenerator.reset();
		mazeGenerator.initialize();
		
		
		
		//Display maze iteratively
		acceptInput = false;
		displayMazeIteratively();

		maze = mazeGenerator.getSnapshot();
		mazeCanvas.setMazeToDisplay(maze);
		
		Point startingPoint = getPlayerStartingPosition();
		
		destination = getFarthestPointFrom(startingPoint,maze);
		
		destRect.x = destination.y*mazeCanvas.getCellWidth();
		destRect.y = destination.x*mazeCanvas.getCellHeight();
		
		destRect.width=mazeCanvas.getCellWidth();
		destRect.height=mazeCanvas.getCellHeight();
		
		player.setX(startingPoint.y*mazeCanvas.getCellHeight());
		player.setY(startingPoint.x*mazeCanvas.getCellWidth());
		
	
		timerModel.reset();
		
		mazeCanvas.paint(gameCanvas.getGraphicsToDrawOn());
		//printFinishMessage();
		
		boolean mazeDone = false;
		
		acceptInput=true;
		while(!mazeDone)
		{
			
			gameCanvas.clear();
			mazeCanvas.paint(gameCanvas.getGraphicsToDrawOn());
			
			
			
			updatePlayer();
			
			keepInBounds(player,mazeCanvas,maze);
			keepInBounds(player,mazeCanvas,maze);
			
			
			playerView.paint(gameCanvas.getGraphicsToDrawOn());
			
			gameCanvas.getGraphicsToDrawOn().setColor(Color.red);
			gameCanvas.getGraphicsToDrawOn().fillRect(destination.y*mazeCanvas.getCellWidth(),
																				destination.x*mazeCanvas.getCellHeight()
																							, playerWIDTH, playerHEIGHT);
			
			timerView.paint(gameCanvas.getGraphicsToDrawOn(), 0, 14);
			gameCanvas.getGraphicsToDrawOn().drawString(" Time limit " + minuteLimit + " : " + secondLimit, 900, 14);
			gameCanvas.repaint();
			
			try {
				Thread.sleep(25);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				
				System.out.println("Fucking exception");
				
			}
			
			if(destRect.intersects(player.getBoundingBox()))
					{
						mazeDone = true;
						lastRoundState = RoundOverState.OverWon;
					}
			
			if(timerModel.getElapsedMinutes() == (long)minuteLimit
					&&
				timerModel.getElapsedSeconds() == (long)secondLimit)
			{
				mazeDone = true;
				lastRoundState = RoundOverState.OverLost;
			}
			
			
			}
		
		   if(lastRoundState == RoundOverState.OverWon)
			   ++wonRounds;
		}
		
		printFinishMessage();
		
	}
	
	
	
	private void printFinishMessage()
	{
		
		Graphics g = gameCanvas.getGraphicsToDrawOn();
		
		String p = " has managed to finish " + wonRounds + " mazes.";
		String m0=" ----------------------------------------------";
		String m1=" Author: Andronache. Costin , IB7, InfoUAIC ";
		String m2=" The sprite is not created by me";
		String m3=" For entertainment purposes.";
		String m4=" No intention of commercializing.";
		
		g.setColor(Color.GRAY);
		g.fill3DRect(200, 350, 300, 220, true);
		
		g.setColor(Color.ORANGE);
		g.setFont(new Font("ComicSans", Font.BOLD, 14));
		g.drawString(p, 240, 420);
		g.drawString(playerName, 280, 400);
		
		
		g.setColor(Color.BLACK);		
		g.setFont(new Font("Arial",Font.BOLD,12));
		g.drawString(m0, 220, 450);
		g.drawString(m1,220,470);
		g.drawString(m2,220,490);
		g.drawString(m3,220,510);
		g.drawString(m4, 220, 530);
		
		gameCanvas.repaint();
	}
	
	private Point getPlayerStartingPosition()
	{
		
		byte[][] maze = mazeGenerator.getSnapshot();
		//mazeCanvas.setMazeToDisplay(maze);
		
		Point destination=null;
		
		boolean stop= false;
		for(int i=0;i<maze.length && !stop;i++)
			for(int j=0;j<maze[i].length && !stop;j++)
				if(maze[i][j] == mazeGenerator.FREE)
				{
					return new Point(i,j);
				}
		
		return destination;
		
	}
	
	private void displayMazeIteratively()
	{
		while(!mazeGenerator.isDone())
		{
			mazeCanvas.setMazeToDisplay(mazeGenerator.getSnapshot());
			mazeCanvas.paint(gameCanvas.getGraphicsToDrawOn());
			
			gameCanvas.repaint();
			mazeGenerator.step();
			
			try {
				Thread.sleep(waitTimeToDisplay);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

		}
	}
		

		private void updatePlayer()
		{
			
			if(movementInfo.isMovingDown())
				player.moveY(movementInfo.getVelocityY());
			
			if(movementInfo.isMovingUp())
				player.moveY(-movementInfo.getVelocityY());
			
			if(movementInfo.isMovingLeft())
				player.moveX(-movementInfo.getVelocityX());
			
			if(movementInfo.isMovingRight())
				player.moveX(movementInfo.getVelocityX());
			
			if(movementInfo.isMovingAtAll())
			playerView.animInfo.stepInAnimation();
		}
	
	class KeyManager extends KeyAdapter
	{
		
		@Override
		public void keyPressed(KeyEvent e)
		{
			//if(acceptInput)
			switch(e.getKeyCode())
			{
			case VK_DOWN:
				if(!movementInfo.isMovingDown())
					{
					playerView.animInfo.changeLine(PlayerView.DOWN);
					playerView.animInfo.changeFrame(0);
					}
				
				movementInfo.moveDown();
				
				//System.out.println("We have key input!");
				break;
				
			case VK_UP:
				
				if(!movementInfo.isMovingUp())
					{
					playerView.animInfo.changeLine(PlayerView.UP);
					playerView.animInfo.changeFrame(0);
					}
				
				movementInfo.moveUp();
				//System.out.println("We have key input!");
				break;
			
			case VK_LEFT:
				
				if(!movementInfo.isMovingLeft())
					{
					playerView.animInfo.changeLine(PlayerView.LEFT);
					playerView.animInfo.changeFrame(0);
					}
				
				movementInfo.moveLeft();
				//System.out.println("We have key input!");
				break;
				
			case VK_RIGHT:
				
				if(!movementInfo.isMovingRight())
					{
					playerView.animInfo.changeLine(PlayerView.RIGHT);
					playerView.animInfo.changeFrame(0);
					}
				
				movementInfo.moveRight();
				//System.out.println("We have key input!");
				break;
				
			case VK_SPACE:
				waitTimeToDisplay=mazeDisplayWait;
				break;
				
			default:
				break;
			}
		}
		
		@Override
		public void keyReleased(KeyEvent e)
		{
			//if(acceptInput)
			switch(e.getKeyCode())
			{
			case VK_DOWN:
				movementInfo.setMovingDown(false);
				break;
			case VK_UP:
				movementInfo.setMovingUp(false);
				break;
				
			case VK_LEFT:
				movementInfo.setMovingLeft(false);
				break;
				
			case VK_RIGHT:
				movementInfo.setMovingRight(false);
				
				break;
			case VK_SPACE:
				waitTimeToDisplay=0;
				break;
			}
			
		}
		
	}
	
	private Point getFarthestPointFrom(Point source, byte[][] maze)
	{
		
		final int FREE = 0;
		final int WALL = -1;
		int[][] myMaze = new int[maze.length][maze[0].length];
		
		final int[] xV = {0,0,-1,1};
		final int[] yV = {-1,1,0,0};
		
		for(int i=0;i<maze.length;i++)
			for(int j=0;j<maze[i].length;j++)
				if(maze[i][j] == mazeGenerator.FREE)
					myMaze[i][j]=FREE;
				else
					myMaze[i][j]=WALL;
		
		Point[] myPointQueue = new Point[maze.length*maze[0].length];
		int p,q;
		
		
		p=q=-1;
		myPointQueue[++q]=(Point)source.clone();
		
		myMaze[source.x][source.y]=1;
		
		Point maxPoint=new Point(source);
		int maxDistance=1;
		
		while(p<q)
		{
			Point currentPoint = (Point)myPointQueue[++p].clone();
			
			for(int i=0;i<4;i++)
			{
				Point aux = new Point(currentPoint.x + xV[i], currentPoint.y + yV[i]);
				
				if(myMaze[aux.x][aux.y] ==FREE)
				{
					myMaze[aux.x][aux.y]=myMaze[currentPoint.x][currentPoint.y]+1;
					
					myPointQueue[++q]=(Point)aux.clone();
					
					if(myMaze[aux.x][aux.y]>maxDistance)
					{
						maxDistance=myMaze[aux.x][aux.y];
						maxPoint = (Point)aux.clone();
					}
					
				}
				
			}
			
		}
		
		return maxPoint;
		
	}
	
	
	private void keepInBounds(PlayerModel player, MazeCanvas mazeCanvas, byte[][] maze)
	{
		int cellWidth = mazeCanvas.getCellWidth();
		int cellHeight = mazeCanvas.getCellHeight();
		
		int cI, cJ;
		
		int x1=player.getPosition().x, x2 = x1 + player.getBoundingBox().width;
		int y1=player.getPosition().y, y2 = y1 + player.getBoundingBox().height;
		
		
		Rectangle r = new Rectangle(0,0,mazeCanvas.getCellWidth(), mazeCanvas.getCellHeight());

		//
		 //Testing (x1,y1)
		{
			
			cJ= x1 / cellWidth;
			cI = y1 / cellHeight;
			
			
			
			if(maze[cI][cJ] == mazeGenerator.WALL)
			{
				
				r.x = cJ*cellWidth;
				r.y = cI*cellHeight;
				
				PlayerModel.pushBackPlayer(player,r);
			}
			
			
		}
		
		// (x2,y1)
		{
			
			x1=player.getPosition().x; x2 = x1 + player.getBoundingBox().width;
			y1=player.getPosition().y; y2 = y1 + player.getBoundingBox().height;
			
			cJ = x2/ cellWidth;
			cI = y1 / cellHeight;
			
			if(maze[cI][cJ] == mazeGenerator.WALL)
			{
				
				r.x = cJ*cellWidth;
				r.y = cI*cellHeight;
				
				PlayerModel.pushBackPlayer(player,r);
			}			
			
		}
		
		//(x1,y2)
		
		{
			x1=player.getPosition().x; x2 = x1 + player.getBoundingBox().width;
			y1=player.getPosition().y; y2 = y1 + player.getBoundingBox().height;
			
			cJ = x1 / cellWidth;
			cI = y2 / cellHeight;
			
			if(maze[cI][cJ] == mazeGenerator.WALL)
			{
				r.x = cJ*cellWidth;
				r.y = cI*cellHeight;
				
				PlayerModel.pushBackPlayer(player,r);
			}
		}
		
		
		//(x2,y2)
		{
			
			x1=player.getPosition().x; x2 = x1 + player.getBoundingBox().width;
			y1=player.getPosition().y; y2 = y1 + player.getBoundingBox().height;
			
			cJ = x2 / cellWidth;
			cI = y2 / cellHeight;
			
			
			if(maze[cI][cJ] == mazeGenerator.WALL)
			{
				
				r.x = cJ*cellWidth;
				r.y = cI*cellHeight;
				
				PlayerModel.pushBackPlayer(player,r);				

			}
		}
	}
	
}
