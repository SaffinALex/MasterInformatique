#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>


struct req{
  int h;
};

void* func(void *par){
struct sembuf opp;
opp.sem_num=0;
opp.sem_num=-1;
opp.sem_flg=0;
struct sembuf opv;
opp.sem_num=0;
opp.sem_num=+1;
opp.sem_flg=0;
struct sembuf opz;
opp.sem_num=0;
opp.sem_num=0;
opp.sem_flg=0;
  struct  req* b = ((struct req*)par);
  semop(b->h, &opp,1);
  semop(b->h, &opz, 1);
  semop(b->h, &opv, 1);
  printf("coucou\n");
}

int main(int argc, char** argv){
  key_t clef = ftok("texte.txt", 40);
  int h = semget(clef,2, IPC_CREAT|0666);
  semctl(h,1, SETVAL, 3);
  struct req maRequete;
  maRequete.h = h;
  pthread_t threads[3];
  pthread_create(&threads[0], NULL, func, &maRequete);
  pthread_create(&threads[1], NULL, func, &maRequete);
  pthread_create(&threads[2], NULL, func, &maRequete);
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  pthread_join(threads[2], NULL);

}
