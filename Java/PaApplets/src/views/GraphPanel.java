/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package views;
import java.awt.*;
import java.util.*;

/**
 *
 * @author Costin
 */
public class GraphPanel extends javax.swing.JPanel {

    /**
     * Creates new form GraphPanel
     */
    public GraphPanel() {
        initComponents();
        
        this.scaleX = this.scaleY = 10.0;
        this.userDrawnPoints = new ArrayList<>();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                formMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 487, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 361, Short.MAX_VALUE)
        );
    }// </editor-fold>//GEN-END:initComponents

    private void formMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_formMouseClicked
        // TODO add your handling code here:
        
         
          RealPoint p = new RealPoint(evt.getPoint().getX(), evt.getPoint().getY());
         p = this.fixedPointFromMouse(p);
        
         this.userDrawnPoints.add(p);
        this.repaint();
        
    }//GEN-LAST:event_formMouseClicked


    // Variables declaration - do not modify//GEN-BEGIN:variables
    // End of variables declaration//GEN-END:variables

    private static int zoomFactor = 500;

    private int zoomLevel = 1;
    private java.util.List<RealPoint> userDrawnPoints;
    private java.util.List<Annotation> annotationList;
    
    private RealPoint[] points;
    private double scaleX, scaleY;
    
    
    public void setScale(double sX, double sY)
    {
        this.scaleX = sX;
        this.scaleY = sY;
    }
    
    public void clearAnnotations()
    {
        this.annotationList.clear();
    }
    
    public void clearDrawnPoints()
    {
        this.userDrawnPoints.clear();
    }
    
    public java.util.List<RealPoint> getListOfDrawnPoints()
    {
        return new ArrayList<>(userDrawnPoints);
    }
    
    public void setAnnotationList(java.util.List<Annotation> annList)
    {
        this.annotationList = annList;
        if(annList != null)
            this.repaint();
    }
    
    public void setPointsToDraw(RealPoint[] points)
    {
        this.points = points;
        
        if(this.points != null)
        {
            this.repaint();
        }
    }
    
    
    @Override
    public void paint(Graphics g)
    {
        super.paint(g);
        this.drawAxes(g);
       
        g.translate(this.getSize().width / 2, this.getSize().height / 2);
        this.plotPoints(points, g);
        this.plotDrawnPoints(g);
        this.drawAnnotationList(g);
    }

    
    private void drawAxes(Graphics g)
    {
        double middleX, middleY;
        Dimension d = this.getSize();
        
        middleX = d.getWidth() / 2;
        middleY = d.getHeight() / 2;
        
        g.setColor(Color.decode("#2C8503"));
        
        g.drawLine((int)middleX, 0, (int)middleX, (int)d.getHeight());
        
        g.setColor(Color.blue);
        
        g.drawLine(0, (int)middleY, (int)d.getWidth(), (int)middleY);
        
    }
    
    
    private void plotPoints(RealPoint[] points, Graphics g)
    {
        if(this.points == null)
        {
            return;
        }
        
        Color c = Color.decode("#033285");
        g.setColor(c);
        
        Dimension d = this.getSize();
        
        double sX = d.getWidth() / this.scaleX;
        double sY = d.getHeight() / this.scaleY;
        
        sY = sX;
        
        for(int i=0; i<points.length-1; i++)
        {
            
            if(points[i] == null || points[i+1] == null)
                continue;
            
            RealPoint p1 = points[i];
            RealPoint p2 = points[i+1];
            
            int x1 = (int)(points[i].getX() * sX);
            int x2 = (int)(points[i+1].getX() * sY);// * d.getWidth());
            
            int y1 = (int)(points[i].getY()* sX);// * d.getHeight());
            int y2 = (int)(points[i+1].getY() *sY);// * d.getHeight());

            g.drawRect(x1,-y1, 
                             1, 1);
            
            g.drawLine(x1, -y1, x2, -y2);
        }
        
    }
    
    private void plotDrawnPoints(Graphics g)
    {
        Dimension d = this.getSize();
        
        double sX = d.getWidth() / this.scaleX;
        double sY = d.getHeight() / this.scaleY;
        
        g.setColor(Color.red);
        
        for(RealPoint p : this.userDrawnPoints)
        {
            int x1 = (int)(p.getX() * sX);
            int y1 = (int)(p.getY() * sX);
            
            System.out.println("" + x1 + ", " + y1);
            
            g.drawRect(x1, -y1, 1, 1);
            
        }
        
    }
    
    private void drawAnnotationList(Graphics g)
    {
        System.out.println("calling drawing annotation");
        if(this.annotationList == null)
            return;
        
        System.out.println("drawing annotations" + this.annotationList.size());
          Dimension d = this.getSize();
        
          
        double sX = d.getWidth() / this.scaleX;
        double sY = d.getHeight() / this.scaleY;
        
        g.setColor(Color.BLACK);
        
        g.setFont(new Font("TimesRoman", Font.PLAIN, 10));
        
        for(Annotation ann : this.annotationList)
        {
            RealPoint p = ann.getPoint();
            int x1 = (int)(p.getX() * sX);
            int y1 = (int)(p.getY() * sX);
            
            g.drawString(ann.getKey(), x1, -y1);
            g.drawString(ann.getValue(), x1, -(y1+20));
            
            System.out.println(ann.getKey());
            
        }
    }
    
    public RealPoint fixedPointFromMouse(RealPoint p)
    {        
        Dimension d = this.getSize();
        double sX = d.getWidth() / this.scaleX;
        double sY = d.getHeight() / this.scaleY;
        double x1 = p.getX();
        double y1 = p.getY();
        
        System.out.println("Before " + x1 + " " + y1);
        
        x1 -= d.getWidth() / 2;
        y1 -= d.getHeight() / 2;
                
        System.out.println("After " + x1 + " " + (-y1));
        
        x1 = x1 / sX;
        y1 = y1 / sX;
        

       return new RealPoint(x1, -y1);
    }
    
    
    public RealPoint getNormalizedPointFrom(RealPoint p)
    {
         Dimension d = this.getSize();
        double sX = d.getWidth() / this.scaleX;
        double sY = d.getHeight() / this.scaleY;
        double x1 = p.getX();
        double y1 = p.getY();
        
        x1 = x1 / sX;
        y1 = y1 / sX;
        
        return new RealPoint(x1, y1);
        
    }
    
    
    public void zoomIn()
    {
        this.zoomLevel ++;
        Dimension d = this.getSize();
        
        d.setSize(d.getWidth() + zoomFactor, d.getHeight() + zoomFactor);
        
        this.setPreferredSize(d);
        
    }
    
    public void zoomOut()
    {
        this.zoomLevel --;
        Dimension d = this.getSize();
        
        d.setSize(d.getWidth() - zoomFactor, d.getHeight() - zoomFactor);
        
        this.setPreferredSize(d);
    }
    
    public int getZoomLevel()
    {
        return this.zoomLevel;
    }
    
    public void setZoomLevel(int zoomLevel)
    {
        this.zoomLevel = zoomLevel;
        Dimension d = this.getSize();
        d.setSize(300 + (zoomFactor * zoomLevel), 300 + (zoomFactor * zoomLevel));
        this.setPreferredSize(d);
        
    }
    
}
