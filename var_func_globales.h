#ifndef VAR_FUNC_GLOBALES
#define VAR_FUNC_GLOBALES

#include <gtk/gtk.h>
#include <bcm2835.h>
#include "ProgramaRiegoDlg.h"


extern volatile bool ejecutar_hebra_1;// = true;
extern volatile bool ejecutar_hebra_2;// = true;

extern volatile bool conmutar_color;// = false;

extern const char* etiquetas_botones[10];// = {"Button_1", "Button_2", "Button_3", "Button_4", "Button_5", "Button_6", "Button_7", "Button_8", "Button_9", "Button_10"};
extern const char* id_botones[10];// = {"button_1", "button_2", "button_3", "button_4", "button_5", "button_6", "button_7", "button_8", "button_9", "button_10"};

extern const char* titulo_ventana_prog_riego;// = "Editar programa de riego";

extern CRepositorio *repositorio;// = 0;

extern GtkWidget *window;
extern GtkWidget *button;
extern GtkWidget *drawing_area;
extern GtkWidget *list_box;
extern GtkComboBox *cbox_quaity;
extern GtkListBox *gtk_list_box;

extern GtkWidget *window_programa;
extern CProgramaRiegoDlg *ventana_programa;// = NULL;

extern GtkWidget *box1;	
extern GtkWidget *box2;	
extern GtkWidget *box3;
extern GtkWidget *box4;
extern GtkWidget *box5;
extern GtkWidget *hbox;

//Funciones relativas al GUI
void inicializar_GUI(void);
void finalizar_GUI(void);
void configurar_botones(void);
void configurar_etiquetas(void);
void configurar_cajas_widgets(void);
void configurar_lista_programas(void);
void configurar_areas_dibujo(void);
void configurar_marco_ventana_ppal(void);

//Funciones de retrollamada para eventos del GUI
static gboolean timer_event(GtkWidget *widget);
gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data);
gint delete_event( GtkWidget *widget, GdkEvent *event, gpointer data);
void selected_event_callback (GtkListBox *list_box, GtkListBoxRow *row, gpointer data);
void callback_botones (GtkWidget *widget, gpointer data);

//Funciones de GPIO
void inicializar_GPIO(void);

#endif
