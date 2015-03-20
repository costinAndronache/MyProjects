#ifndef DBDATABASE_H
    #define DBDATABASE_H

#include "DbTable.h"
#include <fstream>
class DbDatabase
{
    protected:
    std::string name;
public:

    virtual void addNewTable(DbTable*) = 0;
    virtual void dropTable(std::string tbName) = 0;
    virtual DbTable *getTableAccess(std::string tbName) = 0;
    virtual ~DbDatabase(){}
    virtual void loadFromFile(std::string file) = 0;
    virtual void saveToFile(std::string file) = 0;
} ;
#endif // DBDATABASE_H
