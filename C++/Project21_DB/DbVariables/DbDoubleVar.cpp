#include "DbDoubleVar.h"

#include <sstream>

using namespace std;

void DbDoubleVar::setFromString(string stringValue)
{
    stringstream ss(stringValue);

    ss>>actualValue;

    if(!ss)
        throw "Invalid value in string for Double variable";
}

string DbDoubleVar::getStringRepresentation()
{
    stringstream ss;

    ss<<actualValue;

    return ss.str();
}

string  incompatibleDoubleError = "Incompatible rhs type on performing on Double ";

bool DbDoubleVar::operator<(DbVariable &v)
{
    DbType *vType = v.getDbType();
    DbType *thisType = getDbType();

    //Orice este mai > decat NULL
    if(vType == DbNull::getInstance())
        return false;

    if(vType != thisType)
        throw incompatibleDoubleError + "< operation";

    DbDoubleVar *dbv = (DbDoubleVar*)&v;
    return actualValue<dbv->actualValue;
}

bool DbDoubleVar::operator>(DbVariable &v)
{
    DbType *vType = v.getDbType();
    DbType *thisType = getDbType();

    //Orice este mai > decat NULL
    if(vType == DbNull::getInstance())
        return true;

    if(vType != thisType)
        throw incompatibleDoubleError + "> operation";

    DbDoubleVar *dbv = (DbDoubleVar*)&v;
    return actualValue>dbv->actualValue;
}

bool DbDoubleVar::operator<=(DbVariable &v)
{
    DbType *vType = v.getDbType();
    DbType *thisType = getDbType();

    //Orice este mai > decat NULL
    if(vType == DbNull::getInstance())
        return false;

    if(vType != thisType)
        throw incompatibleDoubleError + "<= operation";

    DbDoubleVar *dbv = (DbDoubleVar*)&v;
    return actualValue<=dbv->actualValue;
}

bool DbDoubleVar::operator>=(DbVariable &v)
{
    DbType *vType = v.getDbType();
    DbType *thisType = getDbType();

    //Orice este mai > decat NULL
    if(vType == DbNull::getInstance())
        return true;

    if(vType != thisType)
        throw incompatibleDoubleError + ">= operation";

    DbDoubleVar *dbv = (DbDoubleVar*)&v;
    return actualValue>=dbv->actualValue;
}

bool DbDoubleVar::operator==(DbVariable &v)
{
    DbType *vType = v.getDbType();
    DbType *thisType = getDbType();

    //Orice este mai > decat NULL
    if(vType == DbNull::getInstance())
        return false;

    if(vType != thisType)
        throw incompatibleDoubleError + "== operation";

    DbDoubleVar *dbv = (DbDoubleVar*)&v;
    return actualValue==dbv->actualValue;
}

bool DbDoubleVar::operator!=(DbVariable &v)
{
        DbType *vType = v.getDbType();
    DbType *thisType = getDbType();

    //Orice este mai > decat NULL
    if(vType == DbNull::getInstance())
        return true;

    if(vType != thisType)
        throw incompatibleDoubleError + "!= operation";

    DbDoubleVar *dbv = (DbDoubleVar*)&v;
    return actualValue!=dbv->actualValue;
}
