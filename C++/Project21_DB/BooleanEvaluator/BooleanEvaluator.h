#ifndef BOOLEANEVALUATOR_H
    #define BOOLEANEVALUATOR_H

#include <stack>
#include <vector>
#include "BEOperatorFactory.h"

class BooleanEvaluator
{

    static std::string getPostfixFromInfix(std::string &infixExpression);
    static bool isTFValue(std::string strValue);
    static std::vector<std::string> getTokens(std::string &infixExpression);
    static bool getValue(std::string strValue);

public:
    static bool evaluate(std::string infixExpression);

};

#endif // BOOLEANEVALUATOR_H
