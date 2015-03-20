#ifndef BEOPERATOROR_H
    #define BEOPERATOROR_H

#include "BEvalOperator.h"

class BEOperatorOR : public BEvalOperator
{
public:
    int getPriority(){return 1;}
    std::string getStringID(){return "OR";}
    void operate(std::stack<bool> &bStack)
    {
        bool b1 = bStack.top(); bStack.pop();
        bool b2 = bStack.top(); bStack.pop();

        bStack.push(b1 || b2);
    }
};
#endif // BEOPERATOROR_H
