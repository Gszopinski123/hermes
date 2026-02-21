#ifndef PACKET_HEADERS_H
#define PACKET_HEADERS_H
#include "client_request.h"

//server-headers
// what the server will send to a client
//This enum will help determine what kinda of packet will be sent to the client
typedef enum option_header {
    PEER_LIST,
    CHECK_IN,
} option_header_t;

typedef struct check_in_hdr {
    int status;
} Check_in_hdr;

typedef struct peer_list_hdr {
    int num_of_peers;
} Peer_list_hdr;

typedef union packet_header_options {
        Check_in_hdr check;
        Peer_list_hdr peer;
} Packet_header_options;

typedef struct server_packet_hdr {
    option_header_t opt;
    Packet_header_options hdr_option;
    int payload_size;//without header
} Server_packet_hdr;

typedef struct peer_meta_data {
    char*ip;
    int port;
} Peer_meta_data;



// client-headers
// what a client will send to the server
typedef struct client_request_hdr {
    client_request_t req;
    int port_for_peers;
} Client_request_hdr;


#endif