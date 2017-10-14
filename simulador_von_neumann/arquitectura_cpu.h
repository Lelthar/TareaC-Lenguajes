
struct Registro{
	int valor;
};

struct Flags{
	int carry_flag;
	int signal_flag;
	int zero_flag;
	int interruption_flag;
};

typedef struct {
	
	/*numero de 16 bits*/
	int numero;

	int numero_instruccion;

	int esInstruccion;

	/*instruccion*/
	char operacion[3];//"mul"
	int fuente_operando;//AX
	int destino_operando;//BX
	int dato_extra; // 
}Memoria;

struct Program_counter{
	int numero_memoria;
};

struct Instruction_register{
	int operacion;
	int fuente_operando;
	int destino_operando;
};

struct Unidad_de_control{
	int operacion;
	int operando1;
	int operando2;
};

struct Bus_de_datos{
	int entrada;
};

struct Aritmetic_logic_unit{
	int operacion;
	int b1;
	int b2;
	int b3;
	int b4;
};

struct Registro_de_trabajo{
	struct Registro AX;
	struct Registro BX;
	struct Registro CX;
	struct Registro DX;
};

typedef struct {
	struct Flags flags;
	Memoria  memoria[256];
	struct Program_counter program_counter;
	struct Instruction_register instruction_register;
	struct Unidad_de_control unidad_de_control;
	struct Bus_de_datos bus_de_datos;
	struct Aritmetic_logic_unit aritmetic_logic_unit;
	struct Registro_de_trabajo registro_de_trabajo;
}ArquitecturaCPU;