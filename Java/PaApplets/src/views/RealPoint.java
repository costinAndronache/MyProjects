/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package views;

/**
 *
 * @author Costin
 */
public class RealPoint {
    
    private double x, y;
    
    public double getX()
    {
        return x;
    }
    
    public double getY()
    {
        return y;
    }
    
    public RealPoint(double x, double y)
    {
        this.x = x;
        this.y = y;
    }
    
    public RealPoint()
    {
        x = y = 0.0;
    }
    
    public void setX(double x)
    {
        this.x = x;
    }
    
    public void setY(double y)
    {
        this.y = y;
    }
    
}
