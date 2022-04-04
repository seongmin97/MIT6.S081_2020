#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
	if(argc != 2) write(1, "Wrong number of arguments\n", strlen("Wrong number of arguments"));
	
	int t = atoi(argv[1]);
	sleep(t);

	write(1, "sleep done!\n", strlen("sleep done!\n")); 

	exit(0);
}
