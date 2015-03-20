#include "DbDouble.h"

DbDouble *DbDouble::instance=NULL;

DbType *DbDouble::getInstance()
{
    if(instance == NULL)
        instance = new DbDouble;

    return instance;
}
