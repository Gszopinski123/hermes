### Commentary
 * I will add a cmake file once the software is properly built for macos/linux
 * May need to switch to cpp for better bolierplate code and oop presence 
 * think about multithreading and multiprocesses
 * need to place a new connection in "purgatory" until we get it's request
   * should close after waiting 30seconds-1minute (will help clear dead buffer/connection)
 * remember that client doesn't need to fit server requirements
   * in other words, server will more or less be homogenous whereas client is going to be heterogenous
 * buckets for each different network:
 * Remember that if we are just running client we must include a macro
 * if we are running client and server on the same machine do not include the macro
 * need to start using makefile for the separate builds