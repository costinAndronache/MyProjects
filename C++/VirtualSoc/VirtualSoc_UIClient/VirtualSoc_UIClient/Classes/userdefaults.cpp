#include "userdefaults.h"

UserDefaults::UserDefaults()
{
    isLoggedIn = false;
}

UserDefaults *UserDefaults::_sharedInstance = NULL;
Mutex UserDefaults::_sharedMutex = Mutex();

UserDefaults *UserDefaults::sharedInstance()
{
    _sharedMutex.lock();
    if(_sharedInstance == NULL)
    {
        _sharedInstance = new UserDefaults();
    }
    _sharedMutex.unlock();

    return _sharedInstance;
}
