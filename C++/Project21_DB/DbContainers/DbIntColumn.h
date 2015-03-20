#ifndef DBINTCOLUMN_H
    #define DBINTCOLUMN_H

#include "DbColumn.h"

class DbIntColumn : public DbColumn
{
    void checkVariableType(DbVariable*);
public:
    DbIntColumn(std::string name){this->name = name;}
    DbType *getType() {return DbInt::getInstance();};

    DbVariable *getCopyItemAt(unsigned int index) ;
    void setItemAt(unsigned int index,DbVariable *v) ;
    void addNewItem(DbVariable *newItem) ;
    std::string getName(){return name;}

    DbVariable *getSampleFromString(std::string) ;

    DbColumn *getEmptyCopy(){return new DbIntColumn(name);}

    DbColumn *getFullCopy(){return new DbIntColumn((DbIntColumn&)*this);}

   // void removeItemAt(unsigned int index);
};
#endif // DBINTCOLUMN_H
