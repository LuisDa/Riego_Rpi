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
#include <string.h>

#define PIN RPI_GPIO_P1_12

// and it is controlled by PWM channel 0
#define PWM_CHANNEL 0

// This controls the max range of the PWM signal
#define RANGE 1024

//#include <wiringPi.h> //Da conflicto con bcm2835.h... lo mejor será destripar el fichero y coger lo que nos interese para generar un PWM

const int PWM_pin = 1;   /* GPIO 1 as per WiringPi, GPIO18 as per BCM */

unsigned char gpio_status = 0x00; //Byte para controlar el estado de cada salida de GPIO

volatile bool ejecutar_hebra_1 = true;
volatile bool ejecutar_hebra_2 = true;

volatile bool conmutar_color = false;

const char* etiquetas_botones[10] = {"Button_1", "Button_2", "Button_3", "Button_4", "Button_5", "Button_6", "Button_7", "Button_8", "Button_9", "Button_10"};
const char* id_botones[10] = {"button_1", "button_2", "button_3", "button_4", "button_5", "button_6", "button_7", "button_8", "button_9", "button_10"};

GtkWidget *window;
GtkWidget *button;
GtkWidget *drawing_area;
GtkWidget *list_box;
//GtkListBox *lista;
GtkComboBox *cbox_quaity;
GtkListBox *gtk_list_box;
GtkWidget *box1;	
GtkWidget *box2;	
GtkWidget *box3;
GtkWidget *box4;
GtkWidget *hbox;

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

//Declaración de funciones
void inicializar_GUI(void);

static gboolean timer_event(GtkWidget *widget);

gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data);

gint delete_event( GtkWidget *widget, GdkEvent *event, gpointer data);

void inicializar_GPIO(void);

//Hebras
pthread_t hebra1;
pthread_t hebra2;
int id_hebra1;
int id_hebra2;

void *funcion_hebra1 (void *parametros)
{
	//while(true)
	//for (int i = 0; i < 20; i++)
	while(ejecutar_hebra_1)
	{
		//printf("Hebra 1 ejecutando\n");
		g_print ("Hebra 1 ejecutando\n");
		sleep(1);
	}
}

void *funcion_hebra2 (void *parametros)
{
	//while(true)
	//for (int i = 0; i < 20; i++)
	while(ejecutar_hebra_2)
	{
		printf("Hebra 2 ejecutando\n");
		sleep(1);	
	}
}

void callback_botones (GtkWidget *widget, gpointer data )
{
	g_print ("Botón %s fue pulsado\n", (gchar*)data);
	
	if (strcmp((gchar*)data, "button_1") == 0) bcm2835_gpio_write(RPI_V2_GPIO_P1_11, HIGH);
	else if (strcmp((gchar*)data, "button_2") == 0) bcm2835_gpio_write(RPI_V2_GPIO_P1_13, HIGH);
	else if (strcmp((gchar*)data, "button_3") == 0) bcm2835_gpio_write(RPI_V2_GPIO_P1_33, HIGH);
	else if (strcmp((gchar*)data, "button_4") == 0) bcm2835_gpio_write(RPI_V2_GPIO_P1_35, HIGH);
	else if (strcmp((gchar*)data, "button_5") == 0) bcm2835_gpio_write(RPI_V2_GPIO_P1_37, HIGH);
	else if (strcmp((gchar*)data, "button_6") == 0) bcm2835_gpio_write(RPI_V2_GPIO_P1_11, LOW);
	else if (strcmp((gchar*)data, "button_7") == 0) bcm2835_gpio_write(RPI_V2_GPIO_P1_13, LOW);
	else if (strcmp((gchar*)data, "button_8") == 0) bcm2835_gpio_write(RPI_V2_GPIO_P1_33, LOW);
	else if (strcmp((gchar*)data, "button_9") == 0) bcm2835_gpio_write(RPI_V2_GPIO_P1_35, LOW);
	else if (strcmp((gchar*)data, "button_10") == 0) bcm2835_gpio_write(RPI_V2_GPIO_P1_37, LOW);
	
	if (strcmp((gchar*)data, "button_2") == 0)
	{
		conmutar_color = true;
		gtk_widget_queue_draw(drawing_area);
		//g_signal_emit((gpointer)"draw");
		//gtk_signal_emit_by_name(window, "draw");
		
		//            g_signal_emit (G_OBJECT (puzzle), puzzle_signals [PUZZLE_SOLVED_SIGNAL], 0);
		/*
		  puzzle_signals[PUZZLE_SOLVED_SIGNAL] =
      g_signal_new ("puzzle_solved",
                    G_TYPE_FROM_CLASS (gobject_class),
                    G_SIGNAL_RUN_FIRST, 0, NULL, NULL,
                    g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0, NULL);*/
	}
	
}

void inicializar_GPIO(void)
{
	if (!bcm2835_init()) 
	{	
		printf("Error al ejecutar bcm2835_init()\n");
		exit(1);
	}
	
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_11, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_13, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_33, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_35, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_37, BCM2835_GPIO_FSEL_OUTP);	
}

void inicializar_GUI(void)
{		
	
	/* This is called in all GTK applications. Arguments are parsed
	* from the command line and are returned to the application. */
	//gtk_init (&argc, &argv);
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
	
	hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 8);
	
	box1 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	
	box2 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	
	box3 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	
	box4 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);

	gtk_container_add (GTK_CONTAINER (window), hbox);
	gtk_box_pack_start(GTK_BOX(hbox), box1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), box2, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), box3, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), box4, FALSE, FALSE, 0);
	

	button = gtk_button_new_with_label ("Button_1");		
	gtk_widget_set_size_request(button,2,2);		
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_botones), (gpointer) "button_1");
	gtk_box_pack_start (GTK_BOX(box1), button, FALSE, FALSE, 0);
	gtk_widget_show (button);
		
	button = gtk_button_new_with_label ("Button_2");
	gtk_widget_set_size_request(button,2,2);		
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_botones), (gpointer) "button_2");
	gtk_box_pack_start(GTK_BOX (box1), button, FALSE, FALSE, 0);
	gtk_widget_show (button);

	button = gtk_button_new_with_label ("Button_3");
	gtk_widget_set_size_request(button,2,2);		
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_botones), (gpointer) "button_3");
	gtk_box_pack_start(GTK_BOX (box1), button, FALSE, FALSE, 0);
	gtk_widget_show (button);	

	button = gtk_button_new_with_label ("Button_4");
	gtk_widget_set_size_request(button,2,2);		
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_botones), (gpointer) "button_4");
	gtk_box_pack_start(GTK_BOX (box1), button, FALSE, FALSE, 0);
	gtk_widget_show (button);	
	
	button = gtk_button_new_with_label ("Button_5");
	gtk_widget_set_size_request(button,2,2);		
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_botones), (gpointer) "button_5");
	gtk_box_pack_start(GTK_BOX (box1), button, FALSE, FALSE, 0);
	gtk_widget_show (button);	
	
	
	button = gtk_button_new_with_label ("Button_6");
	gtk_widget_set_size_request(button,2,2);	
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_botones), (gpointer) "button_6");
	gtk_box_pack_start(GTK_BOX (box2), button, FALSE, FALSE, 0);
	gtk_widget_show (button);
	
	button = gtk_button_new_with_label ("Button_7");
	gtk_widget_set_size_request(button,2,2);	
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_botones), (gpointer) "button_7");
	gtk_box_pack_start(GTK_BOX (box2), button, FALSE, FALSE, 0);		
	gtk_widget_show (button);

	button = gtk_button_new_with_label ("Button_8");
	gtk_widget_set_size_request(button,2,2);	
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_botones), (gpointer) "button_8");
	gtk_box_pack_start(GTK_BOX (box2), button, FALSE, FALSE, 0);		
	gtk_widget_show (button);
	
	button = gtk_button_new_with_label ("Button_9");
	gtk_widget_set_size_request(button,2,2);	
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_botones), (gpointer) "button_9");
	gtk_box_pack_start(GTK_BOX (box2), button, FALSE, FALSE, 0);		
	gtk_widget_show (button);
	
	button = gtk_button_new_with_label ("Button_10");
	gtk_widget_set_size_request(button,2,2);	
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_botones), (gpointer) "button_10");
	gtk_box_pack_start(GTK_BOX (box2), button, FALSE, FALSE, 0);		
	gtk_widget_show (button);
	
	drawing_area = gtk_drawing_area_new(); 	   
    //gtk_container_add (GTK_CONTAINER (box3), drawing_area);
    gtk_widget_set_size_request (drawing_area, 100, 50);    
	g_signal_connect (G_OBJECT (drawing_area), "draw", G_CALLBACK (draw_callback), NULL);
	gtk_box_pack_start(GTK_BOX (box3), drawing_area, FALSE, FALSE, 0);
	gtk_widget_show (drawing_area);
	
	//list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	list_box = gtk_list_box_new();	
	gtk_list_box = (GtkListBox*)list_box;	
	gtk_widget_set_size_request (list_box, 100, 300);
	gtk_box_pack_start(GTK_BOX (box4), list_box, FALSE, FALSE, 0);
	gtk_widget_show(list_box);
	
	GtkWidget *etiqueta;
	etiqueta = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(etiqueta), "<span foreground=\"red\" size=\"x-large\">Los chuches</span>");
	gtk_label_set_justify(GTK_LABEL(etiqueta), GTK_JUSTIFY_CENTER);
	gtk_list_box_insert(gtk_list_box, etiqueta, 1);
	gtk_widget_show(etiqueta);
	
	
	/*
	list_box = (GtkListBox*)gtk_list_box_new();
	gtk_list_box_insert(list_box, (GtkWidget*)"Elemento 1", 1);
	gtk_list_box_insert(list_box, (GtkWidget*)"Elemento 2", 2);
	gtk_list_box_insert(list_box, (GtkWidget*)"Elemento 3", 3);
	gtk_widget_set_size_request ((GtkWidget*)list_box, 100, 300);
	gtk_box_pack_start(GTK_BOX (box4), (GtkWidget*)list_box, FALSE, FALSE, 0);
	gtk_widget_show ((GtkWidget*)list_box);
	*/ 
	
	
	g_print("Creando elementos de la ventana\n");
	gtk_widget_show (box1);
	gtk_widget_show (box2);
	gtk_widget_show (box3);
	gtk_widget_show (box4);
	gtk_widget_show (hbox);
	gtk_widget_show (window);
	g_print("Ventana creada\n");
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
    
    if (conmutar_color)
    {
		color.red = 0.1;
		color.green = 0.8;
		color.blue = 1;
		color.alpha = 1;
		conmutar_color = false;
	}
	else
    {
		color.red = 1;
		color.green = 0.4;
		color.blue = 0;
		color.alpha = 1;
	}
    
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

	return 0;
	
}


