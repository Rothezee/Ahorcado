#ifndef PARTIDA_H_INCLUDED
#define PARTIDA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NOMBRE 15
#define MAX_PALABRA 20

/*STRUCTS*/
typedef struct{
    char jugador_nombre[MAX_NOMBRE];
    char jugador_nombre_avatar[MAX_NOMBRE];
}persona;
typedef struct{
    char palabra[MAX_PALABRA];
    int intentos;
    int puntaje;
    persona jugador;
}partida;

/*PROTOTIPOS*/
void init(partida *p);
void cargar_una_partida(partida *p);
void cargar_n_partidas(partida *p, int n); /*n es la cantidad de partidas que se desean cargar*/
void palabra_aleatoria(partida *p); /*Le asigna una palabra aleatoria de un archivo a partida.palabra*/
char insert_letra(partida *p, char l); /*Ingresa una letra y comprueba si está en la palabra*/

void init(partida *p){
    (*p).intentos = 5;
    (*p).puntaje = 0;
}

char insert_letra(partida *p, char l){
    int i=0;
    int tam=strlen((*p).palabra);
    for(i=0;i<tam;i++){
        if((*p).palabra[i] == l){
            (*p).puntaje = (*p).puntaje + 5;
            return(1);
        }else{
            (*p).intentos--;
            return(0);
        }
    }
}



#endif // PARTIDA_H_INCLUDED
