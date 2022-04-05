#include "kernel/types.h"
#include "user/user.h"

# define READ 0
# define WRITE 1

void callRight(int* left){
	close(left[WRITE]);

	int prime, right[2], status, pid, temp;
	pipe(right);
	// pipe() must initial before fork().
	// Because fork() will create child with same memory contents.
	// I put it after fork(), that points to wrong answer.

	// read first value from left process.
	status = read(left[READ], &prime, sizeof(int));
	if(status == 0) exit(0);

	printf("prime %d\n", prime);

	pid = fork();

	if(pid == 0) callRight(right);
	else {
		close(right[READ]);
		while(read(left[READ], &temp, sizeof(int))){
			if(temp % prime == 0) continue;
			write(right[WRITE], &temp, sizeof(int));
		}
		close(right[WRITE]);
		wait(0);
		exit(0);
	}
}

int main(){
	int pid, p[2];
	pipe(p);
	
	pid = fork();
	if(pid == 0){ // child
		callRight(p);
	} else { // parent
		close(p[READ]);
		for(int i=2; i<=35; i++) write(p[WRITE], &i, sizeof(int));
		close(p[WRITE]);
		wait(0);
	}

	exit(0);
}
