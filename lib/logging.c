/* Filename: logging.c
 * Author: Gabriel Szopinski
 * Description: This library is used to effectively log actions during the applications lifetime.
 * This is a skeleton file and is really only meant for development and not for user debugging.
 */

#include "logging.h"
//global log file
static FILE * log_file;
/* Function name: convert_log_level
 * Arguments: log_level_t level; This is the enum to determine what kind of log
 * return: char*; a string that contains the typed out enum
 * Description: This function is used to convert an enum to a string for logging properly
 */
char* convert_log_level(log_level_t level) {
    switch(level) {
        case NETWORK:
            return "NETWORK";
        case ERROR:
            return "ERROR";
        case PIPE:
            return "PIPE";
        case USER:
            return "USER";
        case DATA:
            return "DATA";
    }
}
/* Function name: log_msg
 * arguments: log_level_t level; used to determine a basic classification of log
              const char* msg; a specialized message to determine quickly what is happening
 * return: void
 * Description: This function is to make a log message based on the given arguments
 *               it is then to append the log to the log file as provied in logging.h
 */
// Think about adding semaphores for synchronization
void log_msg(log_level_t level, const char* msg) {
    log_file = fopen(LOG_FILE,"a");
    char * level_str = convert_log_level(level);
    time_t time_now; 
    time(&time_now);
    char* time_as_str = strdup(ctime(&time_now));
    time_as_str[strlen(time_as_str)-1] = '\0';
    fprintf(log_file,"[%s] [%s] %s\n",time_as_str,level_str,msg);
    fclose(log_file);
}