package mazeGameDemo;

import java.awt.Font;
import java.awt.Graphics;

public class TimerView {

	TimerModel timerModel;
	
	Font font;
	
	
	public TimerView(TimerModel timerModel, Font font)
	{
		this.timerModel = timerModel;
		this.font = font;
	}
	
	public void paint(Graphics g, int x,int y)
	{
		
		long minutes = timerModel.getElapsedMinutes();
		long seconds = timerModel.getElapsedSeconds();
		
		g.setFont(font);
		g.drawString("Time passed  " + minutes + " : " + seconds, x, y);
	}
	
	
}
