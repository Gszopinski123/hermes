package dual_pipe

import (
	"os"
	/*
		#cgo CFLAGS: -I../lib
		#include "dual_pipe.h"
		#include "dual_pipe.c"
		#include "logging.h"
		#include "logging.c"
	*/
	"C"
)

const IN_PIPE_NAME  = "data/out_pipe"
const OUT_PIPE_NAME = "data/in_pipe"


const MAX_MSG_SIZE int = 1024
const BUFFER_SIZE int = 1024

// Go Wrapper for wait_initialization
func Wait_intialization() int {
	var err int = int(C.wait_initialization())
	return err
}

func Read_pipe_setup(pathname string) *os.File {
	var filemode os.FileMode
	fileptr, err := os.OpenFile(pathname, os.O_RDONLY, filemode)
	if err != nil {
		return nil
	}	
	return fileptr
}

func Write_pipe_setup(pathname string) *os.File {
	var filemode os.FileMode
	fileptr, err := os.OpenFile(pathname,os.O_WRONLY, filemode)
	if err != nil {
		return nil
	}
	return fileptr
}

func Cleanup_pipe(pipename *os.File) {
	pipename.Close()
}

func Read_pipe(fileptr *os.File, buf []byte) int {
	bytes,err := fileptr.Read(buf)
	if err != nil {
		return -1
	}
	return bytes
}

func Write_pipe(fileptr *os.File, msg []byte) int {
	msg_len := len(msg);
	if msg_len > MAX_MSG_SIZE-1 {
		return -1;
	}
	bytes,err := fileptr.Write(msg);
	if err != nil {
		return -1;
	}
	return bytes;
}
