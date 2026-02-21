/* Filename: dual_pipe.h
 * Author: Gabriel Szopinski (szopinski00@gmail.com)
 * Description: This header file is used to keep track of functions, data structures, or other info needed
 * across files. This file is called dual_pipe.h for two reasons. 1. For the use of named pipes, and 2. bi-directional activity 
 * or aka full duplex. In other words, this file will contain communication functions for both directions and setup functions
 */
#ifndef DUAL_PIPE_H
//Macros associated
#define DUAL_PIPE_H
#define WR_RD_USR_ONLY 0660
#define NO_FLAGS 0
#define CLOSED_SEMAPHORE 0
#define SEMAPHORE_TAG "/pipes_ready"
#define MAX_MSG_SIZE 1024
#define BUFFER_SIZE 1024
#define IN_PIPE_NAME "data/in_pipe"
#define OUT_PIPE_NAME "data/out_pipe"
// Libraries associated
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>
#include "logging.h"
// Function to start pipe!
// will return 0 upon success, a non-zero integer upon failure!
int setup_pipe(const char*);
// These functions will connect to the pipe and either write or read from the pipe
// Will return a file descriptor upon successiful connection, a negative integer upon failure!
int read_pipe_setup(const char*);
int write_pipe_setup(const char*);
// setup pipes with synchronization(semaphores)
// These will call the setupPipe implementation
int wait_initialization();
int initialize_startup(const char*, const char*);
// will be used to ease the process of writing and reading from pipes
int read_pipe(int, char*);
int write_pipe(int, const char*);
int close_pipe_fd(int);

#endif