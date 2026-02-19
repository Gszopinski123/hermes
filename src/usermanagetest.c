

#include "user_management.h"
#include "logging.h"
#include <stdio.h>
int main(void) {
    initialize_list();
    char *ip = malloc(16);
    snprintf(ip,16,"127.0.0.1");
    User_Info *data = malloc(sizeof(User_Info));
    data->ip=ip;
    list->insert(data);
    // list->delete(&data);
    log_msg(ERROR,"HELlO!");
    destroy_list();
}