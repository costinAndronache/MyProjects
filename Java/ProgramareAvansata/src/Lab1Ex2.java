
public class Lab1Ex2 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		if(args.length != 1)
		{
			System.out.println("Usage: Lab1Ex2 string");
			return;
		}
		
		char[][] matrix = Lab1Ex2.buildMatrixFromString(args[0]);
		int n = args[0].length() /4;
		String result = Lab1Ex2.getStringFromMatrix(matrix, n);
		System.out.println("The string is: " + result);
	}
	
	public static char[][] buildMatrixFromString(String arg) throws NumberFormatException
	{
		if(arg.length() % 2 != 0)
			throw new NumberFormatException("The string length must be even! : " + arg + " of length: " + arg.length());
		
		int n = arg.length() / 4;
		char[][] result = new char[n][n];
		
		for(int i=0; i<n; i++)
			{
			   for(int j = 0; j<n; j++)
				 {
				   result[i][j] = arg.charAt(i * n + j);
				   System.out.print(result[i][j]);
				 }
			   System.out.println("");
			}
		
		return result;
	}
	
	public static String getStringFromMatrix(char[][] matrix, int n)
	{
		StringBuilder result = new StringBuilder();
		
		for(int i=0; i<=n-1; i++)
		{
			int j = (n-1) - i;
			result.append(matrix[i][j]);
		}
		
		for(int i=0; i<=n-1; i++)
			result.append(matrix[i][i]);
		
		return result.toString();
	}
}
