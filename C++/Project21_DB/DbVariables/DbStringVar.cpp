#include "DbStringVar.h"
using namespace std;

void DbStringVar ::setFromString(string newString)
{
    actualString = newString;
}

string DbStringVar::getStringRepresentation()
{
    return actualString;
}

string incompatibleSTRINGError = "Incompatible  rhs type for operation on DbString ";

bool DbStringVar::operator<(DbVariable& v)
{
    DbType *thisType = getDbType();
    DbType *vType = v.getDbType();

    if(vType == DbNull::getInstance())
        return false;

    if(vType != thisType)
        throw incompatibleSTRINGError + "< ";

    DbStringVar *dbs= (DbStringVar*)&v;

    return actualString<dbs->actualString;
}

bool DbStringVar::operator<=(DbVariable& v)
{
    DbType *thisType = getDbType();
    DbType *vType = v.getDbType();

    if(vType == DbNull::getInstance())
        return false;

    if(vType != thisType)
        throw incompatibleSTRINGError + "<= ";

    DbStringVar *dbs= (DbStringVar*)&v;

    return actualString<=dbs->actualString;
}

bool DbStringVar::operator>(DbVariable& v)
{
    DbType *thisType = getDbType();
    DbType *vType = v.getDbType();

    if(vType == DbNull::getInstance())
        return true;

    if(vType != thisType)
        throw incompatibleSTRINGError + "> ";

    DbStringVar *dbs= (DbStringVar*)&v;

    return actualString>dbs->actualString;
}

bool DbStringVar::operator>=(DbVariable& v)
{
    DbType *thisType = getDbType();
    DbType *vType = v.getDbType();

    if(vType == DbNull::getInstance())
        return true;

    if(vType != thisType)
        throw incompatibleSTRINGError + ">= ";

    DbStringVar *dbs= (DbStringVar*)&v;

    return actualString>=dbs->actualString;
}

bool DbStringVar::operator==(DbVariable& v)
{
    DbType *thisType = getDbType();
    DbType *vType = v.getDbType();

    if(vType == DbNull::getInstance())
        return false;

    if(vType != thisType)
        throw incompatibleSTRINGError + "== ";

    DbStringVar *dbs= (DbStringVar*)&v;

    return actualString==dbs->actualString;
}

bool DbStringVar::operator!=(DbVariable& v)
{
    DbType *thisType = getDbType();
    DbType *vType = v.getDbType();

    if(vType == DbNull::getInstance())
        return true;

    if(vType != thisType)
        throw incompatibleSTRINGError + " != ";

    DbStringVar *dbs= (DbStringVar*)&v;

    return actualString!=dbs->actualString;
}
