#include "network.h"
#include "logging.h"
#include "user_management.h" 
//#include "dual_pipe.h"


int main(int argc, char** argv) {
    if (argc < 3) {
        return -1;
    }
    initialize_logging();
    //data structure creation
    //initialize_list();
    //server creation    
    char*ip = argv[1];
    int port = atoi(argv[2]);
    int sockfd = open_for_connections(ip,port);
    int clientfd;
    while (1) {
        clientfd = accept_connections(sockfd);
        client_request_t cli_req = initial_accept(clientfd);
        // do something wtih cli_req
        send_client_peers(clientfd);
    }
    close_connection(sockfd);
    close_connection(clientfd);
    
    //data structure destruction issue with this
    //destroy_list();
    complete_logging();
    return 0;
}