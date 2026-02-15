/* Filename: dual_pipe.c
 * Author: Gabriel Szopinski
 * Description: Implementation of functions via dual_pipe.h. this file is an extention of
 * bi-directional pipe implementation. For more details check the header file. logging included
 *  
 */
#include "dual_pipe.h"

/* Function name: setup_pipe
 * Arguments: const char* filepath; Should contain a path/name to setup the named pipe
 * Return: 0 if there was no errors and success, -1 if there was any errors
 * Description: This function will created a named pipe based on the filepath provided and return success measures
 */

int setup_pipe(const char* filepath) {
    log_msg(PIPE,"setup_pipe: Starting setup");
    int err = mkfifo(filepath,WR_RD_USR_ONLY);
    if (errno == EEXIST) {
        log_msg(PIPE,"setup_pipe: pipe already exists");
        return 0;
    }
    if (err < 0) {
        log_msg(ERROR,"setup_pipe: pipe couldn't be created");
        return -1;
    }
    log_msg(PIPE,"setup_pipe: Finished setup");
    return 0;
}
/* Function name: read_pipe_setup
 * Arguments: const char* filepath; give a path to where to find the path/pipe
 * Return: if success will return the associated file descriptor with the pipe if not return -1
 * Description: Will open and set to read only for the named pipe that is based on the filepath
 */
int read_pipe_setup(const char* filepath) {
    log_msg(PIPE,"read_pipe_setup: Setting up read pipe");
    int fd = open(filepath,O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        log_msg(ERROR,"read_pipe_setup: invalid file descriptor");
        return -1;
    }
    log_msg(PIPE,"read_pipe_setup: Finished setting up read pipe");
    return fd;
}
/* Function name: write_pipe_setup
 * Arguments: const char* filepath; give a path to where to find the path/pipe
 * Return: if success will return the associated file descriptor with the pipe if not return -1
 * Description: will open and set to write only for the named pipe that is based on the filepath
 */
int write_pipe_setup(const char* filepath) {
    log_msg(PIPE,"write_pipe_setup: Setting up write pipe");
    int fd = open(filepath,O_WRONLY | O_NONBLOCK);
    if (fd < 0) {
        log_msg(ERROR,"write_pipe_setup: invalid file descriptor");
        return -1;
    }
    log_msg(PIPE,"write_pipe_setup: Finished setting up write pipe");
    return fd;
}
/* Function name: initialize_startup
 * Arguments: const char* in_path; the pipe that will be used to write to for the given process, 
              const char* out_path; the pipe that will be used to read from for the given process
 * Return: will return 0 if the setup was a success -1 otherwise
 * Description: This function will setup the named pipes for the ipc. The implementation uses semaphores to prevent race conditions.
 *              There are error checks for all critical parts of the code as marked. 
 */
int initialize_startup(const char* in_path, const char* out_path) {
    log_msg(PIPE,"initialing startup: semaphore creation");
    sem_t *sem = sem_open(SEMAPHORE_TAG,O_CREAT, WR_RD_USR_ONLY, NO_FLAGS);
    if (sem == SEM_FAILED) {
        log_msg(ERROR,"initialize_startup: semaphore creation failure");
        return -1;
    }
    int err;
    err = setup_pipe(in_path);
    if (err != 0) {
        log_msg(ERROR,"initialize_startup: in_path failure");
        return -1;
    }
    err = setup_pipe(out_path);
    if (err != 0) {
        log_msg(ERROR,"initialize_startup: out_pipe failed");
        return -1;
    }
    sem_post(sem);
    sem_close(sem);
    log_msg(PIPE,"initialize_startup: Initialing startup success: semaphore closed");
    return 0;

}
/* Function name: wait_initialization
 * Arguments: none
 * Return: 0 if success or block/run forever if failure
 * Description: Will be used for the process that doesn't created the pipes and must wait to synchronize. This function will be
 *              The second half of the synchronization process to prevent race conditions. Just a simple semaphore setup.
 */
int wait_initialization() {
    log_msg(PIPE,"wait_initialization: starting to wait for semaphore");
    sem_t *sem;
    while ((sem = sem_open(SEMAPHORE_TAG,NO_FLAGS)) == SEM_FAILED)
        ;;
    sem_wait(sem);
    sem_unlink(SEMAPHORE_TAG);
    sem_close(sem);
    log_msg(PIPE,"wait_initialization: Waiting finished semaphore closed");
    return 0;
}
/* Function name: write_pipe
 * Arguments: int pipe_fd; the pipe file descriptor to send a message to the pipe,
              const char* msg; the associated message we want to write to the pipe
 * Return: if success will return the number of bytes written if not return -1
 * Description: will take in a file descriptor write a message to the pipe and return a measure of success
 */
int write_pipe(int pipe_fd, const char* msg) {
    char log_mg[512];
    sprintf(log_mg,"write_pipe: Writing to pipe %d",pipe_fd);
    log_msg(PIPE,log_mg);
    int msg_len = strlen(msg);
    if (msg_len > MAX_MSG_SIZE-1) {
        log_msg(ERROR,"write_pipe: Buffer size too large");
        return -1;
    }
    int num_bytes = write(pipe_fd,msg,msg_len);
    sprintf(log_mg,"write_pipe: Writing to pipe complete %d",pipe_fd);
    return num_bytes;
}
/* Function name: read_pipe
 * Arguments: int pipe_fd; the pipe file descriptor to receive or check for messages,
              char* buf; is used to record the message that was sent across the pipe
 * Return: if success will return the number of bytes read if not return -1
 * Description: will take in a file descriptor read from that associated pipe and return a measure of success
 */
int read_pipe(int pipe_fd, char* buf) {
    char msg[512];
    sprintf(msg,"read_pipe: Reading from pipe: %d",pipe_fd);
    log_msg(PIPE,msg);
    int num_bytes = read(pipe_fd,buf,BUFFER_SIZE-1);
    sprintf(msg,"read_pipe: Reading from pipe complete: %d",pipe_fd);
    log_msg(PIPE,msg);
    return num_bytes;
}
/* Function name: close_pipe_fd
 * Arguments: int pipe_fd; pipe file descriptor needs to be closed
 * Return: if successifully closed will return 0 if not error will be thrown
 * Description: closes the pipe file descriptor
 */
int close_pipe_fd(int pipe_fd) {
    char msg[512];
    sprintf(msg,"close_pipe_fd: Attempting to close pipe: %d",pipe_fd);
    log_msg(PIPE,msg);
    close(pipe_fd);
    sprintf(msg,"close_pipe_fd: Pipe closed: %d",pipe_fd);
    log_msg(PIPE,msg);
    return 0;
}