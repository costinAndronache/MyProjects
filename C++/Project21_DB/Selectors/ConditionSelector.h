#ifndef CONDITIONSELECTOR_H
    #define CONDITIONSELECTOR_H

#include "TFStatement.h"
#include "Selector.h"

#include <map>
#include "../BooleanEvaluator/BooleanEvaluator.h"

typedef std::map<std::string, TFStatement* > TFStmtMap;

class ConditionSelector : public Selector
{
    TFStmtMap tfMap;
    std::string booleanExpression;

    std::vector<std::string >getTokens(std::string s);

    std::string condition;

public:
    ConditionSelector(std::string condition){this->condition = condition;}
    std::vector<unsigned int> getRowsThatConform(DbTable *table);

};
#endif // CONDITIONSELECTOR_H
