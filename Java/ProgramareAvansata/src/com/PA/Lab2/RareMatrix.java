package com.PA.Lab2;


import java.util.*;

/**
 * Declares a class that efficiently handles the most common
 * operations on matrices (e.g addition, transpose) when these
 * are sparse(i.e most values are 0) by only memorizing the indices
 * and values different from 0. 
 * @author Costinel
 *
 */

public class RareMatrix 
{
	private static double epsilon = 0.0001;
	
	private Map<Integer, Map<Integer, Double>> matrixMap;
	int numOfLines, numOfColumns;
	
	
	RareMatrix(double[][] matrix, int lines, int columns)
	{
		this.commonInit();
		this.numOfColumns = columns;
		this.numOfLines = lines;
		
		for(int i=0; i<lines; i++)
		{
			for(int j=0; j<columns; j++)
			{
				if(matrix[i][j] != 0)
				{
					Map<Integer, Double> map = this.getMapOrCreateForLine(i);
					map.put(j, matrix[i][j]);
				}
			}
		}
		
	}
	
	RareMatrix(double[] arrayMatrix, int lines, int columns)
	{
		this.commonInit();
		this.numOfLines = lines;
		this.numOfColumns = columns;
		
		for(int i=0; i<lines; i++)
		{
			for(int j=0; j<columns; j++)
			{
				double val = arrayMatrix[i*lines+j];
				if(val != 0)
				{
					Map<Integer, Double> map = this.getMapOrCreateForLine(i);
					map.put(j, val);
				}
			}
		}
	}
	
	RareMatrix(int lines, int columns)
	{
		this.commonInit();
		this.numOfLines = lines;
		this.numOfColumns = columns;
	}
	
	public void setValue(int i, int j, double value) 
	{
		this.checkAndThrow("setValue", i, j);
		Map<Integer, Double> map = this.getMapOrCreateForLine(i);
		map.put(j, value);
	}
	
	public double getValue(int i, int j)
	{
		double result = 0.0;
		this.checkAndThrow("getValue", i, j);
		Map<Integer, Double> map = this.matrixMap.get(i);
		 if(map == null)
			 return result;
		 
		 Double unboxed = map.get(j);
		 if(unboxed == null)
			 return result;
		 else
			 return unboxed;
	}
	
	public int getNumberOfColumns()
	{
		return this.numOfColumns;
	}
	
	public int getNumberOfLines()
	{
		return this.numOfLines;
	}
	
	/**
	 * Multiplies the current matrix with the scalar.
	 * The current object is affected.
	 * @param scalar
	 */
	
	public void multiplyWithScalar(double scalar)
	{
		for(int i=0; i<this.numOfLines; i++)
		{
			Map<Integer, Double> lineMap = this.matrixMap.get(i);
			if(lineMap != null)
			{
				for(Map.Entry<Integer, Double> entry : lineMap.entrySet())
				{
					int copyInt = entry.getKey();
					double copyDouble = entry.getValue();
					lineMap.put(copyInt, copyDouble*scalar);
				}
			}
		}
		
	}
	
	/**
	 * Returns a new RareMatrix object representing 
	 * the product of this matrix with the parameter.
	 * This does not affect the current object.
	 * @param aMatrix
	 * @return
	 */
	
	public RareMatrix multiplyWithRareMatrix(RareMatrix aMatrix)
	{
		RareMatrix result= null;
		
		if(this.numOfColumns != aMatrix.numOfLines)
		{
			return result;
		}
		
		result = new RareMatrix(this.numOfLines, aMatrix.numOfColumns);
		Map<Integer, Map<Integer, Double>> hisColumnIndexedMap = aMatrix.getColumnIndexedMap();
		
		for(int i=0; i<this.numOfLines; i++)
		{
			Map<Integer, Double> myLineMap = this.matrixMap.get(i);
			if(myLineMap != null)
			{
					for(int j=0; j<aMatrix.numOfColumns; j++)
					{
						Map<Integer, Double> hisColumnMap = hisColumnIndexedMap.get(j);
						
						if(hisColumnMap != null)
						{
							double totalSum = 0.0;
							for(Integer myKey : myLineMap.keySet())
							{
								Double dRef = hisColumnMap.get(myKey);
								if(dRef != null)
								{
									totalSum += dRef * myLineMap.get(myKey);
								}
							}
							
							if(totalSum != 0.0)
							{
								result.setValue(i, j, totalSum);
							}
						}
					}
			}
			
				
			
		}
		
		return result;
	}
	
	/**
	 * Returns a RareMatrix object representing the 
	 * transpose of the current object. This does not affect
	 * the current object.
	 * @return
	 */
	
	public RareMatrix getTranspose()
	{
		RareMatrix r = new RareMatrix(this.numOfColumns, this.numOfLines);
		
		for(int i=0; i<this.numOfLines; i++)
		{
			for(int j=0; j<this.numOfColumns; j++)
			{
				double d = this.getValue(i, j);
				if(d != 0.0)
				{
					r.setValue(j, i, d);
				}
			}
		}
		
		return r;
	}
	
	/**
	 * Returns a new object representing the sum of this matrix
	 * with the argument. This method does not affect the current object.
	 * @param aMatrix
	 * @return RareMatrix
	 */
	
	public RareMatrix addWithRareMatrix(RareMatrix aMatrix)
	{
		RareMatrix result = null;
		
		if(this.numOfColumns != aMatrix.numOfColumns || this.numOfLines != aMatrix.numOfLines)
			{
			return result;
			}
		
		result = new RareMatrix(this.numOfLines, this.numOfColumns);
		
		for(int i=0; i<this.numOfLines; i++)
		{
			Map<Integer, Double> myMap, hisMap, resultMap;
			myMap = this.matrixMap.get(i);
			hisMap = aMatrix.matrixMap.get(i);
			
			if(myMap == null && hisMap != null)
			{
				{
					resultMap = new HashMap<Integer, Double>();
					//make a deep copy of hisMap
					RareMatrix.deepCopy(hisMap, resultMap);
					result.matrixMap.put(i, resultMap);
				}
			}
			else if(myMap != null && hisMap == null)
			{
				if(hisMap == null)
				{
					resultMap = new HashMap<Integer, Double>();
					//make a deep copy of myMap
					RareMatrix.deepCopy(myMap, resultMap);
					result.matrixMap.put(i, resultMap);
				}
			}
			else
				if(myMap != null && hisMap != null)
			{
					resultMap = new HashMap<Integer, Double>();
					RareMatrix.deepCopy(myMap, resultMap);
					Set<Integer> myKeysSet = myMap.keySet();
					
					for(Integer i1 : myKeysSet)
					{
						Double hisDouble = hisMap.get(i1);
						if(hisDouble != null)
						{
							double dCopy = hisDouble.doubleValue();
							Double myDouble = resultMap.get(i1);
							myDouble += dCopy;
							resultMap.put(i1, myDouble);
						}
					}
					
					Set<Integer> hisKeysSet = hisMap.keySet();
					for(Integer i2 : hisKeysSet)
					{
						Double d = resultMap.get(i2);
						if(d == null)
						{
							Double hisD = hisMap.get(i2);
							double dCopy = hisD.doubleValue();
							resultMap.put(i2, dCopy);
						}
					}
					
					result.matrixMap.put(i, resultMap);
			}
			
		}
		
		return result;
	}
	
	/**
	 * Creates a RareMatrix object with the the specified number of non-zero values,
	 * residing in the current interval (a, b). 
	 * @param numOfValues number of non-zero values
	 * @param a
	 * @param b
	 * @return
	 */
	
	public static RareMatrix generateRandomRareMatrix(int numOfValues, double a, double b)
	{
		RareMatrix result = new RareMatrix(numOfValues, numOfValues);
		
		Random r = new Random();
		double diff = b - a;
		for(int i=1; i<= numOfValues; i++)
		{
			boolean keepGoing = true;
			while(keepGoing)
			{
				int lineIndex = r.nextInt(numOfValues);
				int colIndex = r.nextInt(numOfValues);
				
				double d = result.getValue(lineIndex, colIndex);
				if(d == 0.0)
				{
					keepGoing = false;
					double val = (r.nextDouble() + 0.1) * diff + a;
					result.setValue(lineIndex, colIndex, val);

				}
			}

			

		}
		
		return result;
	}
	
	@Override
	public String toString()
	{
		String result = "";
		
		for(int i=0; i<this.numOfLines; i++)
		{
			Map<Integer, Double> lineMap = this.matrixMap.get(i);
			if(lineMap == null)
			{
				for(int j=0; j<this.numOfColumns; j++)
					result = result + " 0";
			}
			else
			{
				for(int j=0; j<this.numOfColumns; j++)
				{
					Double dRef = lineMap.get(j);
					if(dRef == null)
					{
						result = result +" 0.0";
					}
					else
					{
						result = result + " " + dRef;
					}
				}
					}
			
				result = result + "\n";
		}
		
		return result;
	}
	
	@Override
	public boolean equals(Object o)
	{
		if ( ! (o instanceof RareMatrix))
		{
			return false;
		}
		
		RareMatrix him = (RareMatrix)o;
		
		if(him.numOfColumns != this.numOfColumns || him.numOfLines != this.numOfLines)
		{
			return false;
		}
		
		for(int i=0; i<this.numOfLines; i++)
		{
			Map<Integer, Double> myLineMap, hisLineMap;
			myLineMap = this.matrixMap.get(i);
			hisLineMap = him.matrixMap.get(i);
			
			if(myLineMap == null || hisLineMap == null)
			{
				return false;
			}
			
			if(myLineMap.size() != hisLineMap.size())
			{
				return false;
			}
			
			for(Integer myKey : myLineMap.keySet())
			{
				double myVal = myLineMap.get(myKey);
				Double dRef = hisLineMap.get(myKey);
				
				if(dRef == null || dRef != myVal)
				{
					return false;
				}
			}
		}
		
		return true;
	}
	
	@Override
	public int hashCode()
	{
		int result = 0;
		
		for(Map.Entry<Integer, Map<Integer, Double>> entry : this.matrixMap.entrySet())
		{
			double sumOfLine = 0.0;
			for(Map.Entry<Integer, Double> inEntry : entry.getValue().entrySet())
			{
				sumOfLine += inEntry.getValue() * inEntry.getKey();
			}
			
			sumOfLine *= entry.getKey() + 1;
			
			result += sumOfLine;
		}
		
		return result;
	}
	
	private void checkAndThrow(String method, int i, int j)  throws IndexOutOfBoundsException
	{
		if(i<0 || i>numOfLines-1)
			throw new IndexOutOfBoundsException("In " + method + " i  is out of bounds, lines = " + numOfLines);
		
		if(j<0 || j>numOfColumns-1)
			throw new IndexOutOfBoundsException("In " + method + "j is out of bounds, columns = " + numOfColumns);
	}
	
	private Map<Integer, Map<Integer, Double>> getColumnIndexedMap()
	{
		Map<Integer, Map<Integer, Double> > resultMap = new HashMap<Integer, Map<Integer, Double>>();
		
		for(int j=0; j<this.numOfColumns; j++)
		{
			Map<Integer, Double> colMap = new HashMap<Integer, Double>();
			 for(int i=0; i<this.numOfLines; i++)
			 {
				 Map<Integer, Double> lineMap = this.matrixMap.get(i);
				 if(lineMap != null)
				 {
					 Double dRef = lineMap.get(j);
					 if(dRef != null)
					 {
						 colMap.put(i, dRef);
					 }
				 }
			 }
			 
			 if(colMap.size() > 0)
			 {
				 resultMap.put(j, colMap);
			 }
				 
		}
		
		return resultMap;
	}
	
	private void commonInit()
	{
		this.numOfColumns = this.numOfLines = 0;
		this.matrixMap = new HashMap<Integer, Map<Integer, Double>>();
	}

	
	private Map<Integer, Double> getMapOrCreateForLine(int line)
	{
		Map<Integer, Double> map = this.matrixMap.get(line);
		if(map == null)
		{
			map = new HashMap<Integer, Double>();
			this.matrixMap.put(line, map);
		}
		return map;
	}
	
	private static void deepCopy(Map<Integer, Double> source, Map<Integer, Double> dest)
	{
		for(Map.Entry<Integer, Double> entry : source.entrySet())
		{
			int copyInt = entry.getKey();
			double copyDouble = entry.getValue();
			dest.put(copyInt, copyDouble);
		}
	}
	
	public static void main(String[] args) {
		
		RareMatrix r1, r2;
		double[] arr1 = {1, 2, 3};
		double[] arr2 = {2, 1, 3, 3, 3, 2, 4, 1, 2};
		
		r1 = new RareMatrix(arr2, 3, 3);
		r2 = new RareMatrix(arr2, 3, 3);
		
		RareMatrix r3 = r1.multiplyWithRareMatrix(r2);
		
		System.out.println(r1);
		System.out.println("-------------");
		System.out.println(r1.equals(r2));
		System.out.println(r1.hashCode() + " ---- " + r2.hashCode());
		
	}
}
