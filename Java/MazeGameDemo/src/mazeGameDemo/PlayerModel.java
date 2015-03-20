package mazeGameDemo;


import java.awt.*;


public class PlayerModel {

	private Point position;
	private Rectangle boundingBox;
	
	private boolean movedX, movedY;
	public PlayerModel(Point position, Dimension dimension)
	{
		this.position=(Point)position.clone();
		
		boundingBox = new Rectangle(position.x,position.y, dimension.width, dimension.height);
		 //boundingBox.setBounds(position.x,position.y, dimension.width, dimension.height);
		
		movedX = movedY = false;
	}
	
	public Point getPosition()
	{
		return (Point)position.clone();
	}
	
	public Rectangle getBoundingBox()
	{
		return (Rectangle)boundingBox.clone();
	}
	
	public boolean hasMovedX()
	{
		return movedX;
	}
	
	public boolean hasMovedY()
	{
		return movedY;
	}
	
	private static int modul(int x)
	{
		if(x<0)
			return -x;
		return x;
	}
	
	public static void pushBackPlayer(PlayerModel player, Rectangle r)
	{
		
		int xs=player.getPosition().x, xj = xs + player.getBoundingBox().width;
		int ys=player.getPosition().y, yj = ys + player.getBoundingBox().height;
		
		Point amin, amax, bmin, bmax, mtd;
		
		amin = new Point(xs,ys);
		amax = new Point(xj,yj);
		
		
		
		int rxs=r.x, rxj = rxs + r.width;
		int rys=r.y, ryj = rys + r.height;
		
		bmin = new Point(rxs, rys);
		bmax = new Point(rxj, ryj);
		
		
		mtd = new Point(0,0);
		int left, right,bottom, top;
		
		
		left=bmin.x-amax.x;
	    right=bmax.x-amin.x;
	    top=bmin.y-amax.y;
	    bottom=bmax.y-amin.y;

	    if(modul(left)<right)
	    mtd.x=left;
	    else
	    mtd.x=right;

	    if(modul(top)<bottom)
	    mtd.y=top;
	    else
	    mtd.y=bottom;

	    if(modul(mtd.x)<modul(mtd.y))
	    mtd.y=0;
	    else
	    mtd.x=0;
		
		player.moveX(mtd.x);
		player.moveY(mtd.y);
		
	}
	
	public void moveX(int byHowMuch)
	{
		movedX=true;
		movedY=false;
		
		position.x+=byHowMuch;
		boundingBox.x+=byHowMuch;
		
	}
	
	
	
	
	public void moveY(int byHowMuch)
	{
		movedY=true;
		movedX=false;
		
		position.y+=byHowMuch;
		boundingBox.y+=byHowMuch;
	}
	
	
	public Dimension getDimension()
	{
		return new Dimension(boundingBox.width,boundingBox.height);
	}
	
	public void setX(int newX)
	{
		
		position.x=newX;
		boundingBox.x=newX;
	}
	
	public void setY(int newY)
	{
		position.y=newY;
		boundingBox.y= newY;
	}
	
}
