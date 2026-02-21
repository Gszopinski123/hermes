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
#include "client_request.h"
#include "packet_headers.h"
//prevent circular dependency: user_management.h
typedef struct user_info User_Info;



//server side
int open_for_connections(const char*,int);
User_Info* accept_connections(int);
Client_request_hdr initial_accept(int);
int send_client_peers(User_Info*);

//client side
int connect_to_server(const char*,int);
int connect_to_peer(const char*,int);
int listen_for_peer();
int initial_request(int, client_request_t, int);



int close_connection(int);

//future messaging functions 


#endif