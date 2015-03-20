package mazeGameDemo;

import java.awt.Button;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LastButton implements ActionListener {
	
	private Button source;
	
	public LastButton()
	{
		source = null;
	}
	
	public Button getLastButtonPressed()
	{
		return source;
	}
	
	public void reset()
	{
		source = null;
	}
	
	@Override
	public void actionPerformed(ActionEvent e)
	{
		source = (Button)e.getSource();
	}
}
