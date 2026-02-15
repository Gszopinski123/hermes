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
//structs need for processing users properly
// Needs to be updated but ok for now 2/7/26
typedef struct user_info {
    char* ip;
} User_Info;

typedef struct node {
    User_Info* data;
    struct node* next;
} Node;

typedef struct linked_list {
    Node* head;
    Node* last;
    int len;
    void(*insert)(User_Info*);
    void(*delete)(User_Info*);
} Linked_List;

extern Linked_List *list;

//functions associated with a linked_list
int initialize_list();
void insert(User_Info*);
void delete(User_Info*);
#endif