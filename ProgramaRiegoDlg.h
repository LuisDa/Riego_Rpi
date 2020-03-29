#ifndef PROGRAMA_RIEGO_DLG_H
#define PROGRAMA_RIEGO_DLG_H

#include <gtk/gtk.h>

class CProgramaRiegoDlg
{
	public:
		CProgramaRiegoDlg (gchar* titulo);
		gint delete_event( GtkWidget *widget, GdkEvent *event, gpointer data );
		void mostrar_ventana();
		
		
	private:
		GtkWidget *ventana;
	
};
#endif 


CProgramaRiegoDlg::CProgramaRiegoDlg(gchar* titulo)
{
	ventana = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (ventana), titulo);
	gtk_window_set_default_size(GTK_WINDOW(ventana), 400, 200);
	gtk_window_set_position(GTK_WINDOW(ventana), GTK_WIN_POS_CENTER);
	//g_signal_connect(G_OBJECT (ventana), "delete_event", G_CALLBACK (&CProgramaRiegoDlg::delete_event), NULL);
}

gint CProgramaRiegoDlg::delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_main_quit ();
	return FALSE;
}

void CProgramaRiegoDlg::mostrar_ventana()
{
	gtk_widget_show (ventana);
}
