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
int initial_request(int server_sock_fd, client_request_t req) {
    log_msg(NETWORK,"initial_request: starting client request");
    char*buf = malloc(BUFFER_SIZE);
    if (buf == NULL) {
        log_msg(ERROR,"initial_request: resource allocation failure");
        return -1;
    }
    Client_request_hdr *new_req = (Client_request_hdr*)buf;
    new_req->req = req;
    int bytes = send(server_sock_fd, buf, BUFFER_SIZE-1, NO_FLAGS);
    if (bytes < 0) {
        free(buf);
        log_msg(ERROR,"initial_request: request did not send");
        return -1;
    }
    free(buf);
    log_msg(NETWORK,"initial_request: client request complete");
    return 0;
}

client_request_t initial_accept(int client_sock_fd) {
    log_msg(NETWORK,"initial_accept: starting client accept");
    char *buf = malloc(BUFFER_SIZE);
    if (buf == NULL) {
        log_msg(ERROR,"initial_accept: resource allocation failure");
    }
    int bytes = recv(client_sock_fd,buf,BUFFER_SIZE-1,NO_FLAGS);
    if (bytes < 0) {
        log_msg(ERROR,"initial_accept: message failed to receive");
    }
    Client_request_hdr* new_req = (Client_request_hdr*)buf;
    client_request_t cli_req = new_req->req;
    free(buf);
    log_msg(NETWORK,"initial_accept: client accept completed");
    return cli_req;
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
    log_msg(NETWORK,"close_connection: ");
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
    inet_pton(AF_INET,ip,&server->sin_addr);
    server->sin_port = htons(port);
    server->sin_family = AF_INET;
    if (server == NULL) {
        log_msg(ERROR,"open_for_connection: failure to allocated resources");
        close(sockfd);
        return -1;
    }
    socklen_t server_len = sizeof(struct sockaddr_in);
    af = bind(sockfd,(struct sockaddr*)server,server_len);
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
// need to start storing connections
// a slight gap between the handshake and the initial message
int accept_connections(int sockfd) {
    log_msg(NETWORK,"accept_connection: accepting connections!");
    struct sockaddr_in* client;
    socklen_t client_len = 0;
    int client_fd = accept(sockfd,(struct sockaddr*)client,&client_len);
    char *ip = malloc(INET_ADDRSTRLEN); 
    User_Info *new_user = malloc(sizeof(User_Info));
    if (ip == NULL || new_user == NULL) {
        log_msg(ERROR,"accept_connection: resource allocation failure!\n");
        return -1;
    }
    inet_ntop(AF_INET,&client->sin_addr,ip,INET_ADDRSTRLEN);
    new_user->ip = ip;
    new_user->fd = client_fd;
    list->insert(new_user);
    log_msg(NETWORK,"accept_connection: client accepted!");
    return client_fd;
}