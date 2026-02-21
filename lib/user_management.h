/* Filename: user_management.h
 * Author: Gabriel Szopinski
 * Description: A requirement for a peer-to-peer network is an 
 * "always-on-server". The conceptualization is simple, 
 * but implementation can be tricky. This library header 
 * should ease the process of quickly managing users and leave delay time to a
 * minimum. 
 */

#ifndef USER_MANAGEMENT_H

#define USER_MANAGEMENT_H

//necessary functions to carry out objective
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "network.h"
#include "client_request.h"
//structs need for processing users properly
// Needs to be updated but ok for now 2/7/26


//User_info: ip must be heap allocated!
typedef struct user_info {// 24 bytes?
    char* ip;
    int fd;
    int is_open;
    int port_for_peers;
    int port_for_server;
    client_request_t req;
} User_Info;

typedef struct node {
    User_Info* data;
    struct node* next;
} Node;

typedef struct linked_list {
    Node* head;
    Node* last;
    int len;
    void(*insert)(User_Info*,client_request_t);
    void(*delete)(User_Info*,client_request_t);
    int(*find)(User_Info*,client_request_t);
} Linked_List;

extern Linked_List *list[SIZE_CLIENT_REQ];

//functions associated with a linked_list
int initialize_list(client_request_t);
int initialize_management();
void insert(User_Info*,client_request_t);
void delete(User_Info*,client_request_t);
int find(User_Info*,client_request_t);
void destroy_user_info(User_Info*);
void destroy_node(Node*);
int destroy_list(client_request_t);
int destroy_management();
#endif