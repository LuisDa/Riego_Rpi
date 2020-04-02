#include "ProgramaRiegoDlg.h"

CProgramaRiegoDlg::CProgramaRiegoDlg(const gchar* titulo)
{
	m_hboxVentana = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 8);
	m_vboxEtiquetas = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	m_vboxCampos = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	
	m_ventana = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (m_ventana), titulo);
	gtk_window_set_default_size(GTK_WINDOW(m_ventana), 400, 200);
	gtk_window_set_position(GTK_WINDOW(m_ventana), GTK_WIN_POS_CENTER);
	//g_signal_connect(G_OBJECT (ventana), "delete_event", G_CALLBACK (&CProgramaRiegoDlg::delete_event), NULL);
	
	gtk_container_add (GTK_CONTAINER (m_ventana), m_hboxVentana);
	gtk_box_pack_start(GTK_BOX(m_hboxVentana), m_vboxEtiquetas, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(m_hboxVentana), m_vboxCampos, FALSE, FALSE, 0);
	
	m_etiquetaHoraInicio = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(m_etiquetaHoraInicio), "Hora inicio");
	gtk_label_set_justify(GTK_LABEL(m_etiquetaHoraInicio), GTK_JUSTIFY_CENTER);
	gtk_box_pack_start (GTK_BOX(m_vboxEtiquetas), m_etiquetaHoraInicio, FALSE, FALSE, 0);
	gtk_widget_show (m_etiquetaHoraInicio);
	
	
	//Mostramos por último las cajas de widgets
	gtk_widget_show(m_vboxEtiquetas);
	gtk_widget_show(m_vboxCampos);
	gtk_widget_show(m_hboxVentana);
}

CProgramaRiegoDlg::~CProgramaRiegoDlg()
{
	delete m_ventana;
	m_ventana = NULL;
}

gint CProgramaRiegoDlg::delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_main_quit ();
	return FALSE;
}

void CProgramaRiegoDlg::mostrar_ventana()
{
	gtk_widget_show (m_ventana);
}

