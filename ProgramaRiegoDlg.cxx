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
	gtk_widget_set_size_request(m_etiquetaHoraInicio,2,2);
	gtk_label_set_markup(GTK_LABEL(m_etiquetaHoraInicio), "Hora inicio");
	gtk_label_set_justify(GTK_LABEL(m_etiquetaHoraInicio), GTK_JUSTIFY_RIGHT);
	gtk_box_pack_start (GTK_BOX(m_vboxEtiquetas), m_etiquetaHoraInicio, FALSE, FALSE, 0);
	gtk_widget_show (m_etiquetaHoraInicio);
	
	m_etiquetaDuracionValv1 = gtk_label_new(NULL);
	gtk_widget_set_size_request(m_etiquetaDuracionValv1,2,2);
	gtk_label_set_markup(GTK_LABEL(m_etiquetaDuracionValv1), "Duración valv. 1 (min)");
	gtk_label_set_justify(GTK_LABEL(m_etiquetaDuracionValv1), GTK_JUSTIFY_RIGHT);
	gtk_box_pack_start (GTK_BOX(m_vboxEtiquetas), m_etiquetaDuracionValv1, FALSE, FALSE, 0);
	gtk_widget_show (m_etiquetaDuracionValv1);

	m_etiquetaDuracionValv2 = gtk_label_new(NULL);
	gtk_widget_set_size_request(m_etiquetaDuracionValv2,2,2);
	gtk_label_set_markup(GTK_LABEL(m_etiquetaDuracionValv2), "Duración valv. 2 (min)");
	gtk_label_set_justify(GTK_LABEL(m_etiquetaDuracionValv2), GTK_JUSTIFY_RIGHT);
	gtk_box_pack_start (GTK_BOX(m_vboxEtiquetas), m_etiquetaDuracionValv2, FALSE, FALSE, 0);
	gtk_widget_show (m_etiquetaDuracionValv2);	
	
	m_etiquetaDuracionValv3 = gtk_label_new(NULL);
	gtk_widget_set_size_request(m_etiquetaDuracionValv3,2,2);
	gtk_label_set_markup(GTK_LABEL(m_etiquetaDuracionValv3), "Duración valv. 3 (min)");
	gtk_label_set_justify(GTK_LABEL(m_etiquetaDuracionValv3), GTK_JUSTIFY_RIGHT);
	gtk_box_pack_start (GTK_BOX(m_vboxEtiquetas), m_etiquetaDuracionValv3, FALSE, FALSE, 0);
	gtk_widget_show (m_etiquetaDuracionValv3);		

	m_etiquetaDuracionValv4 = gtk_label_new(NULL);
	gtk_widget_set_size_request(m_etiquetaDuracionValv4,2,2);
	gtk_label_set_markup(GTK_LABEL(m_etiquetaDuracionValv4), "Duración valv. 4 (min)");
	gtk_label_set_justify(GTK_LABEL(m_etiquetaDuracionValv4), GTK_JUSTIFY_RIGHT);
	gtk_box_pack_start (GTK_BOX(m_vboxEtiquetas), m_etiquetaDuracionValv4, FALSE, FALSE, 0);
	gtk_widget_show (m_etiquetaDuracionValv4);	
	
	m_campoHoraInicio = gtk_text_view_new();	
	m_buffHoraInicio = gtk_text_view_get_buffer (GTK_TEXT_VIEW (m_campoHoraInicio));
	gtk_widget_set_size_request(m_campoHoraInicio, 80, 20);
	gtk_box_pack_start (GTK_BOX(m_vboxCampos), m_campoHoraInicio, FALSE, FALSE, 0);
	gtk_widget_show (m_campoHoraInicio);
	gtk_text_buffer_set_text (m_buffHoraInicio, "00:00", -1);
	//gtk_fixed_put(GTK_FIXED(fixed), m_campoHoraInicio, 100, 100);	
	
	m_campoDuracionValv1 = gtk_text_view_new();
	m_buffDuracionValv1 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (m_campoDuracionValv1));
	gtk_widget_set_size_request(m_campoDuracionValv1, 80, 20);
	gtk_box_pack_start (GTK_BOX(m_vboxCampos), m_campoDuracionValv1, FALSE, FALSE, 0);
	gtk_widget_show (m_campoDuracionValv1);	
	gtk_text_buffer_set_text (m_buffDuracionValv1, "0", -1);

	m_campoDuracionValv2 = gtk_text_view_new();
	m_buffDuracionValv2 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (m_campoDuracionValv2));
	gtk_widget_set_size_request(m_campoDuracionValv2, 80, 20);
	gtk_box_pack_start (GTK_BOX(m_vboxCampos), m_campoDuracionValv2, FALSE, FALSE, 0);
	gtk_widget_show (m_campoDuracionValv2);	
	gtk_text_buffer_set_text (m_buffDuracionValv2, "0", -1);
	
	m_campoDuracionValv3 = gtk_text_view_new();
	m_buffDuracionValv3 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (m_campoDuracionValv3));
	gtk_widget_set_size_request(m_campoDuracionValv3, 80, 20);
	gtk_box_pack_start (GTK_BOX(m_vboxCampos), m_campoDuracionValv3, FALSE, FALSE, 0);
	gtk_widget_show (m_campoDuracionValv3);	
	gtk_text_buffer_set_text (m_buffDuracionValv3, "0", -1);
	
	m_campoDuracionValv4 = gtk_text_view_new();
	m_buffDuracionValv4 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (m_campoDuracionValv4));
	gtk_widget_set_size_request(m_campoDuracionValv4, 80, 20);
	gtk_box_pack_start (GTK_BOX(m_vboxCampos), m_campoDuracionValv4, FALSE, FALSE, 0);
	gtk_widget_show (m_campoDuracionValv4);	
	gtk_text_buffer_set_text (m_buffDuracionValv4, "0", -1);	
	
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

