#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define MAX_ARG_LEN 1024

int main(int argc, char *argv[]) {
    int n, buf_index = 0;
    char buf, arg[MAX_ARG_LEN], *args[MAXARG];

    if(argc < 2) {
        fprintf(STDERR, "xargs: wrong number of arguments\n");
        exit(0);
    }

    for(int i = 1; i < argc; ++i) args[i-1] = argv[i];
    args[argc-1] = arg; 
    args[argc] = 0;

    while( (n = read(STDIN, &buf, 1)) > 0 ) {
        if( buf == '\n' || buf == ' ') {
            arg[buf_index] = 0; 

            if(fork()){
                wait(0);
                buf_index = 0;
            } else {
                exec(args[0], args);
            }
        }
        else arg[buf_index++] = buf;
    }
    exit(0);
}