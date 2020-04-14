/*
 * main.cxx
 * 
 * Copyright 2018  <pi@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <cairo.h> 
//#include <gtk/gtk.h>
#include <iostream>
//#include <bcm2835.h>
#include <time.h>
#include <math.h>
#include <sys/sem.h>
#include <pthread.h>
#include <string.h>
#include "var_func_globales.h"
//#include "ProgramaRiegoDlg.h"

#define PIN RPI_GPIO_P1_12

// and it is controlled by PWM channel 0
#define PWM_CHANNEL 0

// This controls the max range of the PWM signal
#define RANGE 1024

//#include <wiringPi.h> //Da conflicto con bcm2835.h... lo mejor será destripar el fichero y coger lo que nos interese para generar un PWM

const int PWM_pin = 1;   /* GPIO 1 as per WiringPi, GPIO18 as per BCM */

unsigned char gpio_status = 0x00; //Byte para controlar el estado de cada salida de GPIO


#define MAX_WORD_SIZE 32

//cairo_t *cr = NULL;
GdkColor color;
GdkRGBA rgba;

//Semáforos
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

static int semaphore1_id;

static int semaphore1_get_access(void)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1; /* P() */
	sem_b.sem_flg = SEM_UNDO;
	
	if (semop(semaphore1_id, &sem_b, 1) == -1)		//Wait until free
	{
		fprintf(stderr, "semaphore1_get_access failed\n");
		return(0);
	}
	
	return(1);	
}

static int semaphore1_release_access(void)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1; /* V() */
	sem_b.sem_flg = SEM_UNDO;
	if (semop(semaphore1_id, &sem_b, 1) == -1)
	{
		fprintf(stderr, "semaphore1_release_access failed\n");
		return(0);
	}
	return(1);	
}

//Funciones relativas al GUI
void inicializar_GUI(void);
void finalizar_GUI(void);
void configurar_botones(void);
void configurar_etiquetas(void);
void configurar_cajas_widgets(void);
void configurar_lista_programas(void);
void configurar_areas_dibujo(void);
void configurar_marco_ventana_ppal(void);


//Funciones de retrollamada para eventos del GUI
static gboolean timer_event(GtkWidget *widget);
gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data);
gint delete_event( GtkWidget *widget, GdkEvent *event, gpointer data);
void selected_event_callback (GtkListBox *list_box, GtkListBoxRow *row, gpointer data);
void callback_botones (GtkWidget *widget, gpointer data);

//Funciones de GPIO
void inicializar_GPIO(void);

//Hebras
pthread_t hebra1;
pthread_t hebra2;
int id_hebra1;
int id_hebra2;

void *funcion_hebra1 (void *parametros)
{
	while(ejecutar_hebra_1)
	{		
		printf("Hebra 1 ejecutando\n");
		sleep(1);
	}
}

void *funcion_hebra2 (void *parametros)
{
	while(ejecutar_hebra_2)
	{
		printf("Hebra 2 ejecutando\n");
		sleep(1);	
	}
}


	//---------------------------------
	//----- CREATE THE GTK WINDOW -----
	//---------------------------------
int main(int argc, char **argv)
{
	/*Creamos el repositorio*/
	repositorio = new CRepositorio();

	/*Creamos las hebras*/
	if (pthread_create(&hebra1, NULL, funcion_hebra1, (void *)&hebra1) != 0) printf("No se pudo crear hebra_1\n");
	if (pthread_create(&hebra2, NULL, funcion_hebra2, (void *)&hebra2) != 0) printf("No se pudo crear hebra_2\n");

	/*Inicializamos GPIO*/	
	inicializar_GPIO();	
	
	/* Inicializamos GTK */
	gtk_init (&argc, &argv);
	inicializar_GUI();


	//gdk_rgba_parse(&rgba, "#80FF00");
	//gtk_widget_override_background_color (box3, GTK_STATE_FLAG_NORMAL, &rgba);
	g_print("Ejecutando gtk_main()\n");
	gtk_main ();
	g_print("Fin ejecución gtk_main()\n");
	
	//finalizar_GUI();
	
	//Indicamos fin de ejecución de ambas hebras
	ejecutar_hebra_1 = false;
	ejecutar_hebra_2 = false;
	
	//Finalizamos las hebras
	g_print("Ejecutando pthread_join a la hebra1\n");
	pthread_join(hebra1, NULL);
	g_print("Fin de pthread_join a la hebra1\n");
	
	g_print("Ejecutando pthread_join a la hebra2\n");	
	pthread_join(hebra2, NULL);
	g_print("Fin de pthread_join a la hebra2\n");

	
	g_print("Ejecutando bcm2835_close\n");
	bcm2835_close();
	g_print("Fin ejecución bcm2835_close\n");
	
	//Finalizando, liberamos el repositorio
	delete repositorio;
	repositorio = NULL;

	return 0;
	
}


