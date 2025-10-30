#include "NetworkManager.h"
#include <sys/socket.h>

using namespace std;

NetworkManager:: NetworkManager(){
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

}

