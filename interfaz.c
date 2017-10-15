#include <gtk/gtk.h>	/* Incluye libreria gtk y libreria g */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arquitectura_cpu.h"

void EscribirMicroPrograma(char *nombreMicroP,char *microInstruccion){
	
    FILE* file = fopen(nombreMicroP, "a"); 
     
    if(file != NULL){
    	
    	/*printf("Yo khe se\n");*/
    	fputs(microInstruccion, file);
    	fputs("\n",file);
    	
    	
	    fclose(file);
    		
    }else{
    	/*printf("Que está pasando doctor garcia\n");*/
    }

}
/*Soy Blanco*/
void construirMicroPrograma(char *nombreArchivo,char *palabra){
	char *puntero1 = (char *) malloc(sizeof(palabra));
	int largo = strlen(palabra);
	int i;
	int contador = 0;

	for(i = 0; i < largo; i++){
		if(*palabra == 10){
			puntero1 -= contador;
			EscribirMicroPrograma(nombreArchivo,puntero1);
			
			memset(puntero1, 0, sizeof(puntero1));
			palabra += 1;
			contador = 0;
			
		}else{
			/*printf("%s\n", palabra)*/;
			*puntero1 = *palabra;
			printf("%s\n", puntero1);
			puntero1 += 1;
			palabra += 1;
			contador++;
		}
	}
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
	arquitectura.bus_de_datos.numero = 0;

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

void setCeldaMemoriaInstruccion(int posicion,int operacion,int operando1,int operando2,int datoExtra){
	arquitectura.memoria[posicion].operacion = operacion;
	arquitectura.memoria[posicion].fuente_operando = operando1;
	arquitectura.memoria[posicion].destino_operando = operando2;
	arquitectura.memoria[posicion].dato_extra = datoExtra;
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

void setInstruccionRegister(int operacion,int operando1,int operando2,int datoExtra){

	arquitectura.instruction_register.operacion = operacion;
	arquitectura.instruction_register.fuente_operando = operando1;
	arquitectura.instruction_register.destino_operando = operando2;
	arquitectura.instruction_register.dato_extra = datoExtra;
}


void setBusDatosAtributo(entrada){
	arquitectura.bus_de_datos.numero = entrada;
}

void setBusDatosInstruccion(operacion,operando1,operando2,datoExtra){
	arquitectura.bus_de_datos.operacion = operacion;
	arquitectura.bus_de_datos.fuente_operando = operando1;
	arquitectura.bus_de_datos.destino_operando = operando2;
	arquitectura.bus_de_datos.dato_extra = datoExtra;
}

int getBusDatosAtributo(){
	return arquitectura.bus_de_datos.numero;
}



void setALU(operacion,operando1,operando2){
	arquitectura.aritmetic_logic_unit.operacion = operacion;
	arquitectura.aritmetic_logic_unit.b1 = operando1;
	arquitectura.aritmetic_logic_unit.b2 = operando2;
}

void setMBRInstruccion(operacion,operando1,operando2,datoExtra){
	arquitectura.MBR.operacion = operacion;
	arquitectura.MBR.fuente_operando = operando1;
	arquitectura.MBR.destino_operando = operando2;
	arquitectura.MBR.dato_extra = datoExtra;
}

void setMBRDato(numero){
	arquitectura.MBR.numero = numero;
}

void escribirArchivoEstructura(){
	ArquitecturaCPU *object = malloc(sizeof(ArquitecturaCPU));
	object = &arquitectura;

	FILE * file= fopen("AFOC1estructura", "wb");
	if (file != NULL) {
		fwrite(object, sizeof(ArquitecturaCPU), 1, file);
		fclose(file);
	}
}

void leerArchivoEstructura(){
	ArquitecturaCPU *object2 = malloc(sizeof(ArquitecturaCPU));
	object2 = &arquitectura;
    FILE * file= fopen("AFOC1estructura", "rb");
    if (file != NULL) {
        fread(object2, sizeof(ArquitecturaCPU), 1, file);
        fclose(file);
    }
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
		int resultado = arquitectura.aritmetic_logic_unit.b1 + arquitectura.aritmetic_logic_unit.b2;
		arquitectura.aritmetic_logic_unit.b3 = resultado;
		if(resultado == 0){
			arquitectura.flags.zero_flag = 1;
		}else if(resultado > 65535){
			arquitectura.flags.carry_flag = 1;
		}else if(resultado < 0){
			arquitectura.flags.signal_flag = 1;
		}
	}else if(arquitectura.aritmetic_logic_unit.operacion == 1){ /*Resta*/
		int resultado = arquitectura.aritmetic_logic_unit.b1 - arquitectura.aritmetic_logic_unit.b2;
		arquitectura.aritmetic_logic_unit.b3 = resultado;
		if(resultado == 0){
			arquitectura.flags.zero_flag = 1;
		}else if(resultado > 65535){
			arquitectura.flags.carry_flag = 1;
		}else if(resultado < 0){
			arquitectura.flags.signal_flag = 1;
		}
	}else if(arquitectura.aritmetic_logic_unit.operacion == 2){ /*MUL*/
		int resultado = arquitectura.aritmetic_logic_unit.b1 * arquitectura.aritmetic_logic_unit.b2;
		arquitectura.aritmetic_logic_unit.b3 = resultado;
		if(resultado == 0){
			arquitectura.flags.zero_flag = 1;
		}else if(resultado > 65535){
			arquitectura.flags.carry_flag = 1;
		}else if(resultado < 0){
			arquitectura.flags.signal_flag = 1;
		}
	}else if(arquitectura.aritmetic_logic_unit.operacion == 3){ /*DIV*/
		int resultado = arquitectura.aritmetic_logic_unit.b1 / arquitectura.aritmetic_logic_unit.b2;
		arquitectura.aritmetic_logic_unit.b3 = resultado;
		arquitectura.aritmetic_logic_unit.b4 = arquitectura.aritmetic_logic_unit.b1 % arquitectura.aritmetic_logic_unit.b2;
		if(resultado == 0){
			arquitectura.flags.zero_flag = 1;
		}else if(resultado > 65535){
			arquitectura.flags.carry_flag = 1;
		}else if(resultado < 0){
			arquitectura.flags.signal_flag = 1;
		}
	}else if(arquitectura.aritmetic_logic_unit.operacion == 4){ /*AND*/
		int resultado = arquitectura.aritmetic_logic_unit.b1 & arquitectura.aritmetic_logic_unit.b2;
		arquitectura.aritmetic_logic_unit.b3 = resultado;
		if(resultado == 0){
			arquitectura.flags.zero_flag = 1;
		}else if(resultado > 65535){
			arquitectura.flags.carry_flag = 1;
		}else if(resultado < 0){
			arquitectura.flags.signal_flag = 1;
		}
	}else if(arquitectura.aritmetic_logic_unit.operacion == 5){ /*OR*/
		int resultado = arquitectura.aritmetic_logic_unit.b1 | arquitectura.aritmetic_logic_unit.b2;
		arquitectura.aritmetic_logic_unit.b3 = resultado;
		if(resultado == 0){
			arquitectura.flags.zero_flag = 1;
		}else if(resultado > 65535){
			arquitectura.flags.carry_flag = 1;
		}else if(resultado < 0){
			arquitectura.flags.signal_flag = 1;
		}
	}else if(arquitectura.aritmetic_logic_unit.operacion == 6){ /*xor*/
		int resultado = arquitectura.aritmetic_logic_unit.b1 ^ arquitectura.aritmetic_logic_unit.b2;
		arquitectura.aritmetic_logic_unit.b3 = resultado;
		if(resultado == 0){
			arquitectura.flags.zero_flag = 1;
		}else if(resultado > 65535){
			arquitectura.flags.carry_flag = 1;
		}else if(resultado < 0){
			arquitectura.flags.signal_flag = 1;
		}
	}else if(arquitectura.aritmetic_logic_unit.operacion == 7){ /*NOT*/
		int resultado = ~ arquitectura.aritmetic_logic_unit.b1;
		arquitectura.aritmetic_logic_unit.b3 = resultado;
		if(resultado == 0){
			arquitectura.flags.zero_flag = 1;
		}else if(resultado > 65535){
			arquitectura.flags.carry_flag = 1;
		}else if(resultado < 0){
			arquitectura.flags.signal_flag = 1;
		}
	}else if(arquitectura.aritmetic_logic_unit.operacion == 8){ /*SHR*/
		int resultado = arquitectura.aritmetic_logic_unit.b1 << arquitectura.aritmetic_logic_unit.b2;
		arquitectura.aritmetic_logic_unit.b3 = resultado;
		if(resultado == 0){
			arquitectura.flags.zero_flag = 1;
		}else if(resultado > 65535){
			arquitectura.flags.carry_flag = 1;
		}else if(resultado < 0){
			arquitectura.flags.signal_flag = 1;
		}
	}else if(arquitectura.aritmetic_logic_unit.operacion == 9){ /*SHL*/
		int resultado = arquitectura.aritmetic_logic_unit.b1 >> arquitectura.aritmetic_logic_unit.b2;
		arquitectura.aritmetic_logic_unit.b3 = resultado;
		if(resultado == 0){
			arquitectura.flags.zero_flag = 1;
		}else if(resultado > 65535){
			arquitectura.flags.carry_flag = 1;
		}else if(resultado < 0){
			arquitectura.flags.signal_flag = 1;
		}
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

void operacionWriteValor(){
	/*arquitectura.memoria[arquitectura.MAR.direccion].operacion = arquitectura.MBR.operacion;
	arquitectura.memoria[arquitectura.MAR.direccion].fuente_operando = arquitectura.MBR.fuente_operando;
	arquitectura.memoria[arquitectura.MAR.direccion].destino_operando = arquitectura.MBR.destino_operando;
	arquitectura.memoria[arquitectura.MAR.direccion].dato_extra = arquitectura.MBR.dato_extra;*/
	arquitectura.memoria[arquitectura.MAR.direccion].numero = arquitectura.MBR.numero;
}

void operacionWriteInstruccion(){
	arquitectura.memoria[arquitectura.MAR.direccion].operacion = arquitectura.MBR.operacion;
	arquitectura.memoria[arquitectura.MAR.direccion].fuente_operando = arquitectura.MBR.fuente_operando;
	arquitectura.memoria[arquitectura.MAR.direccion].destino_operando = arquitectura.MBR.destino_operando;
	arquitectura.memoria[arquitectura.MAR.direccion].dato_extra = arquitectura.MBR.dato_extra;

}

void operacionReadValor(){
	/*arquitectura.MBR.operacion = arquitectura.memoria[arquitectura.MAR.direccion].operacion;
	arquitectura.MBR.fuente_operando = arquitectura.memoria[arquitectura.MAR.direccion].fuente_operando;
	arquitectura.MBR.destino_operando = arquitectura.memoria[arquitectura.MAR.direccion].destino_operando;
	arquitectura.MBR.dato_extra = arquitectura.memoria[arquitectura.MAR.direccion].dato_extra;*/
	arquitectura.MBR.numero = arquitectura.memoria[arquitectura.MAR.direccion].numero;
}

void operacionReadInstruccion(){
	arquitectura.MBR.operacion = arquitectura.memoria[arquitectura.MAR.direccion].operacion;
	arquitectura.MBR.fuente_operando = arquitectura.memoria[arquitectura.MAR.direccion].fuente_operando;
	arquitectura.MBR.destino_operando = arquitectura.memoria[arquitectura.MAR.direccion].destino_operando;
	arquitectura.MBR.dato_extra = arquitectura.memoria[arquitectura.MAR.direccion].dato_extra;
}

void microInstruccionRealizar(char *instruccion){
	if(strcmp(instruccion,"BD<-DE") == 0){
		setBusDatosAtributo(arquitectura.MBR.dato_extra);
	}else if(strcmp(instruccion,"BD<-PC") == 0){
		setBusDatosAtributo(getProgramCounter());
	}else if(strcmp(instruccion,"PC<-BD") == 0){
		setProgramCounter(getBusDatosAtributo());
	}else if(strcmp(instruccion,"BD<-IR") == 0){
		setBusDatosInstruccion(arquitectura.instruction_register.operacion,arquitectura.instruction_register.fuente_operando,arquitectura.instruction_register.destino_operando,arquitectura.instruction_register.dato_extra);
	}else if(strcmp(instruccion,"IR<-BD") == 0){
		setInstruccionRegister(arquitectura.bus_de_datos.operacion,arquitectura.bus_de_datos.fuente_operando,arquitectura.bus_de_datos.destino_operando,arquitectura.bus_de_datos.dato_extra);
	}else if(strcmp(instruccion,"BD<-MAR") == 0){
		setBusDatosAtributo(arquitectura.MAR.direccion);
	}else if(strcmp(instruccion,"MAR<-BD") == 0){
		arquitectura.MAR.direccion = getBusDatosAtributo();
	}else if(strcmp(instruccion,"BD<-MBR") == 0){
		setBusDatosAtributo(arquitectura.MBR.numero);
		setBusDatosInstruccion(arquitectura.MBR.operacion,arquitectura.MBR.fuente_operando,arquitectura.MBR.destino_operando,arquitectura.MBR.dato_extra);
	}else if(strcmp(instruccion,"MBR<-BD") == 0){
		setMBRInstruccion(arquitectura.bus_de_datos.operacion,arquitectura.bus_de_datos.fuente_operando,arquitectura.bus_de_datos.destino_operando,arquitectura.bus_de_datos.dato_extra);
	}else if(strcmp(instruccion,"AX<-BD") == 0){
		setRegistroAx(getBusDatosAtributo());
	}else if(strcmp(instruccion,"BX<-BD") == 0){
		setRegistroBx(getBusDatosAtributo());
	}else if(strcmp(instruccion,"CX<-BD") == 0){
		setRegistroCx(getBusDatosAtributo());
	}else if(strcmp(instruccion,"DX<-BD") == 0){
		setRegistroDx(getBusDatosAtributo());
	}else if(strcmp(instruccion,"BD<-AX") == 0){
		setBusDatosAtributo(getRegistroAx());
	}else if(strcmp(instruccion,"BD<-BX") == 0){
		setBusDatosAtributo(getRegistroBx());
	}else if(strcmp(instruccion,"BD<-CX") == 0){
		setBusDatosAtributo(getRegistroCx());
	}else if(strcmp(instruccion,"BD<-DX") == 0){
		setBusDatosAtributo(getRegistroDx());
	}else if(strcmp(instruccion,"AH<-BD") == 0){
		setParteAltaAX(getBusDatosAtributo());
	}else if(strcmp(instruccion,"AL<-BD") == 0){
		setParteBajaAX(getBusDatosAtributo());
	}else if(strcmp(instruccion,"BH<-BD") == 0){
		setParteAltaBX(getBusDatosAtributo());
	}else if(strcmp(instruccion,"BL<-BD") == 0){
		setParteBajaBX(getBusDatosAtributo());
	}else if(strcmp(instruccion,"CH<-BD") == 0){
		setParteAltaCX(getBusDatosAtributo());
	}else if(strcmp(instruccion,"CL<-BD") == 0){
		setParteBajaCX(getBusDatosAtributo());
	}else if(strcmp(instruccion,"DH<-BD") == 0){
		setParteAltaDX(getBusDatosAtributo());
	}else if(strcmp(instruccion,"DL<-BD") == 0){
		setParteBajaDX(getBusDatosAtributo());
	}else if(strcmp(instruccion,"BD<-AH") == 0){
		setBusDatosAtributo(getParteAltaAX());
	}else if(strcmp(instruccion,"BD<-AL") == 0){
		setBusDatosAtributo(getParteBajaAX());
	}else if(strcmp(instruccion,"BD<-BH") == 0){
		setBusDatosAtributo(getParteAltaBX());
	}else if(strcmp(instruccion,"BD<-BL") == 0){
		setBusDatosAtributo(getParteBajaBX());
	}else if(strcmp(instruccion,"BD<-CH") == 0){
		setBusDatosAtributo(getParteAltaCX());
	}else if(strcmp(instruccion,"BD<-CL") == 0){
		setBusDatosAtributo(getParteBajaCX());
	}else if(strcmp(instruccion,"BD<-DH") == 0){
		setBusDatosAtributo(getParteAltaDX());
	}else if(strcmp(instruccion,"BD<-DL") == 0){
		setBusDatosAtributo(getParteBajaDX());
	}else if(strcmp(instruccion,"B1<-BD") == 0){
		arquitectura.aritmetic_logic_unit.b1 = arquitectura.bus_de_datos.numero;
	}else if(strcmp(instruccion,"B2<-BD") == 0){
		arquitectura.aritmetic_logic_unit.b2 = arquitectura.bus_de_datos.numero;
	}else if(strcmp(instruccion,"BD<-B3") == 0){
		arquitectura.bus_de_datos.numero = arquitectura.aritmetic_logic_unit.b3;
	}else if(strcmp(instruccion,"BD<-B4") == 0){
		arquitectura.bus_de_datos.numero = arquitectura.aritmetic_logic_unit.b4;
	}else if(strcmp(instruccion,"ALU:add") == 0){
		arquitectura.aritmetic_logic_unit.operacion = 0;
		operacionALU();
	}else if(strcmp(instruccion,"ALU:sub") == 0){
		arquitectura.aritmetic_logic_unit.operacion = 1;
		operacionALU();
	}else if(strcmp(instruccion,"ALU:mul") == 0){
		arquitectura.aritmetic_logic_unit.operacion = 2;
		operacionALU();
	}else if(strcmp(instruccion,"ALU:div") == 0){
		arquitectura.aritmetic_logic_unit.operacion = 3;
		operacionALU();
	}else if(strcmp(instruccion,"ALU:and") == 0){
		arquitectura.aritmetic_logic_unit.operacion = 4;
		operacionALU();
	}else if(strcmp(instruccion,"ALU:or") == 0){
		arquitectura.aritmetic_logic_unit.operacion = 5;
		operacionALU();
	}else if(strcmp(instruccion,"ALU:xor") == 0){
		arquitectura.aritmetic_logic_unit.operacion = 6;
		operacionALU();
	}else if(strcmp(instruccion,"ALU:not") == 0){ 
		arquitectura.aritmetic_logic_unit.operacion = 7;
		operacionALU();
	}else if(strcmp(instruccion,"ALU:shr") == 0){
		arquitectura.aritmetic_logic_unit.operacion = 8;
		operacionALU();
	}else if(strcmp(instruccion,"ALU:shl") == 0){
		arquitectura.aritmetic_logic_unit.operacion = 9;
		operacionALU();
	}else if(strcmp(instruccion,"TEST:") == 0){

	}else if(strcmp(instruccion,"MEM:read") == 0){
		setMBRInstruccion(arquitectura.memoria[arquitectura.MAR.direccion].operacion,arquitectura.memoria[arquitectura.MAR.direccion].fuente_operando,arquitectura.memoria[arquitectura.MAR.direccion].destino_operando,arquitectura.memoria[arquitectura.MAR.direccion].dato_extra);
		setMBRDato(arquitectura.memoria[arquitectura.MAR.direccion].numero);
	}else if(strcmp(instruccion,"MEM:write") == 0){
		setCeldaMemoriaNumero(arquitectura.MAR.direccion,arquitectura.MBR.numero);
		setCeldaMemoriaInstruccion(arquitectura.MAR.direccion,arquitectura.MBR.operacion,arquitectura.MBR.fuente_operando,arquitectura.MBR.destino_operando,arquitectura.MBR.dato_extra);
	}else if(strcmp(instruccion,"In") == 0){
		/*Hacer*/
	}else if(strcmp(instruccion,"Out") == 0){
		/*Hacer*/
	}else{
		printf("No existe la microinstruccion\n");
	}

}

char *obtenerFlag(char *puntero){
	char *resultado = (char *) malloc(sizeof(puntero));
	puntero += 5;
	int i;
	for(i = 0; i < 2; i++){
		*resultado = *puntero;
		resultado ++;
		puntero ++;
	}
	resultado -= 2;
	return resultado;
}

int convertirStringNumero2Int(char *puntero){
	int largo = strlen(puntero);
	int largo2 = strlen(puntero);
	int resultado = 0;
	int i;
	for(i = 0; i < largo2; i++){
		resultado += ((*puntero-48)*potencia(10,largo-1));
		largo--;
		puntero++;
	}
	return resultado;
}

int obtenerLargoSalto(char *puntero){
	char *resultado = (char *) malloc(sizeof(puntero));
	puntero += 8;
	int largo = strlen(puntero);
	int i;
	for(i = 0; i < largo; i++){
		*resultado = *puntero;
		resultado ++;
		puntero ++;
	}
	resultado -= largo;
	return convertirStringNumero2Int(resultado);
}


void ejecutarMicroPrograma(char* nombreArchivoMP){
	int largo = cantidadFilasArchivo(nombreArchivoMP);
	char *punteroMP = (char *) malloc(sizeof(nombreArchivoMP));
	printf("Ejecutando microprograma\n");
	int i;
	int salto = 0;
	for(i = 0; i < largo; i++){
		salto = 0;
		punteroMP = leerMicroInstruccion(i,nombreArchivoMP);
		if(*punteroMP == 84){
			char *punteroFlag = (char *) malloc(sizeof(punteroMP));
			char test[] = {"TEST:"};
			char *testPuntero = &test[0];
			strcpy(punteroMP,testPuntero);
			salto = obtenerLargoSalto(punteroMP);
			punteroFlag = obtenerFlag(punteroMP);
			if(strcmp(punteroFlag,"ZF") == 0 && arquitectura.flags.zero_flag == 1){
				i+=(salto-1);
			}else if(strcmp(punteroFlag,"CF") == 0 && arquitectura.flags.carry_flag == 1){
				i+=(salto-1);
			}else if(strcmp(punteroFlag,"SF") == 0 && arquitectura.flags.signal_flag == 1){
				i+=(salto-1);
			}
			
		}
		printf("%s\n", punteroMP);
		microInstruccionRealizar(punteroMP);	
		memset(punteroMP, 0, sizeof(punteroMP));
		
	}
	
}

char *obtenerASMInstruccion(char *palabra){
	char palabraArchivoN[] = {"AFOC1"};
	int largo = strlen(palabra);
	char lista[] = {".txt"};
	char *palabraNumero = (char *) malloc(sizeof(palabra));
	int i;
	int j;
	int k;
	char *resultado = (char *) malloc(sizeof(palabra));
	int contador = 0;
	int valor = 0;
	int contador2 = 0;

	for(i = 0; i < 5; i++){
		*resultado = palabraArchivoN[i];
		resultado++;
	}
	for(j = 0; j < largo; j++){
		if(*palabra != 32){
			if(*palabra == 44){
				*resultado = *palabra;
				resultado++;
				palabra++;
				contador++;
			}else if(*palabra < 58 && *palabra > 47 ){
				*palabraNumero = *palabra;
				contador2++;
				palabra++;
				palabraNumero++;
			}else{
				*resultado = *palabra;
				resultado++;
				palabra++;
				contador++;
			}
			
		}else{
			palabra++;
		}
	}
	for(k = 0; k < 4; k++){
		*resultado = lista[k];
		resultado++;
	}
	palabraNumero -= contador2;
	int numeroDato = convertirStringNumero2Int(palabraNumero);
	if(numeroDato != 0){
		arquitectura.MBR.dato_extra = numeroDato;
	}
	
	resultado -= (contador+9);
	return resultado;
}


void leerASM(char* nombreArchivoMP){
	int largo = cantidadFilasArchivo(nombreArchivoMP);
	char *punteroMP = (char *) malloc(sizeof(nombreArchivoMP));
	printf("Ejecutando asm\n");
	int i;
	for(i = 0; i < largo; i++){

		punteroMP = leerMicroInstruccion(i,nombreArchivoMP);
		char *linea = (char *) malloc(sizeof(punteroMP));
		linea = obtenerASMInstruccion(punteroMP);
		printf("%s\n", linea);
		ejecutarMicroPrograma(linea);
	
		memset(punteroMP, 0, sizeof(punteroMP));
		
	}
	
}


/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/
/*#############################################################################################################################################################################################################################################################################*/




static void view_pc(GtkWidget *button, gpointer window)
{
	GtkWidget *dialog,*label,*content_area;
	dialog = gtk_dialog_new_with_buttons("Program Counter",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	
	int pc = getProgramCounter();
	char spc[10];

	sprintf(spc, "%d", pc);
	label = gtk_label_new(spc);
	gtk_container_add (GTK_CONTAINER (content_area), label);
	/*gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)),label,0,0,0);*/
	gtk_widget_show_all(dialog);
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	if(response == GTK_RESPONSE_OK)
		g_print("The OK is pressed");
	else
		g_print("The CANCEL was clicked");
	gtk_widget_destroy(dialog);
}
static void view_ir(GtkWidget *button, gpointer window)
{
	GtkWidget *dialog,*labelO,*labelF,*labelD,*labelE,*vbox,*content_area;
	dialog = gtk_dialog_new_with_buttons("Instruction Register",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	vbox = gtk_vbox_new(0,0);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> tercera columna*/

	int op = arquitectura.instruction_register.operacion;
	int fuente = arquitectura.instruction_register.fuente_operando;
	int destino = arquitectura.instruction_register.destino_operando;
	int extra = arquitectura.instruction_register.dato_extra;

	char sop[10];
	char sf[10];
	char sd[10];
	char ex[10];

	sprintf(sop, "%d", op);
	sprintf(sf, "%d", fuente);
	sprintf(sd, "%d", destino);
	sprintf(ex, "%d", extra);

	char o[20] = "Operacion: ";
	strcat(o,sop);
	char f[20] = "Fuente: ";
	strcat(f,sf);
	char d[20] = "Destino: ";
	strcat(d,sd);
	char e[20] = "Dato Extra: ";
	strcat(e,ex);

	labelO = gtk_label_new(o);
	labelF = gtk_label_new(f);
	labelD = gtk_label_new(d);
	labelE = gtk_label_new(e);

	gtk_box_pack_start(GTK_BOX(vbox),labelO,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelF,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelD,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelE,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */

	gtk_container_add (GTK_CONTAINER (content_area), vbox);
	gtk_widget_show_all(dialog);
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	if(response == GTK_RESPONSE_OK)
		g_print("The OK is pressed");
	else
		g_print("The CANCEL was clicked");
	gtk_widget_destroy(dialog);
}
static void view_uc(GtkWidget *button, gpointer window)
{
	GtkWidget *dialog,*label,*content_area;
	dialog = gtk_dialog_new_with_buttons("Unidad de Control",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	label = gtk_label_new("            Somos Nosotros! ;)          ");
	gtk_container_add (GTK_CONTAINER (content_area), label);
	/*gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)),label,0,0,0);*/
	gtk_widget_show_all(dialog);
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));

	if(response == GTK_RESPONSE_OK)
		g_print("%d\n",micprog.numero);
	else
		g_print("The CANCEL was clicked");
	gtk_widget_destroy(dialog);
}
static void view_mar(GtkWidget *button, gpointer window)
{
	GtkWidget *dialog,*label,*content_area;
	dialog = gtk_dialog_new_with_buttons("Memory Address Register",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	int mar = arquitectura.MAR.direccion;
	char smar[20];
	sprintf(smar,"%d",mar);
	label = gtk_label_new(mar);
	gtk_container_add (GTK_CONTAINER (content_area), label);
	/*gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)),label,0,0,0);*/
	gtk_widget_show_all(dialog);
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	if(response == GTK_RESPONSE_OK)
		g_print("The OK is pressed");
	else
		g_print("The CANCEL was clicked");
	gtk_widget_destroy(dialog);
}
static void view_mbr(GtkWidget *button, gpointer window)
{
	GtkWidget *dialog,*labelO,*labelE,*labelF,*labelD,*labelN,*content_area,*vbox;
	dialog = gtk_dialog_new_with_buttons("Memory Buffer REgister",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	vbox = gtk_vbox_new(0,12);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> tercera columna*/

	int op = arquitectura.MBR.operacion;
	int fuente= arquitectura.MBR.fuente_operando;
	int destino= arquitectura.MBR.destino_operando;
	int extra = arquitectura.MBR.dato_extra;
	int numero = arquitectura.MBR.numero;

	char sop[10];
	char sf[10];
	char sd[10];
	char ex[10];
	char num[10];

	sprintf(sop, "%d", op);
	sprintf(sf, "%d", fuente);
	sprintf(sd, "%d", destino);
	sprintf(ex, "%d", extra);
	sprintf(num, "%d", numero);

	char o[20] = "Operacion: ";
	strcat(o,sop);
	char f[20] = "Fuente: ";
	strcat(f,sf);
	char d[20] = "Destino: ";
	strcat(d,sd);
	char e[20] = "Dato Extra: ";
	strcat(e,ex);
	char n[20] = "Numero: ";
	strcat(n,num);

	labelO = gtk_label_new(o);
	labelF = gtk_label_new(f);
	labelD = gtk_label_new(d);
	labelE = gtk_label_new(e);
	labelN = gtk_label_new(n);

	gtk_box_pack_start(GTK_BOX(vbox),labelO,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelF,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelD,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelE,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelN,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */

	gtk_container_add (GTK_CONTAINER (content_area), vbox);
	/*gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)),label,0,0,0);*/
	gtk_widget_show_all(dialog);
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	if(response == GTK_RESPONSE_OK)
		g_print("The OK is pressed");
	else
		g_print("The CANCEL was clicked");
	gtk_widget_destroy(dialog);
}
static void cambiar_regsAX(GtkWidget *button, gpointer text){
	char *numero = gtk_entry_get_text(GTK_ENTRY(text));
	printf("%d\n",convertirStringNumero2Int(numero));
	setRegistroAx(convertirStringNumero2Int(numero));
	
}
static void cambiar_regsBX(GtkWidget *button, gpointer text){
	char *numero = gtk_entry_get_text(GTK_ENTRY(text));
	printf("%d\n",convertirStringNumero2Int(numero));
	setRegistroBx(convertirStringNumero2Int(numero));
}
static void cambiar_regsCX(GtkWidget *button, gpointer text){
	char *numero = gtk_entry_get_text(GTK_ENTRY(text));
	setRegistroCx(convertirStringNumero2Int(numero));
}
static void cambiar_regsDX(GtkWidget *button, gpointer text){
	char *numero = gtk_entry_get_text(GTK_ENTRY(text));
	setRegistroDx(convertirStringNumero2Int(numero));
}
static void cambiar_regsAL(GtkWidget *button, gpointer text){
	char *numero = gtk_entry_get_text(GTK_ENTRY(text));
	setParteBajaAX(convertirStringNumero2Int(numero));
}
static void cambiar_regsAH(GtkWidget *button, gpointer text){
	char *numero = gtk_entry_get_text(GTK_ENTRY(text));
	setParteAltaAX(convertirStringNumero2Int(numero));
}
static void cambiar_regsBL(GtkWidget *button, gpointer text){
	char *numero = gtk_entry_get_text(GTK_ENTRY(text));
	setParteBajaBX(convertirStringNumero2Int(numero));
}
static void cambiar_regsBH(GtkWidget *button, gpointer text){
	char *numero = gtk_entry_get_text(GTK_ENTRY(text));
	setParteAltaBX(convertirStringNumero2Int(numero));
}
static void cambiar_regsCL(GtkWidget *button, gpointer text){
	char *numero = gtk_entry_get_text(GTK_ENTRY(text));
	setParteBajaCX(convertirStringNumero2Int(numero));
}
static void cambiar_regsCH(GtkWidget *button, gpointer text){
	char *numero = gtk_entry_get_text(GTK_ENTRY(text));
	setParteAltaCX(convertirStringNumero2Int(numero));
}
static void cambiar_regsDL(GtkWidget *button, gpointer text){
	char *numero = gtk_entry_get_text(GTK_ENTRY(text));
	setParteBajaDX(convertirStringNumero2Int(numero));
}
static void cambiar_regsDH(GtkWidget *button, gpointer text){
	char *numero = gtk_entry_get_text(GTK_ENTRY(text));
	setParteAltaDX(convertirStringNumero2Int(numero));
}
static void view_rt(GtkWidget *button, gpointer window)
{
	GtkWidget *dialog,*buttonCambiarRegAX,*buttonCambiarRegBX,*buttonCambiarRegCX,*buttonCambiarRegDX,*buttonCambiarRegAL,*buttonCambiarRegAH,*buttonCambiarRegBL,*buttonCambiarRegBH,*buttonCambiarRegCL,*buttonCambiarRegCH,*buttonCambiarRegDL,*buttonCambiarRegDH,*hbox,*vbox,*vbox1,*vbox2,*entryAX,*entryBX,*entryCX,*entryDX,*entryAL,*entryAH,*entryBL,*entryBH,*entryCL,*entryCH,*entryDL,*entryDH,*label,*content_area,*labelAX,*labelBX,*labelCX,*labelDX,*labelAL,*labelAH,*labelBL,*labelBH,*labelCL,*labelCH,*labelDL,*labelDH;
	dialog = gtk_dialog_new_with_buttons("Registros de Trabajo",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	vbox = gtk_vbox_new(0,12);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> tercera columna*/
	vbox1 = gtk_vbox_new(0,0);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> tercera columna*/
	vbox2 = gtk_vbox_new(0,0);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> tercera columna*/
	hbox = gtk_hbox_new(0,0);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> tercera columna*/
	
	buttonCambiarRegAX = gtk_button_new_with_mnemonic("_Cambiar");/* Inicializa un boton*/
	buttonCambiarRegBX = gtk_button_new_with_mnemonic("_Cambiar");/* Inicializa un boton*/
	buttonCambiarRegCX = gtk_button_new_with_mnemonic("_Cambiar");/* Inicializa un boton*/
	buttonCambiarRegDX = gtk_button_new_with_mnemonic("_Cambiar");/* Inicializa un boton*/
	buttonCambiarRegAL = gtk_button_new_with_mnemonic("_Cambiar");/* Inicializa un boton*/
	buttonCambiarRegAH = gtk_button_new_with_mnemonic("_Cambiar");/* Inicializa un boton*/
	buttonCambiarRegBL = gtk_button_new_with_mnemonic("_Cambiar");/* Inicializa un boton*/
	buttonCambiarRegBH = gtk_button_new_with_mnemonic("_Cambiar");/* Inicializa un boton*/
	buttonCambiarRegCL = gtk_button_new_with_mnemonic("_Cambiar");/* Inicializa un boton*/
	buttonCambiarRegCH = gtk_button_new_with_mnemonic("_Cambiar");/* Inicializa un boton*/
	buttonCambiarRegDL = gtk_button_new_with_mnemonic("_Cambiar");/* Inicializa un boton*/
	buttonCambiarRegDH = gtk_button_new_with_mnemonic("_Cambiar");/* Inicializa un boton*/
	labelAX = gtk_label_new("AX:");
	labelAL = gtk_label_new("AL:");
	labelAH = gtk_label_new("AH:");
	labelBX = gtk_label_new("BX:");
	labelBL = gtk_label_new("BL:");
	labelBH = gtk_label_new("BH:");
	labelCX = gtk_label_new("CX:");
	labelCL = gtk_label_new("CL:");
	labelCH = gtk_label_new("CH:");
	labelDX = gtk_label_new("DX:");
	labelDL = gtk_label_new("DL:");
	labelDH = gtk_label_new("DH:");
	entryAX = gtk_entry_new();
	entryBX = gtk_entry_new();
	entryCX = gtk_entry_new();
	entryDX = gtk_entry_new();
	entryAL = gtk_entry_new();
	entryAH = gtk_entry_new();
	entryBL = gtk_entry_new();
	entryBH = gtk_entry_new();
	entryCL = gtk_entry_new();
	entryCH = gtk_entry_new();
	entryDL = gtk_entry_new();
	entryDH = gtk_entry_new();

	g_signal_connect(buttonCambiarRegAX,"clicked",G_CALLBACK(cambiar_regsAX),entryAX);
	g_signal_connect(buttonCambiarRegBX,"clicked",G_CALLBACK(cambiar_regsBX),entryBX);
	g_signal_connect(buttonCambiarRegCX,"clicked",G_CALLBACK(cambiar_regsCX),entryCX);
	g_signal_connect(buttonCambiarRegDX,"clicked",G_CALLBACK(cambiar_regsDX),entryDX);
	g_signal_connect(buttonCambiarRegAL,"clicked",G_CALLBACK(cambiar_regsAL),entryAL);
	g_signal_connect(buttonCambiarRegAH,"clicked",G_CALLBACK(cambiar_regsAH),entryAH);
	g_signal_connect(buttonCambiarRegBL,"clicked",G_CALLBACK(cambiar_regsBL),entryBL);
	g_signal_connect(buttonCambiarRegBH,"clicked",G_CALLBACK(cambiar_regsBH),entryBH);
	g_signal_connect(buttonCambiarRegCL,"clicked",G_CALLBACK(cambiar_regsCL),entryCL);
	g_signal_connect(buttonCambiarRegCH,"clicked",G_CALLBACK(cambiar_regsCH),entryCH);
	g_signal_connect(buttonCambiarRegDL,"clicked",G_CALLBACK(cambiar_regsDL),entryDL);
	g_signal_connect(buttonCambiarRegDH,"clicked",G_CALLBACK(cambiar_regsDH),entryDH);

	int ax = getRegistroAx();
	int bx = getRegistroBx();
	int cx = getRegistroCx();
	int dx = getRegistroDx();
	int al = getParteBajaAX();
	int ah = getParteAltaAX();
	int bl = getParteBajaBX();
	int bh = getParteAltaBX();
	int cl = getParteBajaCX();
	int ch = getParteAltaCX();
	int dl = getParteBajaDX();
	int dh = getParteAltaDX();

	char sax[20];
	char sbx[20];
	char scx[20];
	char sdx[20];
	char sal[20];
	char sah[20];
	char sbl[20];
	char sbh[20];
	char scl[20];
	char sch[20];
	char sdl[20];
	char sdh[20];

	sprintf(sax, "%d", ax);
	sprintf(sbx, "%d", bx);
	sprintf(scx, "%d", cx);
	sprintf(sdx, "%d", dx);
	sprintf(sal, "%d", al);
	sprintf(sah, "%d", ah);
	sprintf(sbl, "%d", bl);
	sprintf(sbh, "%d", bh);
	sprintf(scl, "%d", cl);
	sprintf(sch, "%d", ch);
	sprintf(sdl, "%d", dl);
	sprintf(sdh, "%d", dh);

	gtk_entry_set_text(entryAX,sax);
	gtk_entry_set_text(entryBX,sbx);
	gtk_entry_set_text(entryCX,scx);
	gtk_entry_set_text(entryDX,sdx);
	gtk_entry_set_text(entryAL,sal);
	gtk_entry_set_text(entryAH,sah);
	gtk_entry_set_text(entryBL,sbl);
	gtk_entry_set_text(entryBH,sbh);
	gtk_entry_set_text(entryCL,scl);
	gtk_entry_set_text(entryCH,sch);
	gtk_entry_set_text(entryDL,sdl);
	gtk_entry_set_text(entryDH,sdh);

	gtk_box_pack_start(GTK_BOX(vbox),labelAX,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelBX,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelCX,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelDX,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelAL,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelAH,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelBL,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelBH,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelCL,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelCH,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelDL,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelDH,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */

	gtk_box_pack_start(GTK_BOX(vbox1),entryAX,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),entryBX,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),entryCX,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),entryDX,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),entryAL,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),entryAH,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),entryBL,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),entryBH,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),entryCL,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),entryCH,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),entryDL,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),entryDH,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	
	gtk_box_pack_start(GTK_BOX(vbox2),buttonCambiarRegAX,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),buttonCambiarRegBX,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),buttonCambiarRegCX,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),buttonCambiarRegDX,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),buttonCambiarRegAL,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),buttonCambiarRegAH,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),buttonCambiarRegBL,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),buttonCambiarRegBH,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),buttonCambiarRegCL,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),buttonCambiarRegCH,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),buttonCambiarRegDL,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),buttonCambiarRegDH,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */

	gtk_box_pack_start(GTK_BOX(hbox),vbox,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(hbox),vbox1,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(hbox),vbox2,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */

	gtk_container_add (GTK_CONTAINER (content_area),hbox);
	/*gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)),label,0,0,0);*/
	gtk_widget_show_all(dialog);
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	if(response == GTK_RESPONSE_OK)
		g_print("The OK is pressed\n");
	else
		g_print("The CANCEL was clicked\n");
	gtk_widget_destroy(dialog);
}
static void view_flags(GtkWidget *button, gpointer window)
{
	GtkWidget *dialog,*vbox,*labelZ,*labelC,*labelS,*labelI,*content_area;
	dialog = gtk_dialog_new_with_buttons("Flags",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	vbox = gtk_vbox_new(0,0);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> tercera columna*/

	int zero = getZeroFlag();
	int carry = getCarryFlag();
	int sign = getSignalFlag();
	int interrupt = getInterruptionCarryFlag();
	int someInt = 368;
	char strZero[5];
	char strCarry[5];
	char strSign[5];
	char strInterrupt[5];

	sprintf(strZero, "%d", zero);
	sprintf(strCarry, "%d", carry);
	sprintf(strSign, "%d", sign);
	sprintf(strInterrupt, "%d", interrupt);

	char zeroflag[20] = "Zero: ";
	strcat(zeroflag,strZero);
	char carryflag[20] = "Carry: ";
	strcat(carryflag,strCarry);
	char signflag[20] = "Sign: ";
	strcat(signflag,strSign);
	char interruptflag[20] = "Interrupt: ";
	strcat(interruptflag,strInterrupt);	
	labelZ = gtk_label_new(zeroflag);
	labelC = gtk_label_new(carryflag);
	labelS = gtk_label_new(signflag);
	labelI = gtk_label_new(interruptflag);

	gtk_box_pack_start(GTK_BOX(vbox),labelZ,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelC,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelS,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox),labelI,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */

	gtk_container_add (GTK_CONTAINER (content_area), vbox);
	/*gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)),label,0,0,0);*/
	gtk_widget_show_all(dialog);
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	if(response == GTK_RESPONSE_OK)
		g_print("The OK is pressed");
	else
		g_print("The CANCEL was clicked");
	gtk_widget_destroy(dialog);
}
static void view_b1(GtkWidget *button, gpointer window)
{
	GtkWidget *dialog,*label,*content_area;
	dialog = gtk_dialog_new_with_buttons("B1",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	int b4 = arquitectura.aritmetic_logic_unit.b4;
	char sb4[10];
	sprintf(sb4, "%d", b4);
	label = gtk_label_new(sb4);
	gtk_container_add (GTK_CONTAINER (content_area), label);
	/*gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)),label,0,0,0);*/
	gtk_widget_show_all(dialog);
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	if(response == GTK_RESPONSE_OK)
		g_print("The OK is pressed");
	else
		g_print("The CANCEL was clicked");
	gtk_widget_destroy(dialog);
}
static void view_b2(GtkWidget *button, gpointer window)
{
	GtkWidget *dialog,*label,*content_area;
	dialog = gtk_dialog_new_with_buttons("B2",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

	int b3 = arquitectura.aritmetic_logic_unit.b3;
	char sb3[10];
	sprintf(sb3, "%d", b3);
	label = gtk_label_new(sb3);

	gtk_container_add (GTK_CONTAINER (content_area), label);
	/*gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)),label,0,0,0);*/
	gtk_widget_show_all(dialog);
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	if(response == GTK_RESPONSE_OK)
		g_print("The OK is pressed");
	else
		g_print("The CANCEL was clicked");
	gtk_widget_destroy(dialog);
}
static void view_b3(GtkWidget *button, gpointer window)
{
	GtkWidget *dialog,*label,*content_area;
	dialog = gtk_dialog_new_with_buttons("B3",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

	int b2 = arquitectura.aritmetic_logic_unit.b2;
	char sb2[10];
	sprintf(sb2, "%d", b2);

	label = gtk_label_new(sb2);
	gtk_container_add (GTK_CONTAINER (content_area), label);
	/*gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)),label,0,0,0);*/
	gtk_widget_show_all(dialog);
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	if(response == GTK_RESPONSE_OK)
		g_print("The OK is pressed");
	else
		g_print("The CANCEL was clicked");
	gtk_widget_destroy(dialog);
}
static void view_b4(GtkWidget *button, gpointer window)
{
	GtkWidget *dialog,*label,*content_area;
	dialog = gtk_dialog_new_with_buttons("B4",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

	int b1 = arquitectura.aritmetic_logic_unit.b1;
	char sb1[10];
	sprintf(sb1, "%d", b1);

	label = gtk_label_new(sb1);
	gtk_container_add (GTK_CONTAINER (content_area), label);
	/*gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)),label,0,0,0);*/
	gtk_widget_show_all(dialog);
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	if(response == GTK_RESPONSE_OK)
		g_print("The OK is pressed");
	else
		g_print("The CANCEL was clicked");
	gtk_widget_destroy(dialog);
}
static void view_alu(GtkWidget *button, gpointer window)
{
	GtkWidget *dialog,*label,*content_area;
	dialog = gtk_dialog_new_with_buttons("ALU",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	int op = arquitectura.aritmetic_logic_unit.operacion;
	char sop[10];
	sprintf(sop, "%d", op);
	char nomop[30] = "Numero de Operacion: ";
	strcat(nomop,sop);
	label = gtk_label_new(nomop);
	gtk_container_add (GTK_CONTAINER (content_area), label);
	/*gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)),label,0,0,0);*/
	gtk_widget_show_all(dialog);
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	if(response == GTK_RESPONSE_OK)
		g_print("The OK is pressed");
	else
		g_print("The CANCEL was clicked");
	gtk_widget_destroy(dialog);
}
static char* guardar_nombre_instruccion(GtkWidget *button, gpointer data)
{
	char *text = gtk_entry_get_text(GTK_ENTRY(data));
	micprog.nombre = text;
}
static char* guardar_nmonico_instruccion(GtkWidget *button, gpointer data)
{
	char *text = gtk_entry_get_text(GTK_ENTRY(data));
	micprog.nmonico = text;
}
static void guardar_micro_programa(GtkWidget *button, gpointer data){
	g_print("\n%s\n","Nombre:");
	g_print("%s\n",micprog.nombre);
	g_print("%s\n","N-monico:");
	g_print("%s\n",micprog.nmonico);
	g_print("%s\n","Programa:");
	g_print("%s\n",micprog.programa);

	char str[256];
	strcpy(str,micprog.nombre);
	char nombreArchivo[10] = "AFOC1";
	strcat(nombreArchivo,str);
	printf("%s\n", nombreArchivo);	

	construirMicroPrograma(nombreArchivo,micprog.programa);

	printf("%s\n", "Todo bien");
}
static void guardar_micro_instruccion(GtkWidget *button, gpointer data){	// salto de linea para demostrar que la instruccion esta lista
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"\n");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"\n");
		strcpy(micprog.programa, str);	
	}
}
static void mi_ir(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"IR");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"IR");
		strcpy(micprog.programa, str);	
	}
}
static void mi_pc(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"PC");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"PC");
		strcpy(micprog.programa, str);	
	}
}
static void mi_bd(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"BD");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"BD");
		strcpy(micprog.programa, str);	
	}
}

static void mi_mar(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"MAR");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"MAR");
		strcpy(micprog.programa, str);	
	}
}
static void mi_mbr(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"MBR");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"MBR");
		strcpy(micprog.programa, str);	
	}
}
static void mi_arrow(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"<-");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"<-");
		strcpy(micprog.programa, str);	
	}
}
static void mi_AX(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"AX");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"AX");
		strcpy(micprog.programa, str);	
	}
}
static void mi_al(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"AL");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"AL");
		strcpy(micprog.programa, str);	
	}
}
static void mi_ah(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"AH");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"AH");
		strcpy(micprog.programa, str);	
	}
}
static void mi_BX(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"BX");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"BX");
		strcpy(micprog.programa, str);	
	}
}
static void mi_bl(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"BL");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"BL");
		strcpy(micprog.programa, str);	
	}
}
static void mi_bh(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"BH");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"BH");
		strcpy(micprog.programa, str);	
	}
}
static void mi_CX(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"CX");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"CX");
		strcpy(micprog.programa, str);	
	}
}
static void mi_cl(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"CL");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"CL");
		strcpy(micprog.programa, str);	
	}
}
static void mi_ch(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"CH");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"CH");
		strcpy(micprog.programa, str);	
	}
}
static void mi_DX(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"DX");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"DX");
		strcpy(micprog.programa, str);	
	}
}
static void mi_dl(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"DL");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"DL");
		strcpy(micprog.programa, str);	
	}
}
static void mi_dh(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"DH");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"DH");
		strcpy(micprog.programa, str);	
	}
}
static void mi_b1(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"B1");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"B1");
		strcpy(micprog.programa, str);	
	}
}
static void mi_b2(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"B2");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"B2");
		strcpy(micprog.programa, str);	
	}
}
static void mi_b3(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"B3");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"B3");
		strcpy(micprog.programa, str);	
	}
}
static void mi_b4(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"B4");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"B4");
		strcpy(micprog.programa, str);	
	}
}
static void mi_alu_add(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"ALU:add");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"ALU:add");
		strcpy(micprog.programa, str);	
	}
}
static void mi_alu_sub(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"ALU:sub");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"ALU:sub");
		strcpy(micprog.programa, str);	
	}
}
static void mi_alu_mul(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"ALU:mul");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"ALU:mul");
		strcpy(micprog.programa, str);	
	}
}
static void mi_alu_div(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"ALU:div");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"ALU:div");
		strcpy(micprog.programa, str);	
	}
}
static void mi_alu_and(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"ALU:and");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"ALU:and");
		strcpy(micprog.programa, str);	
	}
}
static void mi_alu_or(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"ALU:or");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"ALU:or");
		strcpy(micprog.programa, str);	
	}
}
static void mi_alu_xor(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"ALU:xor");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"ALU:xor");
		strcpy(micprog.programa, str);	
	}
}
static void mi_alu_not(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"ALU:not");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"ALU:not");
		strcpy(micprog.programa, str);	
	}
}
static void mi_alu_shr(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"ALU:shr");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"ALU:shr");
		strcpy(micprog.programa, str);	
	}
}
static void mi_alu_shl(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"ALU:shl");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"ALU:shl");
		strcpy(micprog.programa, str);	
	}
}
static void mi_testCarry(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"TEST:CF,");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"TEST:CF,");
		strcpy(micprog.programa, str);	
	}
}
static void mi_testSign(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"TEST:SF,");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"TEST:SF,");
		strcpy(micprog.programa, str);	
	}
}
static void mi_testZero(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"TEST:ZF,");// + N
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"TEST:ZF,");
		strcpy(micprog.programa, str);	
	}
}
static void mi_testInterrupt(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"TEST:IF,");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"TEST:IF,");
		strcpy(micprog.programa, str);	
	}
}
static void mi_memRead(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"MEM:read");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"MEM:read");
		strcpy(micprog.programa, str);	
	}
}
static void mi_memWrite(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"MEM:write");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"MEM:write");
		strcpy(micprog.programa, str);	
	}
}
static void mi_in(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"In");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"In");
		strcpy(micprog.programa, str);	
	}
}
static void mi_out(GtkWidget *button, gpointer data){
	if(micprog.programa == NULL){
		strcpy(micprog.programa,"Out");
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,"Out");
		strcpy(micprog.programa, str);	
	}
}
static void agregar_n(GtkWidget *button, gpointer data){
	char *numero = gtk_entry_get_text(GTK_ENTRY(data));
	if(micprog.programa == NULL){
		strcpy(micprog.programa,numero);
		g_print("%s\n",micprog.programa);
	}
	else{
		char str[256];
		strcpy(str,micprog.programa);
		g_print("%s\n",micprog.programa);
		strcat(str,numero);
		strcpy(micprog.programa, str);	
	}
}
static void microprogramar(GtkWidget *button, gpointer window)
{
	GtkWidget *window2,*buttonTestN,*labelTestN,*entryTest,*button_alu_shl,*vbox3,*buttonGuardarMicroprograma,*buttonGuardarNmonico,*buttonGuardarNombre,*labelNombre,*labelNmonico,*button_al,*entryNombre,*entryNmonico,*hbox,*vbox1,*vbox2,*layout,*button_uc,*button_ir,*button_pc,*button_mar,*button_mbr,*button_bd,*button_arrow,*button_AX,*button_ah,*button_BX,*button_bl,*button_bh,*button_CX,*button_cl,*button_ch,*button_DX,*button_dl,*button_dh,*button_b1,*button_b2,*button_b3,*button_b4,*button_alu_add,*button_alu_sub,*button_alu_mul,*button_alu_div,*button_alu_and,*button_alu_or,*button_alu_xor,*button_alu_not,*button_alu_shr,*button_memRead,*button_memWrite,*button_testCarry,*button_testSign,*button_testZero,*button_testInterrupt,*button_in,*button_out,*buttonGuardarMicroinstruccion;
	window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window2,"destroy-event",G_CALLBACK(gtk_main_quit),NULL);	/* Apretar boton X para salir de la interfaz*/
	gtk_window_set_modal(window2,TRUE); 

	labelNombre = gtk_label_new("Nombre:");/* Inicializa un label*/
	labelNmonico = gtk_label_new("N-monico:");/* Inicializa un label*/
	labelTestN = gtk_label_new("Numero de microinstruccion\npara el TEST:op :");/* Inicializa un label*/
	entryNombre = gtk_entry_new();
	entryNmonico = gtk_entry_new();
	entryTest = gtk_entry_new();
    layout = gtk_layout_new(NULL, NULL);

	button_ir = gtk_button_new_with_mnemonic("_IR");/* Inicializa un boton*/
    button_pc = gtk_button_new_with_mnemonic("_PC");/* Inicializa un boton*/
    button_mar = gtk_button_new_with_mnemonic("_MAR");/* Inicializa un boton*/
    button_mbr = gtk_button_new_with_mnemonic("_MBR");/* Inicializa un boton*/
    button_bd = gtk_button_new_with_mnemonic("_BD");/* Inicializa un boton*/
    button_arrow = gtk_button_new_with_mnemonic("_<-");/* Inicializa un boton*/
    button_AX = gtk_button_new_with_mnemonic("_AX");/* Inicializa un boton*/
    button_al = gtk_button_new_with_mnemonic("_al");/* Inicializa un boton*/
    button_ah = gtk_button_new_with_mnemonic("_ah");/* Inicializa un boton*/
    button_BX = gtk_button_new_with_mnemonic("_BX");/* Inicializa un boton*/
    button_bl = gtk_button_new_with_mnemonic("_bl");/* Inicializa un boton*/
    button_bh = gtk_button_new_with_mnemonic("_bh");/* Inicializa un boton*/
    button_CX = gtk_button_new_with_mnemonic("_CX");/* Inicializa un boton*/
    button_cl = gtk_button_new_with_mnemonic("_cl");/* Inicializa un boton*/
    button_ch = gtk_button_new_with_mnemonic("_ch");/* Inicializa un boton*/
    button_DX = gtk_button_new_with_mnemonic("_DX");/* Inicializa un boton*/
    button_dl = gtk_button_new_with_mnemonic("_dl");/* Inicializa un boton*/
    button_dh = gtk_button_new_with_mnemonic("_dh");/* Inicializa un boton*/
    button_b1 = gtk_button_new_with_mnemonic("_B1");/* Inicializa un boton*/
    button_b2 = gtk_button_new_with_mnemonic("_B2");/* Inicializa un boton*/
    button_b3 = gtk_button_new_with_mnemonic("_B3");/* Inicializa un boton*/
    button_b4 = gtk_button_new_with_mnemonic("_B4");/* Inicializa un boton*/
    button_alu_add = gtk_button_new_with_mnemonic("_ALU:add");/* Inicializa un boton*/
    button_alu_sub = gtk_button_new_with_mnemonic("_ALU:sub");/* Inicializa un boton*/
    button_alu_mul = gtk_button_new_with_mnemonic("_ALU:mul");/* Inicializa un boton*/
    button_alu_div = gtk_button_new_with_mnemonic("_ALU:div");/* Inicializa un boton*/
    button_alu_and = gtk_button_new_with_mnemonic("_ALU:and");/* Inicializa un boton*/
    button_alu_or = gtk_button_new_with_mnemonic("_ALU:or");/* Inicializa un boton*/
    button_alu_xor = gtk_button_new_with_mnemonic("_ALU:xor");/* Inicializa un boton*/
    button_alu_not = gtk_button_new_with_mnemonic("_ALU:not");/* Inicializa un boton*/
    button_alu_shr = gtk_button_new_with_mnemonic("_ALU:shr");/* Inicializa un boton*/
    button_alu_shl = gtk_button_new_with_mnemonic("_ALU:shl");/* Inicializa un boton*/
    button_testCarry = gtk_button_new_with_mnemonic("_TEST:CF,");/* Inicializa un boton*/
    button_testSign = gtk_button_new_with_mnemonic("_TEST:SF,");/* Inicializa un boton*/
    button_testZero = gtk_button_new_with_mnemonic("_TEST:ZF,");/* Inicializa un boton*/
    button_testInterrupt = gtk_button_new_with_mnemonic("_TEST:IF,");/* Inicializa un boton*/
    button_memRead = gtk_button_new_with_mnemonic("_MEM:read");/* Inicializa un boton*/
    button_memWrite = gtk_button_new_with_mnemonic("_MEM:write");/* Inicializa un boton*/
    button_in = gtk_button_new_with_mnemonic("_In");/* Inicializa un boton*/
    button_out = gtk_button_new_with_mnemonic("_Out");/* Inicializa un boton*/
    buttonTestN = gtk_button_new_with_mnemonic("_Agregar a TEST:op,");/* Inicializa un boton*/

    buttonGuardarMicroinstruccion = gtk_button_new_with_mnemonic("_Guardar Microinstruccion");
    buttonGuardarNombre = gtk_button_new_with_mnemonic("_Guardar Nombre");
    buttonGuardarNmonico = gtk_button_new_with_mnemonic("_Guardar N-monico");
    buttonGuardarMicroprograma = gtk_button_new_with_mnemonic("_Guardar Microprograma");
	hbox = gtk_hbox_new(0,0);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> main*/
	vbox1 = gtk_vbox_new(0,0);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> segunda columna*/
	vbox2 = gtk_vbox_new(0,0);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> tercera columna*/
	vbox3 = gtk_vbox_new(0,0);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> tercera columna*/
    
    g_signal_connect(button_out,"clicked",G_CALLBACK(mi_out),NULL);
    g_signal_connect(button_in,"clicked",G_CALLBACK(mi_in),NULL);
    g_signal_connect(button_memWrite,"clicked",G_CALLBACK(mi_memWrite),NULL);
    g_signal_connect(button_memRead,"clicked",G_CALLBACK(mi_memRead),NULL);
    g_signal_connect(button_testInterrupt,"clicked",G_CALLBACK(mi_testInterrupt),NULL);
    g_signal_connect(button_testZero,"clicked",G_CALLBACK(mi_testZero),NULL);
    g_signal_connect(button_testSign,"clicked",G_CALLBACK(mi_testSign),NULL);
    g_signal_connect(button_testCarry,"clicked",G_CALLBACK(mi_testCarry),NULL);
    g_signal_connect(button_alu_shr,"clicked",G_CALLBACK(mi_alu_shr),NULL);
    g_signal_connect(button_alu_shl,"clicked",G_CALLBACK(mi_alu_shl),NULL);
    g_signal_connect(button_alu_not,"clicked",G_CALLBACK(mi_alu_not),NULL);
    g_signal_connect(button_alu_xor,"clicked",G_CALLBACK(mi_alu_xor),NULL);
    g_signal_connect(button_alu_or,"clicked",G_CALLBACK(mi_alu_or),NULL);
    g_signal_connect(button_alu_and,"clicked",G_CALLBACK(mi_alu_and),NULL);
    g_signal_connect(button_alu_div,"clicked",G_CALLBACK(mi_alu_div),NULL);
    g_signal_connect(button_alu_mul,"clicked",G_CALLBACK(mi_alu_mul),NULL);
    g_signal_connect(button_alu_sub,"clicked",G_CALLBACK(mi_alu_sub),NULL);
    g_signal_connect(button_alu_add,"clicked",G_CALLBACK(mi_alu_add),NULL);
    g_signal_connect(button_b4,"clicked",G_CALLBACK(mi_b4),NULL);
    g_signal_connect(button_b3,"clicked",G_CALLBACK(mi_b3),NULL);
    g_signal_connect(button_b2,"clicked",G_CALLBACK(mi_b2),NULL);
    g_signal_connect(button_b1,"clicked",G_CALLBACK(mi_b1),NULL);
    g_signal_connect(button_dh,"clicked",G_CALLBACK(mi_dh),NULL);
    g_signal_connect(button_dl,"clicked",G_CALLBACK(mi_dl),NULL);
    g_signal_connect(button_DX,"clicked",G_CALLBACK(mi_DX),NULL);
    g_signal_connect(button_ch,"clicked",G_CALLBACK(mi_ch),NULL);
    g_signal_connect(button_cl,"clicked",G_CALLBACK(mi_cl),NULL);
    g_signal_connect(button_CX,"clicked",G_CALLBACK(mi_CX),NULL);
    g_signal_connect(button_bh,"clicked",G_CALLBACK(mi_bh),NULL);
    g_signal_connect(button_bl,"clicked",G_CALLBACK(mi_bl),NULL);
    g_signal_connect(button_BX,"clicked",G_CALLBACK(mi_BX),NULL);
    g_signal_connect(button_ah,"clicked",G_CALLBACK(mi_ah),NULL);
    g_signal_connect(button_al,"clicked",G_CALLBACK(mi_al),NULL);
    g_signal_connect(button_AX,"clicked",G_CALLBACK(mi_AX),NULL);
    g_signal_connect(button_arrow,"clicked",G_CALLBACK(mi_arrow),NULL);
    g_signal_connect(button_mbr,"clicked",G_CALLBACK(mi_mbr),NULL);
    g_signal_connect(button_mar,"clicked",G_CALLBACK(mi_mar),NULL);
    g_signal_connect(button_bd,"clicked",G_CALLBACK(mi_bd),NULL);
    g_signal_connect(button_pc,"clicked",G_CALLBACK(mi_pc),NULL);
    g_signal_connect(button_ir,"clicked",G_CALLBACK(mi_ir),NULL);
    g_signal_connect(buttonGuardarNombre,"clicked",G_CALLBACK(guardar_nombre_instruccion),entryNombre);
    g_signal_connect(buttonGuardarNmonico,"clicked",G_CALLBACK(guardar_nmonico_instruccion),entryNmonico);
	g_signal_connect(buttonGuardarMicroprograma,"clicked",G_CALLBACK(guardar_micro_programa),NULL);
	g_signal_connect(buttonGuardarMicroinstruccion,"clicked",G_CALLBACK(guardar_micro_instruccion),NULL);
	g_signal_connect(buttonTestN,"clicked",G_CALLBACK(agregar_n),entryTest);

	gtk_box_pack_start(GTK_BOX(vbox1),button_ir,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),button_pc,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),button_mar,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),button_mbr,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),button_bd,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),button_arrow,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),button_b1,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),button_b2,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),button_b3,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),button_b4,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),button_in,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),button_out,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	
	gtk_box_pack_start(GTK_BOX(vbox3),button_AX,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox3),button_al,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox3),button_ah,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */	
	gtk_box_pack_start(GTK_BOX(vbox3),button_BX,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */	
	gtk_box_pack_start(GTK_BOX(vbox3),button_bl,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */	
	gtk_box_pack_start(GTK_BOX(vbox3),button_bh,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */	
	gtk_box_pack_start(GTK_BOX(vbox3),button_CX,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */	
	gtk_box_pack_start(GTK_BOX(vbox3),button_cl,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */	
	gtk_box_pack_start(GTK_BOX(vbox3),button_ch,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */	
	gtk_box_pack_start(GTK_BOX(vbox3),button_DX,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */	
	gtk_box_pack_start(GTK_BOX(vbox3),button_dl,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */	
	gtk_box_pack_start(GTK_BOX(vbox3),button_dh,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */	

	gtk_box_pack_start(GTK_BOX(vbox2),button_alu_add,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),button_alu_sub,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),button_alu_mul,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),button_alu_div,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),button_alu_and,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),button_alu_or,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),button_alu_xor,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),button_alu_not,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),button_alu_shr,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),button_alu_shl,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),button_testCarry,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),button_testSign,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),button_testZero,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),button_testInterrupt,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),button_memRead,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),button_memWrite,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */

    gtk_layout_put(GTK_LAYOUT(layout), labelTestN, 70, 160); 
    gtk_layout_put(GTK_LAYOUT(layout), entryTest, 70, 200);
    gtk_layout_put(GTK_LAYOUT(layout), buttonTestN, 70, 230);
    gtk_layout_put(GTK_LAYOUT(layout), buttonGuardarMicroinstruccion, 70, 0);
    gtk_layout_put(GTK_LAYOUT(layout), labelNombre, 70, 280); 
    gtk_layout_put(GTK_LAYOUT(layout), entryNombre, 70, 300);
    gtk_layout_put(GTK_LAYOUT(layout), buttonGuardarNombre, 70, 330);
    gtk_layout_put(GTK_LAYOUT(layout), labelNmonico, 70, 360); 
    gtk_layout_put(GTK_LAYOUT(layout), entryNmonico, 70, 380);
    gtk_layout_put(GTK_LAYOUT(layout), buttonGuardarNmonico, 70, 410);
    gtk_layout_put(GTK_LAYOUT(layout), buttonGuardarMicroprograma, 70, 450);

	gtk_box_pack_start(GTK_BOX(hbox),vbox1,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(hbox),vbox3,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(hbox),layout,1,1,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(hbox),vbox2,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */

	gtk_container_add(GTK_CONTAINER(window2), hbox);
	gtk_widget_set_size_request(window2,600,600);/* Tamaño de la ventana: x, y*/
	gtk_window_set_title(GTK_WINDOW(window2),"Microprogramacion");/* Nombre de la ventana*/
	gtk_widget_show_all(window2);/* Para mostrar la ventana y sus componentes (window tiene los componentes)*/
}
static void open_interrupt(GtkWidget* button, gpointer window)
{
	GtkWidget *dialog,*label,*content_area;
	dialog = gtk_dialog_new_with_buttons("¡Interrupcion!",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

	label = gtk_label_new("¡Se esta atendiendo una interrupcion!");
	gtk_container_add (GTK_CONTAINER (content_area), label);
	/*gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)),label,0,0,0);*/
	gtk_widget_show_all(dialog);
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	if(response == GTK_RESPONSE_OK)
		g_print("The OK is pressed");
	else
		g_print("The CANCEL was clicked");
	gtk_widget_destroy(dialog);
}
static void open_about(GtkWidget* button, gpointer window)
{
	GtkWidget *dialog,*label,*content_area;
	dialog = gtk_dialog_new_with_buttons("Acerca De Simulador Von Neumann",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

	label = gtk_label_new("\t\tINSITUTO TECNOLOGICO DE COSTA RICA\t\t\n\n\t\t\t    ESCUELA DE COMPUTACION\t\t\n\n\t\t           SIMULADOR VON NEUMANN\t\t\n\n\t\t       LENGUAJES DE PROGRAMACION\t\t\n\n\n Profesor: Kirstein Gätjens Soto \n\n\n Hecho Por:\n\n Andres Arriaga Lizano,\n Gerald Morales Alvarado \n\n\n Fecha de Creacion:\n\n 14/10/2017");
	gtk_container_add (GTK_CONTAINER (content_area), label);

	gtk_widget_show_all(dialog);
	gint response = gtk_dialog_run(GTK_DIALOG(dialog));
	if(response == GTK_RESPONSE_OK)
		g_print("The OK is pressed");
	else
		g_print("The CANCEL was clicked");
	gtk_widget_destroy(dialog);
}
static void exec_asm(GtkWidget* button, gpointer data)
{
	char *text = gtk_entry_get_text(GTK_ENTRY(data));
	leerASM(text);
	printf("%s\n", "all good");
}
int main(int argc, char* argv[]){

	gtk_init(&argc,&argv); /* Iniciar gtk*/
	GtkWidget* window,*buttonExec,*entryASM,*buttonAbout,*windowInterrupcion,*buttonInterrupt,*layout,*limit,*cable,*labelUC,*labelIR,*labelPC,*labelRT,*labelFLAGS,*labelALU,*labelB1,*labelB2,*labelB3,*labelB4,*labelMAR,*labelMBR,*buttonUC,*buttonBUS,*buttonPC,*buttonIR,*buttonRT,*buttonFLAGS,*buttonALU,*buttonB1,*buttonB2,*buttonB3,*buttonB4,*buttonMAR,*buttonMBR,*buttonPLAY,*buttonNEXT,*buttonINGRESARINSTRUCCIONASM,*table0,*table1,*table2,*table3,*table4,*table5,*table6,*table7,*table8,*vbox0,*vbox1,*vbox2,*vbox3,*hbox1,*hbox2,*hbox3;/* Declarar widgets como punteros a widget*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);/* Inicializa una ventana en el lado de arriba*/
	g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);	/* Apretar boton X para salir de la interfaz*/
	
	
	GdkColor color;

	gdk_color_parse ("blue", &color);

	entryASM = gtk_entry_new();
	buttonExec = gtk_button_new_with_mnemonic("_Ejecutar ASM");/* Inicializa un boton*/
    buttonAbout = gtk_button_new_with_mnemonic("_Acerca De");/* Inicializa un boton*/
    buttonInterrupt = gtk_button_new_with_mnemonic("_Generar Interrupcion");/* Inicializa un boton*/
    layout = gtk_layout_new(NULL, NULL);
    limit = gtk_image_new_from_file("limit.png");
	cable = gtk_image_new_from_file ("cable.png");
	table0 = gtk_table_new(2,2,0); /*rows, columns, homogenous*/
	table1 = gtk_table_new(2,2,0); /*rows, columns, homogenous*/
	table2 = gtk_table_new(2,2,0); /*rows, columns, homogenous*/
	table3 = gtk_table_new(2,2,0); /*rows, columns, homogenous*/
	table4 = gtk_table_new(2,2,0); /*rows, columns, homogenous*/
	table5 = gtk_table_new(3,4,0); /*rows, columns, homogenous -> para la ALU	*/
	table6 = gtk_table_new(2,2,0); /*rows, columns, homogenous -> para la ALU*/
	table7 = gtk_table_new(2,2,0); /*rows, columns, homogenous -> para la ALU*/
	buttonPC = gtk_button_new_with_mnemonic("_PC");/* Inicializa un boton*/
	buttonIR = gtk_button_new_with_mnemonic("_IR");/* Inicializa un boton*/
	buttonBUS = gtk_button_new_with_mnemonic("_BUS DE\nDATOS");/* Inicializa un boton*/
	buttonUC = gtk_button_new_with_label("UC");/* Inicializa un boton*/
	buttonRT = gtk_button_new_with_mnemonic("_RT");/* Inicializa un boton*/
	buttonFLAGS = gtk_button_new_with_mnemonic("_FLAGS");/* Inicializa un boton*/
	buttonALU = gtk_button_new_with_mnemonic("_ALU");/* Inicializa un boton*/
	buttonB1 = gtk_button_new_with_label("B1");/* Inicializa un boton*/
	buttonB2 = gtk_button_new_with_label("B2");/* Inicializa un boton*/
	buttonB3 = gtk_button_new_with_label("B3");/* Inicializa un boton*/
	buttonB4 = gtk_button_new_with_label("B4");/* Inicializa un boton*/
	buttonMAR = gtk_button_new_with_mnemonic("_MAR");/* Inicializa un boton*/
	buttonMBR = gtk_button_new_with_mnemonic("M_BR");/* Inicializa un boton*/
	buttonPLAY = gtk_button_new_with_mnemonic("_PLAY");/* Inicializa un boton*/
	buttonNEXT = gtk_button_new_with_mnemonic("_>|");/* Inicializa un boton*/
	buttonINGRESARINSTRUCCIONASM = gtk_button_new_with_mnemonic("_Microprogramar Nueva Instruccion");/* Inicializa un boton*/
	labelPC = gtk_label_new(" Program    Counter ");/* Inicializa un label*/
	labelUC = gtk_label_new(" Unidad  de  Control");/* Inicializa un label*/
	labelIR = gtk_label_new("Instruction Register");/* Inicializa un label*/
	labelRT = gtk_label_new("Registros de Trabajo");/* Inicializa un label*/
	labelFLAGS = gtk_label_new("Flags");/* Inicializa un label*/
	labelALU = gtk_label_new("Arithmetic-Logic Unit");/* Inicializa un label*/
	labelMAR = gtk_label_new(" Mem  Address  Reg.");/* Inicializa un label*/
	labelMBR = gtk_label_new("  Mem   Buffer   Reg.");/* Inicializa un label*/
	hbox1 = gtk_hbox_new(0,0);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> main*/
	hbox2 = gtk_hbox_new(0,20);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> control panel*/
	hbox3 = gtk_hbox_new(0,20);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> control panel*/
	vbox0 = gtk_vbox_new(0,20);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> primera columna*/
	vbox1 = gtk_vbox_new(0,60);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> segunda columna*/
	vbox2 = gtk_vbox_new(0,20);/* 1er parametro: tamano homogeneo de componentes, 2do: espacio entre componentes -> tercera columna*/
	
	g_signal_connect(buttonUC,"clicked",G_CALLBACK(view_uc),window);
	g_signal_connect(buttonPC,"clicked",G_CALLBACK(view_pc),window);
	g_signal_connect(buttonIR,"clicked",G_CALLBACK(view_ir),window);
	g_signal_connect(buttonMAR,"clicked",G_CALLBACK(view_mar),window);
	g_signal_connect(buttonMBR,"clicked",G_CALLBACK(view_mbr),window);
	g_signal_connect(buttonRT,"clicked",G_CALLBACK(view_rt),window);
	g_signal_connect(buttonFLAGS,"clicked",G_CALLBACK(view_flags),window);
	g_signal_connect(buttonB1,"clicked",G_CALLBACK(view_b1),window);
	g_signal_connect(buttonB2,"clicked",G_CALLBACK(view_b2),window);
	g_signal_connect(buttonB3,"clicked",G_CALLBACK(view_b3),window);
	g_signal_connect(buttonB4,"clicked",G_CALLBACK(view_b4),window);
	g_signal_connect(buttonALU,"clicked",G_CALLBACK(view_alu),window);
	g_signal_connect(buttonINGRESARINSTRUCCIONASM,"clicked",G_CALLBACK(microprogramar),window);
	g_signal_connect(buttonInterrupt,"clicked",G_CALLBACK(open_interrupt),window);
	g_signal_connect(buttonAbout,"clicked",G_CALLBACK(open_about),window);
	g_signal_connect(buttonExec,"clicked",G_CALLBACK(exec_asm),entryASM);

    gtk_layout_put(GTK_LAYOUT(layout), entryASM, 200, 200);
    gtk_layout_put(GTK_LAYOUT(layout), buttonExec, 200, 250);
    gtk_layout_put(GTK_LAYOUT(layout), limit, 0, 0);
    gtk_layout_put(GTK_LAYOUT(layout), buttonINGRESARINSTRUCCIONASM, 10, 10);
    gtk_widget_set_size_request(buttonINGRESARINSTRUCCIONASM, 50, 40);
    gtk_layout_put(GTK_LAYOUT(layout), buttonInterrupt, 10, 100);
    gtk_layout_put(GTK_LAYOUT(layout), buttonAbout, 400, 0);


	gtk_widget_modify_bg (GTK_WIDGET(buttonUC), GTK_STATE_NORMAL, &color);
	/*gtk_button_set_always_show_image (GTK_BUTTON (buttonUC), TRUE);*/
	/*gtk_button_set_image (GTK_BUTTON (buttonUC), image);*/
	gtk_table_attach(GTK_TABLE(table0), labelUC, 0,1,0,1, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla*/
    gtk_table_attach(GTK_TABLE(table0), buttonUC, 0,1,1,2, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla*/
    gtk_table_attach(GTK_TABLE(table0), cable, 1,2,1,2, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla  */
    cable = gtk_image_new_from_file ("cable.png");  	
    gtk_table_attach(GTK_TABLE(table1), labelPC, 0,1,0,1, GTK_FILL,GTK_FILL, 0,0);/* Pega el label a la tabla*/
    gtk_table_attach(GTK_TABLE(table1), buttonPC, 0,1,1,2, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla	*/
    gtk_table_attach(GTK_TABLE(table1), cable, 1,2,1,2, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla   */ 	
    cable = gtk_image_new_from_file ("cable.png");
	gtk_table_attach(GTK_TABLE(table2), labelIR, 0,1,0,1, GTK_FILL,GTK_FILL, 0,0);/* Pega el label a la tabla*/
    gtk_table_attach(GTK_TABLE(table2), buttonIR, 0,1,1,2, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla*/
    gtk_table_attach(GTK_TABLE(table2), cable, 1,2,1,2, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla   */ 	
    cable = gtk_image_new_from_file ("cable.png");
	gtk_table_attach(GTK_TABLE(table3), labelRT, 1,2,0,1, GTK_FILL,GTK_FILL, 0,0);/* Pega el label a la tabla*/
    gtk_table_attach(GTK_TABLE(table3), buttonRT, 1,2,1,2, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla*/
    gtk_table_attach(GTK_TABLE(table3), cable, 0,1,1,2, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla  */
    cable = gtk_image_new_from_file ("cable.png");
	gtk_table_attach(GTK_TABLE(table4), labelFLAGS, 1,2,0,1, GTK_FILL,GTK_FILL, 0,0);/* Pega el label a la tabla*/
    gtk_table_attach(GTK_TABLE(table4), buttonFLAGS, 1,2,1,2, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla*/
    gtk_table_attach(GTK_TABLE(table4), cable, 0,1,1,2, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla */
    cable = gtk_image_new_from_file ("cable.png");
    gtk_table_attach(GTK_TABLE(table5), buttonB1, 1,2,0,1, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla*/
    gtk_table_attach(GTK_TABLE(table5), cable, 0,1,0,1, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla */
    cable = gtk_image_new_from_file ("cable.png");
    gtk_table_attach(GTK_TABLE(table5), buttonB2, 1,2,2,3, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla*/
    gtk_table_attach(GTK_TABLE(table5), cable, 0,1,2,3, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla */
	gtk_table_attach(GTK_TABLE(table5), labelALU, 2,3,0,1, GTK_FILL,GTK_FILL, 0,0);/* Pega el label a la tabla    */
    gtk_table_attach(GTK_TABLE(table5), buttonALU, 2,3,1,2, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla*/
    gtk_table_attach(GTK_TABLE(table5), buttonB3, 3,4,0,1, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla*/
    gtk_table_attach(GTK_TABLE(table5), buttonB4, 3,4,2,3, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla*/
	cable = gtk_image_new_from_file ("cable.png");
    gtk_table_attach(GTK_TABLE(table6), labelMAR, 0,1,0,1, GTK_FILL,GTK_FILL, 0,0);/* Pega el label a la tabla*/
    gtk_table_attach(GTK_TABLE(table6), buttonMAR, 0,1,1,2, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla	*/
    gtk_table_attach(GTK_TABLE(table6), cable, 1,2,1,2, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla   */
	cable = gtk_image_new_from_file ("cable.png");
    gtk_table_attach(GTK_TABLE(table7), labelMBR, 0,1,0,1, GTK_FILL,GTK_FILL, 0,0);/* Pega el label a la tabla*/
    gtk_table_attach(GTK_TABLE(table7), buttonMBR, 0,1,1,2, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla	*/
    gtk_table_attach(GTK_TABLE(table7), cable, 1,2,1,2, GTK_FILL, GTK_FILL, 0,0);/* Pega el boton a la tabla  */

	gtk_box_pack_start(GTK_BOX(hbox2),buttonPLAY,1,1,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(hbox2),buttonNEXT,1,1,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */

	gtk_box_pack_start(GTK_BOX(vbox0),table0,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox0),table2,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox0),table1,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox0),table6,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox0),table7,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),buttonBUS,1,1,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox1),hbox2,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),table3,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),table4,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(vbox2),table5,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */

	gtk_box_pack_start(GTK_BOX(hbox1),vbox0,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(hbox1),vbox1,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(hbox1),vbox2,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */

	gtk_box_pack_start(GTK_BOX(hbox3),hbox1,0,0,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */
	gtk_box_pack_start(GTK_BOX(hbox3),layout,1,1,0); /* Container, componente, Resizable, Fill, Espacio + gtk_vbox_new() */

    /*button = gtk_button_new_with_mnemonic("B_utton");*/
	/*label = gtk_label_new("Hello World");*/

    /*gtk_table2_attach(GTK_table2(table2), label, 0,1,1,2, GTK_FILL, GTK_FILL, 0,0);*/
    /*gtk_table2_attach(GTK_table2(table2), button, 1,2,1,2, GTK_FILL, GTK_FILL, 0,0);*/
    gtk_container_add(GTK_CONTAINER(window), hbox3);
	/*g_signal_connect(button,"clicked",G_CALLBACK(button_clicked),label);*/

	/*gtk_label_set_text(GTK_LABEL(label),"World Hello");*/
	
	/*gtk_container_add(GTK_CONTAINER(window),hbox);*/
	/*gtk_container_add(GTK_CONTAINER(window),label);*/

	gtk_widget_set_size_request(window,1200,400);/* Tamaño de la ventana: x, y*/
	gtk_window_set_title(GTK_WINDOW(window),"Simulador Von Neumann");/* Nombre de la ventana*/
	gtk_widget_show_all(window);/* Para mostrar la ventana y sus componentes (window tiene los componentes)*/
	gtk_main();	/* Ciclo infinito para correr la interfaz*/
	/*free(image);*/
	return 0;
}

/*

1. gsignal para ambos entries => ir haciendo el micro programa (validar con bd intermedio)
2. mostrar mi en ventana microprogramacion 
3. trabajar lo de Edit ASM

BD<-PC
PC<-BD
BD<-IR
IR<-BD
BD<-MAR
MAR<-BD
BD<-MBR
MBR<-BD

Reg16<-BD

AX<-BD
BX<-BD
CX<-BD
DX<-BD

BD<-Reg16

BD<-AX
BD<-BX
BD<-CX
BD<-DX

Reg8<-BD

AH<-BD
AL<-BD
BH<-BD
BL<-BD
CH<-BD
CL<-BD
DH<-BD
DL<-BD

BD<-Reg8

BD<-AH
BD<-AL
BD<-BH
BD<-BL
BD<-CH
BD<-CL
BD<-DH
BD<-DL


B1<-BD
B2<-BD
BD<-B3
BD<-B4
ALU:add
ALU:sub
ALU:mul
ALU:div
ALU:and
ALU:or
ALU:xor
ALU:not
ALU:shr
ALU:shl
TEST:carry
TEST:sign
TEST:zero
TEST:interrupt
MEM:read
MEM:writ
In
Out

typedef struct{
	char programa[65365];
	char *nombre;
	char *nmonico;
	int numero;
}MicroprogramaTransfer;
MicroprogramaTransfer micprog;

*/