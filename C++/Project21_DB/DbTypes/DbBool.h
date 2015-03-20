#ifndef DBBOOL_H
    #define DBBOOL_H

#include "DbType.h"

class DbBool : public DbType
{
    static DbBool *instance;
    DbBool(){}
public:
    std::string getID(){return "BOOL";}
    static DbType *getInstance();
};
#endif // DBBOOL_H
