#ifndef DBSTRING_H
    #define DBSTRING_H


#include "DbType.h"

class DbString : public DbType
{
    static DbString *instance;
    DbString(){}
public:
    std::string getID(){return "STRING";}
    static DbType *getInstance();
};
#endif // DBSTRING_H
