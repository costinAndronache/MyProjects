#ifndef LOCK_H_VIRTUALSOC
 #define LOCK_H_VIRTUALSOC

#include "Mutex.h"

class Lock {
    mutex &m;
public:
    Lock(mutex &m) : m(m) { m.lock(); }
    ~Lock() { m.unlock(); }
};
#endif
