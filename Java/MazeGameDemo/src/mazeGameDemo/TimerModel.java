package mazeGameDemo;

import java.util.concurrent.TimeUnit;

public class TimerModel {

	private long lastTime;
	
	public TimerModel()
	{
		lastTime = System.currentTimeMillis();
	}
	
	public long getElapsedTime()
	{
		return System.currentTimeMillis() - lastTime; 
	}
	
	public long getElapsedMinutes()
	{
		long delta = System.currentTimeMillis() - lastTime;
		
		return TimeUnit.MILLISECONDS.toMinutes(delta);
	}
	
	public long getElapsedSeconds()
	{
		long delta = System.currentTimeMillis() - lastTime;
		
		return TimeUnit.MILLISECONDS.toSeconds(delta)%60;
	}
	
	public void reset()
	{
		lastTime = System.currentTimeMillis();
	}
}
