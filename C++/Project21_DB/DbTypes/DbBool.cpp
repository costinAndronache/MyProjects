#include "DbBool.h"

DbBool *DbBool::instance=NULL;

DbType *DbBool::getInstance()
{
    if(instance == NULL)
        instance = new DbBool;

    return instance;
}
