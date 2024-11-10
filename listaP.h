#ifndef LISTAP_H
#define LISTAP_H
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "partida.h"
#define MAX 100
#define MAX_NOMBRE 15

/*STRUCTS*/

typedef struct Nodo{
    persona vipd;
    struct Nodo *ps;
}Nodo;

typedef struct{
    Nodo *acc, *caux, *c;
}Lista;

/*PROTOTIPOS*/

void initLP(Lista *L);
void insertLP (Lista *L, persona p);
int supressLP (Lista *L, persona p);
persona copyLP (Lista *L);
void resetLP (Lista *L);
void forwareLP(Lista *L);
int isEmptyLP(Lista L);
int isFullLP(Lista L);
int isOssLP(Lista L);
void agregar_jugador(Lista* lista, persona p);

/*FUNCIONES*/
void initLP(Lista *L){
    L->acc = L->caux = L->c = NULL;
}
void insertLP(Lista *L, persona p){
    Nodo *N=(Nodo *)malloc(sizeof(Nodo));
    if (N == NULL) return; /*checkeo del malloc*/
    N->vipd = p;
    /*Para el primer elemento a insertar.*/
    if(L->acc == L->c){
        L->acc = N;
        N->ps = L->c;
        L->c = L->caux = N;
    }
    /*Para insertar elementos en el medio de una lista.*/
    else{
        L->caux->ps = N;
        N->ps = L->c;
        L->c = N;
    }
}
int supressLP(Lista *L, persona P){
    Nodo *N = NULL;
    L->caux = L->acc;
    /*Recorre la lista hasta encontrar la estructura de la persona a eliminar*/
    while ((L->caux != NULL) && (L->caux->vipd.jugador_nombre != P.jugador_nombre)){
        N = L->caux;
        L->caux = L->caux->ps;
    }

    /*Control para saber si se encontro el elemento.*/
    if(L->caux == NULL){
        return 1;
    }
    /*Si el elemento esta al pricipio*/
    if (L->caux == L->acc){
        L->acc = L->caux->ps;
    }
    /*Si el elemento a eliminar esta en el medio*/
    else{
        N->ps = L->caux->ps;
    }
    free((void*)L->caux);
    L->caux=N;
    return 0;
}
persona copyLP(Lista *L){
    return L->c->vipd;
}
void resetLP(Lista *L){
    L->c = L->acc;
    L->caux = NULL;
}
void forwardLP(Lista *L){
    if(L->c != NULL) {
        L->caux = L->c;
        L->c = L->c->ps;
    }

}
int isEmpty(Lista L){
    return (L.acc == NULL);
}
int isFull(Lista L){
    Nodo *N = (Nodo *)malloc(sizeof(Nodo));
    if (N==NULL){
        return 1;
    }else{
        return 0;
    }
}
int isOss(Lista L){
    if (L.c == NULL) return 0;
    else return 1;
}
void agregar_jugador(Lista* lista, persona p) {
    Nodo* nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo_nodo == NULL){
        return; /*control de malloc*/
    }

    strcpy(nuevo_nodo->vipd.jugador_nombre, p.jugador_nombre);
    nuevo_nodo->ps = NULL;

    if (lista->acc == NULL) {
        lista->acc = nuevo_nodo;
    } else {
        lista->c = lista->acc;
        while (lista->c->ps != NULL) {
            lista->c = lista->c->ps;
        }
        lista->c->ps = nuevo_nodo;
    }
}                                        //Que es nombre_archivo? pq lo pasa?
void guardar_jugadores(Lista* lista, const char* nombre_archivo, partida *p) {
    FILE *arch = fopen("jugadores.txt", "w");
    if (arch == NULL) {
        return;
    }

    Nodo* nodo_actual = lista->acc;
    while (nodo_actual != NULL) {
        fprintf(arch, "Nombre Jugador: %s\n", nodo_actual->vipd.jugador_nombre);
        fprintf(arch, "Nombre Avatar: %s\n", nodo_actual->vipd.jugador_nombre_avatar);

        fprintf(arch, "Palabra: %s\n", p->palabra);
        fprintf(arch, "Intentos: %d\n", p->intentos);
        fprintf(arch, "Puntaje: %d\n", calcular_puntaje(p, strlen(p->palabra)));
        fprintf(arch, "Aciertos: %d\n", letras_acert(p));
        fprintf(arch, "Tiempo de Finalizaci�n: %ld\n", (long)p->tiempo_finalizacion); // Convierte time_t a long

        fprintf(arch, "\n"); // Nueva l�nea para separar las entradas de cada jugador

        nodo_actual = nodo_actual->ps; // Mover al siguiente nodo
    }

    fclose(arch);
}
void liberar_lista(Lista* lista) {
    Nodo* nodo_actual = lista->acc;
    Nodo* nodo_siguiente;

    while (nodo_actual != NULL) {
        nodo_siguiente = nodo_actual->ps;
        free(nodo_actual);
        nodo_actual = nodo_siguiente;
    }

    lista->acc = NULL;
}
void cargar_al_archivo(Lista *l, const char *nombre_archivo, partida p){
    char fecha[20];
    float puntaje;
    int val;

    FILE *archivo = fopen(nombre_archivo,"r");
    if(archivo == NULL){
        return;
    }
    strftime(fecha,sizeof(fecha),"%d/%m/%Y %H:%M:%S",localtime(&p.tiempo_finalizacion));
    puntaje = calcular_puntaje(&p,0);

    rewind(archivo);
    val = getc(archivo);

    if(val == '\n'){
        fclose(archivo);
        archivo=fopen(nombre_archivo,"w");
        fprintf(archivo,"%s %s %s %.2f\n",p.jugador.jugador_nombre,p.jugador.jugador_nombre_avatar,fecha,puntaje);
        fclose(archivo);
        return;
    }

    fclose(archivo);
    archivo=fopen(nombre_archivo,"a");
    fprintf(archivo,"%s %s %s %.2f\n",p.jugador.jugador_nombre,p.jugador.jugador_nombre_avatar,fecha,puntaje);

    fclose(archivo);

}
void cargar_jugadores(Lista *l, const char *nomb){
    persona pe;
    float puntaje;
    char fecha[20];
    FILE *a = fopen(nomb,"r");
    if(a == NULL){
        return;
    }
    while(fscanf(a,"%s %s %s %s %f",pe.jugador_nombre,pe.jugador_nombre_avatar,fecha,fecha,&puntaje)==5){

        insertLP(l,pe);
    }
    fclose(a);
}

#endif // LISTAP_H
