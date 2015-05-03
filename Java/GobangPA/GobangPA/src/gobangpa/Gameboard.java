/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package gobangpa;

/**
 *
 * @author Costinel
 */
public class Gameboard 
{
    private  int rows = 0;
    private  int columns = 0;
    private  CircleType[][] matrix = null;
    
    public Gameboard(int rows, int columns)
    {
        this.rows = rows;
        this.columns = columns;
        this.matrix = new CircleType[this.rows][this.columns];
        
        for(int i=0;i<this.rows; i++)
            for(int j=0; j<this.columns; j++)
                this.matrix[i][j] = CircleType.CircleTypeUndefined;
        
    }
    
    
    public boolean isCellFree(int i, int j)
    {
        return this.matrix[i][j] == CircleType.CircleTypeUndefined;
    }
    
    public void setCircleAt(CircleType circle, int i, int j) throws Exception
    {
        if(!this.isCellFree(i, j))
        {
            throw new Exception("setCircleAt: the position (i,j) is not free !");
        }
        
        this.matrix[i][j] = circle;
    }
    
    public CircleType[][] getMatrixRepresentation()
    {
        CircleType aMatrix[][] = new CircleType[this.rows][];
        
        for(int i=0; i<this.rows; i++)
        {
            CircleType myLine[] = this.matrix[i];
            aMatrix[i] = new CircleType[this.columns];
            System.arraycopy(myLine, 0, aMatrix[i], 0, this.columns);
        }
        
        return aMatrix;
    }
}
