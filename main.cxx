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
#include <gtk/gtk.h>
#include <iostream>
#include <bcm2835.h>
#include <time.h>


unsigned char gpio_status = 0x00; //Byte para controlar el estado de cada salida de GPIO

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
	
	return TRUE; //Si devuelve TRUE, el temporizador volverá a lanzarse, si devuelve FALSE, se detiene.
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
	
	/*Ponemos el pin 11 como salida*/
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_11, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_13, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_33, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_35, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RPI_V2_GPIO_P1_37, BCM2835_GPIO_FSEL_OUTP);
	
	/* GtkWidget is the storage type for widgets */
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *box1;	
	GtkWidget *box2;	
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
	hbox = gtk_hbox_new (FALSE, 8);	
	box1 = gtk_vbox_new (FALSE, 5);
	box2 = gtk_vbox_new (FALSE, 5);

	gtk_container_add (GTK_CONTAINER (window), hbox);
	gtk_box_pack_start(GTK_BOX(hbox), box1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), box2, FALSE, FALSE, 0);
	
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
	
	
	gtk_widget_show (box1);
	gtk_widget_show (box2);
	gtk_widget_show (hbox);
	gtk_widget_show (window);
	
	gtk_main ();

	return 0;
	
}


