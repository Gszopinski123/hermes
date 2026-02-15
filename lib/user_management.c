/* Filename: user_management.c
 * Author: Gabriel Szopinski
 * Description: library is to help manage the influx of users and eventually "pass" them off
 */

//associated header
#include "user_management.h"
//global list of users (temporary)
Linked_List* list = NULL;
/* Function name: initialize_list
 * arguments: void;
 * return: int; 0 upon successiful creation of the list or -1 upon failure
 * Description: This function will generate a linked list and setup the list
 */
int initialize_list() {
    list = malloc(sizeof(Linked_List));
    if (list == NULL) {
        return -1;
    }
    list->len = 0;
    list->head = NULL;
    list->last = NULL;
    list->insert = &insert;
    list->delete = &delete;
    return 0;
}
/* File name: delete
 * arguments: User_Info* data; the data that needs to be removed from the list
 * return: void;
 * Description: find the data and removed it from the list
 */
void delete(User_Info* data) {
    // loop through the linkedlist
    Node* temp = list->head;
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
    
    // 2. data was in the head slot
    if (prev == NULL) {
        if (list->last == list->head) {
            list->last = NULL;
        }
        list->head = temp->next;
        free(temp);
        return;
    }
    // 3. data was somewhere in the list
    //reconnect
    prev->next = temp->next;
    //free memory
    free(temp);
    return;
}
/* Function name: insert
 * arguments: User_Info * new_data; the data that needs to be placed in the list
 * return: void;
 * Description: will insert a new piece of data into the list
 */
void insert(User_Info* new_data) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return;
    }
    new_node->data = new_data;
    new_node->next = NULL;
    // assumed that list is already allocated.
    // special case when there are no items.
    if (list->len == 0) {
        list->head = new_node;
        list->last = new_node;
        return;
    }
    list->len++;
    //attached
    list->last->next = new_node;
    //reassign
    list->last = new_node;
    return;
}