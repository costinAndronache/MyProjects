package model;

import java.util.Stack;

public interface ExpressionToken 
{
	public int precedence();
	
	public void apply(Stack<Float> resultStack);
	
}
