#ifndef VAR_FUNC_GLOBALES
#define VAR_FUNC_GLOBALES

#include <gtk/gtk.h>
#include <bcm2835.h>
#include "Repositorio.h"

#include "libcomms/include/message_sender.hpp"
#include "libcomms/include/message_receiver.hpp"

extern CMessageSender* emisor_local;
extern CMessageReceiver* receptor_local;

extern volatile bool ejecutar_hebra_1;// = true;
extern volatile bool ejecutar_hebra_2;// = true;

extern volatile bool conmutar_color;// = false;

extern const char* etiquetas_botones[10];// = {"Button_1", "Button_2", "Button_3", "Button_4", "Button_5", "Button_6", "Button_7", "Button_8", "Button_9", "Button_10"};
extern const char* id_botones[10];// = {"button_1", "button_2", "button_3", "button_4", "button_5", "button_6", "button_7", "button_8", "button_9", "button_10"};

extern const char* titulo_ventana_prog_riego;// = "Editar programa de riego";

extern CRepositorio *repositorio;// = 0;
extern char prueba;

//Variables GUI ventana principal
extern GtkWidget *ventana_ppal;
extern GtkWidget *button;
extern GtkWidget *drawing_area;
extern GtkWidget *list_box;
extern GtkComboBox *cbox_quaity;
extern GtkListBox *gtk_list_box;
extern char titulo_vent_prog_riego[28];

//Variables GUI ventana edición programas de riego
extern GtkWidget *ventana_edic_programa;
extern GtkWidget *hboxVentana_edicProg;
extern GtkWidget *vboxEtiquetas_edicProg;
extern GtkWidget *vboxCampos_edicProg;
extern GtkWidget *vboxBoton_edicProg;
extern GtkWidget *etiquetaHoraInicio_edicProg;
extern GtkWidget *etiquetaDuracionValv1_edicProg;
extern GtkWidget *etiquetaDuracionValv2_edicProg;
extern GtkWidget *etiquetaDuracionValv3_edicProg;
extern GtkWidget *etiquetaDuracionValv4_edicProg;		
extern GtkWidget *campoHoraInicio_edicProg;
extern GtkWidget *campoDuracionValv1_edicProg;
extern GtkWidget *campoDuracionValv2_edicProg;
extern GtkWidget *campoDuracionValv3_edicProg;
extern GtkWidget *campoDuracionValv4_edicProg;		
extern GtkTextBuffer *buffHoraInicio_edicProg;
extern GtkTextBuffer *buffDuracionValv1_edicProg;		
extern GtkTextBuffer *buffDuracionValv2_edicProg;
extern GtkTextBuffer *buffDuracionValv3_edicProg;
extern GtkTextBuffer *buffDuracionValv4_edicProg;		
extern GtkWidget *botonAplicar_edicProg;
extern bool ventana_prog_riego_activa;

extern GtkWidget *box1;	
extern GtkWidget *box2;	
extern GtkWidget *box3;
extern GtkWidget *box4;
extern GtkWidget *box5;
extern GtkWidget *hbox;

//Funciones relativas al GUI, ventana principal
void inicializar_GUI(void);
void finalizar_GUI(void);
void configurar_botones(void);
void configurar_etiquetas(void);
void configurar_cajas_widgets(void);
void configurar_lista_programas(void);
void configurar_areas_dibujo(void);
void configurar_marco_ventana_ppal(void);

//Funciones relativas a la ventana de edición de programa de riego
void configurar_ventana_prog_riego(void);
void mostrar_ventana_prog_riego(void);
void callback_boton_aplicar(GtkWidget *widget, gpointer data);


//Funciones de retrollamada para eventos del GUI, ventana principal
static gboolean timer_event(GtkWidget *widget);
gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data);
gint delete_event( GtkWidget *widget, GdkEvent *event, gpointer data);
void selected_event_callback (GtkListBox *list_box, GtkListBoxRow *row, gpointer data);
void callback_botones (GtkWidget *widget, gpointer data);

//Funciones de GPIO
void inicializar_GPIO(void);

#endif
