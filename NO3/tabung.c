#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include <pthread.h>
#include <sys/shm.h>
#include<sys/ipc.h>
#include<math.h>
#define T 10

int main() {
    key_t key = 1234;
    double *luas_lingkaran;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    luas_lingkaran = shmat(shmid, NULL, 0);

    printf("Volume Tabung : %lf x %d = %lf\n", *luas_lingkaran, T, *luas_lingkaran * T);

    shmdt(luas_lingkaran);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}