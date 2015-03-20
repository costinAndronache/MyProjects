#ifndef DBNULL_H
    #define DBNULL_H

#include "DbTypes.h"

class DbNull : public DbType
{
    static DbNull *instance;
    DbNull(){}
public:
    std::string getID(){return "NULL";}
    static DbType *getInstance();
};
#endif // DBNULL_H
