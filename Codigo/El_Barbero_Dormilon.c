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
			printf("Cliente: cof cof despierte señor \n");
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
