#ifndef CLIENT_REQUEST_H
#define CLIENT_REQUEST_H

typedef enum client_request {
    MESSAGING,
    IOT,
    // These options are under proposition
    // FILE,
    // STORAGE,
    // VPN
    SIZE_CLIENT_REQ
} client_request_t;

#endif