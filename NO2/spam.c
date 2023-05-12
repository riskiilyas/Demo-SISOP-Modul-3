#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include <pthread.h>

/*
    spam.c

    process 1 -> print 1-1.000.000 dipisah dgn \n ke angka.txt
    process 2 -> folder dgn nama /latihan & bkin subfolder /{1-100}. pke multithreading
                masukkan angka.txt ke dalam subfolder2 tsb
*/

void* buatSubfolder(void*arg){
    int *i = arg;

    char inp[100];
    sprintf(inp, "mkdir latihan/%d", *i);
    system(inp);

    char inp2[100];
    sprintf(inp2, "cp angka.txt latihan/%d", *i);
    system(inp2);
}

int main() {
    pid_t p1, p2;

    p1 = fork();
    if(p1<0){
        exit(1);
    } else if(p1==0){
        system("touch angka.txt");
        for(int i=1; i<=1000000; i++) {
            char inp[100];
            sprintf(inp, "echo %d >> angka.txt", i);
            system(inp);
        }
        exit(1);
    }

    p2 = fork();
    if(p2<0){
        exit(1);
    } else if(p2==0){
        system("mkdir latihan");
        pthread_t t[100];
        for(int i=0; i<100; i++) {
            int *num_to_check = (int *)malloc(sizeof(int));
		    *num_to_check = i;
            pthread_create(&t[i], NULL, buatSubfolder, (void *)num_to_check);
        }

        for(int i=0; i<100; i++) {
            pthread_join(t[i], NULL);
        }
        exit(1);
    }

    return 0;
}