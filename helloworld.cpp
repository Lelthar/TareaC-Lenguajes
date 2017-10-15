#include <gtk/gtk.h>

int main(int argc, char* argv[])
{
	gtk_init(&argc,&argv); // Iniciar gtk
	GtkWidget *window,* label;		// Declarar una ventana como puntero a un widget
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);	// Inicializa una ventana en el lado de arriba
	g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);	// Conectar una señal con una funcion de salir de la interface gtk 
	gtk_widget_show(window);
	gtk_main();	// Ciclo infinito para correr la interfaz
	return 0;
}