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
public class Annotation 
{
    String key, value;
    RealPoint point;
    
    public String getKey()
    {
        return key;
    }
    
    public String getValue()
    {
        return value;
    }
    
    public RealPoint getPoint()
    {
        return point;
    }
    
    public Annotation(String key, String value, RealPoint p)
    {
        this.key = key;
        this.value = value;
        this.point = p;
    }
    
}
