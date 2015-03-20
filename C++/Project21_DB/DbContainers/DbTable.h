#ifndef DBTABLE_H
    #define DBTABLE_H

#include "DbColumn.h"
#include "DbTableSnapshot.h"
#include "../Selectors/Selector.h"

class DbTable
{
protected:
    std::string name;
    int rows;
public:
    DbTable(){rows = 0;}
    virtual void addNewColumn(DbColumn *newColumn) = 0;
    virtual void removeColumn(std::string columnName) = 0;
    virtual void insertInto(std::vector<std::string> &columnList, std::vector<DbVariable*> &valueList) = 0;
    virtual DbTableSnapshot selectRows(std::vector<std::string> *columnList,Selector *S) = 0;
    virtual void deleteRows(Selector *S) = 0;
    virtual DbColumn *getColumnAccess(std::string columnName) = 0;

    std::string getName(){return name;}
    int getRows(){return rows;}
    virtual ~DbTable(){}

    void setNumOfRows(int rows){this->rows = rows;}
    virtual int getNumberOfColumns() = 0;

    virtual std::vector<std::string> getColumnNames() = 0;
};
#endif // DBTABLE_H
