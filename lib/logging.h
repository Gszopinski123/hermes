/* Filename: Logging.h
 * Author: Gabriel Szopinski
 * Description: A basic logging library for use in the mboard project
 */

#ifndef LOGGING_H
#define LOGGING_H
//associated libraries
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LOG_FILE "log/app.log"
// Log types important for logging
typedef enum log_level {
    NETWORK,
    PIPE,
    USER,
    ERROR,
    DATA
} log_level_t;
//functions to support logging
char* convert_log_level(log_level_t);
void log_msg(log_level_t, const char*);



#endif