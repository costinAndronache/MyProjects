#ifndef DBVARIABLE_H
    #define DBVARIABLE_H

#include "../DbTypes/DbType.h"


class DbVariable
{

public:
    virtual void setFromString(std::string) = 0;
    virtual std::string getStringRepresentation() = 0;
    virtual DbType* getDbType() = 0 ;






    virtual bool operator<=(DbVariable&) = 0;
    virtual bool operator<(DbVariable&) = 0;
    virtual bool operator>=(DbVariable&) = 0;
    virtual bool operator>(DbVariable&) = 0;
    virtual bool operator==(DbVariable&) = 0;
    virtual bool operator!=(DbVariable&) = 0;
};

#endif // DBVARIABLE_H
