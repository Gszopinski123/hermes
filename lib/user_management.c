/* Filename: user_management.c
 * Author: Gabriel Szopinski
 * Description: library is to help manage the influx of users and eventually "pass" them off
 */

//associated header
#include "user_management.h"
//global list of users (temporary)
Linked_List* list[SIZE_CLIENT_REQ] = {NULL};

int initialize_management() {
    log_msg(DATA,"initialize_management: Intializing buckets");
    for (int i = 0; i != SIZE_CLIENT_REQ; i++) {
        if (initialize_list(i) < 0) {
            log_msg(ERROR,"initialize_management: Resource allocation failure");
            return -1;
        }
    }
    log_msg(DATA,"initialize_management: Buckets created");
    return 0;
}

int destroy_management() {
    log_msg(DATA,"destroy_management: starting deallocation");
    for (int i = 0; i != SIZE_CLIENT_REQ; i++) {
        if (destroy_list(i) < 0) {
            log_msg(ERROR,"destroy_management: Failure to deallocate");
            return -1;
       }
    }
    log_msg(DATA,"destroy_management: deallocation complete");
    return 0;
}

/* Function name: initialize_list
 * arguments: void;
 * return: int; 0 upon successiful creation of the list or -1 upon failure
 * Description: This function will generate a linked list and setup the list
 */
int initialize_list(client_request_t index) {
    list[index] = malloc(sizeof(Linked_List));
    if (list[index] == NULL) {
        return -1;
    }
    list[index]->len = 0;
    list[index]->head = NULL;
    list[index]->last = NULL;
    list[index]->insert = &insert;
    list[index]->delete = &delete;
    list[index]->find = &find;
    return 0;
}
/* File name: delete
 * arguments: User_Info* data; the data that needs to be removed from the list
 * return: void;
 * Description: find the data and removed it from the list
 */
void delete(User_Info* data,client_request_t index) {
    // loop through the linkedlist
    Node* temp = list[index]->head;
    Node* prev = NULL;
    while (temp != NULL && strcmp(data->ip, temp->data->ip)) {
        prev = temp;
        temp = temp->next;
    }
    //3 cases 
    // 1. data not found
    if (temp == NULL) {
        return;
    }
    list[index]->len--;
    // 2. data was in the head slot
    if (prev == NULL) {
        if (list[index]->last == list[index]->head) {
            list[index]->last = NULL;
        }
        list[index]->head = temp->next;
        destroy_node(temp);
        return;
    }
    // 3. data was somewhere in the list
    //reconnect
    prev->next = temp->next;
    //free memory
    destroy_node(temp);
    return;
}
/* Function name: insert
 * arguments: User_Info * new_data; the data that needs to be placed in the list
 * return: void;
 * Description: will insert a new piece of data into the list
 */
void insert(User_Info* new_data, client_request_t index) { 
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return;
    }
    // This will completely transfer ownership over to the application
    User_Info* data = malloc(sizeof(User_Info));
    memcpy(data,new_data,sizeof(User_Info));
    //ownership is swapped
    new_node->data = data;
    new_node->next = NULL;
    // assumed that list is already allocated.
    // special case when there are no items.
    if (list[index]->len == 0) {
        list[index]->head = new_node;
        list[index]->last = new_node;
        list[index]->len++;
        return;
    }
    list[index]->len++;
    //attached
    list[index]->last->next = new_node;
    //reassign
    list[index]->last = new_node;
    return;
}

int find(User_Info* user, client_request_t index) {
    Node* temp = list[index]->head;
    if (temp == NULL) {
        return 0;
    }
    while (temp != NULL && strcmp(temp->data->ip,user->ip)) {
        temp = temp->next;
    }
    if (temp == NULL) {
        return 0;
    }
    return 1;
} 

void destroy_user_info(User_Info* curr) {
    free(curr->ip);
    free(curr);
}

void destroy_node(Node *curr) {
    destroy_user_info(curr->data);
    free(curr);
}

int destroy_list(client_request_t index) {
    if (list[index] == NULL) {
        return 0;
    }
    Node* prev;
    Node* cur = list[index]->head;
    while (cur != NULL) {
        prev = cur;
        cur = cur->next;
        destroy_node(prev);
    }
    free(list[index]);
    return 0;
}