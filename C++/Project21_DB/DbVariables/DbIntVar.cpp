#include "DbIntVar.h"
#include "../DbTypes/DbNull.h"
#include <sstream>

using namespace std;

void DbIntVar::setFromString(string stringValue)
{
    stringstream ss(stringValue);

    ss>>actualValue;

    if(!ss)
        throw "Invalid value in string for INT variable";
}

string DbIntVar::getStringRepresentation()
{
    stringstream ss;

    ss<<actualValue;

    return ss.str();
}

string  incompatibleINTError = "Incompatible rhs type on performing on INT ";

bool DbIntVar::operator<(DbVariable &v)
{
    DbType *vType = v.getDbType();
    DbType *thisType = getDbType();

    //Orice este mai > decat NULL
    if(vType == DbNull::getInstance())
        return false;

    if(vType != thisType)
        throw incompatibleINTError + "< operation";

    DbIntVar *dbv = (DbIntVar*)&v;
    return actualValue<dbv->actualValue;
}

bool DbIntVar::operator>(DbVariable &v)
{
    DbType *vType = v.getDbType();
    DbType *thisType = getDbType();

    //Orice este mai > decat NULL
    if(vType == DbNull::getInstance())
        return true;

    if(vType != thisType)
        throw incompatibleINTError + "> operation";

    DbIntVar *dbv = (DbIntVar*)&v;
    return actualValue>dbv->actualValue;
}

bool DbIntVar::operator<=(DbVariable &v)
{
    DbType *vType = v.getDbType();
    DbType *thisType = getDbType();

    //Orice este mai > decat NULL
    if(vType == DbNull::getInstance())
        return false;

    if(vType != thisType)
        throw incompatibleINTError + "<= operation";

    DbIntVar *dbv = (DbIntVar*)&v;
    return actualValue<=dbv->actualValue;
}

bool DbIntVar::operator>=(DbVariable &v)
{
    DbType *vType = v.getDbType();
    DbType *thisType = getDbType();

    //Orice este mai > decat NULL
    if(vType == DbNull::getInstance())
        return true;

    if(vType != thisType)
        throw incompatibleINTError + ">= operation";

    DbIntVar *dbv = (DbIntVar*)&v;
    return actualValue>=dbv->actualValue;
}

bool DbIntVar::operator==(DbVariable &v)
{
    DbType *vType = v.getDbType();
    DbType *thisType = getDbType();

    //Orice este mai > decat NULL
    if(vType == DbNull::getInstance())
        return false;

    if(vType != thisType)
        throw incompatibleINTError + "== operation";

    DbIntVar *dbv = (DbIntVar*)&v;
    return actualValue==dbv->actualValue;
}

bool DbIntVar::operator!=(DbVariable &v)
{
    DbType *vType = v.getDbType();
    DbType *thisType = getDbType();

    //Orice este mai > decat NULL
    if(vType == DbNull::getInstance())
        return true;

    if(vType != thisType)
        throw incompatibleINTError + " != operation";

    DbIntVar *dbv = (DbIntVar*)&v;
    return actualValue!=dbv->actualValue;
}
