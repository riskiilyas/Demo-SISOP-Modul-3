#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#define MSGSIZE 100

// parent -> child: hello
// child -> parent: hi

int main() {
    int pipe1[2];
    int pipe2[2];

    char parentToChild[] = "hello";
    char childToParent[] = "hi";
	char inbuf[MSGSIZE]; 

    pid_t pid;

    if(pipe(pipe1)<0) {
        exit(1); 
    }

    if(pipe(pipe2)<0) {
        exit(1); 
    }

    pid = fork();

    if(pid<0){
        // ERROR
        exit(1); 
    } else if(pid==0) {
        // CHILD
        write(pipe1[1], childToParent, MSGSIZE);
        read(pipe2[0], inbuf, MSGSIZE); 
		printf("Dari CHILD: %s\n", inbuf);     
    } else {
        // PARENT
        write(pipe2[1], parentToChild, MSGSIZE);
        read(pipe1[0], inbuf, MSGSIZE); 
		printf("DARI PARENT: %s\n", inbuf);  
    }

    return 0;
}