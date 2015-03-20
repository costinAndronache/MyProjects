package mazeGameDemo;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.image.BufferedImage;

public class MazeCanvas {
	
	int  cellWidth, cellHeight;
	Color colorFree, colorWall;
	
	byte charFree, charWall;
	
	byte[][] mazeMatrix;
	
	

	
	public MazeCanvas()
	{

		
		colorFree = Color.GRAY;
		colorWall = Color.BLACK;
		
		charFree = 'o'; // space
		charWall = 'x';
		
		cellWidth = cellHeight = 16;
		
		mazeMatrix = null;
		
		
		
	}
	
	
	public void setMazeToDisplay(byte[][] mazeMatrix)
	{
		this.mazeMatrix = mazeMatrix;
	}
	
	
	
	public void paint(Graphics g)
	{
		if(mazeMatrix!=null)
		{
			
			for(int i=0;i<mazeMatrix.length;i++)
				for(int j=0;j<mazeMatrix[i].length;j++)
				{
					Color displayColor = mazeMatrix[i][j]==charWall?colorWall:colorFree;
					
					g.setColor(displayColor);
					g.fillRect(j*cellWidth, i*cellHeight, cellWidth, cellHeight);
					
					
				}
			
			//System.out.println("called mazeCanvas paint");
		}
	}
	

	

	public void setCharFree(byte c)
	{
		charFree = c;
	}
	
	public void setCharWall(byte c)
	{
		charWall = c;
	}
	

	
	public void setCellWidth(int cellWidth)
	{
		this.cellWidth = cellWidth;
	}
	
	public void setCellHeight(int cellHeight)
	{
		this.cellHeight = cellHeight;
	}
	
	public void setColorFree(Color colorFree)
	{
		this.colorFree = colorFree;
	}
	
	public void setColorWall(Color colorWall)
	{
		this.colorWall = colorWall;
	}
	
	
	
	public Color getColorFree()
	{
		return colorFree;
	}
	
	public Color getColorWall()
	{
		return colorWall;
	}
	
	public int getCellHeight()
	{
		return cellHeight;
	}
	
	public int getCellWidth()
	{
		return cellWidth;
	}
	

	
}

