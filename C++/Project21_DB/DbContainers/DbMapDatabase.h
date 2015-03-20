#ifndef DBMAPDATABASE_H
    #define DBMAPDATABASE_H

#include "DbDatabase.h"
#include "DbColumnFactory.h"
#include "DbMapTable.h"
#include <map>
#include <string>

typedef std::map<std::string,DbTable*> TBMap;
class DbMapDatabase : public DbDatabase
{

    TBMap tbMap;

public:
    DbMapDatabase(std::string name){this->name = name;}

    void addNewTable(DbTable*);
    void dropTable(std::string);
    DbTable *getTableAccess(std::string);
    ~DbMapDatabase();

    void loadFromFile(std::string file);
    void saveToFile(std::string file);
};
#endif // DBMAPDATABASE_H
