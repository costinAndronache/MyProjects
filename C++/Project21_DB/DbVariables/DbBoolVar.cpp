#include "DbBoolVar.h"

using namespace std;

void DbBoolVar:: setFromString(string strValue)
{
    if(strValue == "TRUE" || strValue == "true")
    {
        actualValue=true;
        return;
    }

    if(strValue == "FALSE" || strValue == "false")
    {
        actualValue = false;
        return;
    }

    throw "Invalid value for BOOL in string representation";

}

string DbBoolVar::getStringRepresentation()
{
    if(actualValue==true)
        return "TRUE";

    return "FALSE";
}


string incompatibleBOOLError = "Incompatible rhs type for operation on DbBool ";

bool DbBoolVar :: operator<(DbVariable &v)
{

    DbType *thisType = getDbType(), *vType = v.getDbType();

    if(vType == DbNull::getInstance())
        return false;

    if(vType != thisType)
        throw incompatibleBOOLError + " <";

    DbBoolVar *b= (DbBoolVar*)&v;

    return actualValue<b->actualValue;


}

bool DbBoolVar :: operator<=(DbVariable &v)
{

    DbType *thisType = getDbType(), *vType = v.getDbType();

    if(vType == DbNull::getInstance())
        return false;

    if(vType != thisType)
        throw incompatibleBOOLError + " <=";

    DbBoolVar *b= (DbBoolVar*)&v;

    return actualValue<=b->actualValue;


}

bool DbBoolVar :: operator>(DbVariable &v)
{

    DbType *thisType = getDbType(), *vType = v.getDbType();

    if(vType == DbNull::getInstance())
        return true;

    if(vType != thisType)
        throw incompatibleBOOLError + " >";

    DbBoolVar *b= (DbBoolVar*)&v;

    return actualValue>b->actualValue;


}

bool DbBoolVar :: operator>=(DbVariable &v)
{

    DbType *thisType = getDbType(), *vType = v.getDbType();

    if(vType == DbNull::getInstance())
        return true;

    if(vType != thisType)
        throw incompatibleBOOLError + " >=";

    DbBoolVar *b= (DbBoolVar*)&v;

    return actualValue>=b->actualValue;


}

bool DbBoolVar :: operator==(DbVariable &v)
{

    DbType *thisType = getDbType(), *vType = v.getDbType();

    if(vType == DbNull::getInstance())
        return false;

    if(vType != thisType)
        throw incompatibleBOOLError + " ==";

    DbBoolVar *b= (DbBoolVar*)&v;

    return actualValue==b->actualValue;


}

bool DbBoolVar ::operator!=(DbVariable &v)
{

        DbType *thisType = getDbType(), *vType = v.getDbType();

    if(vType == DbNull::getInstance())
        return true;

    if(vType != thisType)
        throw incompatibleBOOLError + " !=";

    DbBoolVar *b= (DbBoolVar*)&v;

    return actualValue!=b->actualValue;

}
