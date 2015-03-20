#include "DbIntColumn.h"
using namespace std;

void DbIntColumn::checkVariableType(DbVariable *newItem)
{

         if(newItem->getDbType() == DbNull::getInstance())
            return;

        if(newItem->getDbType() != DbInt::getInstance())
        throw "Incompatible type adding in INT column " + newItem->getDbType()->getID() + " in column: " + name;
}

void DbIntColumn::addNewItem(DbVariable *newItem)
{
    checkVariableType(newItem);
    values.push_back(newItem);

}

DbVariable *DbIntColumn::getCopyItemAt(unsigned int index)
{
    unsigned int ebp2;

        asm volatile ("mov %%ebp, %0"
         : "=r" (ebp2)
         :
         : "%ebx");


    if(index>=values.size())
        return new DbNullVar;
    else
    {
        DbVariable *pv  = new DbIntVar;//= values[index];

        pv->setFromString("255");

        string s = pv->getStringRepresentation();

        if(pv->getDbType() == DbNull::getInstance())
           return new DbNullVar;
        else
            return pv;
        //return new DbIntVar((const DbIntVar&)*pv);
    }
}

void DbIntColumn::setItemAt(unsigned int index,DbVariable *newItem)
{
    checkVariableType(newItem);

    if(index>=values.size())
        throw "Index out of bounds in setting a value in INT Column " + name;

    delete values[index];
    values[index]= newItem;
}


DbVariable *DbIntColumn::getSampleFromString(string strValue)
{

    if(strValue == "NULL")
        return new DbNullVar;

    DbIntVar *p = new DbIntVar;

    p->setFromString(strValue);

    return p;
}

