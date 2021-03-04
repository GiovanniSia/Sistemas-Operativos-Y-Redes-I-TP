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
