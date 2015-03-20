
import java.util.*;
import java.lang.*;
public class Lab1Ex1 {

	public static int kMaxLength = 32;
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		
		int[] theArray = null;
		if (args.length == 0 || args.length > kMaxLength) 
		{
			System.out.println("Usage: Lab1Ex1 n1 [n2 ...] max up to n" + kMaxLength);
			return;
		}
		
		if(args.length == 1)
		{
				int length = Integer.parseInt(args[0]);
				if(length > 32)
				{
					System.out.println("The size argument cannot exceed " + kMaxLength +" :( ...");
					return;
				}
				
				theArray = Lab1Ex1.generateRandomArrayWithSize(length);
				System.out.println("Your random array: ");
				for(int i=0; i<theArray.length; i++)
					System.out.print(theArray[i] + ", ");
		}
		else
		{
			theArray = Lab1Ex1.generateIntegerArrayFromArgs(args);
			
		}
		
		long start = System.currentTimeMillis();
		long maxValue = (int) (Math.pow(2, theArray.length));
		for(long arrangement = 0; arrangement <maxValue; arrangement++)
		{
			if (Lab1Ex1.thisArrangementIsGood(arrangement, theArray) == true)
			{
				System.out.println("Found a good arrangement: " + Lab1Ex1.generateSetsFromArrangement(arrangement, theArray));
				long stop = System.currentTimeMillis();
				System.out.println("Time passed: " + stop + " --- " + start);
				return;
			}
		}
		long delta = System.currentTimeMillis() - start;
		double seconds = (delta / 1000.);
		System.out.println("Time passed: " + seconds + " seconds.");
	}
	
	public static int[] generateIntegerArrayFromArgs(String[] args) throws NumberFormatException
	{
		int[] result = new int[args.length];
		
		for(int i=0; i<args.length; i++)
		{
			int aVal;
			try
			{
			aVal = Integer.parseInt(args[i]);
			result[i] = aVal;
			}
			catch(NumberFormatException ex)
			{
				System.out.println("Could not convert " + args[i] + " as a number.\n");
				return null;
			}
			
			if(aVal < 0)
			{
				throw new NumberFormatException("Only natural numbers allowed: " + aVal);
			}
		}
		
		return result;
	}
	
	
	public static int[] generateRandomArrayWithSize(int size) throws NumberFormatException
	{
		
		if(size < 0)
			throw new NumberFormatException("Size argument cannot be negative or zero");
		Random rn = new Random();
		int[] result = new int[size];
		for(int i=0; i<size; i++)
		{
			 int randomValue = rn.nextInt();
			 if(randomValue < 0)
				 randomValue = -randomValue;
			 
			result[i] = randomValue % 100;
			
		}
		
		return result;
	}
	
	public static boolean thisArrangementIsGood(long map, int[] array)
	{
		boolean result = false;
		int sumA = 0, sumB = 0;
		for(int i = 0; i < array.length; i++)
		{
			long mask = 1 << i;
			if( (mask & map) > 0)
			{
				sumB += array[i];
			}
			else
			{
				sumA += array[i];
			}
		}
		
		result = (sumA == sumB);
		return result;
	}
	
	public static ArrayList<ArrayList<Integer> > generateSetsFromArrangement(long map, int[] array)
	{
		ArrayList< ArrayList<Integer> > sets = new ArrayList< ArrayList<Integer> >();
		ArrayList<Integer> setA = new ArrayList<Integer>();
		ArrayList<Integer> setB = new ArrayList<Integer>();
		
		sets.add(setA);
		sets.add(setB);
		
		for(int i = 0; i < array.length; i++)
		{
			long mask = 1 << i;
			if( (mask & map) > 0)
			{
				setB.add(array[i]);
			}
			else
			{
				setA.add(array[i]);
			}
		}
		
		return sets;
	}
}
