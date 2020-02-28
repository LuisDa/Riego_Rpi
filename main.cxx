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
#include <gtk/gtk.h>
#include <iostream>
#include <bcm2835.h>
#include <time.h>
#include <math.h>
#include <sys/sem.h>
#include <pthread.h>

#define PIN RPI_GPIO_P1_12

// and it is controlled by PWM channel 0
#define PWM_CHANNEL 0

// This controls the max range of the PWM signal
#define RANGE 1024

//#include <wiringPi.h> //Da conflicto con bcm2835.h... lo mejor será destripar el fichero y coger lo que nos interese para generar un PWM

const int PWM_pin = 1;   /* GPIO 1 as per WiringPi, GPIO18 as per BCM */

unsigned char gpio_status = 0x00; //Byte para controlar el estado de cada salida de GPIO

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

//Hebras
pthread_t hebra1;
pthread_t hebra2;
int id_hebra1;
int id_hebra2;

void *funcion_hebra1 (void *parametros)
{
	//while(true)
	for (int i = 0; i < 20; i++)
	{
		printf("Hebra 1 ejecutando\n");
		sleep(1);
	}
}

void *funcion_hebra2 (void *parametros)
{
	//while(true)
	for (int i = 0; i < 20; i++)
	{
		printf("Hebra 2 ejecutando\n");
		sleep(1);	
	}
}

/* Our new improved callback. The data passed to this function
* is printed to stdout. */
void callback_1( GtkWidget *widget, gpointer data )
{
	g_print ("Hello again - %s was pressed\n", (gchar *) data);
	
	bcm2835_gpio_write(RPI_V2_GPIO_P1_11, HIGH);
}

void callback_2( GtkWidget *widget, gpointer data )
{
	g_print ("Hello again - %s was pressed\n", (gchar *) data);
	
	bcm2835_gpio_write(RPI_V2_GPIO_P1_13, HIGH);
}

void callback_3( GtkWidget *widget, gpointer data )
{
	g_print ("Hello again - %s was pressed\n", (gchar *) data);
	
	bcm2835_gpio_write(RPI_V2_GPIO_P1_33, HIGH);
}

void callback_4( GtkWidget *widget, gpointer data )
{
	g_print ("Hello again - %s was pressed\n", (gchar *) data);
	
	bcm2835_gpio_write(RPI_V2_GPIO_P1_35, HIGH);
}

void callback_5( GtkWidget *widget, gpointer data )
{
	g_print ("Hello again - %s was pressed\n", (gchar *) data);
	
	bcm2835_gpio_write(RPI_V2_GPIO_P1_37, HIGH);
}

void callback_6( GtkWidget *widget, gpointer data )
{
	g_print ("Hello again - %s was pressed\n", (gchar *) data);
	
	bcm2835_gpio_write(RPI_V2_GPIO_P1_11, LOW);
}

void callback_7( GtkWidget *widget, gpointer data )
{
	g_print ("Hello again - %s was pressed\n", (gchar *) data);
	
	bcm2835_gpio_write(RPI_V2_GPIO_P1_13, LOW);
}

void callback_8( GtkWidget *widget, gpointer data )
{
	g_print ("Hello again - %s was pressed\n", (gchar *) data);
	
	bcm2835_gpio_write(RPI_V2_GPIO_P1_33, LOW);
}

void callback_9( GtkWidget *widget, gpointer data )
{
	g_print ("Hello again - %s was pressed\n", (gchar *) data);
	
	bcm2835_gpio_write(RPI_V2_GPIO_P1_35, LOW);
}

void callback_10( GtkWidget *widget, gpointer data )
{
	g_print ("Hello again - %s was pressed\n", (gchar *) data);
	
	bcm2835_gpio_write(RPI_V2_GPIO_P1_37, LOW);
}

//Callback para el TIMER
static gboolean timer_event(GtkWidget *widget)
{
	g_print ("Saltose el evento del TIMER\n");
	//bcm2835_pwm_set_data(PWM_CHANNEL, 1024);

	return TRUE; //Si devuelve TRUE, el temporizador volverá a lanzarse, si devuelve FALSE, se detiene.
}

//Callback para dibujar
gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data)
{
    guint width, height;
    GdkRGBA color;
    GtkStyleContext *context;
    
    g_print ("Redibujando\n");

    context = gtk_widget_get_style_context (widget);
    width = 100;//gtk_widget_get_allocated_width (widget);
    height = 50;//gtk_widget_get_allocated_height (widget);
    gtk_render_background(context, cr, 0, 0, width, height);
    cairo_arc (cr, width/2.0, height/2.0, /*MIN (width, height) / 2.0*/10, 0, 2 * G_PI);
    gtk_style_context_get_color (context, gtk_style_context_get_state (context), &color);
    
    color.red = 1;
    color.green = 0.4;
    color.blue = 0;
    color.alpha = 1;
    
    gdk_cairo_set_source_rgba (cr, &color);
    gdk_cairo_set_source_rgba (cr, &color);
    cairo_fill (cr);
    return FALSE;
}

/* another callback */
gint delete_event( GtkWidget *widget, GdkEvent *event, gpointer data )
{
	gtk_main_quit ();
	return FALSE;
}

	//---------------------------------
	//----- CREATE THE GTK WINDOW -----
	//---------------------------------
int main(int argc, char **argv)
{
	if (!bcm2835_init()) return 1;

	/*PWM para el pin 18*/
	//bcm2835_gpio_fsel(18,BCM2835_GPIO_FSEL_ALT5 );    
	//bcm2835_gpio_fsel(18,BCM2835_GPIO_FSEL_ALT1 );   
	
	/* 
	bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_ALT5);
	bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
    bcm2835_pwm_set_mode(PWM_CHANNEL, 1, 1);
    bcm2835_pwm_set_range(PWM_CHANNEL, RANGE);
	*/
	/*Creamos las hebras*/
	id_hebra1 = pthread_create(&hebra1, NULL, funcion_hebra1, (void *)&hebra1);
	
	if (id_hebra1 != 0)
	{
		printf("No se pudo crear hebra 1\n");
	}
	
	id_hebra2 = pthread_create(&hebra2, NULL, funcion_hebra2, (void *)&hebra2);

	if (id_hebra2 != 0)
	{
		printf("No se pudo crear hebra 2\n");
	}

	
	/*Ponemos el pin 11 como salida*/
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_11, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_13, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_33, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_35, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_37, BCM2835_GPIO_FSEL_OUTP);
	
	/* GtkWidget is the storage type for widgets */
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *drawing_area;
	GtkWidget *box1;	
	GtkWidget *box2;	
	GtkWidget *box3;
	GtkWidget *box4;
	GtkWidget *hbox;
		
	
	/* This is called in all GTK applications. Arguments are parsed
	* from the command line and are returned to the application. */
	gtk_init (&argc, &argv);
	/* Create a new window */
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);	
	gtk_window_set_title (GTK_WINDOW (window), "GÜINDOU");
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 500);		//Size of the the client area (excluding the additional areas provided by the window manager)
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
		
	g_timeout_add(1000, (GSourceFunc) timer_event, (gpointer) window); //Configuramos el temporizador para que genere un evento cada segundo (1000 ms)
	
	g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (delete_event), NULL);	
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	
	/* We create a box to pack widgets into. This is described in detail
	* in the "packing" section. The box is not really visible, it
	* is just used as a tool to arrange widgets. */
	//hbox = gtk_hbox_new (FALSE, 8);	
	hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 8);
	//box1 = gtk_vbox_new (FALSE, 5);
	box1 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	//box2 = gtk_vbox_new (FALSE, 5);
	box2 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	
	box3 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);

	gtk_container_add (GTK_CONTAINER (window), hbox);
	gtk_box_pack_start(GTK_BOX(hbox), box1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), box2, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), box3, FALSE, FALSE, 0);
	
	button = gtk_button_new_with_label ("Button_1");		
	gtk_widget_set_size_request(button,2,2);	
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_1), (gpointer) "button_1");	
	gtk_box_pack_start (GTK_BOX(box1), button, FALSE, FALSE, 0);
	gtk_widget_show (button);
		
	button = gtk_button_new_with_label ("Button_2");
	gtk_widget_set_size_request(button,2,2);	
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_2), (gpointer) "button_2");
	gtk_box_pack_start(GTK_BOX (box1), button, FALSE, FALSE, 0);
	gtk_widget_show (button);

	button = gtk_button_new_with_label ("Button_3");
	gtk_widget_set_size_request(button,2,2);	
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_3), (gpointer) "button_3");
	gtk_box_pack_start(GTK_BOX (box1), button, FALSE, FALSE, 0);
	gtk_widget_show (button);	

	button = gtk_button_new_with_label ("Button_4");
	gtk_widget_set_size_request(button,2,2);	
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_4), (gpointer) "button_4");
	gtk_box_pack_start(GTK_BOX (box1), button, FALSE, FALSE, 0);
	gtk_widget_show (button);	
	
	button = gtk_button_new_with_label ("Button_5");
	gtk_widget_set_size_request(button,2,2);	
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_5), (gpointer) "button_5");
	gtk_box_pack_start(GTK_BOX (box1), button, FALSE, FALSE, 0);
	gtk_widget_show (button);	
	
	button = gtk_button_new_with_label ("Button_6");
	gtk_widget_set_size_request(button,2,2);
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_6), (gpointer) "button_6");
	gtk_box_pack_start(GTK_BOX (box2), button, FALSE, FALSE, 0);
	gtk_widget_show (button);
	
	button = gtk_button_new_with_label ("Button_7");
	gtk_widget_set_size_request(button,2,2);
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_7), (gpointer) "button_7");
	gtk_box_pack_start(GTK_BOX (box2), button, FALSE, FALSE, 0);		
	gtk_widget_show (button);

	button = gtk_button_new_with_label ("Button_8");
	gtk_widget_set_size_request(button,2,2);
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_8), (gpointer) "button_8");
	gtk_box_pack_start(GTK_BOX (box2), button, FALSE, FALSE, 0);		
	gtk_widget_show (button);
	
	button = gtk_button_new_with_label ("Button_9");
	gtk_widget_set_size_request(button,2,2);
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_9), (gpointer) "button_9");
	gtk_box_pack_start(GTK_BOX (box2), button, FALSE, FALSE, 0);		
	gtk_widget_show (button);
	
	button = gtk_button_new_with_label ("Button_10");
	gtk_widget_set_size_request(button,2,2);
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_10), (gpointer) "button_10");
	gtk_box_pack_start(GTK_BOX (box2), button, FALSE, FALSE, 0);		
	gtk_widget_show (button);
	
	drawing_area = gtk_drawing_area_new(); 	   
    //gtk_container_add (GTK_CONTAINER (box3), drawing_area);
    gtk_widget_set_size_request (drawing_area, 100, 50);    
	g_signal_connect (G_OBJECT (drawing_area), "draw", G_CALLBACK (draw_callback), NULL);
	gtk_box_pack_start(GTK_BOX (box3), drawing_area, FALSE, FALSE, 0);
	gtk_widget_show (drawing_area);
	
	gtk_widget_show (box1);
	gtk_widget_show (box2);
	gtk_widget_show (box3);
	gtk_widget_show (hbox);
	gtk_widget_show (window);

	//gdk_rgba_parse(&rgba, "#80FF00");
	//gtk_widget_override_background_color (box3, GTK_STATE_FLAG_NORMAL, &rgba);
	
	gtk_main ();
	
	//Finalizamos las hebras
	pthread_join(hebra1, NULL);
	pthread_join(hebra2, NULL);
	
	void* result;	
    if ((pthread_join(hebra1, &result)) == -1) {
        perror("No se pudo hacer join a la hebra 1\n");        
    }

	//void* result;	
    if ((pthread_join(hebra2, &result)) == -1) {
        perror("No se pudo hacer join a la hebra 2\n");        
    }
	
	pthread_exit(NULL);
	
	bcm2835_close();

	return 0;
	
}


