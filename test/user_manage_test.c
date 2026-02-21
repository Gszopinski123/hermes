

#include <assert.h>
#include "user_management.h"
#include <stdlib.h>
// can take a while but that is because I am doing a random search versus a sequential search
#define SIZEOFIP 32
#define SIZE_OF_LIST 10

void view_list(Linked_List *list);
char* random_string_generator();
void free_ls_strings(char***ls);
int check_catalog(int*ls);

int main(void) {
    srand(time(NULL));
    initialize_logging();
    initialize_management();
    char***ls;
    ls = (char***)malloc(sizeof(char***)*SIZE_CLIENT_REQ);
    int string_catalog[SIZE_CLIENT_REQ][SIZE_OF_LIST] = {0};
    for (int i = 0; i != SIZE_CLIENT_REQ; i++) {
        ls[i] = (char**)malloc(sizeof(char**)*SIZE_OF_LIST);
        int count = 0;
        for (int j = 0; j != SIZE_OF_LIST; j++) {
            ls[i][j] = malloc(SIZEOFIP);
            char * ip = random_string_generator();
            memcpy(ls[i][j],ip,SIZEOFIP);
            User_Info user = {.fd=-1,.ip=ip,.is_open=0,.req=MESSAGING};
            list[i]->insert(&user,i);
            // testing count
            assert(list[i]->find(&user,i) == 1);
            assert(list[i]->len == ++count);
        }
    }

    for (int i = 0; i != 2; i++) {
        int count = SIZE_OF_LIST;
        while (!check_catalog(string_catalog[i])) {
            int rand_index = rand() % SIZE_OF_LIST;
            if (string_catalog[i][rand_index]) {
                continue;
            }
            string_catalog[i][rand_index] = 1;
            User_Info user = {.ip=ls[i][rand_index]};
            list[i]->delete(&user,i);
            // testing count
            assert(list[i]->find(&user,i) == 0);
            assert(--count == list[i]->len);
        } 
    }
    


    free_ls_strings(ls);
    destroy_management();
    complete_logging();
}

int check_catalog(int*ls) {
    for (int i= 0; i !=SIZE_OF_LIST; i++) {
        if (ls[i] == 0) { 
            return 0;
        }
    }
    return 1;
}


char* random_string_generator() {
    char* string = malloc(SIZEOFIP);
    for (int i = 0; i != SIZEOFIP-1; i++) {
        char s = (rand() % 26) + 65;
        string[i] = s;
        //65-90 -> 26
    }
    string[SIZEOFIP-1] = '\0';
    return string;
}


void view_list(Linked_List *list) {
    Node* temp = list->head;
    while(temp != NULL) {
        printf("%s\n",temp->data->ip);
        temp = temp->next;
    }

}
void free_ls_strings(char***ls) {
    for (int i = 0; i != SIZE_CLIENT_REQ; i++) {
        for (int j = 0; j != SIZE_OF_LIST; j++) {
            free(ls[i][j]);
        }
        free(ls[i]);
    }
    free(ls);
}