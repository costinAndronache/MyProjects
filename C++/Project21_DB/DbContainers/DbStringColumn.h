#ifndef DBSTRINGCOLUMN_H
    #define DBSTRINGCOLUMN_H



#include "DbColumn.h"

class DbStringColumn : public DbColumn
{
    void checkVariableType(DbVariable *newItem);

public:
    DbStringColumn(std::string name){this->name = name;}
    DbType *getType() {return DbString::getInstance();};

    DbVariable *getCopyItemAt(unsigned int index) ;
    void setItemAt(unsigned int index,DbVariable *v) ;
    void addNewItem(DbVariable *newItem) ;
    std::string getName(){return name;}

    DbVariable *getSampleFromString(std::string) ;
    DbColumn *getEmptyCopy(){return new DbStringColumn(name);}
    DbColumn *getFullCopy(){return new DbStringColumn((DbStringColumn&)*this);}

    //void removeItemAt(unsigned int index);
};

#endif // DBSTRINGCOLUMN_H
