package mazeGameDemo;

import java.awt.Rectangle;
import java.awt.image.BufferedImage;

public class AnimationInfo 
{
	
	private BufferedImage[][] sprites;
	int currentFrame;
	int currentLine;
	
	int waitTime;
	int currentTime;
	
	public AnimationInfo(BufferedImage[][] sprites, int currentFrame, int currentLine, int waitTime)
	{
		
		this.sprites = new BufferedImage[sprites.length][];
		
		for(int i=0;i<sprites.length;i++)
			this.sprites[i]=sprites[i].clone();
		
		this.currentFrame = currentFrame;
		this.currentLine = currentLine;
		
		this.waitTime = waitTime;
		
		currentTime = 0;
	}
	
	public  BufferedImage getCurrentSprite()
	{
		return sprites[currentLine][currentFrame];
	}
	
	public void stepInAnimation()
	{
		
		if(currentTime>=waitTime)
		{
			currentTime=0;
		
		currentFrame++;
		currentFrame%=sprites[currentLine].length;
		}
		else
			++currentTime;
	}
	
	public void changeLine(int newLine)
	{
		currentLine = newLine;
	}
	
	public void changeFrame(int newFrame)
	{
		currentFrame = newFrame;
	}
	
	public int getCurrentLine()
	{
		return currentLine;
	}
	
	public int getCurrentFrame()
	{
		return currentFrame;
	}
	
	
	

}
