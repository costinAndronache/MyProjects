#ifndef MUTEX_H_VIRTUALSOC
 #define MUTEX_H_VIRTUALSOC

#include<pthread.h>


class Mutex {
    pthread_mutex_t m;
public:
    Mutex()       { pthread_mutex_init(&m, NULL);    }
    ~Mutex()      { pthread_mutex_destroy(&m); }
    void lock()   { pthread_mutex_lock(&m);    }
    void unlock() { pthread_mutex_unlock(&m);  }
};

#endif
