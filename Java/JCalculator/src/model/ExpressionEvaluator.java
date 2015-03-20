package model;

import java.util.LinkedList;
import java.util.Stack;

public class ExpressionEvaluator {

	
	
	
	public ExpressionEvaluator()
	{
	}
	
	
	
	private static void prepareForTokenizing(StringBuffer sb)
	{
		int i=0;
		
		while(i<sb.length())
		{
			if( isToBeSpacefied(sb.charAt(i)))
			{
				sb.insert(i, ' ');
				sb.insert(i+2, ' ');
				i=i+2;
			}
			
			if (sb.charAt(i) == ',')
				sb.setCharAt(i, ' ');
			
			i++;
		}
	}
	
	private static boolean isToBeSpacefied(char c)
	{
		return ( c=='+' || c=='/' || c=='*' || c=='-' || c==')' || c=='(' || c=='%');
	}
	
	
	private static boolean isNumber(String s)
	{
		try
		{
			Float.parseFloat(s);
			return true;
		}
		catch(NumberFormatException e)
		{
			return false;
		}
	}
	
	
	
	public static String getPostfixFromInfix(String infix)
	{
		StringBuffer tokenizer = new StringBuffer(infix);
		
		prepareForTokenizing(tokenizer);
		String[] tokens = tokenizer.toString().split("[ ]+");
		
		StringBuffer sb = new StringBuffer();
		
		Stack<Integer> intStack = new Stack<Integer>();
		
	    LinkedList<String> operatorStack = new LinkedList<String>();//, finalString = new ArrayList<String>();
	    
	    
	    for(int i=0;i<tokens.length;i++)
	    {
	    	if(isNumber(tokens[i]))
	    		sb.append(" " + tokens[i]);
	    	else
	    		if ( tokens[i].equals("(") )
	    			intStack.push(operatorStack.size()-1);
	    		
	    		else
	    			if( tokens[i].equals(")"))
	    			{
	    				int stopPos = intStack.pop();
	    				
	    				while(operatorStack.size()-1 > stopPos)
	    				{
	    					sb.append(" " + operatorStack.removeLast());
	    				}

	    				ExpressionTokenFactory tkFactory = ExpressionTokenFactory.getInstance();
	    				ExpressionToken tokTop = tkFactory.getToken(operatorStack.peekLast());
	    				
	    				if(tokTop!=null && tokTop.precedence()==3)
	    					sb.append(" " + operatorStack.removeLast());
	    				
	    				
	    			}
	    			else
	    			{
	    				if(operatorStack.size()>0)
	    				{
	    				ExpressionTokenFactory tkFactory = ExpressionTokenFactory.getInstance();
	    				ExpressionToken tokTop = tkFactory.getToken(operatorStack.peekLast());
	    				ExpressionToken tokToAdd = tkFactory.getToken(tokens[i]);
	    				
	    				while( tokTop!=null && tokTop.precedence()>tokToAdd.precedence() )
	    				{
	    					boolean b;
	    					if(intStack.size()>0)
	    					b=(operatorStack.size()-1 != intStack.peek());
	    					else
	    						b=true;
	    					
	    					if(b)
	    					{sb.append(" " + operatorStack.removeLast());
	    					tokTop = tkFactory.getToken(operatorStack.peekLast());}
	    					
	    				}
	    				
	    				
	    				
	    				
	    			}
	    				operatorStack.addLast(tokens[i]);
	    	
	                   }
	    	}
	    
	    
	    while(operatorStack.size()>0)
	    	sb.append(" " + operatorStack.removeLast());
	    
		return new String(sb.toString());
		
	}
	
	private float evaluatePostfix(String postfix)
	{
		
		String[] tokens = postfix.split("[ ]+");
		Stack<Float> resultStack = new Stack<Float>();
		
		ExpressionTokenFactory tkf= ExpressionTokenFactory.getInstance();
		ExpressionToken tkn;
		
		for(int i=1;i<tokens.length;i++)
			if(isNumber(tokens[i]))
				resultStack.push(Float.parseFloat(tokens[i]));
			else
			{
				tkn = tkf.getToken(tokens[i]);
				tkn.apply(resultStack);
			}
		
		return resultStack.pop();
	}
	
	public float evaluateExpression(String expression)
	{
		return evaluatePostfix(getPostfixFromInfix(expression));
	}
	

}
