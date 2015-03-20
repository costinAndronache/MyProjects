#include "DbBoolColumn.h"

#include "DbBoolColumn.h"
using namespace std;

void DbBoolColumn::checkVariableType(DbVariable *newItem)
{

         if(newItem->getDbType() == DbNull::getInstance())
            return;

        if(newItem->getDbType() != DbBool::getInstance())
        throw "Incompatible type adding in BOOL column " + newItem->getDbType()->getID() + " in column: " + name;
}

void DbBoolColumn::addNewItem(DbVariable *newItem)
{
    checkVariableType(newItem);
    values.push_back(newItem);

}

DbVariable *DbBoolColumn::getCopyItemAt(unsigned int index)
{
    if(index>=values.size())
        return new DbNullVar;
    else
    {
        DbVariable *pv = values[index];
        DbVariable *xv = values.at(index);

        if(pv->getDbType() == DbNull::getInstance())
           return new DbNullVar;
        else

        return new DbBoolVar((const DbBoolVar&)*pv);
    }
}

void DbBoolColumn::setItemAt(unsigned int index,DbVariable *newItem)
{
    checkVariableType(newItem);

    if(index>=values.size())
        throw "Index out of bounds in setting a value in BOOL Column " + name;

    delete values[index];
    values[index]= newItem;
}





