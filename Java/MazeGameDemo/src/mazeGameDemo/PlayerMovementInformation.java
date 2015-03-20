package mazeGameDemo;



public class PlayerMovementInformation {

	
	private boolean movingLeft, movingRight, movingUp, movingDown;
	private MovingDirection lastMovingDirection;
	
	int velocityX, velocityY;
	
	public PlayerMovementInformation(int velocityX, int velocityY)
	{
		this.velocityX=velocityX;
		this.velocityY=velocityY;
		lastMovingDirection = MovingDirection.NULL;
		
	}
	
	
	public void moveLeft()
	{
		movingLeft=true;
		movingRight=false;
	}
	
	public void moveRight()
	{
		movingRight=true;
		movingLeft=false;
	}
	
	public void moveUp()
	{
		movingUp=true;
		movingDown=false;
	}
	
	public void moveDown()
	{
		movingDown=true;
		movingUp=false;
	}
	
	
	public boolean isMovingLeft()
	{
		return movingLeft;
	}
	
	public boolean isMovingRight()
	{
		return movingRight;
	}
	
	public boolean isMovingUp()
	{
		return movingUp;
	}
	
	public boolean isMovingDown()
	{
		return movingDown;
	}
	
	
	public int getVelocityX()
	{
		return velocityX;
	}
	
	public int getVelocityY()
	{
		return velocityY;
	}
	
	public void setMovingUp(boolean b)
	{
		movingUp = b;
	}
	
	public void setMovingDown(boolean b)
	{
		movingDown = b;
	}
	
	public void setMovingLeft(boolean b)
	{
		movingLeft= b;
	}
	
	public void setMovingRight(boolean b)
	{
		movingRight = b;
	}
	
	public boolean isMovingAtAll()
	{
		return movingLeft || movingRight || movingUp || movingDown ;
	}
	
}

