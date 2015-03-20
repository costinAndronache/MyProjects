#ifndef DBCOLUMNFACTORY_H
    #define DBCOLUMNFACTORY

#include "DbColumns.h"

class DbColumnFactory
{

public:
    static DbColumn *getColumnOfType(std::string typeID, std::string columnName);
};
#endif // DBCOLUMNFACTORY_H
