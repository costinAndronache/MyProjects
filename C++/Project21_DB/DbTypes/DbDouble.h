#ifndef DBDOUBLE_H
    #define DBDOUBLE_H

#include "DbType.h"

class DbDouble : public DbType
{
    static DbDouble *instance;
    DbDouble(){}
public:
    std::string getID(){return "DOUBLE";}
    static DbType *getInstance();
};
#endif // DBDOUBLE_H
