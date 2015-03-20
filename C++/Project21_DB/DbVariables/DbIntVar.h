#ifndef DBINTVAR_H
    #define DBINTVAR_H

#include "DbVariable.h"
#include "../DbTypes/DbTypes.h"

class DbIntVar : public DbVariable
{
private:
    int actualValue;
public:
    DbIntVar(){actualValue=0;}
    void setFromString(std::string);
    std::string getStringRepresentation();

    DbType* getDbType(){return DbInt::getInstance();};






    bool operator<=(DbVariable&);
    bool operator<(DbVariable&);
    bool operator>=(DbVariable&);
    bool operator>(DbVariable&);
    bool operator==(DbVariable&);
    bool operator!=(DbVariable&);

};
#endif // DBINTVAR_H
