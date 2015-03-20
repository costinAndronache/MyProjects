#ifndef DBSTRINGVAR_H
    #define DBSTRINGVAR_H

#include "../DbTypes/DbTypes.h"
#include "DbVariable.h"

class DbStringVar : public DbVariable
{

private:
    std::string actualString;
public:
    void setFromString(std::string);
    std::string getStringRepresentation();

    DbType* getDbType(){return DbString::getInstance();};






    bool operator<=(DbVariable&);
    bool operator<(DbVariable&);
    bool operator>=(DbVariable&);
    bool operator>(DbVariable&);
    bool operator==(DbVariable&);
    bool operator!=(DbVariable&);
};
#endif // DBSTRINGVAR_H
