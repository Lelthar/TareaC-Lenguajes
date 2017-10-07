
#include <stdio.h>
#include "arquitectura_cpu.h"

ArquitecturaCPU nuevo1;
ArquitecturaCPU nuevo2;

int main(){
	nuevo2.bus_de_datos.entrada = 5;
	nuevo1.bus_de_datos.entrada = 3;
	printf("%d\n", nuevo1.bus_de_datos.entrada);
	printf("%d\n", nuevo2.bus_de_datos.entrada);
	return 0;
}

