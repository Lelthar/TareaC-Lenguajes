
struct Registro{
	int parteBaja;
	int parteAlta;
};

struct Flags{
	char carry_flag;
	char signal_flag;
	char zero_flag;
	char interruption_flag;
};

typedef struct {
	
	//numero de 16 bits
	int numero;

	//instruccion
	char operacion[3];
	char fuente_operando[10];
	char destino_operando[10];
	int dato_extra;
}Memoria;

struct Program_counter{
	int numero_memoria;
};

struct Instruction_register{
	char operacion[3];
	char fuente_operando[10];
	char destino_operando[10];
};

struct Unidad_de_control{
	int operacion;
	int operando1;
	int operando2;
};

struct Bus_de_datos{
	int entrada;
	int salida;
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
}ArquitecturaCPU;