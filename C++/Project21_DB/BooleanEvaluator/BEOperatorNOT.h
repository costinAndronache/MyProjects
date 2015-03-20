#ifndef BEOPERATORNOT_H
    #define BEOPERATORNOT_H

#include "BEOperatorNOT.h"

class BEOperatorNOT : public BEvalOperator
{

public:
    std::string getStringID(){return "NOT";}
    void operate(std::stack<bool> &bStack)
    {
        bool b = bStack.top();
        bStack.pop();

        bStack.push(!b);
    };
    int getPriority(){return 3;}

};
#endif // BEOPERATORNOT_H
