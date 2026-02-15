/* Filename: network.c
 * Author: Gabriel Szopinski
 * Description: the source code for the network portion of this application. boilerplate code 
 */

#include "network.h"
/* Function name: connect_to_server
 * Arguments: const char* ip; the ip address associated with the always on server
              int port; the port associated with the always on server
 * Return: int; a file descriptor to the always on server 
 */

int connect_to_server(const char* ip,int port) {
    log_msg(NETWORK,"connect_to_server: starting connection to 'always-on' server");
    int sockfd = socket(AF_INET,SOCK_STREAM,NO_FLAGS);
    if (sockfd < 0) {
        log_msg(ERROR,"connect_to_server: file descriptor failure");
        return -1;
    }
    struct sockaddr_in* server = malloc(sizeof(struct sockaddr_in));
    if (server == NULL) {
        log_msg(ERROR,"connect_to_server: resource allocation failure");
        close(sockfd);
        return -1;
    }
    inet_pton(AF_INET,ip,&server->sin_addr);
    server->sin_family = AF_INET;
    server->sin_port = htons(port);
    int err = connect(sockfd,(struct sockaddr*)server,sizeof(struct sockaddr_in));
    if (err < 0) {
        log_msg(ERROR,"connect_to_server: connection failure");
        free(server);
        close(sockfd);
        return -1;
    }
    log_msg(NETWORK,"connect_to_server: connection to 'always-on' server success");
    free(server);
    return sockfd;
}
int connect_to_peer(const char* ip,int port) {
    return 0;
}
int listen_for_peer() {
    return 0;
}
/* Function name: close_connection
 * Arguments int sockfd; The socket(file descriptor) that needs to be closed
 * return: int 0 upon success 
 * Description: This function's purpose is too help clear up any overhead that is generated.
 *              via future data structures that are allocated or other resources
 */
int close_connection(int sockfd) {
    log_msg(NETWORK,"close_connection: closing server connection");
    close(sockfd);
    return 0;
}
/* Function name: open_for_connection
 * Arguments: const char* ip; the ip in string format the server needs to bind to.
              int port; the port associated with the server
 * Return int; 0 upon successiful setup of the server, otherwise for failure
 * Description: This function will setup the server and get it ready for connections.
 */
int open_for_connections(const char* ip,int port) {
    log_msg(NETWORK,"open_for_connection: starting up server for connections");
    int sockfd = socket(AF_INET,SOCK_STREAM,NO_FLAGS);
    if (sockfd < 0) {
        log_msg(ERROR,"open_for_connection: failure to setup socket");
        return -1;
    }
    int af;
    struct sockaddr_in* server = malloc(sizeof(struct sockaddr_in));
    if (server == NULL) {
        log_msg(ERROR,"open_for_connection: failure to allocated resources");
        close(sockfd);
        return -1;
    }
    int server_len = sizeof(struct sockaddr_in);
    af = bind(sockfd,(struct sockaddr*)server,&server_len);
    if (af < 0) {
        log_msg(ERROR,"open_for_connection: failure to bind socket");
        close(sockfd);
        free(server);
        return -1;
    }

    af = listen(sockfd,QUEUE_BACKLOG);
    if (af < 0) {
        log_msg(ERROR,"open_for_connection: unable to listen for connections");
        free(server);
        close(sockfd);
        return -1;
    }
    free(server);
    log_msg(NETWORK,"open_for_connection: Server Successifully setup");
    return sockfd;
}