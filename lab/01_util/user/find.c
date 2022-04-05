#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char* fmtname(char *path){ // this function uses to find first character after last slash
	char *p;
	for(p=path+strlen(path); p >= path && *p != '/'; p--);
	return ++p;
}

void find(char* path, char* file){
	int fd;
	struct stat st;
	struct dirent de;
	char buf[512], *p;
	
	if((fd = open(path, 0)) < 0){ // check if the path can be opened.
		fprintf(2, "find: cannot open %s\n", path);
		return;
	}

	if(fstat(fd, &st) < 0){ // get the state of the path.
		fprintf(2, "find: cannot state %s\\n", path);
		close(fd);
		return;
	}
	
	switch(st.type){
		case T_FILE:
			if(strcmp(fmtname(path), file) == 0) printf("%s\n", path);
			break;
		case T_DIR:
			strcpy(buf, path);
			p = buf+strlen(buf);
			*p++ = '/';

			// read the files in the directory
			while(read(fd, &de, sizeof(de)) == sizeof(de)){
				if(de.inum == 0 || 
					strcmp(de.name, ".") == 0 ||
					strcmp(de.name, "..") == 0)  continue;
				memmove(p, de.name, DIRSIZ);
				p[DIRSIZ]=0;
				find(buf, file);
			}
			break;
	}
	close(fd);

}

int main(int argc, char *argv[]){
	if(argc != 3) {
		fprintf(2, "find: error number of params\n");
		exit(1);
	}
	find(argv[1], argv[2]);
	exit(0);
}
