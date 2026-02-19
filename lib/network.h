/* Filename: network.h
 * Author: Gabriel Szopinski
 * Description: This file should help abstract away "ugly" boilerplate code.
 * It should also help manage connections
 */


#ifndef NETWORK_H
#define NETWORK_H

#define QUEUE_BACKLOG 5
//associated Libraries
#include "dual_pipe.h"
#include "logging.h"
#include "user_management.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>



typedef enum client_request {
    MESSAGING,
    IOT
    // These options are under proposition
    // FILE,
    // STORAGE,
    // VPN
} client_request_t;


typedef struct client_request_hdr {
    client_request_t req;
} Client_request_hdr;

//server side
int open_for_connections(const char*,int);
int accept_connections(int);
client_request_t initial_accept(int);
send_client_peers(int);

//client side
int connect_to_server(const char*,int);
int connect_to_peer(const char*,int);
int listen_for_peer();



int close_connection(int);

//future messaging functions 


#endif