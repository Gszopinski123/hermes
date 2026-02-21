#include "network.h"
#include <assert.h>
#define IP "127.0.0.1"
#define PORT 5001
#define PEER_PORT 5212
//client
int main(int argc,char** argv) {
//testing connection side!
    initialize_logging();

    int sockfd = connect_to_server(IP,PORT);
    assert(sockfd > 0);
    initial_request(sockfd, MESSAGING, PEER_PORT);
    
    complete_logging();
//int connect_to_peer(const char*,int);
//int listen_for_peer();

//close_connection()

}