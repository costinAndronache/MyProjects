#ifndef DBNULLVAR_H
    #define DBNULLVAR_H

#include "../DbTypes/DbTypes.h"
#include "DbVariable.h"

class DbNullVar : public DbVariable
{

public:
    void setFromString(std::string){};
    std::string getStringRepresentation(){return "NULL";};

    DbType* getDbType(){return DbNull::getInstance();};






    bool operator<=(DbVariable&){return true;}
    bool operator<(DbVariable&){return true;}
    bool operator>=(DbVariable&){return false;}
    bool operator>(DbVariable&){return false;}
    bool operator==(DbVariable &v)
    {

        return v.getDbType() == DbNull::getInstance() ? true : false;}

    bool operator!=(DbVariable&){return true;}


};
#endif // DBNULLVAR_H
