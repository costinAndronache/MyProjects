#include "DbString.h"

DbString *DbString::instance=NULL;

DbType *DbString::getInstance()
{
    if(instance == NULL)
        instance = new DbString;

    return instance;

}
