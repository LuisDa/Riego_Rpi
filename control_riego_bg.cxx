#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <bcm2835.h>
#include "Repositorio.h"

#define BUF_SIZE 10
#define SHM_KEY 0x1234
//#define PRUEBA_BYTE_SIMPLE //Con esto no funciona


//Variables globales del programa
CRepositorio* repositorio = NULL;
pthread_t hebra_control_GPIO;
pthread_t hebra_chequeo_hora;
volatile bool actualizar_estado_valvulas = false;
volatile bool ejecutar_hebra_control_valvulas = true;
volatile bool ejecutar_hebra_chequeo_hora = true;


struct shmseg {
   int cnt;
   int enviado;
   int complete;
   //char buf[BUF_SIZE];
   char comando;
};

void inicializar_GPIO()
{
	if (!bcm2835_init()) 
	{	
		printf("Error al ejecutar bcm2835_init()\n");
		exit(1);
	}
	
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_11, BCM2835_GPIO_FSEL_OUTP); //Válvula 1
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_13, BCM2835_GPIO_FSEL_OUTP); //Válvula 2
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_33, BCM2835_GPIO_FSEL_OUTP); //Válvula 3
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_35, BCM2835_GPIO_FSEL_OUTP); //Válvula 4
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_37, BCM2835_GPIO_FSEL_OUTP); //Válvula maestra		
}

void *funcion_hebra_control_valvulas(void* parametros)
{
	while (ejecutar_hebra_control_valvulas)
	{
		if (actualizar_estado_valvulas)
		{
			if (repositorio->getEstadoValvula(1) == true) bcm2835_gpio_write(RPI_V2_GPIO_P1_11, HIGH);
			else bcm2835_gpio_write(RPI_V2_GPIO_P1_11, LOW);
			
			if (repositorio->getEstadoValvula(2) == true) bcm2835_gpio_write(RPI_V2_GPIO_P1_13, HIGH);
			else bcm2835_gpio_write(RPI_V2_GPIO_P1_13, LOW);		
			
			if (repositorio->getEstadoValvula(3) == true) bcm2835_gpio_write(RPI_V2_GPIO_P1_33, HIGH);
			else bcm2835_gpio_write(RPI_V2_GPIO_P1_33, LOW);
			
			if (repositorio->getEstadoValvula(4) == true) bcm2835_gpio_write(RPI_V2_GPIO_P1_35, HIGH);
			else bcm2835_gpio_write(RPI_V2_GPIO_P1_35, LOW);	
			
			if (repositorio->getEstadoValvula(5) == true) bcm2835_gpio_write(RPI_V2_GPIO_P1_37, HIGH);
			else bcm2835_gpio_write(RPI_V2_GPIO_P1_37, LOW);			
			
			actualizar_estado_valvulas = false;
		}
		
		//sleep(1);
		usleep(100000);
	}
}

void *funcion_chequeo_hora(void* parametros)
{
	while(ejecutar_hebra_chequeo_hora)
	{	
		time_t rawtime;
		struct tm* fecha_hora;
		time(&rawtime);
		fecha_hora = localtime(&rawtime);
		static int prog_activo = 0;
		static int valv_activa = 0;
		static unsigned int contador_tiempo_valv = 0;
		
		printf("Chequeando la hora: %d:%d:%d\n", fecha_hora->tm_hour, fecha_hora->tm_min, fecha_hora->tm_sec);
		
		if ((repositorio->programaIncluido(fecha_hora->tm_hour, fecha_hora->tm_min) > 0)
			&& (repositorio->getProgramaActivo() == 0))
		{
			prog_activo = repositorio->programaIncluido(fecha_hora->tm_hour, fecha_hora->tm_min);
			printf(" => Hallose programa, activando %d\n", prog_activo);
			repositorio->setProgramaActivo(prog_activo);
			
			valv_activa = 1;
			contador_tiempo_valv = 60*(repositorio->getDuracionValv(prog_activo, valv_activa));
		}
		else if (repositorio->getProgramaActivo() > 0) //Ciclo de riego activo.
		{			
			/*
			if (valv_activa == 0)
			{
				valv_activa = 1;
				contador_tiempo_valv = repositorio->getDuracionValv(prog_activo, valv_activa);
			}
			else
			{
			* */
				contador_tiempo_valv--;
				
				printf(" => Dentro del ciclo de riego, programa %d, válvula %d, contador %d\n", prog_activo, valv_activa, contador_tiempo_valv);
				
				if (contador_tiempo_valv == 0)
				{
					if (valv_activa < 4)
					{
						valv_activa++;
						contador_tiempo_valv = 60*(repositorio->getDuracionValv(prog_activo, valv_activa));
					}
					else
					{
						contador_tiempo_valv = 0;
						repositorio->setEstadoValvula(4, false);
						valv_activa = 0;
						repositorio->setProgramaActivo(0);
					}					
					
				}
				
				switch (valv_activa)
				{
					case 1:			
						printf ("Activando válvula 1\n");
						repositorio->setEstadoValvula(1, true);
						actualizar_estado_valvulas = true;
						break;
					case 2:
						printf ("Parando válvula 1 y activando válvula 2\n");
						repositorio->setEstadoValvula(1, false);
						repositorio->setEstadoValvula(2, true);
						actualizar_estado_valvulas = true;
						break;
					case 3:
						printf ("Parando válvula 2 y activando válvula 3\n");	
						repositorio->setEstadoValvula(2, false);
						repositorio->setEstadoValvula(3, true);
						actualizar_estado_valvulas = true;
						break;
					case 4:
						printf ("Parando válvula 3 y activando válvula 4\n");
						repositorio->setEstadoValvula(3, false);
						repositorio->setEstadoValvula(4, true);
						actualizar_estado_valvulas = true;
						break;
					default:
						printf ("Nasti de plasti\n");
						break;
						
						
				}
			//}
		}
		//usleep(500000);
		
		//Definir aquí la estructura de la secuencia de control de las válvulas
		
		sleep(1);
	}
}

int main (int argc, char* argv[])
{
	int shmid;
	struct shmseg *shmp;	
	
	char *shm_byte_p;
	char cmd;
	
	repositorio = new CRepositorio();

	if (pthread_create(&hebra_control_GPIO, NULL, funcion_hebra_control_valvulas, (void *)&hebra_control_GPIO) != 0) 
	{
		printf("No se pudo crear hebra de control del GPIO\n");
	}
	
	if (pthread_create(&hebra_chequeo_hora, NULL, funcion_chequeo_hora, (void *)&hebra_chequeo_hora) != 0)
	{
		printf("No se pudo crear hebra de chequeo de hora\n");
	}
	
	inicializar_GPIO();

#ifndef PRUEBA_BYTE_SIMPLE	
	shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
	//shmid = shmget(SHM_KEY, 12, 0644|IPC_CREAT);
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
	//En este bucle, procesamos el comando.   
	while (shmp->complete != 1) {
		//printf("segment contains : \n\"%s\"; Comando %.02X \n", shmp->buf, shmp->comando);
		if (shmp->enviado == 1)
		{
			printf("Segmento contiene: %.02X\n", shmp->comando);
					
			if (shmp->cnt == -1) {
				perror("read");
				return 1;
			}
			
			switch (shmp->comando)
			{
				case 0x11: 
					printf("Activando válvula 1\n"); 
					repositorio->setEstadoValvula(1, true);
					break;
				case 0x12: 
					printf("Activando válvula 2\n"); 
					repositorio->setEstadoValvula(2, true);
					break;
				case 0x13: 
					printf("Activando válvula 3\n"); 
					repositorio->setEstadoValvula(3, true);
					break;
				case 0x14: 
					printf("Activando válvula 4\n"); 
					repositorio->setEstadoValvula(4, true);
					break;
				case 0x15: 
					printf("Activando válvula M\n"); 
					repositorio->setEstadoValvula(5, true);
					break;
							
				case 0x01: 
					printf("Desactivando válvula 1\n"); 
					repositorio->setEstadoValvula(1, false);
					break;
				case 0x02: 
					printf("Desactivando válvula 2\n"); 
					repositorio->setEstadoValvula(2, false);
					break;
				case 0x03: 
					printf("Desactivando válvula 3\n"); 
					repositorio->setEstadoValvula(3, false);
					break;
				case 0x04: 
					printf("Desactivando válvula 4\n"); 
					repositorio->setEstadoValvula(4, false);
					break;
				case 0x05: 
					printf("Desactivando válvula M\n"); 
					repositorio->setEstadoValvula(5, false);
					break;
				
				case 0xFF: //Aquí nunca entra, porque el valor de complete está a 1 y se sale del bucle antes
					printf("Finalizando servidor \n"); 
					ejecutar_hebra_chequeo_hora = false;
					ejecutar_hebra_control_valvulas = false;
					break;
				
				default: printf("Comando no contemplado\n"); break;			
				
			}
			
			actualizar_estado_valvulas = true;
			
			
			printf("Reading Process: Shared Memory: Read %d bytes\n", shmp->cnt);
			shmp->enviado = 0;
		}
		
		//sleep(1);
		usleep(100000);
	}
	
	ejecutar_hebra_control_valvulas = false;
	ejecutar_hebra_chequeo_hora = false;
	
	printf("Reading Process: Reading Done, Detaching Shared Memory\n");
	
	if (shmdt(shmp) == -1) {
		perror("shmdt");
		return 1;
	}
	
   if (shmctl(shmid, IPC_RMID, 0) == -1) {
      perror("shmctl");
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
	
	pthread_join(hebra_control_GPIO, NULL);
	
	
	bcm2835_close();
	
	printf("Reading Process: Complete\n");
	return 0;
}



