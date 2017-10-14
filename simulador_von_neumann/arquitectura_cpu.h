
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
	int operacion;
	int fuente_operando;
	int destino_operando;
	int dato_extra; 
}Memoria;

struct Program_counter{
	int numero_memoria;
};

struct Instruction_register{
	int operacion;
	int fuente_operando;
	int destino_operando;
	int dato_extra;
};

struct Unidad_de_control{
	int operacion;
	int operando1;
	int operando2;
};

struct Bus_de_datos{
	/*Este dato es por si le pasan un registro*/
	int numero;

	int operacion;
	int fuente_operando;
	int destino_operando;
	int dato_extra;
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

struct Memory_buffer_register{
	int operacion;
	int fuente_operando;
	int destino_operando;
	int dato_extra;

	int numero;
};

struct Memory_address_register{
	int direccion;
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
	struct Memory_buffer_register MBR;
	struct Memory_address_register MAR;
}ArquitecturaCPU;

ArquitecturaCPU arquitectura;
int potencia(int,int);
void printPuntero(int *,int);
void iniciarlizadorMemoria(void);
void inicializadorArquitecturaProcesador(void);

int *convertirDecimal2Binario(int,int*,int);
int convertirBinario2Decimal(int *,int);

void setRegistroAx(int);
void setRegistroBx(int);
void setRegistroCx(int);
void setRegistroDx(int);

void setParteAltaAX(int);
void setParteBajaAX(int);

void setParteAltaBX(int);
void setParteBajaBX(int);

void setParteAltaCX(int);
void setParteBajaCX(int);

void setParteAltaDX(int);
void setParteBajaDX(int);

int getRegistroAx(void);
int getRegistroBx(void);
int getRegistroCx(void);
int getRegistroDx(void);

int getParteAltaAX(void);
int getParteBajaAX(void);
int getParteAltaBX(void);
int getParteBajaBX(void);
int getParteAltaCX(void);
int getParteBajaCX(void);
int getParteAltaDX(void);
int getParteBajaDX(void);

void setCarryFlag(int);
void setSignalFlag(int);
void setZeroFlag(int);
void setInterruptionFlag(int);

int getCarryFlag(void);
int getSignalFlag(void);
int getZeroFlag(void);
int getInterruptionCarryFlag(void);

void setCeldaMemoriaInstruccion(int,int,int,int,int);
void setCeldaMemoriaNumero(int,int);

void setProgramCounter(int);
int getProgramCounter(void);

void setInstruccionRegister(int,int,int,int);

/*void setUnidadControl(char*,int,int);*/
void setBusDatosAtributo(int);
int getBusDatosAtributo(void);
void setBusDatosInstruccion(int,int,int,int);

void setALU(int,int,int);

void setMBRInstruccion(int,int,int,int);
void setMBRDato(int);

void escribirArchivoEstructura(void);
void leerArchivoEstructura(void);
char* leerMicroInstruccion(int,char*);
int cantidadFilasArchivo(char*);

void operacionALU(void);

int sePuedeInsertar(char*,char*);

void EscribirText(char*,char*);

int tieneDosOperandos(char*);

char *obtenerOperacionN(char*);
char *obtenerOperando1N(char*);
char *obtenerOperando2N(char*);

char *obtenerOperando2D(char*);
char *obtenerOperandoUnidad(char*);

void operacionWriteValor(void);
void operacionWriteInstruccion(void);
void operacionReadValor(void);
void operacionReadInstruccion(void);

void microInstruccionRealizar(char*);

char *obtenerFlag(char*);

void ejecutarMicroPrograma(char*);