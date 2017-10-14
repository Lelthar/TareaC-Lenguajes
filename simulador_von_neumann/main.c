
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arquitectura_cpu.h"



int main(){


	char nombre[] = {"prueba.txt"};
	char *puntero = &nombre[0];

	char nombre1[] = {"IN"};
	char *puntero1 = &nombre1[0];

	char *puntero3 = obtenerOperandoUnidad(puntero1);
	printf("%s\n",puntero3);
	/*char texto[] = {"puerta.txt"};
	char *punteroTexto = &nombre[0];
	rintf("Se creó\n");*/
	/*EscribirText(puntero,puntero1);*/
	/*int largo = cantidadFilasArchivo(puntero);
	printf("Cantidad filas archivo: %d\n", largo);
	
	char *puntero2;*/
	
	/*if(strcmp(puntero,puntero1) == 0){
		printf("si\n");
	}else{
		printf("no\n");
	}*/

	
	
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
		free(object);
		fclose(file);
	}
}

void leerArchivoEstructura(){
	struct Bus_de_datos *object2=malloc(sizeof(struct Bus_de_datos));
    FILE * file= fopen("output", "rb");
    if (file != NULL) {
        fread(object2, sizeof(struct Bus_de_datos), 1, file);
        free(object2);
        fclose(file);
    }
    printf("%d\n", object2->entrada);
}

/*void escribirText(){

}*/

char *leerMicroInstruccion(int posicion,char *nombreArchivo){
	/*char const* const fileName = argv[1];*/ /* should check that argc > 1 */
	
    FILE* file = fopen(nombreArchivo, "r"); /* should check the result */
    char line[256];
    char *str = (char *) malloc(sizeof(line));
    
    if(file != NULL){
    	while(fgets(line, sizeof(line), file)) {
	 		
    		if(posicion == 0){
    			
    			break;
    		}else{
    			posicion-=1;
    		}
	         
	    }
    	/*while(!feof(file)){
    		if(posicion == 0){
    			fgets(line,sizeof(line),file);
    			break;
    		}else{
    			fgets(line,sizeof(line),file);
    			posicion-=1;
    		}
    	}*/

	    int i;
	    for(i = 0; i < strlen(line);i++){
	    	if(line[i] != 10){
	    	   *str = line[i];
	    		str += 1;
	    	}else{
	    		str += 1;
	    	}
	    	
	    }
	    str -= (strlen(line));
	   

	    fclose(file);
	    free(str);
	  	
	    return str;	
    		
    }else{
    	printf("No sirve\n");
    	return str;
    }
    

}

int cantidadFilasArchivo(char *nombreArchivo){
	/*char const* const fileName = argv[1];*/ /* should check that argc > 1 */
	
    FILE* file = fopen(nombreArchivo, "r"); /* should check the result */
    char line[256];
    int largo = 0;
    
    if(file != NULL){
    	while (fgets(line, sizeof(line), file)) {
	 		largo++;
	    }

	    fclose(file);
	  
	    return largo;	
    		
    }else{
    	printf("No sirve\n");
    	return largo;
    }
    

}



void operacionALU(){
	if(arquitectura.aritmetic_logic_unit.operacion == 0){ /*Suma*/
		arquitectura.aritmetic_logic_unit.b3 = arquitectura.aritmetic_logic_unit.b1 + arquitectura.aritmetic_logic_unit.b2;
	}else if(arquitectura.aritmetic_logic_unit.operacion == 1){ /*Resta*/
		arquitectura.aritmetic_logic_unit.b3 = arquitectura.aritmetic_logic_unit.b1 - arquitectura.aritmetic_logic_unit.b2;
	}else if(arquitectura.aritmetic_logic_unit.operacion == 2){ /*MUL*/
		arquitectura.aritmetic_logic_unit.b3 = arquitectura.aritmetic_logic_unit.b1 * arquitectura.aritmetic_logic_unit.b2;
	}else if(arquitectura.aritmetic_logic_unit.operacion == 3){ /*DIV*/
		arquitectura.aritmetic_logic_unit.b3 = arquitectura.aritmetic_logic_unit.b1 / arquitectura.aritmetic_logic_unit.b2;
		arquitectura.aritmetic_logic_unit.b4 = arquitectura.aritmetic_logic_unit.b1 % arquitectura.aritmetic_logic_unit.b2;
	}else if(arquitectura.aritmetic_logic_unit.operacion == 4){ /*AND*/
		arquitectura.aritmetic_logic_unit.b3 = arquitectura.aritmetic_logic_unit.b1 & arquitectura.aritmetic_logic_unit.b2;
	}else if(arquitectura.aritmetic_logic_unit.operacion == 5){ /*OR*/
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

int sePuedeInsertar(char* nombreArchivoMP,char *nombreArchivoAFOC){
	int largo = cantidadFilasArchivo(nombreArchivoAFOC);
	char *puntero = (char *) malloc(sizeof(nombreArchivoAFOC));;
	int i;

	for(i = 0; i < largo; i++){
		
		puntero = leerMicroInstruccion(i,nombreArchivoAFOC);
		printf("%s\n", puntero);

		if(strcmp(puntero,nombreArchivoMP) == 0){
			
			return 0;
		}
	}
	
	return 1;
}


void EscribirText(char *nombreArchivoAFOC,char *nombreArchivoMP){
	
    FILE* file = fopen(nombreArchivoAFOC, "a"); 
     
    if(file != NULL){
    	if(sePuedeInsertar(nombreArchivoMP,nombreArchivoAFOC) == 1){
    		/*printf("Yo khe se\n");*/
    		fputs(nombreArchivoMP, file);
    		fputs("\n",file);
    	}else{
    		printf("Ya existe\n");
    	}
    	
	    fclose(file);
    		
    }else{
    	/*printf("Que está pasando doctor garcia\n");*/
    }

}

int tieneDosOperandos(char *instruccion){
	char *puntero = (char *) malloc(sizeof(instruccion));
	int contador = 0;
	while(*instruccion != 32){
		*puntero = *instruccion;
		puntero += 1;
		instruccion +=1;
		contador ++;
	}
	puntero -= contador;
	if(strcmp(puntero,"ALU:") == 0 || strcmp(puntero,"MEM:") == 0 || strcmp(puntero,"TEST:") == 0){
		printf("Sirve\n");
		return 0;
	}else{
		printf("No sirve\n");
		return 1;
	}
	
}

/* ALU: operacion se usa obtenerOperacionN  obtenerOperando2D
   reg16 <- BD se usa obtenerOperacionN obtenerOperando1N obtenerOperando2N
   IN se usa obtenerOperandoUnidad
*/
char* obtenerOperacionN(char *instruccion){
	char *puntero = (char *) malloc(sizeof(instruccion));
	int contador = 0;

	while(*instruccion != 32){
		*puntero = *instruccion;
		puntero += 1;
		instruccion +=1;
		contador ++;
	}
	puntero -= contador;

	return puntero;
}

char* obtenerOperando1N(char *instruccion){
	char *puntero = (char *) malloc(sizeof(instruccion));
	int contador = 0;

	while(*instruccion != 32){
		instruccion +=1;
	}

	instruccion+=1;

	while(*instruccion != 32){
		*puntero = *instruccion;
		puntero += 1;
		instruccion +=1;
		contador ++;
	}

	puntero -= contador;

	return puntero;
}

char* obtenerOperando2N(char *instruccion){
	char *puntero = (char *) malloc(sizeof(instruccion));
	int contador = 0;
	int espacios = 0;
	int largo = strlen(instruccion);
	/*printf("%d\n", strlen(instruccion)); *//*"reg16 <- BD"*/
	int i;
	for(i = 0; i < largo; i++){
		if(espacios == 2){
			*puntero = *instruccion;
			puntero += 1;
			instruccion +=1;
			contador ++;
		}else if(*instruccion == 32){
			instruccion += 1;
			espacios += 1;
		}else{
			instruccion += 1;
		}
	}
	
	puntero -= contador;
	return puntero;
}

char* obtenerOperando2D(char *instruccion){
	char *puntero = (char *) malloc(sizeof(instruccion));
	int contador = 0;
	int espacios = 0;
	int largo = strlen(instruccion);
	/*printf("%d\n", strlen(instruccion)); *//*"reg16 <- BD"*/
	int i;
	for(i = 0; i < largo; i++){
		if(espacios == 1){
			*puntero = *instruccion;
			puntero += 1;
			instruccion +=1;
			contador ++;
		}else if(*instruccion == 32){
			instruccion += 1;
			espacios += 1;
		}else{
			instruccion += 1;
		}
	}
	
	puntero -= contador;
	return puntero;
}

char* obtenerOperandoUnidad(char *instruccion){
	char *puntero = (char *) malloc(sizeof(instruccion));
	int contador = 0;
	int largo = strlen(instruccion);
	/*printf("%d\n", strlen(instruccion)); *//*"reg16 <- BD"*/
	int i;
	for(i = 0; i < largo; i++){
		*puntero = *instruccion;
		puntero += 1;
		instruccion +=1;
		contador ++;

	}
	
	puntero -= contador;

	return puntero;
}

void operacionWrite(){
	arquitectura.memoria[arquitectura.MAR.direccion].operacion = arquitectura.MBR.operacion;
	arquitectura.memoria[arquitectura.MAR.direccion].fuente_operando = arquitectura.MBR.fuente_operando;
	arquitectura.memoria[arquitectura.MAR.direccion].destino_operando = arquitectura.MBR.destino_operando;
	arquitectura.memoria[arquitectura.MAR.direccion].dato_extra = arquitectura.MBR.dato_extra;
}

void operacionRead(){
	arquitectura.MBR.operacion = arquitectura.memoria[arquitectura.MAR.direccion].operacion;
	arquitectura.MBR.fuente_operando = arquitectura.memoria[arquitectura.MAR.direccion].fuente_operando;
	arquitectura.MBR.destino_operando = arquitectura.memoria[arquitectura.MAR.direccion].destino_operando;
	arquitectura.MBR.dato_extra = arquitectura.memoria[arquitectura.MAR.direccion].dato_extra;
}