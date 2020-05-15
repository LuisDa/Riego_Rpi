#include <string.h>
#include <math.h>
#include "var_func_globales.h"

char prueba = '0';

CMessageSender* emisor_local;
CMessageReceiver* receptor_local;

volatile bool ejecutar_hebra_1 = true;
volatile bool ejecutar_hebra_2 = true;

volatile bool conmutar_color = false;

const char* etiquetas_botones[10] = {"Button_1", "Button_2", "Button_3", "Button_4", "Button_5", "Button_6", "Button_7", "Button_8", "Button_9", "Button_10"};
const char* id_botones[10] = {"button_1", "button_2", "button_3", "button_4", "button_5", "button_6", "button_7", "button_8", "button_9", "button_10"};

const char* titulo_ventana_prog_riego = "Editar programa de riego";
CRepositorio *repositorio = 0;

GtkWidget *ventana_ppal;


GtkWidget *button;
GtkWidget *drawing_area;
GtkWidget *list_box;
GtkComboBox *cbox_quaity;
GtkListBox *gtk_list_box;
char titulo_vent_prog_riego[28];

GtkWidget *box1;	
GtkWidget *box2;	
GtkWidget *box3;
GtkWidget *box4;
GtkWidget *box5;
GtkWidget *hbox;

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
	else if (strcmp((gchar*)data, "edit_programa") == 0)
	{		
		sprintf(titulo_vent_prog_riego, "Editar programa de riego %d", repositorio->getIdProgramaSeleccionado());
		titulo_vent_prog_riego[27] = 0;
			
		configurar_ventana_prog_riego();
		mostrar_ventana_prog_riego();
	}
		
	if (strcmp((gchar*)data, "button_2") == 0)
	{
		conmutar_color = true;
		gtk_widget_queue_draw(drawing_area);
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

void configurar_botones(void)
{
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
	
	button = gtk_button_new_with_label ("Editar Programa");
	gtk_widget_set_size_request(button,2,2);
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (callback_botones), (gpointer) "edit_programa");
	gtk_box_pack_start(GTK_BOX (box5), button, FALSE, FALSE, 0);
	gtk_widget_show (button);
}

void configurar_etiquetas(void)
{
	GtkWidget *etiqueta;
	etiqueta = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(etiqueta), "<span foreground=\"black\" size=\"x-small\">Programa 1</span>");
	gtk_label_set_justify(GTK_LABEL(etiqueta), GTK_JUSTIFY_CENTER);
	gtk_list_box_insert(gtk_list_box, etiqueta, -1);
	gtk_widget_show(etiqueta);
	
	etiqueta = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(etiqueta), "<span foreground=\"black\" size=\"x-small\">Programa 2</span>");
	gtk_label_set_justify(GTK_LABEL(etiqueta), GTK_JUSTIFY_CENTER);
	gtk_list_box_insert(gtk_list_box, etiqueta, -1);
	gtk_widget_show(etiqueta);	
	
	etiqueta = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(etiqueta), "<span foreground=\"black\" size=\"x-small\">Programa 3</span>");
	gtk_label_set_justify(GTK_LABEL(etiqueta), GTK_JUSTIFY_CENTER);
	gtk_list_box_insert(gtk_list_box, etiqueta, -1);
	gtk_widget_show(etiqueta);	
}

void configurar_cajas_widgets(void)
{
	hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 8);
	
	box1 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	
	box2 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	
	box3 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	
	box4 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	
	box5 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);

	gtk_container_add (GTK_CONTAINER (ventana_ppal), hbox);
	gtk_box_pack_start(GTK_BOX(hbox), box1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), box2, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), box3, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), box4, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), box5, FALSE, FALSE, 0);	
}

void configurar_lista_programas(void)
{
	list_box = gtk_list_box_new();	
	gtk_list_box = (GtkListBox*)list_box;
	g_signal_connect (G_OBJECT (gtk_list_box), "row-selected", G_CALLBACK (selected_event_callback), NULL);
	gtk_widget_set_size_request (list_box, 100, 300);
	gtk_box_pack_start(GTK_BOX (box4), list_box, FALSE, FALSE, 0);
	gtk_widget_show(list_box);	
}

void configurar_areas_dibujo(void)
{
	drawing_area = gtk_drawing_area_new(); 	       
    gtk_widget_set_size_request (drawing_area, 100, 50);    
	g_signal_connect (G_OBJECT (drawing_area), "draw", G_CALLBACK (draw_callback), NULL);
	gtk_box_pack_start(GTK_BOX (box3), drawing_area, FALSE, FALSE, 0);
	gtk_widget_show (drawing_area);	
}

void configurar_marco_ventana_ppal(void)
{
	ventana_ppal = gtk_window_new (GTK_WINDOW_TOPLEVEL);	
	gtk_window_set_title (GTK_WINDOW (ventana_ppal), "GÜINDOU");
	gtk_window_set_default_size(GTK_WINDOW(ventana_ppal), 600, 500);		//Size of the the client area (excluding the additional areas provided by the window manager)
	gtk_window_set_position(GTK_WINDOW(ventana_ppal), GTK_WIN_POS_CENTER);
		
	g_timeout_add(1000, (GSourceFunc) timer_event, (gpointer) ventana_ppal); //Configuramos el temporizador para que genere un evento cada segundo (1000 ms)
	
	g_signal_connect (G_OBJECT (ventana_ppal), "delete_event", G_CALLBACK (delete_event), NULL);	
	gtk_container_set_border_width (GTK_CONTAINER (ventana_ppal), 10);		
}

void inicializar_GUI(void)
{
	configurar_marco_ventana_ppal();	
	configurar_cajas_widgets();	
	configurar_botones();
	configurar_areas_dibujo();
	configurar_lista_programas();	
	configurar_etiquetas();
		
	g_print("Creando elementos de la ventana\n");
	gtk_widget_show (box1);
	gtk_widget_show (box2);
	gtk_widget_show (box3);
	gtk_widget_show (box4);
	gtk_widget_show (box5);
	gtk_widget_show (hbox);
	gtk_widget_show (ventana_ppal);
	g_print("Ventana creada\n");
}

void finalizar_GUI(void)
{
	delete button;
	button = NULL;
	
	delete list_box;
	list_box = NULL;

	delete gtk_list_box;
	gtk_list_box = NULL;
	
	delete drawing_area;
	drawing_area = NULL;
	
	delete box1; 
	box1 = NULL;
	
	delete box2; 
	box2 = NULL;
	
	delete box3; 
	box3 = NULL;
	
	delete box4; 
	box4 = NULL;		
	
	delete box5; 
	box5 = NULL;
	
		
}

//Callback para el TIMER
static gboolean timer_event(GtkWidget *widget)
{
	//g_print ("Saltose el evento del TIMER\n");
	
	if (ventana_prog_riego_activa)
	{
		if (prueba == '9') prueba = '0';
		else prueba++;
		char cadena[2];
		cadena[0] = prueba;
		cadena[1] = 0;
		
		gtk_text_buffer_set_text (buffDuracionValv1_edicProg, cadena, -1);	
	}
	
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

void selected_event_callback (GtkListBox *list_box, GtkListBoxRow *row, gpointer data)
{
	GtkListBoxRow *listBoxRow = (GtkListBoxRow*)gtk_list_box_get_selected_row (list_box);
	int prog_seleccionado = gtk_list_box_row_get_index(listBoxRow);
	repositorio->setIdProgramaSeleccionado(prog_seleccionado+1);
	
	//g_print("Seleccionada línea en lista, gafas\n");
	printf("Seleccionada línea %d en lista, gafas\n", prog_seleccionado);
}


/* another callback */
gint delete_event( GtkWidget *widget, GdkEvent *event, gpointer data )
{
	if (widget == ventana_edic_programa)
	{		
		//gtk_widget_hide(widget);
		ventana_prog_riego_activa = false;
	}
	else if (widget == ventana_ppal)
	{	
		//finalizar_GUI();
		gtk_main_quit ();		
	}
	
	return FALSE;		
}


