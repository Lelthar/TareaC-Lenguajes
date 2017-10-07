#include <gtk/gtk.h>	// Incluye libreria gtk y libreria g 

static void button_clicked(GtkWidget *widget, gpointer data)
{
        g_print("%s\n", gtk_entry_get_text(GTK_ENTRY(data)));
//      gtk_entry_set_text(GTK_ENTRY(data),"Text printed");
        gtk_editable_select_region(GTK_EDITABLE(data), 0,-1); // text from 0 to the end
        gtk_editable_copy_clipboard(GTK_EDITABLE(data));
}

int main(int argc, char* argv[]){
	gtk_init(&argc,&argv); // Iniciar gtk
	GtkWidget* window,*cable,*labelUC,*labelIR,*labelPC,*labelRT,*labelFLAGS,*labelALU,*labelB1,*labelB2,*labelB3,*labelB4,*labelMAR,*labelMBR,*buttonUC,*buttonBUS,*buttonPC,*buttonIR,*buttonRT,*buttonFLAGS,*buttonALU,*buttonB1,*buttonB2,*buttonB3,*buttonB4,*buttonMAR,*buttonMBR,*table0,*table1,*table2,*table3,*table4,*table5,*table6,*table7,*table8,*vbox0,*vbox1,*vbox2,*vbox3,*hbox1;// Declarar widgets como punteros a widget
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);// Inicializa una ventana en el lado de arriba
	g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);	// Apretar boton X para salir de la interfaz
	
	GdkColor color;

	gdk_color_parse ("blue", &color);

	cable = gtk_image_new_from_file ("cable.png");
	table0 = gtk_table_new(2,2,0); //rows, columns, homogenous
	table1 = gtk_table_new(2,2,0); //rows, columns, homogenous
	table2 = gtk_table_new(2,2,0); //rows, columns, homogenous
	table3 = gtk_table_new(2,2,0); //rows, columns, homogenous
	table4 = gtk_table_new(2,2,0); //rows, columns, homogenous
	table5 = gtk_table_new(3,4,0); //rows, columns, homogenous -> para la ALU	
	table6 = gtk_table_new(2,2,0); //rows, columns, homogenous -> para la ALU
	table7 = gtk_table_new(2,2,0); //rows, columns, homogenous -> para la ALU
	buttonPC = gtk_button_new_with_mnemonic("_PC");// Inicializa un boton
	buttonIR = gtk_button_new_with_mnemonic("_IR");// Inicializa un boton
	buttonBUS = gtk_button_new_with_mnemonic("_BUS DE\nDATOS");// Inicializa un boton
	buttonUC = gtk_button_new_with_label("UC");// Inicializa un boton
	buttonRT = gtk_button_new_with_mnemonic("_RT");// Inicializa un boton
	buttonFLAGS = gtk_button_new_with_mnemonic("_FLAGS");// Inicializa un boton
	buttonALU = gtk_button_new_with_mnemonic("_ALU");// Inicializa un boton
	buttonB1 = gtk_button_new_with_label("B1");// Inicializa un boton
	buttonB2 = gtk_button_new_with_label("B2");// Inicializa un boton
	buttonB3 = gtk_button_new_with_label("B3");// Inicializa un boton
	buttonB4 = gtk_button_new_with_label("B4");// Inicializa un boton
	buttonMAR = gtk_button_new_with_mnemonic("_MAR");// Inicializa un boton
	buttonMBR = gtk_button_new_with_mnemonic("M_BR");// Inicializa un boton
	labelPC = gtk_label_new(" Program    Counter ");// Inicializa un label
	labelUC = gtk_label_new(" Unidad  de  Control");// Inicializa un label
	labelIR = gtk_label_new("Instruction Register");// Inicializa un label
	labelRT = gtk_label_new("Registros de Trabajo");// Inicializa un label
	labelFLAGS = gtk_label_new("Flags");// Inicializa un label
	labelALU = gtk_label_new("Arithmetic-Logic Unit");// Inicializa un label
	labelMAR = gtk_label_new(" Mem  Address  Reg.");// Inicializa un label
	labelMBR = gtk_label_new("  Mem   Buffer   Reg.");// Inicializa un label
	hbox1 = gtk_hbox_new(0,0);// 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes
	vbox0 = gtk_vbox_new(0,40);// 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes
	vbox1 = gtk_vbox_new(0,0);// 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes
	vbox2 = gtk_vbox_new(0,40);// 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes
	
	gtk_widget_modify_bg (GTK_WIDGET(buttonUC), GTK_STATE_NORMAL, &color);
	//gtk_button_set_always_show_image (GTK_BUTTON (buttonUC), TRUE);
	//gtk_button_set_image (GTK_BUTTON (buttonUC), image);

    gtk_table_attach(GTK_TABLE(table0), labelUC, 0,1,0,1, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla
    gtk_table_attach(GTK_TABLE(table0), buttonUC, 0,1,1,2, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla
    gtk_table_attach(GTK_TABLE(table0), cable, 1,2,1,2, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla  
    cable = gtk_image_new_from_file ("cable.png");  	
    gtk_table_attach(GTK_TABLE(table1), labelPC, 0,1,0,1, GTK_FILL,GTK_FILL, 0,0);// Pega el label a la tabla
    gtk_table_attach(GTK_TABLE(table1), buttonPC, 0,1,1,2, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla	
    gtk_table_attach(GTK_TABLE(table1), cable, 1,2,1,2, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla    	
	cable = gtk_image_new_from_file ("cable.png");
	gtk_table_attach(GTK_TABLE(table2), labelIR, 0,1,0,1, GTK_FILL,GTK_FILL, 0,0);// Pega el label a la tabla
    gtk_table_attach(GTK_TABLE(table2), buttonIR, 0,1,1,2, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla
    gtk_table_attach(GTK_TABLE(table2), cable, 1,2,1,2, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla    	
    cable = gtk_image_new_from_file ("cable.png");
	gtk_table_attach(GTK_TABLE(table3), labelRT, 1,2,0,1, GTK_FILL,GTK_FILL, 0,0);// Pega el label a la tabla
    gtk_table_attach(GTK_TABLE(table3), buttonRT, 1,2,1,2, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla
    gtk_table_attach(GTK_TABLE(table3), cable, 0,1,1,2, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla  
    cable = gtk_image_new_from_file ("cable.png");
	gtk_table_attach(GTK_TABLE(table4), labelFLAGS, 1,2,0,1, GTK_FILL,GTK_FILL, 0,0);// Pega el label a la tabla
    gtk_table_attach(GTK_TABLE(table4), buttonFLAGS, 1,2,1,2, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla
    gtk_table_attach(GTK_TABLE(table4), cable, 0,1,1,2, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla 
    cable = gtk_image_new_from_file ("cable.png");
    gtk_table_attach(GTK_TABLE(table5), buttonB1, 1,2,0,1, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla
    gtk_table_attach(GTK_TABLE(table5), cable, 0,1,0,1, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla 
    cable = gtk_image_new_from_file ("cable.png");
    gtk_table_attach(GTK_TABLE(table5), buttonB2, 1,2,2,3, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla
    gtk_table_attach(GTK_TABLE(table5), cable, 0,1,2,3, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla 
	gtk_table_attach(GTK_TABLE(table5), labelALU, 2,3,0,1, GTK_FILL,GTK_FILL, 0,0);// Pega el label a la tabla    
    gtk_table_attach(GTK_TABLE(table5), buttonALU, 2,3,1,2, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla
    gtk_table_attach(GTK_TABLE(table5), buttonB3, 3,4,0,1, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla
    gtk_table_attach(GTK_TABLE(table5), buttonB4, 3,4,2,3, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla
    cable = gtk_image_new_from_file ("cable.png");
    gtk_table_attach(GTK_TABLE(table6), labelMAR, 0,1,0,1, GTK_FILL,GTK_FILL, 0,0);// Pega el label a la tabla
    gtk_table_attach(GTK_TABLE(table6), buttonMAR, 0,1,1,2, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla	
    gtk_table_attach(GTK_TABLE(table6), cable, 1,2,1,2, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla   
    cable = gtk_image_new_from_file ("cable.png");
    gtk_table_attach(GTK_TABLE(table7), labelMBR, 0,1,0,1, GTK_FILL,GTK_FILL, 0,0);// Pega el label a la tabla
    gtk_table_attach(GTK_TABLE(table7), buttonMBR, 0,1,1,2, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla	
    gtk_table_attach(GTK_TABLE(table7), cable, 1,2,1,2, GTK_FILL, GTK_FILL, 0,0);// Pega el boton a la tabla  	

	gtk_box_pack_start(GTK_BOX(vbox0),table0,0,0,0); // Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() 
	gtk_box_pack_start(GTK_BOX(vbox0),table2,0,0,0); // Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() 
	gtk_box_pack_start(GTK_BOX(vbox0),table1,0,0,0); // Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() 
	gtk_box_pack_start(GTK_BOX(vbox0),table6,0,0,0); // Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() 
	gtk_box_pack_start(GTK_BOX(vbox0),table7,0,0,0); // Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() 
	gtk_box_pack_start(GTK_BOX(vbox1),buttonBUS,1,1,0); // Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() 
	gtk_box_pack_start(GTK_BOX(vbox2),table3,0,0,0); // Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() 
	gtk_box_pack_start(GTK_BOX(vbox2),table4,0,0,0); // Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() 
	gtk_box_pack_start(GTK_BOX(vbox2),table5,0,0,0); // Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() 

	gtk_box_pack_start(GTK_BOX(hbox1),vbox0,0,0,0); // Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() 
	gtk_box_pack_start(GTK_BOX(hbox1),vbox1,0,0,0); // Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() 
	gtk_box_pack_start(GTK_BOX(hbox1),vbox2,0,0,0); // Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() 

    //button = gtk_button_new_with_mnemonic("B_utton");
	//label = gtk_label_new("Hello World");

    //gtk_table2_attach(GTK_table2(table2), label, 0,1,1,2, GTK_FILL, GTK_FILL, 0,0);
    //gtk_table2_attach(GTK_table2(table2), button, 1,2,1,2, GTK_FILL, GTK_FILL, 0,0);
    gtk_container_add(GTK_CONTAINER(window), hbox1);
	//g_signal_connect(button,"clicked",G_CALLBACK(button_clicked),label);

	//gtk_label_set_text(GTK_LABEL(label),"World Hello");
	
	//gtk_container_add(GTK_CONTAINER(window),hbox);
	//gtk_container_add(GTK_CONTAINER(window),label);

	gtk_widget_set_size_request(window,1200,600);// Tamaño de la ventana: x, y
	gtk_window_set_title(GTK_WINDOW(window),"Simulador Von Neumann");// Nombre de la ventana
	gtk_widget_show_all(window);// Para mostrar la ventana y sus componentes (window tiene los componentes)
	gtk_main();	// Ciclo infinito para correr la interfaz
	//free(image);
	return 0;
}
