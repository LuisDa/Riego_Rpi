#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <bcm2835.h>
#include "Repositorio.h"

#define BUF_SIZE 10
#define SHM_KEY 0x1234
//#define PRUEBA_BYTE_SIMPLE


struct shmseg {
   int cnt;
   int complete;
   //char buf[BUF_SIZE];
   char comando;
};

void inicializar_GPIO()
{
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_11, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_13, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_33, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_35, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_37, BCM2835_GPIO_FSEL_OUTP);		
}

int main (int argc, char* argv[])
{
	int shmid;
	struct shmseg *shmp;	
	
	char *shm_byte_p;
	char cmd;

#ifdef PRUEBA_BYTE_SIMPLE	
	shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
#else
	shmid = shmget(SHM_KEY, 1, 0644|IPC_CREAT);
#endif	
   
	if (shmid == -1) {
		perror("Shared memory get failed");
		return 1;
	}
	
#ifndef PRUEBA_BYTE_SIMPLE	
	// Attach to the segment to get a pointer to it.
	shmp = (shmseg*)shmat(shmid, NULL, 0);
	
	if (shmp == (void *) -1) {
		perror("Shared memory attach");
		return 1;
	}
	
	
	   /* Transfer blocks of data from shared memory to stdout*/
	while (shmp->complete != 1) {
		//printf("segment contains : \n\"%s\"; Comando %.02X \n", shmp->buf, shmp->comando);
		printf("Segmento contiene: %.02X\n", shmp->comando);
		
		if (shmp->cnt == -1) {
			perror("read");
			return 1;
		}
		
		printf("Reading Process: Shared Memory: Read %d bytes\n", shmp->cnt);
		sleep(1);
	}
	
	printf("Reading Process: Reading Done, Detaching Shared Memory\n");
	
	if (shmdt(shmp) == -1) {
		perror("shmdt");
		return 1;
	}
#else
	shm_byte_p = (char*)shmat(shmid, NULL, 0);
	
	if (shm_byte_p == (void *) -1) {
		perror("Shared memory attach");
		return 1;
	}
	
	while (*shm_byte_p != 'J')
	{
		printf ("Recibiose por memoria compartida %c \n", *shm_byte_p);
		sleep(1);
	}

	if (shmdt(shm_byte_p) == -1) {
		perror("shmdt");
		return 1;
	}

#endif
	
	printf("Reading Process: Complete\n");
	return 0;
}



