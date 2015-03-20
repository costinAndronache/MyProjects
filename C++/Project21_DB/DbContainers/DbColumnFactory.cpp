#include "DbColumnFactory.h"
using namespace std;

DbColumn *DbColumnFactory::getColumnOfType(string typeID, string columnName)
{
    if(typeID==DbInt::getInstance()->getID())
        return new DbIntColumn(columnName);

    if(typeID == DbString::getInstance()->getID())
        return new DbStringColumn(columnName);

    if(typeID == DbBool::getInstance()->getID())
        return new DbBoolColumn(columnName);

    //more types to add ...
}
