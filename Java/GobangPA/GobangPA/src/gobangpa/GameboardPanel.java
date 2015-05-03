/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gobangpa;


import java.awt.*;

/**
 *
 * @author Costinel
 */

class DetectInfo
{
    public Rectangle r;
    public int i;
    public int j;
    
    public DetectInfo(Rectangle r, int i, int j)
    {
        this.r = r;
        this.i = i;
        this.j = j;
    }
    
}

public class GameboardPanel extends javax.swing.JPanel {

    /**
     * Creates new form GameboardPanel
     */
    public GameboardPanel() {
        initComponents();
        
        this.circleRadius = 15;
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        statusLabel = new javax.swing.JLabel();

        addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                formMouseClicked(evt);
            }
        });
        addMouseMotionListener(new java.awt.event.MouseMotionAdapter() {
            public void mouseMoved(java.awt.event.MouseEvent evt) {
                formMouseMoved(evt);
            }
        });

        statusLabel.setFont(new java.awt.Font("Tahoma", 1, 14)); // NOI18N
        statusLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        statusLabel.setText("STATUS");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(459, Short.MAX_VALUE)
                .addComponent(statusLabel)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(344, Short.MAX_VALUE)
                .addComponent(statusLabel)
                .addContainerGap())
        );
    }// </editor-fold>//GEN-END:initComponents

    private void formMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_formMouseClicked
       
        if(!this.userInteractionEnabled)
            return;
        
        DetectInfo di = this.getRectForPoint(evt.getPoint());
        if(di != null)
        {
            if(this.listener != null)
            {
                this.listener.gameboardPanelDidClickAt(this, di.i, di.j);
            }
        }
        
    }//GEN-LAST:event_formMouseClicked

    private void formMouseMoved(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_formMouseMoved
        // TODO add your handling code here:
        
        if(!this.userInteractionEnabled)
            return;
        
        DetectInfo di = this.getRectForPoint(evt.getPoint());
        if(di != null)
        {
            this.highlightRect = di.r;
                    this.repaint();

        }
    }//GEN-LAST:event_formMouseMoved

    public void presentWaitForOtherPlayer()
    {
        this.userInteractionEnabled = false;
        this.statusLabel.setText("Waiting for the other player");
    }
    
    
    public void presentWaitForInput()
    {
        this.userInteractionEnabled = true;
        this.statusLabel.setText("Your turn.");
    }
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel statusLabel;
    // End of variables declaration//GEN-END:variables

    private boolean userInteractionEnabled = true;
    private static final int offset = 10;
    
    private Rectangle highlightRect;
    
    private Gameboard gameBoard;
    private int circleRadius;
    
    private GameboardPanelListener listener;
    
    public void setGameboard(Gameboard g)
    {
        this.gameBoard = g;
       
        CircleType[][] m = g.getMatrixRepresentation();
    }
    
    public void setCircleRadius(int newRadius)
    {
        this.circleRadius = newRadius;
    }
    
    public void setListener(GameboardPanelListener listener)
    {
        this.listener = listener;
    }
    
    @Override
    public void paint(Graphics g)
    {
        super.paint(g);
        
        if(this.gameBoard == null)
            return;
   
        if(this.highlightRect != null)
        {
            Color cH = new Color((float)0.99, 0, 0, (float)0.30);
            g.setColor(cH);
            g.fillOval((int)this.highlightRect.getX(), (int)this.highlightRect.getY(), 
                       (int)this.highlightRect.getWidth(), (int)this.highlightRect.getHeight());
        }
        
        //1.Draw the lines
        g.setColor(Color.black);
        
        CircleType[][] matrix = this.gameBoard.getMatrixRepresentation();
        
        Dimension d = this.getSize();
        
        for(int i=0; i< matrix.length; i++)
        {
            g.drawLine(offset, offset + (i*2*this.circleRadius), matrix.length *2 * this.circleRadius - this.circleRadius,
                    offset+ (i*2*this.circleRadius));
        }
        
        for(int j=0; j<matrix[0].length; j++)
        {
            g.drawLine(offset + (j*2*this.circleRadius), offset, offset + (j*2*this.circleRadius),
                    matrix[0].length * 2 * this.circleRadius - this.circleRadius);
        }
        
        for(int i=0; i<matrix.length; i++)
        {
            for(int j=0; j<matrix[i].length; j++)
            {
                Color c;
                
                switch(matrix[i][j])
                {
                    case CircleTypeBlack:
                         c = Color.black;
                        break;
                    case CircleTypeWhite:
                        c = Color.white;
                        break;
                    default:
                        c = null;
                }
                
                if(c == null)
                    continue;
                
                g.setColor(c);
                
                g.fillOval(offset + (j*2*this.circleRadius) - this.circleRadius/2, offset + (i*2*this.circleRadius) 
                        - this.circleRadius/2,
                        this.circleRadius, this.circleRadius);
                
                
                
            }
        }
     
        
    }

    
    private DetectInfo getRectForPoint(Point p)
    {
        CircleType[][] matrix = this.gameBoard.getMatrixRepresentation();
        for(int i = 0; i< matrix.length; i++)
        {
            for(int j=0; j<matrix[i].length; j++)
            {
                
                Rectangle r = new Rectangle(offset + (j*2*this.circleRadius) - this.circleRadius/2, offset + (i*2*this.circleRadius) 
                        - this.circleRadius/2,
                        this.circleRadius, this.circleRadius);
                
                if(r.contains(p))
                {
                    return new DetectInfo(r, i, j);
                }
            }
        }
        return null;
    }
}
