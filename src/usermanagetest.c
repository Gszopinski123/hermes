

#include "user_management.h"
#include "logging.h"
#include <stdio.h>
int main(void) {
    initialize_list();
    User_Info data = {.ip="127.0.0.1"};
    list->insert(&data);
    list->delete(&data);
    log_msg(ERROR,"HELlO!");
}