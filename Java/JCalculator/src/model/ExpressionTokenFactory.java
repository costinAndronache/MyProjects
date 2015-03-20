package model;

import java.util.*;

public class ExpressionTokenFactory {
	
	private Map<String,ExpressionToken> tokenMap;
	private static ExpressionTokenFactory instance=null;
	
	public static ExpressionTokenFactory getInstance()
	{
		if(instance == null)
			instance = new ExpressionTokenFactory();
		
		return instance;
	}
	
	public ExpressionToken getToken(String tokenID)
	{
		return tokenMap.get(tokenID);
	}
	
	private ExpressionTokenFactory()
	{
		tokenMap = new HashMap<String,ExpressionToken>();
		
		tokenMap.put("log", new LogarithmToken());
		tokenMap.put("sqrt", new SquareRootToken());
		tokenMap.put("+", new PlusToken() );
		tokenMap.put("*", new MultiplyToken());
		tokenMap.put("-", new MinusToken());
		tokenMap.put("/", new DivideToken());
		tokenMap.put("%", new ModuloToken());
		tokenMap.put("sin", new SinToken());
		tokenMap.put("cos", new CosToken());
		tokenMap.put("tan", new TgToken());
		tokenMap.put("pow", new PowToken());
		tokenMap.put("ln", new LnToken());
		tokenMap.put("fact", new FactorialToken());
	}
	
	public static void main(String[] args)
	{
		ExpressionTokenFactory etf = ExpressionTokenFactory.getInstance();
		ExpressionToken eTkn;
		
		String[] stringArray = new String[3];
		
		stringArray[0]="log";
		stringArray[1]="*";
		stringArray[2]="+";
		
		
		Stack<Float> resultStack = new Stack<Float>();
		
		resultStack.push(2.f);
		resultStack.push(100.f);
		resultStack.push(2.f);
		resultStack.push(8.f);
		
	   for(int i=0;i<stringArray.length;i++)
	   {
		   eTkn = etf.getToken(stringArray[i]);
		   eTkn.apply(resultStack);
	   }
		
	   System.out.println("The result of 2 + 100 * log(2,8) is: " + resultStack.pop());
	   
		
	}
	
}



class LogarithmToken implements ExpressionToken 
{
	public void apply(Stack<Float> resultStack) 
	{

		
		float exponent=resultStack.pop();
		float base=resultStack.pop();
		
		float result = (float)(Math.log10((double)exponent) / Math.log10((double)base));
		
		resultStack.push(result);
	}
	
	public int precedence()
	{
		return 3;
	}
}

class LnToken implements ExpressionToken
{
	public void apply(Stack<Float> resultStack)
	{
		float arg=resultStack.pop();
		
		float result = (float)Math.log((double)arg);
		resultStack.push(result);
	}
	
	public int precedence()
	{
		return 3;
	}
}



class SquareRootToken implements ExpressionToken
{
	public void apply(Stack<Float> resultStack)
	{
		float arg=resultStack.pop();
		
		float result = (float)Math.sqrt((double)arg);
		resultStack.push(result);
	}
	
	public int precedence()
	{
		return 3;
	}
}

class PlusToken implements ExpressionToken
{
	public void apply(Stack<Float> resultStack)
	{
		float operand1 = resultStack.pop();
		float operand2 = resultStack.pop();
		
		resultStack.push(operand1 + operand2);
	}
	
	public int precedence()
	{
		return 1;
	}
}

class MultiplyToken implements ExpressionToken
{
	public void apply(Stack<Float> resultStack)
	{
		float operand1 = resultStack.pop();
		float operand2 = resultStack.pop();
		
		resultStack.push(operand1 * operand2);
	}
	
	public int precedence()
	{
		return 2;
	}
}

class MinusToken implements ExpressionToken
{
	public void apply(Stack<Float> resultStack)
	{
		float operandRight = resultStack.pop();
		float operandLeft = resultStack.pop();
		
		resultStack.push(operandLeft - operandRight);
	}
	
	public int precedence()
	{
		return 1;
	}
}

class DivideToken implements ExpressionToken
{
	public void apply(Stack<Float> resultStack)
	{
		float operandRight = resultStack.pop();
		float operandLeft = resultStack.pop();
		
		resultStack.push(operandLeft / operandRight);
	}
	
	public int precedence()
	{
		return 2;
	}
}


class ModuloToken implements ExpressionToken
{
	public int precedence(){return 3;}
	
	public void apply(Stack<Float> resultStack)
	{
		float operandRight = resultStack.pop();
		float operandLeft = resultStack.pop();
		
		resultStack.push( (float)((int)operandLeft % (int)operandRight));
	}
}

class PowToken implements ExpressionToken
{
	public void apply(Stack<Float> resultStack)
	{
		float exponent = resultStack.pop();
		float base = resultStack.pop();
		
		resultStack.push( (float)( Math.pow(  (double)base, (double)exponent)  ));
	}
	
	public int precedence(){return 3;}
}


class SinToken implements ExpressionToken
{
	
	public int precedence(){return 3;}
	
	public void apply(Stack<Float> resultStack)
	{
		float arg = resultStack.pop();
		
		resultStack.push((float)Math.sin((double)arg));
	}
}

class CosToken implements ExpressionToken
{
	
	public int precedence(){return 3;}
	
	public void apply(Stack<Float> resultStack)
	{
		float arg = resultStack.pop();
		
		resultStack.push((float)Math.cos((double)arg));
	}
}

class TgToken implements ExpressionToken
{
	
	public int precedence(){return 3;}
	
	public void apply(Stack<Float> resultStack)
	{
		float arg = resultStack.pop();
		
		resultStack.push((float)Math.tan((double)arg));
	}
}

class FactorialToken implements ExpressionToken
{
	
	public int precedence(){return 3;}
	
	public void apply(Stack<Float> resultStack)
	{
		float arg = resultStack.pop();
		
		if(arg<0)
			throw new IllegalArgumentException();
		
		float result=1.f;
		for(int i=2;i<=(int)arg;i++)
		   result = result * i;
		
		resultStack.push(result);
	}
}















