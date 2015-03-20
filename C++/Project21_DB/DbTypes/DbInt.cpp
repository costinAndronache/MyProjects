#include "DbInt.h"

DbInt *DbInt::instance=NULL;

DbType *DbInt::getInstance()
{
    if(instance == NULL)
        instance = new DbInt;

    return instance;
}
