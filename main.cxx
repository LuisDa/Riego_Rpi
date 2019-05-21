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


GtkWidget *image_button_down;
GtkWidget *event_box_button_down;

//***********************************************
//***********************************************
//********** A BUTTON HAS BEEN PRESSED **********
//***********************************************
//***********************************************
gboolean event_button_press_event (GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	std::cout << "BOTON PULSADO" << std::endl;
	
	if (widget == event_box_button_down)
	{
		gtk_image_set_from_file(GTK_IMAGE(image_button_down), "/home/pi/projects/Control_Riego_Rpi/button_down_b.jpg");
	}

	return FALSE;							//Return false so event will be called again
}


//************************************************
//************************************************
//********** A BUTTON HAS BEEN RELEASED **********
//************************************************
//************************************************
gboolean event_button_release_event (GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	std::cout << "BOTON SOLTADO" << std::endl;
	
	if (widget == event_box_button_down)
	{
		gtk_image_set_from_file(GTK_IMAGE(image_button_down), "/home/pi/projects/Control_Riego_Rpi/button_down_a.png");

	}
	
	return FALSE;							//Return false so event will be called again
}

/* Our new improved callback. The data passed to this function
* is printed to stdout. */
void callback( GtkWidget *widget, gpointer data )
{
	g_print ("Hello again - %s was pressed\n", (gchar *) data);
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

////PRIMERA VERSIÓN DE LA VENTANA
/*
    GtkWidget *window, *image;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
    gtk_window_set_title(GTK_WINDOW(window), "Image");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    gtk_container_set_border_width(GTK_CONTAINER(window), 2);

    image = gtk_image_new_from_file("/home/testbed/Downloads/efnbxw.jpg");
    //gtk_container_add(GTK_CONTAINER(window), image);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget* eventBox = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(window), eventBox);

    // Capture button presses.                                                                                                                     
    gtk_widget_add_events (eventBox, GDK_BUTTON_PRESS_MASK);
    g_signal_connect(G_OBJECT(eventBox), "button-press-event", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_add(GTK_CONTAINER(eventBox), image);

    gtk_widget_show_all(window);
    gtk_main();
*/


////SEGUNDA VERSIÓN DE LA VENTANA
/*
	GtkWidget *fixed;

	
	GtkWidget *MainWindow;
	
	gtk_init(&argc, &argv);
	
	MainWindow= gtk_window_new(GTK_WINDOW_TOPLEVEL); 		//GTK_WINDOW_TOPLEVEL = Has a titlebar and border, managed by the window manager. 
	gtk_window_set_title(GTK_WINDOW(MainWindow), "My Application");
	gtk_window_set_default_size(GTK_WINDOW(MainWindow), 600, 500);		//Size of the the client area (excluding the additional areas provided by the window manager)
	gtk_window_set_position(GTK_WINDOW(MainWindow), GTK_WIN_POS_CENTER);
	
	//----- EVENT BOX BASED IMAGE BUTTON -----
	image_button_down = gtk_image_new_from_file("/home/pi/projects/Control_Riego_Rpi/button_down_a.png");
	event_box_button_down = gtk_event_box_new();
	
	gtk_container_add(GTK_CONTAINER(MainWindow), event_box_button_down);
	
	gtk_container_add(GTK_CONTAINER(event_box_button_down), image_button_down);
	gtk_widget_add_events (event_box_button_down, GDK_BUTTON_PRESS_MASK);
	g_signal_connect(G_OBJECT(event_box_button_down), "button_press_event", G_CALLBACK(event_button_press_event), NULL);
	g_signal_connect(G_OBJECT(event_box_button_down), "button_release_event", G_CALLBACK(event_button_release_event), NULL);
	gtk_container_add(GTK_CONTAINER(event_box_button_down), image_button_down);
	
	//gtk_widget_set_size_request(event_box_button_down, 68, 68);			//Will be image size by default, but you can force the widget to be either larger or smaller than it normally would be using this
	fixed = gtk_fixed_new ();
	gtk_fixed_put(GTK_FIXED(fixed), event_box_button_down, 460, 570);		//x, y from top left	
	//gtk_container_add(GTK_CONTAINER(MainWindow), event_box_button_down);

	//----- SET EVENTS TO BE CALLED ----- 
	//g_signal_connect(G_OBJECT(event_box_button_down), "button_press_event", G_CALLBACK(event_button_press_event), NULL);		//("button_press_event" must not be changed)
	//g_signal_connect(G_OBJECT(event_box_button_down), "button_release_event", G_CALLBACK(event_button_release_event), NULL);	//Include if you want the release event ("button_release_event" must not be changed)	
	
	
	gtk_widget_show_all(MainWindow);



	//Close the application if the x button is pressed if ALT+F4 is used
	g_signal_connect(G_OBJECT(MainWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);


	//----- ENTER THE GTK MAIN LOOP -----
	gtk_main();		//Enter the GTK+ main loop until the application closes.
*/

	////TERCERA VERSIÓN DE LA VENTANA
	/* GtkWidget is the storage type for widgets */
	GtkWidget *window;
	GtkWidget *button;
	GtkButton *button1;
	GtkButton *button2;	
	GtkWidget *box1;
	/* This is called in all GTK applications. Arguments are parsed
	* from the command line and are returned to the application. */
	gtk_init (&argc, &argv);
	/* Create a new window */
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	/* This is a new call, which just sets the title of our
	* new window to "Hello Buttons!" */
	gtk_window_set_title (GTK_WINDOW (window), "Hello Buttons!");
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 500);		//Size of the the client area (excluding the additional areas provided by the window manager)
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	
	/* Here we just set a handler for delete_event that immediately
	* exits GTK. */
	g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (delete_event), NULL);
	/* Sets the border width of the window. */
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	/* We create a box to pack widgets into. This is described in detail
	* in the "packing" section. The box is not really visible, it
	* is just used as a tool to arrange widgets. */
	box1 = gtk_hbox_new (FALSE, 0);
	/* Put the box into the main window. */
	gtk_container_add (GTK_CONTAINER (window), box1);
	/* Creates a new button with the label "Button 1". */
	button = gtk_button_new_with_label ("Button 1");
	button1 = new GtkButton;//("Boton 1");
	button2 = new GtkButton;//("Boton 2");
	gtk_button_set_label(button1, "Boton_1");
	gtk_button_set_label(button2, "Boton_2");
		
	gtk_widget_set_size_request(button,2,2);
	
	/* Now when the button is clicked, we call the "callback" function
	* with a pointer to "button 1" as its argument */
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback), (gpointer) "button 1");
	
	/* Instead of gtk_container_add, we pack this button into the invisible
	 *  box, which has been packed into the window. */
	gtk_box_pack_start (GTK_BOX(box1), button, TRUE, FALSE, 0);
	
	/* Always remember this step, this tells GTK that our preparation
	for
	* this button is complete, and it can now be displayed. */
	gtk_widget_show (button);
	//gtk_widget_show (button1);
	/* Do these same steps again to create a second button */
	button = gtk_button_new_with_label ("Button 2");
	gtk_widget_set_size_request(button,2,2);
	
	/* Call the same callback function with a different argument,
	* passing a pointer to "button 2" instead. */
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback), (gpointer) "button 2");
	gtk_box_pack_start(GTK_BOX (box1), button, TRUE, FALSE, 0);
	/* The order in which we show the buttons is not really important,
	but I
	* recommend showing the window last, so it all pops up at once. */
	gtk_widget_show (button);
	gtk_widget_show (box1);
	gtk_widget_show (window);
	/* Rest in gtk_main and wait for the fun to begin! */
	gtk_main ();

	return 0;
	
}


