package main

import "dual_pipe/dual_pipe"
import "fmt"

func main() {
	dual_pipe.Wait_intialization()
	writeFilePtr := dual_pipe.Write_pipe_setup(dual_pipe.OUT_PIPE_NAME);
	readFilePtr := dual_pipe.Read_pipe_setup(dual_pipe.IN_PIPE_NAME);

	buf := make([]byte,dual_pipe.MAX_MSG_SIZE)
	dual_pipe.Write_pipe(writeFilePtr,[]byte("Hello Other side!"))
	dual_pipe.Read_pipe(readFilePtr,buf)
	fmt.Printf("%s\n",buf)
	


	dual_pipe.Cleanup_pipe(writeFilePtr)
	dual_pipe.Cleanup_pipe(readFilePtr)
	fmt.Println("Hello Machine!")

}