#include "DbStringColumn.h"

using namespace std;
void DbStringColumn::checkVariableType(DbVariable *newItem)
{

             if(newItem->getDbType() == DbNull::getInstance())
            return;

    if(newItem->getDbType() != DbString::getInstance())
        throw "Incompatible type adding in STRING column " + newItem->getDbType()->getID() + " in column:" + name;
}

void DbStringColumn::addNewItem(DbVariable *newItem)
{
    checkVariableType(newItem);
    values.push_back(newItem);
}

DbVariable *DbStringColumn::getCopyItemAt(unsigned int index)
{
    if(index>=values.size())
        return new DbNullVar;

            if(values[index] ->getDbType() == DbNull::getInstance())
           return new DbNullVar;

    return new DbStringVar((const DbStringVar&)*values[index]);
}

DbVariable *DbStringColumn::getSampleFromString(string strValue)
{

    if(strValue == "NULL")
        return new DbNullVar;

    DbStringVar *v = new DbStringVar;

    v->setFromString(strValue);

    return v;
}

void DbStringColumn::setItemAt(unsigned int index,DbVariable *v)
{
    checkVariableType(v);

    if(index>=values.size())
        throw "Index out of bounds in setting a value for STRING column " + name;

    delete values[index];
    values[index] = v;

}

