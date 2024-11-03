#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "partida.h"
#define MAX_DIBUJO 15


/*PROTOTIPOS*/
void menu_inicio();
void menu_jugar();
void menu_dentro_juego();
void dibujo();
void espacio_palabra();
int control(int, int, int);
void imprimir_fecha_formato(time_t tiempo, int []);



/*MAIN*/
int main()
{
    int op=0, i=0, letras_acertadas;
    char letras_erradas[5];
    int datos_tiempo[6];
    char *letra=(char*)malloc(sizeof(char)),auxc[MAX_PALABRA+1];
    partida *p = (partida*)malloc(sizeof(partida));
    FILE *fp = (FILE*)malloc(sizeof(FILE));

    do{
        /*Menu de opciones*/
        init(p);
        letras_acertadas=0;
        system("cls");
        menu_inicio();
        printf("\t");scanf("%d", &op); getchar();
        op=control(op, 1, 3); /*Control de opcion*/
        /*control de op*/

        switch(op){
            case 1:
                system("cls");
                menu_jugar();
                printf("\t");scanf("%d", &op);
                op=control(op, 1, 2); /*Control de opcion*/
                /*Palabra aleatoria o una palabra ingresada*/
                if(op==1){
                    system("cls");
                    palabra_aleatoria(p);
                    //printf("La palabra es: %s \n",get_palabra(*p));
                    system("pause");
                }else{
                    system("cls");
                    printf("\n\t\tQue palabra desea ingresar?\n");
                    printf("\t");scanf("%s", auxc);getchar();
                    while(strlen(auxc)>=MAX_PALABRA){ /*Control tamanio de la palabra*/

                        printf("\n\t\tPalabra demasiado larga! Ingrese otra!\n\t");
                        scanf("%s", auxc);getchar();
                    }
                    set_palabra(p,auxc);
                }
                system("cls");
                printf("\n\n\n");

                /*Bucle dentro de la partida*/
                while(get_intentos(*p)>0 && letras_acertadas<strlen(get_palabra(*p))){

                /*Dibujo de ahorcado inicial y espacios para las letras*/
                    dibujo(get_intentos(*p));

                /*Linea donde se mustra la plabra*/
                    espacio_palabra(p);

                    /*Ingreso de caracter*/
                    printf("\n\n\t\tIngrese la letra: ");
                    scanf(" %c", letra); getchar(); /*Falta control de la letra ingresada*/

                    /*control de l*/
                    while((*letra<'A' || *letra>'Z')&&(*letra<'a' || *letra>'z')){
                        printf("\n\t\tCaracter invalido, ingrese la letra nuevamente: ");
                        scanf(" %c", letra); getchar();
                    }
                    system("cls");
                    if(insert_letra(p, *letra)==0){
                        printf("\n\tPifiaste! Intentos restantes: %d\n\tPuntuacion: %d\n", get_intentos(*p), calcular_puntaje(p,0));
                        letras_erradas[5 - get_intentos(*p)]=*letra;
                    }else{
                            printf("\n\tLa letra es correcta! Intentos restantes: %d\n\tPuntuacion: %d\n", get_intentos(*p), calcular_puntaje(p,0));
                    }
                    printf("\tLetras erradas: ");
                    for(i=0;i<5;i++){
                        printf("%c ", letras_erradas[i]);
                    }
                    letras_acertadas=0;
                    for(i=0;i<strlen(get_palabra(*p));i++){
                        if((*p).puntaje_letras[i]==5){
                            letras_acertadas++;
                        }
                    }
                }
                /*Mensaje al terminar la partida*/
                p->tiempo_finalizacion = time(NULL);
                if(letras_acertadas==strlen(get_palabra(*p))){
                    dibujo(8);
                    printf("\t%s", get_palabra(*p));
                    printf("\n\t\t\tGanaste!!!\n");

                }else{
                    printf("%c", *letra);
                    dibujo(7);
                    printf("\n\t\tLa palabra era: %s", get_palabra(*p));
                    printf("\n\t\t\tPerdiste!\n");

                }
                printf("\n\tFecha y hora de finalizacion: ");
                imprimir_fecha_formato(p->tiempo_finalizacion, &datos_tiempo);getchar();

                /*GUARDAR LA INFORMACIÓN DE LA PARTIDA*/
                fp = fopen("registro.txt", "w");
                if(fp==NULL){
                    printf("Error al abrir el archivo de registro");
                }
                fprintf(fp, "intentos:%d\tpuntos:%d\tFecha:%02d/%02d/%04d\tHora:%02d:%02d:%02d\n", /*get_jugador_nombre(p)*/ get_intentos(*p), letras_acertadas*5, datos_tiempo[0], datos_tiempo[1], datos_tiempo[2], datos_tiempo[3], datos_tiempo[4], datos_tiempo[5]);
                fclose(fp);



                break;

            case 2:
                /*tabla_de_puntuacion();*/
                break;

            case 3:
                printf("\n\t\tOprima cualquier letra para salir!\n");
        }
    }while(op!=3);
    free(p);
    free(letra);
    return 0;
}

/*FUNCIONES*/
void menu_inicio(){
    printf("\n\t\t\tBienvenido al juego del Ahorcado!\n");
    printf("\n\t\t\tSeleccione una opcion!\n");
    printf("\n\t[1] - Jugar\n");
    printf("\t[2] - Ver tabla de puntuacion\n");
    printf("\t[3] - Salir\n");
}
void menu_jugar(){
    printf("\n\t\tElija con que palabra desea jugar!\n");
    printf("\n\t[1] - Palabra aleatoria\n");
    printf("\t[2] - Ingresar una palabra\n");
}
void dibujo(int intentos){
    switch(intentos){

        case 6:
            printf("\n\n\t+----+   ");
            printf("\n\t|        ");
            printf("\n\t|        ");
            printf("\n\t|        ");
            printf("\n\t=======  \n");
            break;
        case 5:
            printf("\n\n\t+----+   ");
            printf("\n\t|    O   ");
            printf("\n\t|        ");
            printf("\n\t|        ");
            printf("\n\t=======  \n");
            break;
        case 4:
            printf("\n\n\t+----+   ");
            printf("\n\t|    O   ");
            printf("\n\t|    |   ");
            printf("\n\t|        ");
            printf("\n\t=======  \n");
            break;
        case 3:
            printf("\n\n\t+----+   ");
            printf("\n\t|    O   ");
            printf("\n\t|   /|   ");
            printf("\n\t|        ");
            printf("\n\t=======  \n");
            break;
        case 2:
            printf("\n\n\t+----+   ");
            printf("\n\t|    O   ");
            printf("\n\t|   /|\\ ");
            printf("\n\t|        ");
            printf("\n\t=======  \n");
            break;

        case 1:
            printf("\n\n\t+----+   ");
            printf("\n\t|    O   ");
            printf("\n\t|   /|\\ ");
            printf("\n\t|   /    ");
            printf("\n\t=======  \n");
            break;


        case 7:
            printf("\n\n\t+----+   ");
            printf("\n\t|    O   ");
            printf("\n\t|   /|\\ ");
            printf("\n\t|   / \\ ");
            printf("\n\t=======  \n");
            break;
        case 8:
            printf("\n\n\t   (^o^)  ");
            printf("\n\t    /|\\  ");
            printf("\n\t    / \\  ");
            printf("\n\t===========  \n");
            break;
    }
}
void espacio_palabra(partida *p){
    int i=0;
    printf("\t");
    for(i=0;i<strlen((*p).palabra);i++){
        if((*p).puntaje_letras[i]==5){
            printf("%c ", (*p).palabra[i]);
        }else{
            printf("_ ");
        }
    }
}
int control(int valor, int min, int max){
    while(valor<min || valor>max){
        printf("\n\t\tReingrese el valor!\n");
        printf("\t");scanf("%d", &valor); getchar();
    }
    return(valor);
}
void imprimir_fecha_formato(time_t tiempo, int datos_tiempo[]) {
    struct tm *tiempo_local = localtime(&tiempo);
    printf("%02d/%02d/%04d %02d:%02d:%02d\n",
        tiempo_local->tm_mday,
        tiempo_local->tm_mon + 1,
        tiempo_local->tm_year + 1900,
        tiempo_local->tm_hour,
        tiempo_local->tm_min,
        tiempo_local->tm_sec);
    datos_tiempo[6]=(tiempo_local->tm_mday, tiempo_local->tm_mon + 1,tiempo_local->tm_year + 1900,tiempo_local->tm_hour,tiempo_local->tm_min,tiempo_local->tm_sec);
    for(int i=0; i<6; i++){
        printf("%02d", datos_tiempo[i]);
    }
}
