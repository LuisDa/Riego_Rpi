#include <iostream>
#include <fstream>
#include <string.h>
#include "var_func_globales.h"

using namespace std;

GtkWidget *ventana_edic_programa;

GtkWidget *hboxVentana_edicProg;
GtkWidget *vboxEtiquetas_edicProg;
GtkWidget *vboxCampos_edicProg;
GtkWidget *vboxBoton_edicProg;

GtkWidget *etiquetaHoraInicio_edicProg;
GtkWidget *etiquetaDuracionValv1_edicProg;
GtkWidget *etiquetaDuracionValv2_edicProg;
GtkWidget *etiquetaDuracionValv3_edicProg;
GtkWidget *etiquetaDuracionValv4_edicProg;		

GtkWidget *campoHoraInicio_edicProg;
GtkWidget *campoDuracionValv1_edicProg;
GtkWidget *campoDuracionValv2_edicProg;
GtkWidget *campoDuracionValv3_edicProg;
GtkWidget *campoDuracionValv4_edicProg;		

GtkTextBuffer *buffHoraInicio_edicProg;
GtkTextBuffer *buffDuracionValv1_edicProg;		
GtkTextBuffer *buffDuracionValv2_edicProg;
GtkTextBuffer *buffDuracionValv3_edicProg;
GtkTextBuffer *buffDuracionValv4_edicProg;		

GtkWidget *botonAplicar_edicProg;

bool ventana_prog_riego_activa = false;

void configurar_ventana_prog_riego(void)
{
	//char* campo_valv = " ";
	char campo_valv[3];
	char campo_hora_ini[6];
	
	hboxVentana_edicProg = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 8);
	vboxEtiquetas_edicProg = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	vboxCampos_edicProg = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	vboxBoton_edicProg = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	
	ventana_edic_programa = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (ventana_edic_programa), titulo_vent_prog_riego);
	gtk_window_set_default_size(GTK_WINDOW(ventana_edic_programa), 400, 200);
	gtk_window_set_position(GTK_WINDOW(ventana_edic_programa), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT (ventana_edic_programa), "delete_event", G_CALLBACK (delete_event), NULL);
	
	gtk_container_add (GTK_CONTAINER (ventana_edic_programa), hboxVentana_edicProg);
	gtk_box_pack_start(GTK_BOX(hboxVentana_edicProg), vboxEtiquetas_edicProg, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hboxVentana_edicProg), vboxCampos_edicProg, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hboxVentana_edicProg), vboxBoton_edicProg, FALSE, FALSE, 0);
		
	etiquetaHoraInicio_edicProg = gtk_label_new(NULL);
	gtk_widget_set_size_request(etiquetaHoraInicio_edicProg,2,2);
	gtk_label_set_markup(GTK_LABEL(etiquetaHoraInicio_edicProg), "Hora inicio");
	gtk_label_set_justify(GTK_LABEL(etiquetaHoraInicio_edicProg), GTK_JUSTIFY_RIGHT);
	gtk_box_pack_start (GTK_BOX(vboxEtiquetas_edicProg), etiquetaHoraInicio_edicProg, FALSE, FALSE, 0);
	gtk_widget_show (etiquetaHoraInicio_edicProg);
			
	etiquetaDuracionValv1_edicProg = gtk_label_new(NULL);
	gtk_widget_set_size_request(etiquetaDuracionValv1_edicProg,2,2);
	gtk_label_set_markup(GTK_LABEL(etiquetaDuracionValv1_edicProg), "Duración valv. 1 (min)");
	gtk_label_set_justify(GTK_LABEL(etiquetaDuracionValv1_edicProg), GTK_JUSTIFY_RIGHT);
	gtk_box_pack_start (GTK_BOX(vboxEtiquetas_edicProg), etiquetaDuracionValv1_edicProg, FALSE, FALSE, 0);
	gtk_widget_show (etiquetaDuracionValv1_edicProg);

	etiquetaDuracionValv2_edicProg = gtk_label_new(NULL);
	gtk_widget_set_size_request(etiquetaDuracionValv2_edicProg,2,2);
	gtk_label_set_markup(GTK_LABEL(etiquetaDuracionValv2_edicProg), "Duración valv. 2 (min)");
	gtk_label_set_justify(GTK_LABEL(etiquetaDuracionValv2_edicProg), GTK_JUSTIFY_RIGHT);
	gtk_box_pack_start (GTK_BOX(vboxEtiquetas_edicProg), etiquetaDuracionValv2_edicProg, FALSE, FALSE, 0);
	gtk_widget_show (etiquetaDuracionValv2_edicProg);	

	etiquetaDuracionValv3_edicProg = gtk_label_new(NULL);
	gtk_widget_set_size_request(etiquetaDuracionValv3_edicProg,2,2);
	gtk_label_set_markup(GTK_LABEL(etiquetaDuracionValv3_edicProg), "Duración valv. 3 (min)");
	gtk_label_set_justify(GTK_LABEL(etiquetaDuracionValv3_edicProg), GTK_JUSTIFY_RIGHT);
	gtk_box_pack_start (GTK_BOX(vboxEtiquetas_edicProg), etiquetaDuracionValv3_edicProg, FALSE, FALSE, 0);
	gtk_widget_show (etiquetaDuracionValv3_edicProg);		
	
	etiquetaDuracionValv4_edicProg = gtk_label_new(NULL);
	gtk_widget_set_size_request(etiquetaDuracionValv4_edicProg,2,2);
	gtk_label_set_markup(GTK_LABEL(etiquetaDuracionValv4_edicProg), "Duración valv. 4 (min)");
	gtk_label_set_justify(GTK_LABEL(etiquetaDuracionValv4_edicProg), GTK_JUSTIFY_RIGHT);
	gtk_box_pack_start (GTK_BOX(vboxEtiquetas_edicProg), etiquetaDuracionValv4_edicProg, FALSE, FALSE, 0);
	gtk_widget_show (etiquetaDuracionValv4_edicProg);	

	campoHoraInicio_edicProg = gtk_text_view_new();	
	buffHoraInicio_edicProg = gtk_text_view_get_buffer (GTK_TEXT_VIEW (campoHoraInicio_edicProg));
	gtk_widget_set_size_request(campoHoraInicio_edicProg, 80, 20);
	gtk_box_pack_start (GTK_BOX(vboxCampos_edicProg), campoHoraInicio_edicProg, FALSE, FALSE, 0);
	gtk_widget_show (campoHoraInicio_edicProg);
	
	char hora_inicio = repositorio->getHoraInicio(repositorio->getIdProgramaSeleccionado());
	char min_inicio = repositorio->getMinutoInicio(repositorio->getIdProgramaSeleccionado());
	sprintf(campo_hora_ini, "%d:%d\0", hora_inicio, min_inicio);
	
	//gtk_text_buffer_set_text (buffHoraInicio_edicProg, "00:00", -1);
	gtk_text_buffer_set_text (buffHoraInicio_edicProg, (const char*)campo_hora_ini, -1);
	//gtk_fixed_put(GTK_FIXED(fixed), m_campoHoraInicio, 100, 100);	
	
	campoDuracionValv1_edicProg = gtk_text_view_new();
	buffDuracionValv1_edicProg = gtk_text_view_get_buffer (GTK_TEXT_VIEW (campoDuracionValv1_edicProg));
	gtk_widget_set_size_request(campoDuracionValv1_edicProg, 80, 20);
	gtk_box_pack_start (GTK_BOX(vboxCampos_edicProg), campoDuracionValv1_edicProg, FALSE, FALSE, 0);
	gtk_widget_show (campoDuracionValv1_edicProg);	
	//gtk_text_buffer_set_text (buffDuracionValv1_edicProg, "0", -1);
	
	//campo_valv[0] = '2';// repositorio->getDuracionValv(repositorio->getIdProgramaSeleccionado(), 1);	
	char duracion_valvula = repositorio->getDuracionValv(repositorio->getIdProgramaSeleccionado(), 1);
	sprintf(campo_valv, "%d\0", duracion_valvula);	
	gtk_text_buffer_set_text (buffDuracionValv1_edicProg, (const char*)campo_valv, -1);	

	campoDuracionValv2_edicProg = gtk_text_view_new();
	buffDuracionValv2_edicProg = gtk_text_view_get_buffer (GTK_TEXT_VIEW (campoDuracionValv2_edicProg));
	gtk_widget_set_size_request(campoDuracionValv2_edicProg, 80, 20);
	gtk_box_pack_start (GTK_BOX(vboxCampos_edicProg), campoDuracionValv2_edicProg, FALSE, FALSE, 0);
	gtk_widget_show (campoDuracionValv2_edicProg);	
	
	duracion_valvula = repositorio->getDuracionValv(repositorio->getIdProgramaSeleccionado(), 2);
	sprintf(campo_valv, "%d\0", duracion_valvula);	
	gtk_text_buffer_set_text (buffDuracionValv2_edicProg, (const char*)campo_valv, -1);	
	//campo_valv[0] = repositorio->getDuracionValv(repositorio->getIdProgramaSeleccionado(), 2);	
	//gtk_text_buffer_set_text (buffDuracionValv2_edicProg, (const char*)campo_valv, -1);	
	//gtk_text_buffer_set_text (buffDuracionValv2_edicProg, "0", -1);

	campoDuracionValv3_edicProg = gtk_text_view_new();
	buffDuracionValv3_edicProg = gtk_text_view_get_buffer (GTK_TEXT_VIEW (campoDuracionValv3_edicProg));
	gtk_widget_set_size_request(campoDuracionValv3_edicProg, 80, 20);
	gtk_box_pack_start (GTK_BOX(vboxCampos_edicProg), campoDuracionValv3_edicProg, FALSE, FALSE, 0);
	gtk_widget_show (campoDuracionValv3_edicProg);	
	
	duracion_valvula = repositorio->getDuracionValv(repositorio->getIdProgramaSeleccionado(), 3);
	sprintf(campo_valv, "%d\0", duracion_valvula);	
	gtk_text_buffer_set_text (buffDuracionValv3_edicProg, (const char*)campo_valv, -1);	
	//campo_valv[0] = repositorio->getDuracionValv(repositorio->getIdProgramaSeleccionado(), 3);	
	//gtk_text_buffer_set_text (buffDuracionValv2_edicProg, (const char*)campo_valv, -1);		
	//gtk_text_buffer_set_text (buffDuracionValv3_edicProg, "0", -1);

	campoDuracionValv4_edicProg = gtk_text_view_new();
	buffDuracionValv4_edicProg = gtk_text_view_get_buffer (GTK_TEXT_VIEW (campoDuracionValv4_edicProg));
	gtk_widget_set_size_request(campoDuracionValv4_edicProg, 80, 20);
	gtk_box_pack_start (GTK_BOX(vboxCampos_edicProg), campoDuracionValv4_edicProg, FALSE, FALSE, 0);
	gtk_widget_show (campoDuracionValv4_edicProg);	
	
	duracion_valvula = repositorio->getDuracionValv(repositorio->getIdProgramaSeleccionado(), 4);
	sprintf(campo_valv, "%d\0", duracion_valvula);	
	gtk_text_buffer_set_text (buffDuracionValv4_edicProg, (const char*)campo_valv, -1);		
	
	//campo_valv[0] = repositorio->getDuracionValv(repositorio->getIdProgramaSeleccionado(), 4);	
	//gtk_text_buffer_set_text (buffDuracionValv4_edicProg, (const char*)campo_valv, -1);	
	//gtk_text_buffer_set_text (buffDuracionValv4_edicProg, "0", -1);	
	
	
	botonAplicar_edicProg = gtk_button_new_with_label ("Aplicar");
	gtk_widget_set_size_request(botonAplicar_edicProg,2,2);
	g_signal_connect (G_OBJECT (botonAplicar_edicProg), "clicked", G_CALLBACK (callback_boton_aplicar), NULL);
	gtk_box_pack_start(GTK_BOX (vboxBoton_edicProg), botonAplicar_edicProg, FALSE, FALSE, 0);
	gtk_widget_show (botonAplicar_edicProg);
	
	
	//Mostramos por último las cajas de widgets
	gtk_widget_show(vboxEtiquetas_edicProg);
	gtk_widget_show(vboxCampos_edicProg);
	gtk_widget_show(vboxBoton_edicProg);
	gtk_widget_show(hboxVentana_edicProg);	
	
}

void mostrar_ventana_prog_riego(void)
{
	gtk_widget_show (ventana_edic_programa);
	ventana_prog_riego_activa = true;
}

void callback_boton_aplicar(GtkWidget *widget, gpointer data)
{
	g_print("Pulsado botón Aplicar\n");
	
	GtkTextIter inicio, fin;
	char *buffer;
	buffer = new char[6];
	memset(buffer, 0x00, sizeof(buffer));

	ofstream fichero;
	
	/*
	if (repositorio->getIdProgramaSeleccionado() == 1) fichero.open("programa_1.txt");
	else if (repositorio->getIdProgramaSeleccionado() == 2) fichero.open("programa_2.txt");
	else if (repositorio->getIdProgramaSeleccionado() == 3) fichero.open("programa_3.txt");
	*/
	
	if (programa_seleccionado == 0) fichero.open("programa_1.txt");
	else if (programa_seleccionado == 1) fichero.open("programa_2.txt");
	else if (programa_seleccionado == 2) fichero.open("programa_3.txt");
		
	//Guardamos en primer lugar la hora de inicio	//buffHoraInicio_edicProg
	gtk_text_buffer_get_start_iter (buffHoraInicio_edicProg, &inicio);
	gtk_text_buffer_get_end_iter (buffHoraInicio_edicProg, &fin);
	buffer = gtk_text_buffer_get_text (buffHoraInicio_edicProg, &inicio, &fin, FALSE); 
	fichero << "H " << buffer << std::endl;	
	
	//Actualizamos hora y minuto en el repositorio	
	string str_hora_ini(buffer);
	repositorio->actualizarHoraInicio(str_hora_ini, (programa_seleccionado+1));
		
	//Guardamos el contenido de los campos en un fichero
	gtk_text_buffer_get_start_iter (buffDuracionValv1_edicProg, &inicio);
	gtk_text_buffer_get_end_iter (buffDuracionValv1_edicProg, &fin);
	buffer = gtk_text_buffer_get_text (buffDuracionValv1_edicProg, &inicio, &fin, FALSE); 	
	repositorio->setDuracionValv(repositorio->getIdProgramaSeleccionado(), 1, atoi(buffer));	
	fichero << "V1 " << buffer << std::endl;
	
	gtk_text_buffer_get_start_iter (buffDuracionValv2_edicProg, &inicio);
	gtk_text_buffer_get_end_iter (buffDuracionValv2_edicProg, &fin);
	buffer = gtk_text_buffer_get_text (buffDuracionValv2_edicProg, &inicio, &fin, FALSE); 	
	repositorio->setDuracionValv(repositorio->getIdProgramaSeleccionado(), 2, atoi(buffer));	
	fichero << "V2 " << buffer << std::endl;
	
	gtk_text_buffer_get_start_iter (buffDuracionValv3_edicProg, &inicio);
	gtk_text_buffer_get_end_iter (buffDuracionValv3_edicProg, &fin);
	buffer = gtk_text_buffer_get_text (buffDuracionValv3_edicProg, &inicio, &fin, FALSE); 
	repositorio->setDuracionValv(repositorio->getIdProgramaSeleccionado(), 3, atoi(buffer));
	fichero << "V3 " << buffer << std::endl;	
	
	gtk_text_buffer_get_start_iter (buffDuracionValv4_edicProg, &inicio);
	gtk_text_buffer_get_end_iter (buffDuracionValv4_edicProg, &fin);
	buffer = gtk_text_buffer_get_text (buffDuracionValv4_edicProg, &inicio, &fin, FALSE); 
	repositorio->setDuracionValv(repositorio->getIdProgramaSeleccionado(), 4, atoi(buffer));
	fichero << "V4 " << buffer << std::endl;
	
	fichero.close();
	
	habilitar_edicion_programa = true;

	//Enviamos comando de refresco de repositorio por memoria compartida
	shmem_p->comando = 0x20;	
	shmem_p->complete = 0;
	shmem_p->enviado = 1;
	
	gtk_widget_destroy(ventana_edic_programa);

	//std::cout << "Válvula 1: <<"<< buffer << ">> "<< std::endl;
}
