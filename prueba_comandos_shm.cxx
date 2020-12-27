/* Filename: shm_write.c */
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define BUF_SIZE 10
#define SHM_KEY 0x1234

//#define PRUEBA_BYTE_SIMPLE

struct shmseg {
   int cnt;
   int enviado;
   int complete;
   //char buf[BUF_SIZE];
   char comando;
};
int fill_buffer(char * bufptr, int size);

int main(int argc, char *argv[]) {
   int shmid, numtimes;
   struct shmseg *shmp;
   char *bufptr;
   int spaceavailable;
   
   char *shm_byte_p;
   
   
#ifndef PRUEBA_BYTE_SIMPLE   
   shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
   //shmid = shmget(SHM_KEY, 12, 0644|IPC_CREAT);
#else
   shmid = shmget(SHM_KEY, 1, 0644|IPC_CREAT);
#endif   
   
   
   if (shmid == -1) {
      perror("Shared memory");
      return 1;
   }

#ifndef PRUEBA_BYTE_SIMPLE   
   // Attach to the segment to get a pointer to it.
   shmp = (shmseg*) shmat(shmid, NULL, 0);
   
   if (shmp == (void *) -1) {
      perror("Shared memory attach");
      return 1;
   }
   
   /* Transfer blocks of data from buffer to shared memory */
   //bufptr = shmp->buf;
   spaceavailable = BUF_SIZE;
   
   /*
   for (numtimes = 0; numtimes < 5; numtimes++) {
      //shmp->cnt = fill_buffer(bufptr, spaceavailable);
      shmp->complete = 0;
      shmp->comando = 0xA0 + numtimes;
      shmp->cnt = 1;
      printf("Writing Process: Shared Memory Write: Wrote %d bytes\n", shmp->cnt);
      //bufptr = shmp->buf;
      spaceavailable = BUF_SIZE;
      sleep(1);
   }
   */
   if (argc < 2) 
   {
	   printf("Uso: %s <cmd> <num valvula>\n", argv[0]);
	   return 1;
   }
   else if (argc == 2)
   {
	   if (strcmp(argv[1], "s") == 0)
	   {
		   shmp->comando = 0xFF;
		   shmp->complete = 1;
	   }
	   else if (strcmp(argv[1], "r") == 0) //recargar repositorio
	   {
		   shmp->comando = 0x20;		   
	   }	   
   }
   else if (argc == 3)
   {
	   if (strcmp(argv[1], "a") == 0)
	   {
		   char num_valv = (char)atoi(argv[2]);
		   shmp->comando = 0x10 + num_valv;		   
	   }
	   else if (strcmp(argv[1], "d") == 0)
	   {
		   char num_valv = (char)atoi(argv[2]);
		   shmp->comando = 0x00 + num_valv;		   
	   }
	   	   
	   shmp->complete = 0;
   }
   
   shmp->enviado = 1;
     
   //printf("Writing Process: Wrote %d times\n", numtimes);
   //shmp->complete = 1;


   if (shmdt(shmp) == -1) {
      perror("shmdt");
      return 1;
   }

/* //Esto elimina el ID de los segmentos de memoria compartida
   if (shmctl(shmid, IPC_RMID, 0) == -1) {
      perror("shmctl");
      return 1;
   }
*/   
#else   
   shm_byte_p = (char*) shmat(shmid, NULL, 0);
   
   if (shm_byte_p == (void *) -1) {
      perror("Shared memory attach");
      return 1;
   } 
   
   for (int i = 0; i < 10; i++)
   {
	   char enviado = 'A' + i;
	   printf ("Enviando %c\n", enviado);
	   shm_byte_p = &enviado;
	   sleep (1);
   }
   
   if (shmdt(shm_byte_p) == -1) {
      perror("shmdt");
      return 1;
   }

   if (shmctl(shmid, IPC_RMID, 0) == -1) {
      perror("shmctl");
      return 1;
   }
   
#endif   
   
   printf("Writing Process: Complete\n");
   return 0;
}

int fill_buffer(char * bufptr, int size) {
   static char ch = 'A';
   int filled_count;
   
   //printf("size is %d\n", size);
   memset(bufptr, ch, size - 1);
   bufptr[size-1] = '\0';
   if (ch > 122)
   ch = 65;
   if ( (ch >= 65) && (ch <= 122) ) {
      if ( (ch >= 91) && (ch <= 96) ) {
         ch = 65;
      }
   }
   filled_count = strlen(bufptr);
   
   //printf("buffer count is: %d\n", filled_count);
   //printf("buffer filled is:%s\n", bufptr);
   ch++;
   return filled_count;
}

