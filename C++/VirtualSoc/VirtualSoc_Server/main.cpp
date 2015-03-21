#include <iostream>
#include <json/json.h>
#include <json/json.h>
#include <Worker.h>
#include <cstdlib>
#include <unistd.h>
#include "WorkerManager.h"
#include "CommonConstants.h"
#include "ApiManager.h"
#include <NetworkUtilities/NetworkUtilities.h>
#include <sys/socket.h>

#include "ChatGroupMiniServer.h"

using namespace std;

int main()
{

    WorkerManager apiWorkerManager;
    try
    {
        int server = createBindedServerSocket(2277, 5);
        while(1)
        {
            int clientSocket = accept(server, NULL, NULL);

            if(clientSocket > 0)
            {
                apiWorkerManager.createNewWorkerForSocket(clientSocket, true);
            }
        }

    }
    catch(exception &ex)
    {
        cout<<ex.what();
    }

    cout << "Hello world!" << endl;
    return 0;
}
