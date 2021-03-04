# Sistemas-Operativos-Y-Redes-I-TP

En este trabajo, se realizaron varias actividades relacionadas con los temas vistos en la materia con el fin de reforzar los conocimientos adquiridos.
En primer lugar, se trabajó con el shell, y un supermenu, en el cual se fueron añadiendo funciones que facilitan la ejecución de diversas tareas, como por ejemplo: crear o borrar 100 carpetas dentro del sistema. Además, el supermenu contaba con la función de sincronizarse con Gitlab a través de un proyecto, en el cual se permite ver el estado del proyecto, y además subir archivos en el mismo.
Por otro lado, a través de un servidor Debian creado dentro de la universidad, con el software “Putty” se accedió al mismo con el fin de testear el supermenu y facilitar el uso del sistema operativo.
En segunda instancia, se creó un programa codificado en lenguaje C, el cual realiza operaciones aritméticas (suma), y operaciones de I/O (leer el input del usuario). Luego de hacer esto, se usó la herramienta htop, con la cual se pueden ver los estados por los que pasa el programa. 
En la siguiente captura de pantalla, se observa al proceso esperando un valor de entrada:
 

En esta otra imagen se observa al proceso en ejecución:
 

Por otro lado, se utilizó la herramienta web “Trello”, la cual permite organizar las tareas por realizar de forma sencilla y ordenada, clasificando las tareas según el estado en el que se encuentren (nuevo, listo para hacer, running, esperando y terminado).

 

En tercer término, se presentó un programa ya armado, en el cuál se pedía que se interpretara el output que devolvía el mismo, además de calcular cuantas veces se repetiría el String “¡Hola mundo!” para n veces. El análisis realizado es el siguiente:
⦁	Con i = 0, se creará un proceso A, y se imprimirá dos veces “¡Hola mundo!”, ya que el comando lo realizará el proceso padre y el A. 
⦁	Con i = 1, el proceso padre y el proceso A tendrán un nuevo proceso hijo cada uno, y luego los cuatro procesos imprimirán “¡Hola mundo!”.
⦁	Con i = 2, la cual es la última iteración, todos los procesos tendrán un hijo cada uno, quedando así ya ocho procesos en total, y cada uno imprimirá “¡Hola mundo!”.
Como conclusión de este seguimiento, sacamos que para n iteraciones se crearán 2^n procesos, y se imprimirá “2^n + 2^n – 1 + ... + 2^2 + 2^1” veces “¡Hola mundo!”.
El código anterior podría convertirse en una bomba fork en si el ciclo nunca termina, ya que de esta manera se crearían infinitos procesos, con un orden de 2^n, donde n va a ir a infinito.
Luego de realizar esto, se presentó el problema del barbero dormilón, el cuál consistía en una sincronización de procesos. Esto simulaba las siguientes situaciones:
⦁	La barbería consiste en dos habitaciones: la sala de espera con n sillas y la sala del barbero con una sola silla para cortar.
⦁	Cuando no hay clientes el barbero se pone a dormir.
⦁	Cuando el cliente llega, si la sala esta full se va (se pierde un cliente). Si hay lugar para esperar entonces ingresa, si el barbero está durmiendo lo despierta para que le corte el pelo, si el barbero está ocupado entonces el cliente espera en una silla.
Para simular esta situación, se implementó un programa escrito en C, el cual consistía en intercambiar entre los threads “barbero”, y “cliente”, usando las variables compartidas “cant_clientes”, que representa la cantidad de clientes que están en espera, y “cant_sillas”, el cual indica la cantidad de sillas disponibles dentro de la sala. Por otro lado, se utilizaron dos semáforos, uno para el barbero y otro para el cliente, los cuales permitían la ejecución de los hilos en el orden deseado, y además un mutex llamado “mi_mutex”, el cual cumplía la función de guardar la zona crítica de cada thread, con el fin de que no haya una inconsistencia en  los datos.
Por otro lado, se implementó en un programa el diálogo del barbero de Sevilla de la ópera de Gioachino Rossini. Esto se logró a través de threads, los cuales simbolizan cada verso del diálogo (“Fígaro”), y varios semáforos, los cuales se encargan de que el diálogo se muestre en el orden que se desea. El software imprime en pantalla el diálogo del barbero, además de repetirlo las veces que desee el usuario.
Por último, se comprobó el potencial del paralelismo a través de la evaluación del tiempo y velocidad de descarga de un archivo a través de dos métodos de descarga: Por un lado, se utilizó la “forma tradicional” a través de la herramienta wget, la cual descarga utilizando un único hilo; y por el otro, la herramienta axel, la cual descarga a través de múltiples hilos. 
Se compararon los tiempos de descarga de un archivo, el cual pesaba aproximadamente 300 MB, con las herramientas previamente mencionadas. Luego de realizar las mismas, se observó que la herramienta wget descarga con mayor velocidad que el axel, pero el axel a su vez, mientras más threads (hilos o procesos) le asignes, mayor velocidad de descarga va a tener. Por eso, cabe la posibilidad de que, si se realiza la misma comparación en una computadora con más recursos, la herramienta axel sobrepase a la de wget.
El tipo de paralelismo que emplea axel es el paralelismo de datos. Se descarta que sea a través del paralelismo de tareas, porque al ejecutarse la herramienta, en vez de utilizar procesos para diversas tareas independientes dentro de un mismo dato, se observa en la terminal que los procesos creados comparten la misma tarea de descargar partes distribuidas del elemento que se desea adquirir. 
A la hora de realizar estas actividades, se presentaron varios obstáculos, para los cuales se plantearon soluciones:
⦁	Hubo un problema al implementar los threads del barbero de Sevilla en orden, debido a que los hilos no se ejecutaban en paralelo y en el orden correcto. Para solucionar ese problema, se optó por utilizar un semáforo por cada thread, además de tres semáforos adicionales, los cuales cumplían con la función de restringir la ejecución del thread 5 hasta que se hayan ejecutado primero los threads 2, 3 y 4.
⦁	El principal problema que encontramos en este ejercicio fue que tomamos por hecho al principio que al final del ciclo, tendríamos solo 2^n veces “¡Hola mundo!”. Luego entendimos que en realidad tendríamos la suma de 2^n, 2^n – 1 ... 2^1, ya que por cada iteración se va imprimiendo el mensaje.
⦁	Surgió una dificultad a la hora de implementar el barbero dormilón, la cual era que el programa entraba en bucle. Esto se veía porque a la hora de imprimir en la terminal, se observaba que cada vez que el barbero cortaba el pelo, entraba un cliente infinitamente, por ende nunca se llenaba la sala, ni tampoco quedaba vacía. Debido a esto, se pensó y se implementó otro código que recibe un límite de clientes, y cuando se alcanza corta el ciclo. Pero tuvimos un problema, el cual consistía en que el proceso quedaba en “zombie”.

Código fuente
Supermenú
#!/bin/bash
#------------------------------------------------------
# PALETA DE COLORES
#------------------------------------------------------
#setaf para color de letras/setab: color de fondo
        red=`tput setaf 1`;
        green=`tput setaf 2`;
        blue=`tput setaf 4`;
        bg_blue=`tput setab 4`;
        reset=`tput sgr0`;
        bold=`tput setaf bold`;
#------------------------------------------------------
# TODO: Completar con su path
#------------------------------------------------------
proyectoActual=$(pwd);

#------------------------------------------------------
# DISPLAY MENU
#------------------------------------------------------
imprimir_menu () {
    imprimir_encabezado "\t  S  U  P  E  R  -  M  E  N U ";
    echo -e "\t\t El proyecto actual es:";
    echo -e "\t\t $proyectoActual";
    echo -e "\t\t";
    echo -e "\t\t Opciones:";
    echo "";
    echo -e "\t\t\t a.  Ver estado del proyecto";
    echo -e "\t\t\t b.  Guardar cambios";
    echo -e "\t\t\t c.  Actualizar repo";
    echo -e "\t\t\t f.  Abrir en terminal";
    echo -e "\t\t\t g.  Abrir en carpeta";
    echo -e "\t\t\t h.  Crear 100 carpetas";
    echo -e "\t\t\t i.  Borar las 100 carpetas";
    echo -e "\t\t\t j.  Estados de un Proceso";
    echo -e "\t\t\t k.  El barbero dormilon";
    echo -e "\t\t\t m.  La opera de Gioachino Rossini";
    echo -e "\t\t\t q.  Salir";
    echo "";
    echo -e "Escriba la opción y presione ENTER";
}

#------------------------------------------------------
# FUNCIONES AUXILIARES
#------------------------------------------------------
imprimir_encabezado () {
    clear;
    #Se le agrega formato a la fecha que muestra
    #Se agrega variable $USER para ver que usuario está       ejecutando
    echo -e "`date +"%d-%m-%Y %T" `\t\t\t\t\t USERNAME:$USER";
    echo "";
    #Se agregan colores a encabezado
    echo -e "\t\t ${bg_blue} ${red} ${bold}--------------------------------------\t${reset}";
    echo -e "\t\t ${bold}${bg_blue}${red}$1\t\t${reset}";
    echo -e "\t\t ${bg_blue}${red} ${bold} --------------------------------------\t${reset}";
    echo "";
}
esperar () {
    echo "";
    echo -e "Presione enter para continuar";
    read ENTER ;
}
malaEleccion () {
    echo -e "Selección Inválida ..." ;
}
decidir () {
        echo $1;
        while true; do
                echo "desea ejecutar? (s/n)";
                read respuesta;
                case $respuesta in
                        [Nn]* ) break;;
                        [Ss]* ) eval $1
                                break;;
                        * ) echo "Por favor tipear S/s ó N/n.";;
                esac
        done
}
#------------------------------------------------------
# FUNCIONES del MENU
#------------------------------------------------------
a_funcion () {
        imprimir_encabezado "\tOpción a.  Ver estado del proyecto";
        echo "---------------------------"
        echo "Somthing to commit?"
        decidir "cd $proyectoActual; git status";

        echo "---------------------------"
        echo "Incoming changes (need a pull)?"
   decidir "cd $proyectoActual; git fetch origin"
        decidir "cd $proyectoActual; git log HEAD..origin/master --oneline"
}
b_funcion () {
        git config --global user.name "Giovanni Sia"
        git config --global user.email "giovanni_sia@yahoo.com"
        imprimir_encabezado "\tOpción b.  Guardar cambios";
        git init
        git remote add origin https://gitlab.com/Giovanni_S/tp-1.git
        git push -u origin master
        decidir "cd $proyectoActual; git add -A";
        echo "Ingrese mensaje para el commit:";
        read mensaje;
        decidir "cd $proyectoActual; git commit -m \"$mensaje\"";
        decidir "cd $proyectoActual; git push";
}
c_funcion () {
        imprimir_encabezado "\tOpción c.  Actualizar repo";
        decidir "cd $proyectoActual; git pull";
}

f_funcion () {
        imprimir_encabezado "\tOpción f.  Abrir en terminal";
        decidir "cd $proyectoActual; xterm &";
}

g_funcion () {
        imprimir_encabezado "\tOpción g.  Abrir en carpeta";
        decidir "gnome-open $proyectoActual &";
}
#------------------------------------------------------
# TODO: Completar con el resto de ejercicios del TP, una funcion por cada item
#------------------------------------------------------
h_funcion () {
        imprimir_encabezado "\tOpción h.  Crear 100 carpetas";
        for i in {0..99}
                do
                        #Creo las carpetas
                        mkdir grupo$i
                        chmod 640 grupo$i
                done
}
i_funcion () {
        imprimir_encabezado "\tOpción i.  Borrar las 100 carpetas";
        for i in {0..99}
                do
                        cd $proyectoActual
                        rmdir grupo$i
				  done
}
j_funcion(){
        imprimir_encabezado "\tOpción j. Estados de un Proceso";
        ./Estados_De_Un_Proceso;
}
k_funcion(){
    imprimir_encabezado "\tOpción k. El barbero dormilon";
    ./El_Barbero_Dormilon
}
m_funcion(){
        imprimir_encabezado "\tOpción m. La opera de Gioachino Rossini";
        ./figaro;
}

#------------------------------------------------------
# LOGICA PRINCIPAL
#------------------------------------------------------
while  true
do
    # 1. mostrar el menu
    imprimir_menu;
    # 2. leer la opcion del usuario
    read opcion;
    case $opcion in
        a|A) a_funcion;;
        b|B) b_funcion;;
        c|C) c_funcion;;
        d|D) d_funcion;;
        e|E) e_funcion;;
        f|F) f_funcion;;
        g|G) g_funcion;;
        h|H) h_funcion;;
        i|I) i_funcion;;
        j|J) j_funcion;;
        k|K) k_funcion;;
        m|M) m_funcion;;
        q|Q) break;;
        *) malaEleccion;;
    esac
    esperar;
done

Estados de un Proceso
#include <stdio.h>
#include <limits.h>

int main() {

	int valor_max;

	printf("Digite un numero: ");
	scanf("%i",&valor_max);	
        ///////////////////////////////////////////////////////////////    
//*en este punto el proceso esta en Estado Bloqueado (S+D)/////        ///////////////////////////////////////////////////////////////

	int i=1; 
	while(i<=valor_max){

////////////////////////////////////////////////////////////    
//en este punto el proceso esta en Estado de Ejecucion (R)//                        ////////////////////////////////////////////////////////////    
		printf("%i.\n",i);	
		i++;	
	}
return 0;
 
//////////////////////////////////////////////////////////
//en este punto el proceso esta en Estado Terminado (T)///
//////////////////////////////////////////////////////////
}
/*
Compilar:
    gcc ejercicio2.c -o ejecutar

Ejecutar:
    ./ejecutar

Ver Proceso con mas opciones y colores:
    htop

*/
Exclusión Mutua: Barbero Dormilón
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdbool.h>

sem_t barberListo;
sem_t cliente; 
sem_t inicio;
pthread_mutex_t mi_mutex;
int cant_clientes;
int sillas;
bool barbero_durmiendo;

void* Cliente(){
	 while(true){
		sleep(0.000001);
		pthread_mutex_lock(&mi_mutex);
		 if (barbero_durmiendo && cant_clientes == 0){
			printf("Cliente: cof cof despierte seÃ±or \n");
			barbero_durmiendo = false;
			cant_clientes++;
			printf("...le indica como se quiere cortar...-\n");
			 pthread_mutex_unlock(&mi_mutex);
			sem_post(&cliente);
		}else{
			pthread_mutex_unlock(&mi_mutex);
			//Acceso exclusivo a cant_clientes
			pthread_mutex_lock(&mi_mutex);
			 if (cant_clientes <= sillas){
				cant_clientes++;
				printf("...llega un cliente y se sienta...\n");
				pthread_mutex_unlock(&mi_mutex);

				sem_wait(&barberListo);
				printf("Cliente: Ya me toca!!!");
				printf("...le indica como se quiere cortar...-\n");
				sem_post(&cliente);

			}else{
				//Se va si no hay lugar
				pthread_mutex_unlock(&mi_mutex);
				printf("Cliente(afuera): Esta re lleno, me vooy!!!\n");
			}
		}
	}
}

void* Barber(){
	 while(true){
		pthread_mutex_lock(&mi_mutex);
		if (cant_clientes == 0 && !barbero_durmiendo){
			barbero_durmiendo = true;
			printf("Barbero: ZZZZZ\n");
		}
		pthread_mutex_unlock(&mi_mutex);

		sem_wait(&cliente);

		pthread_mutex_lock(&mi_mutex);
		//Un cliente va a ser atendido
		cant_clientes--;
		pthread_mutex_unlock(&mi_mutex);

		printf("...XXXXXcortandoXXXXX...\n");
		sleep(1);
		printf("Barbero: Ya termine, quedaste divinx\n");
		//barbero esta libre
		printf("Barbero: SIGUIENTE!\n");
		sem_post(&barberListo);
	}
}

int main(){

	printf("Ingrese cuantas sillas hay: ");
	scanf("%i",&sillas);
	// agregue esto para ver que onda
	sem_init(&barberListo, 0,0);
	sem_init (&cliente, 0,0);
	//-------------------------------
	pthread_t p1;
	pthread_t p2;

	int rc;

	rc = pthread_create(&p1,NULL,&Barber,NULL);
	rc = pthread_create(&p2,NULL,&Cliente,NULL);

	if (rc){
	    printf("Error: no disponible creacion thread, %d \n", rc);
	    exit(-1);
	 }

    pthread_mutex_destroy(&mi_mutex);

    pthread_exit(NULL);
}

Otra implementación
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>

int sillas; 
int limite_clientes; 

sem_t barbero;
sem_t cliente;
pthread_mutex_t mi_mutex;

int cant_clientes=0;

//0 "Durmiendo", 1 "Cortando"
int estadoBarbero = 0; 


void* Cliente () {
    pthread_mutex_lock (&mi_mutex);
    if (cant_clientes < sillas) {
        cant_clientes++;
        if(estadoBarbero==0){
            printf ("Ejem, ejem...,cof, cof...\n");
            estadoBarbero=1;
        }else{
            printf("Leyendo una revista\n");
            sleep (0.1);
        }
        sem_post (&cliente);
        pthread_mutex_unlock (&mi_mutex);
        sem_wait (&barbero);
    }else {
        printf ("Chau Chau\n");
        pthread_mutex_unlock (&mi_mutex);
    }
}

void* Barbero () { 
    while (1) {
        sem_wait (&cliente);
        pthread_mutex_lock (&mi_mutex);
        if(cant_clientes==0){
            estadoBarbero=0;
            printf("ZZZZZ...\n");
        }else{  
            cant_clientes--;
            printf ("XXXXX\n");
            sleep (0.1);
        }
        sem_post (&barbero);
        pthread_mutex_unlock (&mi_mutex);
    }
    pthread_exit(NULL);
}

int main () {
    printf("Ingrese cuantas sillas hay: ");
    scanf("%i",&sillas);
    printf("Ingrese cuanta gente entrara: ");
    scanf("%i",&limite_clientes);



    pthread_mutex_init ( &mi_mutex, NULL);

    sem_init(&barbero,0,0);
    sem_init(&cliente,0,1);
    pthread_t t_barbero;
    pthread_t t_cliente[limite_clientes];
    
    //crea y lanzar ambos threads
    int rc;
    rc=pthread_create(&t_barbero,NULL,Barbero,NULL);

    for (int i=0;i<limite_clientes;i++){
        sleep(0.1);
        rc=pthread_create(&t_cliente[i],NULL,Cliente,NULL);
        if (rc){
            printf("Error:unable to create thread, %d \n", rc);
            exit(-1);
         }
    }
    
  
    
    pthread_mutex_destroy(&mi_mutex);
   
   pthread_exit(NULL);
    return(0);
}




Sincronización: Barbero de Sevilla
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>

/*Declaro el semaforo*/
sem_t s2;
sem_t s3;
sem_t s4;
sem_t s5;
sem_t s6;

int cont=0;

/*Funciones*/
void* Thread1(){
	printf(" Fiiiigaro");
	sem_post(&s2);
	sem_post(&s3);
	sem_post(&s4);
	pthread_exit(0);
}

void* Thread2(){
	sem_wait(&s2);
	printf("\n Figaro1");
	cont++;
	if(cont==3)
	{
		sem_post(&s5);
	}
	pthread_exit(0);
}


void* Thread3(){
	sem_wait(&s3);
	printf("\n Figaro2");
	cont++;
	if(cont==3){
		sem_post(&s5);
	}
	pthread_exit(0);
}

void* Thread4(){
	sem_wait(&s4);
	printf("\n Figaro3");
	cont++;
	if(cont==3){
		sem_post(&s5);
	}
	pthread_exit(0);
}

void* Thread5(){	
	sem_wait(&s5);
	printf("\n Figaro Fi");
	sem_post(&s6);
	pthread_exit(0);
}

void* Thread6(){
	sem_wait(&s6);
	printf("\n Figaro Fa \n");
	pthread_exit(0);
}

int main(){
	/*Creamos los threads*/
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	pthread_t t4;
	pthread_t t5;
	pthread_t t6;
	
	/*Asigno las funciones que utilizaran los threads*/

	pthread_create(&t1,NULL,Thread1,NULL);
	pthread_create(&t2,NULL,Thread2,NULL);
	pthread_create(&t3,NULL,Thread3,NULL);
	pthread_create(&t4,NULL,Thread4,NULL);
	pthread_create(&t5,NULL,Thread5,NULL);
	pthread_create(&t6,NULL,Thread6,NULL);

	/*Espero la salida de los threads*/
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	pthread_join(t4,NULL);
	pthread_join(t5,NULL);	
	pthread_join(t6,NULL);

	return 0;
}
