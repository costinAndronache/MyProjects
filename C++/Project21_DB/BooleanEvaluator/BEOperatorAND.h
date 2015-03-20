#ifndef BEOPERATORAND_H
    #define BEOPERATORAND_H

#include "BEvalOperator.h"

class BEOperatorAND : public BEvalOperator
{
public:
    std::string getStringID(){return "AND";}
    int getPriority(){return 2;}

    void operate(std::stack<bool> &bStack)
    {
        bool b1 = bStack.top(); bStack.pop();
        bool b2 = bStack.top(); bStack.pop();

        bStack.push(b1 && b2);
    }
};
#endif // BEOPERATORAND_H
