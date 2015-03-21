#include "WorkerDatabase.h"

WorkerDatabase::WorkerDatabase()
{
    //ctor
}

WorkerDatabase::~WorkerDatabase()
{
    //dtor
}

WorkerDatabase* WorkerDatabase::_sharedInstance = NULL;
Mutex WorkerDatabase::_sharedMutex = Mutex();

WorkerDatabase* WorkerDatabase::sharedInstance()
{
    _sharedMutex.lock();
    if(_sharedInstance == NULL)
    {
        _sharedInstance = new WorkerDatabase;
    }
    _sharedMutex.unlock();
    return _sharedInstance;
}

void WorkerDatabase::addNewWorkerForUserID(Worker *worker, int userID)
{
    this->mutex.lock();
    pUW p(userID, worker);
    mapOfWorkers.insert(p);
    this->mutex.unlock();
}

void WorkerDatabase::removeWorkerForUserID(int userID)
{
    this->mutex.lock();
    mapOfWorkers.erase(userID);
    this->mutex.unlock();
}

Worker* WorkerDatabase::getWorkerForUserID(int userID)
{
    Worker *result = NULL;
    this->mutex.lock();
    MapUserIDWorker::iterator it = mapOfWorkers.find(userID);
    this->mutex.unlock();
    if(it != mapOfWorkers.end())
    {
        result = it->second;
    }
    return result;
}

