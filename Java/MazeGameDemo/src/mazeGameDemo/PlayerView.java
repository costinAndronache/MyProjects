package mazeGameDemo;

import java.awt.Graphics;
import java.awt.geom.AffineTransform;
import java.awt.image.AffineTransformOp;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class PlayerView {

	public final static int LEFT = 1;
	public  final static int RIGHT = 2;
	public static final int DOWN=0;
	public static final int UP=3;
	
	public AnimationInfo animInfo;
	PlayerModel playerModel;
	
	
	public PlayerView(String imagePath, PlayerModel playerModel)
	{
		BufferedImage image = null;
		try {
			 image = ImageIO.read(new File(imagePath));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		BufferedImage[][] spriteImages = new BufferedImage[4][3];
		
	
		if(image!=null)
		
		{for(int i=0;i<=3;i++)
			for(int j=0;j<=2;j++)	
				spriteImages[i][j] = image.getSubimage(j*16, i*16, 14, 16);
		


		
		
		}
				
			
		this.playerModel = playerModel;
		//this.movementInfo = movementInfo;
		
		animInfo = new AnimationInfo(spriteImages,0,0,5);
		
	}
	

	
	
	public void paint(Graphics g)
	{

		
		int x = playerModel.getPosition().x;
		int y = playerModel.getPosition().y;
		
		g.drawImage(animInfo.getCurrentSprite(),x,y,null);
		
		
		
	}
	
	
	public static BufferedImage getFlippedVertically(BufferedImage image)
	{
		  AffineTransform tx = AffineTransform.getScaleInstance(1, -1);
		   tx.translate(0, -image.getHeight(null));
		    AffineTransformOp op = new AffineTransformOp(tx, AffineTransformOp.TYPE_NEAREST_NEIGHBOR);
		    return op.filter(image, null);
		
	}
}
