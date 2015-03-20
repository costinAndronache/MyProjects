#ifndef DBBOOLVAR_H
    #define DBBOOLVAR_H

#include "../DbTypes/DbTypes.h"
#include "DbVariable.h"

class DbBoolVar : public DbVariable
{

private:
    bool actualValue;
public:
    DbBoolVar(){actualValue=false;}
    void setFromString(std::string);
    std::string getStringRepresentation();
    DbType* getDbType(){return DbBool::getInstance();};






    bool operator<=(DbVariable&);
    bool operator<(DbVariable&);
    bool operator>=(DbVariable&);
    bool operator>(DbVariable&);
    bool operator==(DbVariable&);
    bool operator!=(DbVariable&);

};
#endif // DBBOOLVAR_H
