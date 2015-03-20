package mazeGameDemo;

import java.awt.Point;
import java.util.Stack;
import java.util.Random;

public class MazeGenerator {

	public static final byte WALL = 'x';
	public static final byte FREE = 'o';
	
	private static int NUMBER_OF_AREAS = 4;
	private static int CELLS_PER_AREA = 6;
	
	Random r;
	
	static final Point[] directionsToDig = { new Point(-1,0), new Point(1,0), new Point(0,-1), new Point(0,1)};
	
	
	
	static final Point[][] cellsToCheck =
		{
		
		{  new Point(-1,-1), new Point(-2,-1), new Point(-1,0), new Point(-2,0), new Point(-1,1), new Point(-2,1) },
		{  new Point(1,-1), new Point(2,-1), new Point(1,0), new Point(2,0), new Point(1,1), new Point(2,1) },
		{  new Point(-1,-1),  new Point(-1,-2), new Point(0,-1), new Point(0,-2), new Point(1,-1), new Point(1,-2) },
		{  new Point(-1,1), new Point(-1,2), new Point(0,1), new Point(0,2), new Point(1,1), new Point(1,2) }  
		    
		};
	
	private int mazeWidth, mazeHeight;
	
	Stack<Point> pointStack;
	Point lastCell;
	
	byte[][] mazeMatrix;
	
	
	
	public void reset(int mazeWidth, int mazeHeight)
	{
		this.mazeHeight=mazeHeight;
		this.mazeWidth=mazeWidth;
		
		mazeMatrix = new byte[mazeHeight+4][mazeWidth+4];
		
		r = new Random();
		
		
		
		for(int i=1;i<=mazeHeight+2;i++)
			for(int j=1;j<=mazeWidth+2;j++)
				try{
				mazeMatrix[i][j]=WALL;
				}
				catch(ArrayIndexOutOfBoundsException e)
				{
					System.out.println(i + " --i and j--- " + j);
					System.out.println("and the matrix's dimensions: " + mazeMatrix.length + " x " + mazeMatrix[0].length);
					System.exit(0);
				}
		
		for(int i=0;i<mazeHeight+4;i++)
			mazeMatrix[i][0]=mazeMatrix[i][mazeWidth+3]=FREE;
		
		
		for(int j=0;j<mazeWidth+4;j++)
			mazeMatrix[0][j]=mazeMatrix[mazeHeight+3][j]=FREE;
	}
	
	
	
	public  MazeGenerator(int mazeWidth, int mazeHeight)
	{
		reset(mazeWidth,mazeHeight);
	}
	
	
	private int[] getAvailableAreas(Point whatCell)
	{
		int numberOfGoodAreas = 0;
		
		boolean[] areaMark = new boolean[4];
		
		for(int i=0;i<NUMBER_OF_AREAS;i++)
		{
			
			boolean isAreaGood = true;
			
				for(int j=0;j<CELLS_PER_AREA;j++)
				{
					
					int x = whatCell.x + cellsToCheck[i][j].x;
					int y = whatCell.y + cellsToCheck[i][j].y;

					

					try{
					if(mazeMatrix[x][y]!=WALL)
						isAreaGood = false;
					}
					catch(ArrayIndexOutOfBoundsException e)
					{
						System.out.println("The current cell is : " + whatCell);
						System.out.println("The cell to check is: " +cellsToCheck[i][j]);
						
						System.out.println("The stack is: " +pointStack);
						
						System.exit(0);
					}
				}
				

				if( isAreaGood)
				{
					++numberOfGoodAreas;
				}
				
			
				areaMark[i] = isAreaGood;
				
				
		}
		
		if(numberOfGoodAreas == 0)
		{
			return null;
		}
		
		int[] areas = new int[numberOfGoodAreas];
		
		int k=0;
		
		for(int i=0;i<NUMBER_OF_AREAS;i++)
			if(areaMark[i] == true)
			{
				areas[k] = i;
				k++;
			}
		
		return areas;
			
		
	}
	
	public void step()
	{
		
		Point currentCell = (Point)pointStack.peek().clone();
		
		int[] areas = getAvailableAreas(currentCell);
		
		if(areas != null)
		{
			int areaIndex = r.nextInt();
			 if(areaIndex<0)
				 areaIndex = -areaIndex;
			 
			 areaIndex = areaIndex % areas.length;
			
			currentCell.x+=directionsToDig[areas[areaIndex]].x;
			currentCell.y+=directionsToDig[areas[areaIndex]].y;
			
			mazeMatrix[currentCell.x][currentCell.y] = FREE;
			
			pointStack.push(currentCell);
		}
		else
			pointStack.pop();
		
		
		
		
	}
	
	public void initialize()
	{
		
		
		Point p =new Point();
		
		p.x = r.nextInt();
		p.y = r.nextInt();
		
		if(p.x<0)
			p.x = -p.x;
		
		if(p.y<0)
			p.y = -p.y;
		
		p.x = (p.x % (mazeHeight-1) )+2;
		
		p.y = (p.y % (mazeWidth-1)) +2;
		
		pointStack = new Stack<Point>();
		
		pointStack.push(p);
		
		mazeMatrix[p.x][p.y]=FREE;
	}
	
	public boolean isDone()
	{
		return pointStack.isEmpty();
	}
	
	public byte[][] getSnapshot()
	{
		byte[][] snapshot = new byte[mazeHeight+2][mazeWidth+2];
		
		for(int i=1;i<=mazeHeight+2;i++)
			for(int j=1;j<=mazeWidth+2;j++)
				snapshot[i-1][j-1]=mazeMatrix[i][j];
		
		return snapshot;
	}
	
	public byte[][] getFinalResult()
	{
		
		while(!pointStack.isEmpty())
			step();
		
		return getSnapshot();
	}
	
	
	
	public void reset()
	{
		reset(mazeWidth,mazeHeight);
		
	}
	
	
	public int getWidth()
	{
		if(mazeMatrix != null)
		{
			return mazeMatrix[0].length;
		}
		else
			return 0;
	}
	
	public int getHeight()
	{
		if(mazeMatrix != null)
		{
			return mazeMatrix.length;
		}
		else
			return 0;	
	}
	
}
