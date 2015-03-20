#ifndef DBBOOLCOLUMN_H
    #define DBBOOLCOLUMN_H

#include "DbColumn.h"

class DbBoolColumn : public DbColumn
{
    void checkVariableType(DbVariable*);
public:
    DbBoolColumn(std::string name){this->name = name;}
    DbType *getType() {return DbBool::getInstance();};

    DbVariable *getCopyItemAt(unsigned int index);
    void setItemAt(unsigned int index,DbVariable *v);
    void addNewItem(DbVariable *newItem);
    std::string getName(){return name;}

    DbVariable *getSampleFromString(std::string strValue)
    {
        if(strValue == "NULL")
            return new DbNullVar;

        DbBoolVar *b = new DbBoolVar;
        b->setFromString(strValue);
        return b;
    };

    DbColumn *getEmptyCopy() {return new DbBoolColumn(name);};

    DbColumn *getFullCopy(){return new DbBoolColumn(*this);};
};
#endif // DBBOOLCOLUMN_H
