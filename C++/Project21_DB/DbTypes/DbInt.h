#ifndef DBINT_H
    #define DBINT_H

#include "DbType.h"

class DbInt : public DbType
{
    static DbInt *instance;
    DbInt(){}
    public:
    std::string getID(){return "INT";}
    static DbType *getInstance();
};
#endif // DBINT_H
