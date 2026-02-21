#include "network.h"
#include <assert.h>
#define IP "127.0.0.1"
#define PORT 5001
#define PEER_PORT 5212

int main(int argc, char** argv) {
    initialize_logging();
    int sockfd = open_for_connections(IP,PORT);
    assert(sockfd > 0);
    User_Info* user = accept_connections(sockfd);
    //IP is wildcard
    //Port is also wildcard

    Client_request_hdr cli_hdr = initial_accept(user->fd);
    assert(cli_hdr.port_for_peers == PEER_PORT);
    assert(cli_hdr.req == MESSAGING);
    //int send_client_peers(User_Info*);
    close_connection(sockfd);
    complete_logging();
}