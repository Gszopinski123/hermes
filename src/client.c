#include <stdio.h>
#include <string.h>
#include "network.h"
#include "dual_pipe.h"
#define NO_FLAGS 0
#define PORT 5001


int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Not enough arguments!\n");
        return 1;
    }
    #ifdef SERVER_CLIENT_DIFFERENT_MACHINE
        initialize_logging();
    #endif
    #ifdef PIPES_OPEN
        int err = initialize_startup(IN_PIPE_NAME,OUT_PIPE_NAME);
        if (err < 0) {
            return -1;
        }
        //need to make sure they do not deadlock
        int rfd = read_pipe_setup(IN_PIPE_NAME);
        int wfd = write_pipe_setup(OUT_PIPE_NAME);
        if (rfd < 0 || wfd < 0) {
            return -1;
        }
    #endif
    #ifdef CONNECTION_OPEN
        int sockfd = connect_to_server(argv[1],atoi(argv[2]));
        if (sockfd < 0) {
            return -1;
        }
        const char* msg = "Hello From Lothlorien!";
        send(sockfd,msg,strlen(msg),NO_FLAGS);
        close_connection(sockfd);
    #endif
    #ifdef PIPES_OPEN
        char buf[MAX_MSG_SIZE];
        read_pipe(rfd,buf);
        printf("%s\n",buf);
        write_pipe(wfd,"Hello driver!");
        close_pipe_fd(rfd);
        close_pipe_fd(wfd);
    #endif
    #ifdef SERVER_CLIENT_DIFFERENT_MACHINE
        complete_logging();
    #endif
    return 0;
}