#include "BooleanEvaluator.h"
#include <cstring>
#include <iostream>
using namespace std;

bool BooleanEvaluator::isTFValue(string strValue)
{
    return (strValue == "T" || strValue == "F" || strValue==" T" || strValue == " F");
}

bool BooleanEvaluator::getValue(string strValue)
{

    return (strValue == "T" || strValue==" T") ? true : false;

}

vector<string> BooleanEvaluator::getTokens(string &infixExpression)
{
    char *cstr = new char[infixExpression.length()+1];

    strcpy(cstr,infixExpression.c_str());

    strtok(cstr," ");

    vector<string> result;

    char *p=cstr;

    while(p)
    {
        result.push_back(string(p));
        p = strtok(NULL," ");
    }

    delete[] cstr;

    return result;

}

string BooleanEvaluator::getPostfixFromInfix(string &infixExpression)
{

    vector<string> tokens = getTokens(infixExpression);
    string result="";

    stack<string> operatorStack;
    stack<int> intStack;

    const char *rd = result.c_str();
    BEOperatorFactory *opFactory = BEOperatorFactory::getInstance();



    for(int i=0;i<tokens.size();i++)
    {
        string debugS = tokens[i];

        if(isTFValue(tokens[i]))
        {
            string aux = tokens[i] + " ";
            result.append(aux);

            //cout<<"This block!\n";
        }
         else
            if(tokens[i] == "(" || tokens[i] == " (")
                {
                    intStack.push(operatorStack.size() - 1 );



                        }
                else
            if(tokens[i] == ")")
            {
                int stopPos = intStack.top();intStack.pop();

                while(operatorStack.size()-1>stopPos)
                {
                    result.append(operatorStack.top() + " ");
                    operatorStack.pop();

                }

                BEvalOperator *op = opFactory->getOperator(operatorStack.top());

                if(op!=NULL && op->getPriority() == 3)
                {
                    result.append(operatorStack.top() + " ");
                    operatorStack.pop();
                }



            }
            else
            {

                if(operatorStack.size() > 0)
                {

                    BEvalOperator *opTop = opFactory->getOperator(operatorStack.top());
                    BEvalOperator *opToAdd = opFactory->getOperator(tokens[i]);

                   // if(i == 7)
                    {
                       // cout<<tokens[i]<<' '<<i<<'\n';
                    }

                    while(opTop!=NULL && opTop->getPriority()>opToAdd->getPriority())

                    {
                        bool b;
                        if(intStack.size())
                        {
                            b=operatorStack.size()-1 != intStack.top();
                        }
                        else
                            b=true;

                        if(b)
                        {result.append(operatorStack.top() + " ");
                           operatorStack.pop();

                        if(operatorStack.size())
                        opTop = opFactory->getOperator(operatorStack.top());
                        else
                            opTop=NULL;

                        }
                        else
                            break;

                    }

                }

                operatorStack.push(tokens[i]);




            }

        //cout<<result<<' '<<i<<'\n';
    }

    while(operatorStack.size()>0)
    {
        result.append(operatorStack.top() + " ");
        operatorStack.pop();
    }

   return result;

}

bool BooleanEvaluator::evaluate(string infixExpression)
{
    string postfix = getPostfixFromInfix(infixExpression);
    vector<string> postfixTokens = getTokens(postfix);

    BEOperatorFactory *opFactory = BEOperatorFactory::getInstance();
    stack<bool> bStack;

    for(int i=0;i<postfixTokens.size();i++)
    {
        string debugS = postfixTokens[i];
        if(isTFValue(postfixTokens[i]))
            bStack.push(getValue(postfixTokens[i]));
        else
        {
            BEvalOperator *op = opFactory->getOperator(postfixTokens[i]);
            op->operate(bStack);
        }
    }



    //cout<<postfix<<'\n';


    return bStack.top();

}
