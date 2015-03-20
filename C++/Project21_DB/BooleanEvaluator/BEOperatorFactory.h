#ifndef BEOPERATORFACTORY_H
    #define BEOPERATORFACTORY_H

#include "BEOperatorAND.h"
#include "BEOperatorNOT.h"
#include "BEOperatorOR.h"

#include <map>

class BEOperatorFactory
{

    static BEOperatorFactory *instance;
    BEOperatorFactory();
    std::map<std::string, BEvalOperator*> opMap;
public:
    static BEOperatorFactory *getInstance();
    BEvalOperator *getOperator(std::string id);


};
#endif // BEOPERATORFACTORY_H
