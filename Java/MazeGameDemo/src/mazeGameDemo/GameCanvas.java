package mazeGameDemo;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.image.BufferedImage;

public class GameCanvas extends Canvas 
{
	
	BufferedImage bufferedImage;
	Graphics graphicsImage;
	
	public GameCanvas(int width, int height)
	{
		super();
		super.setBounds(0,0,width,height);
		
		bufferedImage = new BufferedImage(width,height,BufferedImage.TYPE_INT_ARGB);
		graphicsImage = bufferedImage.getGraphics();
		
	}
	
	
	public Graphics getGraphicsToDrawOn()
	{
		return graphicsImage;
	}
	
	@Override
	public void paint(Graphics g)
	{
		//System.out.println("Called gameCanvas paint");

		g.drawImage(bufferedImage,0,0,null);
		
		
		//graphicsImage.setColor(Color.white);
		//graphicsImage.fillRect(0, 0, getWidth(), getHeight());
		
		
	}
	
	@Override
	public void update(Graphics g)
	{
		paint(g);
		
	}
	
	@Override
	public void setBounds(int x,int y,int width,int height)
	{
		super.setBounds(x, y, width, height);
		
		bufferedImage = new BufferedImage(width,height,BufferedImage.TYPE_INT_ARGB);
		graphicsImage = bufferedImage.getGraphics();
	}
	
	
	public void clear()
	{
		graphicsImage.setColor(Color.WHITE);
		graphicsImage.fillRect(0, 0, getWidth(), getHeight());
	}
	

}
