#ifndef WORKERDATABASE_H
#define WORKERDATABASE_H

#include <ThreadUtilities/Mutex.h>

#include<string>
#include<map>
using namespace std;

class Worker;


typedef map<int, Worker*> MapUserIDWorker;
typedef pair<int, Worker*> pUW;


class WorkerDatabase
{
    public:

        virtual ~WorkerDatabase();

        void addNewWorkerForUserID(Worker *worker, int userID);
        void removeWorkerForUserID(int userID);
        Worker* getWorkerForUserID(int userID);

        static WorkerDatabase* sharedInstance();
    private:
    WorkerDatabase();
    MapUserIDWorker mapOfWorkers;
    Mutex mutex;

    static WorkerDatabase *_sharedInstance;
    static Mutex _sharedMutex;
};

#endif // WORKERDATABASE_H
