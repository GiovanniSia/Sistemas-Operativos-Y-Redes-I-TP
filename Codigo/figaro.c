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
sem_t s22;
sem_t s33;
sem_t s44;
sem_t s6;

/*Funciones*/
void* Thread1(){
	printf(" Fiiiigaro");

	/*Thread 2*/
	sem_post(&s2);

	/*Thread 3*/
	sem_post(&s3);

	/*Thread 4*/
	sem_post(&s4);

	pthread_exit(0);
}

void* Thread2(){
	sem_wait(&s2);
	printf("\n Figaro");
	sem_post(&s22);
	pthread_exit(0);
}

void* Thread3(){
	sem_wait(&s3);
	printf("\n Figaro");
	sem_post(&s33);
	pthread_exit(0);
}

void* Thread4(){
	sem_wait(&s4);
	printf("\n Figaro");
	sem_post(&s44);
	pthread_exit(0);
}

void* Thread5(){
	sem_wait(&s22);
	sem_wait(&s33);
	sem_wait(&s44);	
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
	int valor;
	printf("Ingrese cuantas veces quiere repetir la opera: ");
	scanf("%i",&valor);	
	for (int i = 0; i < valor; ++i)
	{
	
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
}
	return 0;
}
