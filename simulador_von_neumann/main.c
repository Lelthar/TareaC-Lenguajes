
#include <stdio.h>
#include <stdlib.h>

#include "arquitectura_cpu.h"

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

void setCeldaMemoriaInstruccion(int,char*,int,int);
void setCeldaMemoriaNumero(int,int);

void setProgramCounter(int);
int getProgramCounter(void);

void setInstruccionRegister(int,int,int);

/*void setUnidadControl(char*,int,int);*/
void setBusDatos(int);
int getBusDatos(void);

void setALU(int,int,int);

void escribirArchivoEstructura(void);
void leerArchivoEstructura(void);
char* leerMicroInstruccion(int,char*);
void obtenerSegundoOperando(char *);

void operacionALU(void);

void EscribirText(char*,char*);

int main(){

	/*setParteAltaAX(1);*/
	/*setParteBajaAX(255);*/
	/*setProgramCounter(256);*/
	/*printf("%d\n",getProgramCounter());*/
	/*char palabra[3] = {"mov"};
	char *puntero = &palabra[0];
	setUnidadControl(puntero,1,2);*/
	/*printf("El registro AX tiene: %d y la parte alta tiene: %d La parte baja tiene: %d\n", getRegistroAx(),getParteAltaAX(),getParteBajaAX());*/
 	/*printPuntero(puntero,16);*/
	/*escribirArchivoEstructura();*/
	char nombre[] = {"prueba.txt"};
	char *puntero = &nombre[0];
	//char texto[] = {"puerta.txt"};
	//char *punteroTexto = &nombre[0];
	//printf("Se creó\n");
	int posicion = 1;
	char *puntero2;
	puntero = leerMicroInstruccion(posicion,puntero);
	printf("%s", puntero);
	//obtenerSegundoOperando(puntero);
	//setALU(9,60,2);
	//operacionALU();
	//printf("El b3 tiene: %d y el b4 tiene: %d\n", arquitectura.aritmetic_logic_unit.b3,arquitectura.aritmetic_logic_unit.b4);
	/*EscribirText(puntero,punteroTexto);*/
	//printf("%s\n",puntero);
	/*leerArchivoEstructura();*/
	return 0;
}

int potencia(base,exponente){
	int resultado = 1;
	while(exponente != 0){
		resultado = resultado * base;
		exponente--;
	}
	return resultado;
}

void printPuntero(int *puntero,int largo){
	int i;
	for(i = 0; i < largo; i++){
		printf("%d", *puntero);
		puntero = puntero + 1;
	}
	printf("\n");
	
}

void iniciarlizadorMemoria(){
	int i;
	for(i = 0; i < 256; i++){
		arquitectura.memoria[i].numero = 0;
		arquitectura.memoria[i].dato_extra = 0;
		arquitectura.memoria[i].numero_instruccion = 0;
		arquitectura.memoria[i].esInstruccion = 0;
		arquitectura.memoria[i].fuente_operando = 0;
		arquitectura.memoria[i].destino_operando = 0;
	}
	
}

void inicializadorArquitecturaProcesador(){
	/*Banderas*/
	arquitectura.flags.carry_flag = 0;
	arquitectura.flags.signal_flag = 0;
	arquitectura.flags.zero_flag = 0;
	arquitectura.flags.interruption_flag = 0;
	
	/*memoria*/
	iniciarlizadorMemoria();

	/*program_counter*/
	arquitectura.program_counter.numero_memoria = 0;


	/*unidad_de_control*/
	arquitectura.unidad_de_control.operacion = 0;
	arquitectura.unidad_de_control.operando1 = 0;
	arquitectura.unidad_de_control.operando2 = 0;

	/*bus_de_datos*/
	arquitectura.bus_de_datos.entrada = 0;

	/*aritmetic_logic_unit*/
	arquitectura.aritmetic_logic_unit.operacion = 0;
	arquitectura.aritmetic_logic_unit.b1 = 0;
	arquitectura.aritmetic_logic_unit.b2 = 0;
	arquitectura.aritmetic_logic_unit.b3 = 0;
	arquitectura.aritmetic_logic_unit.b4 = 0;

	/*registro_de_trabajo*/
	arquitectura.registro_de_trabajo.AX.valor = 0;
	arquitectura.registro_de_trabajo.BX.valor = 0;
	arquitectura.registro_de_trabajo.CX.valor = 0;
	arquitectura.registro_de_trabajo.DX.valor = 0;

}

int *convertirDecimal2Binario(int numero,int *puntero,int largo){
	
	int i;
	for(i = 0; i < largo; i++){
		*puntero = (numero%2);
		numero = numero / 2;
		puntero = puntero-1;
	}
	return puntero+1;

}

int convertirBinario2Decimal(int *puntero,int largo){
	int resultado = 0;
	int i;
	while(largo != 0){
		resultado += (*puntero * potencia(2,largo-1));
		puntero += 1;
		largo -= 1;
	}
	return resultado;
}

/*
 *Sirve para asignarle un valor al registro AX
 */
void setRegistroAx(numero){
	arquitectura.registro_de_trabajo.AX.valor = numero;
}

/*
 *Sirve para asignarle un valor al registro BX
 */
void setRegistroBx(numero){
	arquitectura.registro_de_trabajo.BX.valor = numero;
}

/*
 *Sirve para asignarle un valor al registro CX
 */
void setRegistroCx(numero){
	arquitectura.registro_de_trabajo.CX.valor = numero;
}

/*
 *Sirve para asignarle un valor al registro DX
 */
void setRegistroDx(numero){
	arquitectura.registro_de_trabajo.DX.valor = numero;
}

void setParteAltaAX(numero){
	if(numero < 256){
		int resultado;
		int numeroRegistro[16];
		int numeroParteAlta[8];
		int *punteroRegistro = &numeroRegistro[15];
		int *punteroParteAlta = &numeroParteAlta[7];
		punteroRegistro = convertirDecimal2Binario(arquitectura.registro_de_trabajo.AX.valor,punteroRegistro,16);
		punteroParteAlta = convertirDecimal2Binario(numero,punteroParteAlta,8);
		int i;
		for(i = 0; i < 8; i++){
			*punteroRegistro = *punteroParteAlta;
			punteroRegistro +=1;
			punteroParteAlta +=1;
		}
		punteroRegistro -= 8;
		/*printPuntero(punteroRegistro,16);*/
		resultado = convertirBinario2Decimal(punteroRegistro,16);
		arquitectura.registro_de_trabajo.AX.valor = resultado;

	}else{
		printf("ERROR: El tamaño del numero, excede los 8 bits\n");
	}
	
}

void setParteBajaAX(numero){
	if(numero < 256){
		int resultado;
		int numeroRegistro[16];
		int numeroParteBaja[8];
		int *punteroRegistro = &numeroRegistro[15];
		int *punteroParteBaja = &numeroParteBaja[7];
		punteroRegistro = convertirDecimal2Binario(arquitectura.registro_de_trabajo.AX.valor,punteroRegistro,16);
		punteroParteBaja = convertirDecimal2Binario(numero,punteroParteBaja,8);
		int i;
		punteroRegistro += 8;
		for(i = 0; i < 8; i++){
			*punteroRegistro = *punteroParteBaja;
			punteroRegistro +=1;
			punteroParteBaja +=1;
		}
		punteroRegistro -= 16;
		/*printPuntero(punteroRegistro,16);*/
		resultado = convertirBinario2Decimal(punteroRegistro,16);
		arquitectura.registro_de_trabajo.AX.valor = resultado;

	}else{
		printf("ERROR: El tamaño del numero, excede los 8 bits\n");
	}
	
}

void setParteAltaBX(numero){
	if(numero < 256){
		int resultado;
		int numeroRegistro[16];
		int numeroParteAlta[8];
		int *punteroRegistro = &numeroRegistro[15];
		int *punteroParteAlta = &numeroParteAlta[7];
		punteroRegistro = convertirDecimal2Binario(arquitectura.registro_de_trabajo.BX.valor,punteroRegistro,16);
		punteroParteAlta = convertirDecimal2Binario(numero,punteroParteAlta,8);
		int i;
		for(i = 0; i < 8; i++){
			*punteroRegistro = *punteroParteAlta;
			punteroRegistro +=1;
			punteroParteAlta +=1;
		}
		punteroRegistro -= 8;
		resultado = convertirBinario2Decimal(punteroRegistro,16);
		arquitectura.registro_de_trabajo.BX.valor = resultado;

	}else{
		printf("ERROR: El tamaño del numero, excede los 8 bits\n");
	}
	
}

void setParteBajaBX(numero){
	if(numero < 256){
		int resultado;
		int numeroRegistro[16];
		int numeroParteBaja[8];
		int *punteroRegistro = &numeroRegistro[15];
		int *punteroParteBaja = &numeroParteBaja[7];
		punteroRegistro = convertirDecimal2Binario(arquitectura.registro_de_trabajo.BX.valor,punteroRegistro,16);
		punteroParteBaja = convertirDecimal2Binario(numero,punteroParteBaja,8);
		int i;
		punteroRegistro += 8;
		for(i = 0; i < 8; i++){
			*punteroRegistro = *punteroParteBaja;
			punteroRegistro +=1;
			punteroParteBaja +=1;
		}
		punteroRegistro -= 16;
		resultado = convertirBinario2Decimal(punteroRegistro,16);
		arquitectura.registro_de_trabajo.BX.valor = resultado;

	}else{
		printf("ERROR: El tamaño del numero, excede los 8 bits\n");
	}
	
}

void setParteAltaCX(numero){
	if(numero < 256){
		int resultado;
		int numeroRegistro[16];
		int numeroParteAlta[8];
		int *punteroRegistro = &numeroRegistro[15];
		int *punteroParteAlta = &numeroParteAlta[7];
		punteroRegistro = convertirDecimal2Binario(arquitectura.registro_de_trabajo.CX.valor,punteroRegistro,16);
		punteroParteAlta = convertirDecimal2Binario(numero,punteroParteAlta,8);
		int i;
		for(i = 0; i < 8; i++){
			*punteroRegistro = *punteroParteAlta;
			punteroRegistro +=1;
			punteroParteAlta +=1;
		}
		punteroRegistro -= 8;
		resultado = convertirBinario2Decimal(punteroRegistro,16);
		arquitectura.registro_de_trabajo.CX.valor = resultado;

	}else{
		printf("ERROR: El tamaño del numero, excede los 8 bits\n");
	}
	
}

void setParteBajaCX(numero){
	if(numero < 256){
		int resultado;
		int numeroRegistro[16];
		int numeroParteBaja[8];
		int *punteroRegistro = &numeroRegistro[15];
		int *punteroParteBaja = &numeroParteBaja[7];
		punteroRegistro = convertirDecimal2Binario(arquitectura.registro_de_trabajo.CX.valor,punteroRegistro,16);
		punteroParteBaja = convertirDecimal2Binario(numero,punteroParteBaja,8);
		int i;
		punteroRegistro += 8;
		for(i = 0; i < 8; i++){
			*punteroRegistro = *punteroParteBaja;
			punteroRegistro +=1;
			punteroParteBaja +=1;
		}
		punteroRegistro -= 16;
		resultado = convertirBinario2Decimal(punteroRegistro,16);
		arquitectura.registro_de_trabajo.CX.valor = resultado;

	}else{
		printf("ERROR: El tamaño del numero, excede los 8 bits\n");
	}
	
}

void setParteAltaDX(numero){
	if(numero < 256){
		int resultado;
		int numeroRegistro[16];
		int numeroParteAlta[8];
		int *punteroRegistro = &numeroRegistro[15];
		int *punteroParteAlta = &numeroParteAlta[7];
		punteroRegistro = convertirDecimal2Binario(arquitectura.registro_de_trabajo.DX.valor,punteroRegistro,16);
		punteroParteAlta = convertirDecimal2Binario(numero,punteroParteAlta,8);
		int i;
		for(i = 0; i < 8; i++){
			*punteroRegistro = *punteroParteAlta;
			punteroRegistro +=1;
			punteroParteAlta +=1;
		}
		punteroRegistro -= 8;
		resultado = convertirBinario2Decimal(punteroRegistro,16);
		arquitectura.registro_de_trabajo.DX.valor = resultado;

	}else{
		printf("ERROR: El tamaño del numero, excede los 8 bits\n");
	}
	
}

void setParteBajaDX(numero){
	if(numero < 256){
		int resultado;
		int numeroRegistro[16];
		int numeroParteBaja[8];
		int *punteroRegistro = &numeroRegistro[15];
		int *punteroParteBaja = &numeroParteBaja[7];
		punteroRegistro = convertirDecimal2Binario(arquitectura.registro_de_trabajo.DX.valor,punteroRegistro,16);
		punteroParteBaja = convertirDecimal2Binario(numero,punteroParteBaja,8);
		int i;
		punteroRegistro += 8;
		for(i = 0; i < 8; i++){
			*punteroRegistro = *punteroParteBaja;
			punteroRegistro +=1;
			punteroParteBaja +=1;
		}
		punteroRegistro -= 16;
		resultado = convertirBinario2Decimal(punteroRegistro,16);
		arquitectura.registro_de_trabajo.DX.valor = resultado;

	}else{
		printf("ERROR: El tamaño del numero, excede los 8 bits\n");
	}
	
}

int getRegistroAx(){
	return arquitectura.registro_de_trabajo.AX.valor;
}

int getRegistroBx(){
	return arquitectura.registro_de_trabajo.BX.valor;
}

int getRegistroCx(){
	return arquitectura.registro_de_trabajo.CX.valor;
}

int getRegistroDx(){
	return arquitectura.registro_de_trabajo.DX.valor;
}

int getParteAltaAX(){
	int resultado;
	int numeroRegistro[16];
	int *punteroRegistro = &numeroRegistro[15];
	punteroRegistro = convertirDecimal2Binario(arquitectura.registro_de_trabajo.AX.valor,punteroRegistro,16);
	resultado = convertirBinario2Decimal(punteroRegistro,8);
	return resultado;
}

int getParteBajaAX(){
	int resultado;
	int numeroRegistro[16];
	int *punteroRegistro = &numeroRegistro[15];
	punteroRegistro = convertirDecimal2Binario(arquitectura.registro_de_trabajo.AX.valor,punteroRegistro,16);
	punteroRegistro += 8;
	resultado = convertirBinario2Decimal(punteroRegistro,8);
	return resultado;
}

int getParteAltaBX(){
	int resultado;
	int numeroRegistro[16];
	int *punteroRegistro = &numeroRegistro[15];
	punteroRegistro = convertirDecimal2Binario(arquitectura.registro_de_trabajo.BX.valor,punteroRegistro,16);
	resultado = convertirBinario2Decimal(punteroRegistro,8);
	return resultado;
}

int getParteBajaBX(){
	int resultado;
	int numeroRegistro[16];
	int *punteroRegistro = &numeroRegistro[15];
	punteroRegistro = convertirDecimal2Binario(arquitectura.registro_de_trabajo.BX.valor,punteroRegistro,16);
	punteroRegistro += 8;
	resultado = convertirBinario2Decimal(punteroRegistro,8);
	return resultado;
}

int getParteAltaCX(){
	int resultado;
	int numeroRegistro[16];
	int *punteroRegistro = &numeroRegistro[15];
	punteroRegistro = convertirDecimal2Binario(arquitectura.registro_de_trabajo.CX.valor,punteroRegistro,16);
	resultado = convertirBinario2Decimal(punteroRegistro,8);
	return resultado;
}

int getParteBajaCX(){
	int resultado;
	int numeroRegistro[16];
	int *punteroRegistro = &numeroRegistro[15];
	punteroRegistro = convertirDecimal2Binario(arquitectura.registro_de_trabajo.CX.valor,punteroRegistro,16);
	punteroRegistro += 8;
	resultado = convertirBinario2Decimal(punteroRegistro,8);
	return resultado;
}

int getParteAltaDX(){
	int resultado;
	int numeroRegistro[16];
	int *punteroRegistro = &numeroRegistro[15];
	punteroRegistro = convertirDecimal2Binario(arquitectura.registro_de_trabajo.DX.valor,punteroRegistro,16);
	resultado = convertirBinario2Decimal(punteroRegistro,8);
	return resultado;
}

int getParteBajaDX(){
	int resultado;
	int numeroRegistro[16];
	int *punteroRegistro = &numeroRegistro[15];
	punteroRegistro = convertirDecimal2Binario(arquitectura.registro_de_trabajo.DX.valor,punteroRegistro,16);
	punteroRegistro += 8;
	resultado = convertirBinario2Decimal(punteroRegistro,8);
	return resultado;
}

void setCarryFlag(int numero){
	if(numero == 0 || numero == 1){
		arquitectura.flags.carry_flag = numero; 
	}else{
		printf("ERROR: La bandera no recibe otro tipo de valor\n");
	}
	
}

void setSignalFlag(int numero){
	if(numero == 0 || numero == 1){
		arquitectura.flags.signal_flag = numero; 
	}else{
		printf("ERROR: La bandera no recibe otro tipo de valor\n");
	}
	
}

void setZeroFlag(int numero){
	if(numero == 0 || numero == 1){
		arquitectura.flags.zero_flag = numero; 
	}else{
		printf("ERROR: La bandera no recibe otro tipo de valor\n");
	}
	
}

void setInterruptionFlag(int numero){
	if(numero == 0 || numero == 1){
		arquitectura.flags.interruption_flag = numero; 
	}else{
		printf("ERROR: La bandera no recibe otro tipo de valor\n");
	}
	
}

int getCarryFlag(){
	return arquitectura.flags.carry_flag;
}
int getSignalFlag(){
	return arquitectura.flags.signal_flag;
}

int getZeroFlag(){
	return arquitectura.flags.zero_flag;
}

int getInterruptionCarryFlag(){
	return arquitectura.flags.interruption_flag;
}

void setCeldaMemoriaInstruccion(int posicion,char *operacion,int operando1,int operando2){
	int i;
	for(i = 0; i < 3; i++){
		arquitectura.memoria[posicion].operacion[i] = *operacion;
		operacion+=1;
	}
	arquitectura.memoria[posicion].fuente_operando = operando1;
	arquitectura.memoria[posicion].destino_operando = operando2;
	arquitectura.memoria[posicion].esInstruccion = 1;
}

void setCeldaMemoriaNumero(posicion,numero){
	arquitectura.memoria[posicion].numero = numero;
	arquitectura.memoria[posicion].esInstruccion = 0;
}

void setProgramCounter(int posicion){
	if(0 <= posicion && posicion < 256){
		arquitectura.program_counter.numero_memoria = posicion;
	}else{
		setProgramCounter(posicion%256);
	}
	
}

int getProgramCounter(){
	return arquitectura.program_counter.numero_memoria;
}

void setInstruccionRegister(int operacion,int operando1,int operando2){

	/*for(i = 0; i < 3; i++){
		arquitectura.instruction_register.operacion[i] = *operacion;
		operacion+=1;
	}*/
	arquitectura.instruction_register.operacion = operacion;
	arquitectura.instruction_register.fuente_operando = operando1;
	arquitectura.instruction_register.destino_operando = operando2;
}

/*void setUnidadControl(char*instruccion, int*listaOperandos,int largo){
	char lista[3];
	int i;
	for(i = 0; i < 3; i++){
		lista[i] = *instruccion;
		instruccion += 1;
	}
	if(strcmp(lista,"sum") == 0){
		
	}else if(strcmp(lista,"mov") == 0){
		
	}
	
}*/

void setBusDatos(entrada){
	arquitectura.bus_de_datos.entrada = entrada;
}

int getBusDatos(){
	return arquitectura.bus_de_datos.entrada;
}

void setALU(operacion,operando1,operando2){
	arquitectura.aritmetic_logic_unit.operacion = operacion;
	arquitectura.aritmetic_logic_unit.b1 = operando1;
	arquitectura.aritmetic_logic_unit.b2 = operando2;
}

void escribirArchivoEstructura(){
	struct Bus_de_datos *object = malloc(sizeof(struct Bus_de_datos));
	object->entrada = 5;

	FILE * file= fopen("output", "wb");
	if (file != NULL) {
		fwrite(object, sizeof(struct Bus_de_datos), 1, file);
		fclose(file);
	}
}

void leerArchivoEstructura(){
	struct Bus_de_datos *object2=malloc(sizeof(struct Bus_de_datos));
    FILE * file= fopen("output", "rb");
    if (file != NULL) {
        fread(object2, sizeof(struct Bus_de_datos), 1, file);
        fclose(file);
    }
    printf("%d\n", object2->entrada);
}

/*void escribirText(){

}*/

char *leerMicroInstruccion(int posicion,char *nombreArchivo){
	/*char const* const fileName = argv[1];*/ /* should check that argc > 1 */
	//char fileName[] = {"prueba.txt"};
    FILE* file = fopen(nombreArchivo, "r"); /* should check the result */
    char line[256];
    char *str = (char *) malloc(sizeof(line));
   //char *puntero; 
    if(file != NULL){
    	while (fgets(line, sizeof(line), file)) {
	        /* note that fgets don't strip the terminating \n, checking its
	           presence would allow to handle lines longer that sizeof(line) */
    		if(posicion == 0){
    			//printf("%s", line);
    			break;
    		}else{
    			posicion-=1;
    		}
	         
	    }
	    int i;
	    for(i = 0; i < 256;i++){
	    	*str = line[i];
	    	str += 1;
	    }
	    str -= 256;

	    /* may check feof here to make a difference between eof and io failure -- network
	       timeout for instance */

	    fclose(file);
	    //printf("%s\n", str);
	    return str;	
    		
    }else{
    	printf("No sirve\n");
    	return str;
    }
    

}

void obtenerSegundoOperando(char *entrada){
	printf("%s\n", entrada);
	char palabra[6];
	int contador = 0;
	int i;
	for(i = 0; i < sizeof(entrada);i++){
		if(i+1 == sizeof(entrada)){
			palabra[contador] = *entrada;
			printf("%d\n", i);
			contador += 1;
			entrada += 1;
		}else if(*entrada == 32){
			palabra[0] = '\0';
			contador = 0;
			entrada += 1;
			//printf("%d %d %d\n", *entrada,palabra[0],i);
		}else{
			palabra[contador] = *entrada;
			contador += 1;
			entrada += 1;
		}
	} 
	//char *puntero = &palabra[0];
	printf("%s\n", palabra);
	/*while(*entrada != 32){
		//printf("%c\n", *entrada);
		entrada += 1;
	}
	printf("Encontré un vacio\n");
	entrada += 1;

	while(*entrada != 32){
		//printf("%d\n", *entrada);
		entrada += 1;
	}
	printf("Encontré un vacio\n");
	entrada += 1;
	while(*entrada != 32){
		printf("%d\n", *entrada);
		entrada += 1;
	}*/
}

void operacionALU(){
	if(arquitectura.aritmetic_logic_unit.operacion == 0){ /*Suma*/
		arquitectura.aritmetic_logic_unit.b3 = arquitectura.aritmetic_logic_unit.b1 + arquitectura.aritmetic_logic_unit.b2;
	}else if(arquitectura.aritmetic_logic_unit.operacion == 1){ /*Resta*/
		arquitectura.aritmetic_logic_unit.b3 = arquitectura.aritmetic_logic_unit.b1 - arquitectura.aritmetic_logic_unit.b2;
	}else if(arquitectura.aritmetic_logic_unit.operacion == 2){ /*Resta*/
		arquitectura.aritmetic_logic_unit.b3 = arquitectura.aritmetic_logic_unit.b1 * arquitectura.aritmetic_logic_unit.b2;
	}else if(arquitectura.aritmetic_logic_unit.operacion == 3){ /*Resta*/
		arquitectura.aritmetic_logic_unit.b3 = arquitectura.aritmetic_logic_unit.b1 / arquitectura.aritmetic_logic_unit.b2;
		arquitectura.aritmetic_logic_unit.b4 = arquitectura.aritmetic_logic_unit.b1 % arquitectura.aritmetic_logic_unit.b2;
	}else if(arquitectura.aritmetic_logic_unit.operacion == 4){ /*Resta*/
		arquitectura.aritmetic_logic_unit.b3 = arquitectura.aritmetic_logic_unit.b1 & arquitectura.aritmetic_logic_unit.b2;
	}else if(arquitectura.aritmetic_logic_unit.operacion == 5){ /*Resta*/
		arquitectura.aritmetic_logic_unit.b3 = arquitectura.aritmetic_logic_unit.b1 | arquitectura.aritmetic_logic_unit.b2;
	}else if(arquitectura.aritmetic_logic_unit.operacion == 6){ /*Resta*/
		arquitectura.aritmetic_logic_unit.b3 = arquitectura.aritmetic_logic_unit.b1 ^ arquitectura.aritmetic_logic_unit.b2;
	}else if(arquitectura.aritmetic_logic_unit.operacion == 7){ /*Resta*/
		arquitectura.aritmetic_logic_unit.b3 = ~ arquitectura.aritmetic_logic_unit.b1;
	}else if(arquitectura.aritmetic_logic_unit.operacion == 8){ /*Resta*/
		arquitectura.aritmetic_logic_unit.b3 = arquitectura.aritmetic_logic_unit.b1 << arquitectura.aritmetic_logic_unit.b2;
	}else if(arquitectura.aritmetic_logic_unit.operacion == 9){ /*Resta*/
		arquitectura.aritmetic_logic_unit.b3 = arquitectura.aritmetic_logic_unit.b1 >> arquitectura.aritmetic_logic_unit.b2;
	}
}

void EscribirText(char *nombreArchivo,char *texto){
	/*char const* const fileName = argv[1];*/ /* should check that argc > 1 */
	//char fileName[] = {"prueba.txt"};
    FILE* file = fopen(nombreArchivo, "a"); /* should check the result */
     
    if(file != NULL){
    	printf("Yo khe se\n");
    	
    	fputs(texto, file);
    	fputs("\n",file);
    	//fputs(texto, file);
    	//fwrite(texto, sizeof(texto),1, file);
	    fclose(file);
    		
    }else{
    	printf("Que está pasando doctor garcia\n");
    }
    
    

}