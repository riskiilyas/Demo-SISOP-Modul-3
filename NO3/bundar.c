#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include<pthread.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<math.h>
#define R 7
#define PI 3.14

int main() {
    key_t key = 1234;
    double *luas;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    luas = shmat(shmid, NULL, 0);

    *luas = PI*R*R;

    printf("Luas Lingkaran : %lf\n", *luas);

    sleep(5);

    shmdt(luas);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}