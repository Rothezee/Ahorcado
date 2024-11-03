#ifndef PARTIDA_H_INCLUDED
#define PARTIDA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NOMBRE 15
#define MAX_PALABRA 20

/*STRUCTS*/
typedef struct{
    char jugador_nombre[MAX_NOMBRE];
    char jugador_nombre_avatar[MAX_NOMBRE];
}persona;
typedef struct{
    char palabra[MAX_PALABRA];
    int aciertos[MAX_PALABRA]; /*Arreglo en donde cada posición es 0 o 1, dependiendo si acertó esa letra*/
    int intentos;
    int puntaje;
    persona jugador;
    time_t tiempo_finalizacion;
}partida;

/*PROTOTIPOS*/
void init(partida *p);
void cargar_una_partida(partida *p);
void cargar_n_partidas(partida *p, int n); /*n es la cantidad de partidas que se desean cargar*/
void palabra_aleatoria(partida *p); /*Le asigna una palabra aleatoria de un archivo a partida.palabra*/
void escribirEnArchivo(const char *texto); /*Escribe en el archivo la palabra que ingreso el usuario*/
int insert_letra(partida *p, char letra); /*Ingresa una letra y comprueba si está en la palabra*/

void init(partida *p){
    int i=0;
    (*p).intentos = 5;
    (*p).puntaje = 0;
    for(i=0; i<MAX_PALABRA; i++){
        (*p).aciertos[i]=0;
    }
}

int insert_letra(partida *p, char letra){
    int i=0, correct=0; //repetido=0;
    for(i=0;i<strlen((*p).palabra);i++){
        if((((*p).palabra[i] == letra)||((*p).palabra[i] == letra+32)||((*p).palabra[i] == letra-32)) && (*p).aciertos[i] == 0){/*Si la letra está en la palabra y no fue acertada antes*/
                (*p).aciertos[i] = 1;
                (*p).puntaje = (*p).puntaje + 5;
                correct=1;
        }else{
            correct=correct+0;
        }
    }
    if(correct==0){
        (*p).intentos--;
        }
    return(correct);
}

/*ESTE BLOQUE GUARDA LAS PALABRAS INGRESADAS POR EL USUARIO*/
void escribirEnArchivo(const char *texto) {
    FILE *archivo;
    int ultimoNumero = 0;

    archivo = fopen("data.txt", "r");
    if (archivo != NULL) {
        int numero;
        // Leer el archivo línea por línea
        while (fscanf(archivo, "%d %*s", &numero) == 1) {
            ultimoNumero = numero;  // Actualizar el último número encontrado
        }
        fclose(archivo);
    }

    int nuevoNumero = ultimoNumero + 1;

    archivo = fopen("data.txt", "a");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    fprintf(archivo,"\n%d %s", nuevoNumero, texto);
    fclose(archivo);
}
/*FIN DEL BLOQUE*/


#endif // PARTIDA_H_INCLUDED
