#ifndef NETWORK_UTILS_VSOC
    #define NETWORK_UTILS_VSOC

#include <unistd.h>

int createConnectedClientSocket(char *address, int port);
int createBindedServerSocket(int PORT, int N);
int createBindedServerSocketToRandomPort(int *backPort, int N);

#endif // NETWORK_UTILS_VSOC
