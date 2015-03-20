#ifndef DBDOUBLEVAR_H
    #define DBDOUBLEVAR_H

#include "../DbTypes/DbTypes.h"
#include "DbVariable.h"

class DbDoubleVar : public DbVariable
{
private:
    double actualValue;

public:
    DbDoubleVar(){actualValue=0;}
    void setFromString(std::string);
    std::string getStringRepresentation();

    DbType* getDbType(){return DbDouble::getInstance();};






    bool operator<=(DbVariable&);
    bool operator<(DbVariable&);
    bool operator>=(DbVariable&);
    bool operator>(DbVariable&);
    bool operator==(DbVariable&);
    bool operator!=(DbVariable&);
};
#endif // DBDOUBLEVAR_H
