#include "BEOperatorFactory.h"

using namespace std;


BEOperatorFactory *BEOperatorFactory::instance = NULL;

BEOperatorFactory *BEOperatorFactory::getInstance()
{
    if(instance == NULL)
        instance = new BEOperatorFactory();
    return instance;
}

BEOperatorFactory::BEOperatorFactory()
{

    opMap["AND"] = new BEOperatorAND;
    opMap["OR"] = new BEOperatorOR;
    opMap["NOT"] = new BEOperatorNOT;
}

BEvalOperator *BEOperatorFactory::getOperator(string id)
{
    map<string,BEvalOperator*>::iterator it = opMap.find(id);

    if(it == opMap.end())
        return NULL;

    return it->second;
}
