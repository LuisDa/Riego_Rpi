#ifndef PROGRAMA_RIEGO_DLG_H
#define PROGRAMA_RIEGO_DLG_H

#include <gtk/gtk.h>

class CProgramaRiegoDlg
{
	public:
		CProgramaRiegoDlg (const gchar* titulo);
		~CProgramaRiegoDlg();
		gint delete_event( GtkWidget *widget, GdkEvent *event, gpointer data );
		void mostrar_ventana();
		
		
	private:
		GtkWidget *m_ventana;
		
		GtkWidget *m_hboxVentana;
		GtkWidget *m_vboxEtiquetas;
		GtkWidget *m_vboxCampos;
		
		GtkWidget *m_etiquetaHoraInicio;
		GtkWidget *m_etiquetaDuracionValv1;
		GtkWidget *m_etiquetaDuracionValv2;
		GtkWidget *m_etiquetaDuracionValv3;
		GtkWidget *m_etiquetaDuracionValv4;
	
};
#endif 


