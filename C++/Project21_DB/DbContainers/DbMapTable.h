#ifndef DBMAPTABLE_H
    #define DBMAPTABLE_H

#include "DbTable.h"
#include <map>

typedef  std::map<std::string, DbColumn*> ColumnMap;
class DbMapTable : public DbTable
{
private:
   ColumnMap columnMap;
public:
    DbMapTable(std::string tableName){name = tableName;}
     void addNewColumn(DbColumn *newColumn);

     void removeColumn(std::string columnName);

     void insertInto(std::vector<std::string> &columnList, std::vector<DbVariable*> &valueList);

     DbTableSnapshot selectRows(std::vector<std::string> *columnList,Selector *S);

     void deleteRows(Selector *S);

     virtual DbColumn *getColumnAccess(std::string columnName) ;

     int getNumberOfColumns(){return columnMap.size();}
     ~DbMapTable();

     std::vector<std::string> getColumnNames();
};
#endif // DBMAPTABLE_H
