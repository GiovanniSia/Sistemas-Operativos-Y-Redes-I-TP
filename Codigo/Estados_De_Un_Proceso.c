#include <stdio.h>
#include <limits.h>

int main() {

	int valor_max;

	printf("Digite un numero: ");
	scanf("%i",&valor_max);	
    
        ///////////////////////////////////////////////////////////////    
        //en este punto el proceso esta en Estado Bloqueado (S+ ó D)*//
        ///////////////////////////////////////////////////////////////

	int i=0; 
	
	while(i<valor_max){
		////////////////////////////////////////////////////////////    
        //en este punto el proceso esta en Estado de Ejecucion (R)//               
        ////////////////////////////////////////////////////////////    
		i++;	
	}
return 0; 
//////////////////////////////////////////////////////////
// en este punto el proceso está en Estado Terminado (T)//
//////////////////////////////////////////////////////////
}
/*
Compilar:
    gcc Estados_De_Un_Proceso.c -o Estados_De_Un_Proceso

Ejecutar:
    ./Estados_De_Un_Proceso

Ver Proceso con mas opciones y colores:
    htop

*/



