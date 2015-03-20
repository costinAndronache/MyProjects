#ifndef BEVALOPERATOR_H
    #define BEVALOPERATOR_H

#include <stack>
#include <string>


class BEvalOperator
{

public:
    virtual std::string getStringID() = 0;
    virtual void operate(std::stack<bool> &bStack) = 0;
    virtual int getPriority() = 0;


};
#endif // BEVALOPERATOR_H
