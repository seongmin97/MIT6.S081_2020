#include "kernel/types.h"
#include "user/user.h"

int main(){
	int pid, pfd[2], cfd[2];
	pipe(pfd);
	pipe(cfd);

	char buf[32];	
	pid = fork();

	if(pid == 0){ // this is child
		read(pfd[0], buf, 4);
		printf("%d: received %s\n", getpid(), buf);
		write(cfd[1], "pong", 4);
	} else { // this is parent
		write(pfd[1], "ping", 4);
		read(cfd[0], buf, 4);
		printf("%d: received %s\n", getpid(), buf);
	}

	exit(0);
}
