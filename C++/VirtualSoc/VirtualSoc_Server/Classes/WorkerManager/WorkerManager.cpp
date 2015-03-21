#include "WorkerManager.h"
#include "Worker.h"
#include "ChatGroupMiniServer.h"
#include <iostream>

WorkerManager::WorkerManager()
{
    //ctor
    this->hostMiniServer = NULL;
}

WorkerManager::~WorkerManager()
{
    //dtor
}




void WorkerManager::createNewWorkerForSocket(int socket, bool isForApiWorker)
{
    this->mutex.lock();
     std::cout<<"Adding a worker for socket "<<socket<<"\n";
     Worker *newWorker = new Worker(this, socket, isForApiWorker);
     pSocketWorker p(socket, newWorker);
     theMap.insert(p);
     newWorker->start();
    this->mutex.unlock();

}

void WorkerManager::removeWorkerForSocket(int socket)
{
     this->mutex.lock();
     std::cout<<"Removing the worker for " << socket<<"\n";
     map<int, Worker*>::iterator it=theMap.find(socket);
     if(it != theMap.end())
     {
         std::cout<<"Will delete a worker for socket "<<socket<<'\n';
         delete it->second;
     }

     theMap.erase(socket);
     this->mutex.unlock();


     if(theMap.size() == 0 && this->hostMiniServer!=NULL)
     {
         std::cout<<"Calling host mini server. ";
         this->hostMiniServer->workerManagerReportsAllWorkersClosed();
     }
}

void WorkerManager::sendANewMessageToAllWorkers(std::string &message)
{


    MapSocketWorker::iterator it;
    for(it = this->theMap.begin(); it != theMap.end(); it++)
    {
        Worker *aWorker = it->second;
        std::cout<<"Appending " << message<<" for socket: "<<it->first<<"\n";
        aWorker->appendJSONtoSend(message);
    }


}
