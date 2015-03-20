#include "DbNull.h"

DbNull *DbNull::instance=NULL;

DbType *DbNull::getInstance()
{
    if(instance == NULL)
        instance = new DbNull;

    return instance;
}
