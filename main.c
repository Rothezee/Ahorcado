#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partida.h"
#define MAX_DIBUJO 15


/*PROTOTIPOS*/
void menu_inicio();
void menu_jugar();

void dibujo();
void espacio_palabra();



/*MAIN*/
int main()
{
    int op=0, i=0, letras_acertadas=0;
    char *letra=(char*)malloc(sizeof(char));
    *letra = 'a';
    partida *p = (partida*)malloc(sizeof(partida));

    do{
        /*Menu de opciones*/
        init(p);
        menu_inicio();
        scanf("%d", &op); getchar();
        /*control de op*/

        switch(op){
            case 1:
                system("cls");
                menu_jugar();
                scanf("%d", &op);

                /*Palabra aleatoria o una palabra ingresada*/
                if(op==1){
                    //palabra_aleatoria(&p);
                }else{
                    system("cls");
                    printf("\n\t\tQue palabra desea ingresar?\n");
                    scanf("%s", (*p).palabra);
                }

                system("cls");
                printf("\n\n\n");
                /*Bucle dentro de la partida*/
                while((*p).intentos>=0 && letras_acertadas<strlen((*p).palabra)){

                    /*Dibujo de ahorcado inicial y espacios para las letras*/
                    dibujo((*p).intentos);

                    /*Linea donde se mustra la plabra*/
                    espacio_palabra(p);

                    /*Ingreso de caracter*/
                    printf("\n\t\tIngrese la letra: ");
                    scanf(" %c", letra); getchar();
                    /*control de l*/
                    system("cls");
                    if(insert_letra(p, *letra)==0){
                        printf("\n\tPifiaste! Intentos restantes: %d\n\tPuntuacion: %d\n", (*p).intentos, (*p).puntaje);
                    }else{
                            printf("\n\tLa letra es correcta! Intentos restantes: %d\n\tPuntuacion: %d\n", (*p).intentos, (*p).puntaje);
                    }
                    letras_acertadas=0;
                    for(i=0;i<strlen((*p).palabra);i++){
                        if((*p).aciertos[i]==1){
                            letras_acertadas++;
                        }
                    }
                }
                if(letras_acertadas==strlen((*p).palabra)){
                    dibujo(7);
                    printf("\t%s", (*p).palabra);
                    printf("\n\t\t\tGanaste!!!\n");
                    scanf("%c", &op);
                }else{
                    dibujo(6);
                    printf("\n\t\tLa palabra era: %s", (*p).palabra);
                    printf("\n\t\t\tPerdiste!\n");
                    scanf("%c", &op);
                }


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
    system("cls");
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
        case 5:
            printf("\n\t+----+   \n");
            printf("\n\t|        \n");
            printf("\n\t|        \n");
            printf("\n\t|        \n");
            printf("\n\t=======  \n\n");
            break;
        case 4:
            printf("\n\t+----+   \n");
            printf("\n\t|    O   \n");
            printf("\n\t|        \n");
            printf("\n\t|        \n");
            printf("\n\t=======  \n\n");
            break;
        case 3:
            printf("\n\t+----+   \n");
            printf("\n\t|    O   \n");
            printf("\n\t|    |   \n");
            printf("\n\t|        \n");
            printf("\n\t=======  \n\n");
            break;
        case 2:
            printf("\n\t+----+   \n");
            printf("\n\t|    O   \n");
            printf("\n\t|   /|   \n");
            printf("\n\t|        \n");
            printf("\n\t=======  \n\n");
            break;
        case 1:
            printf("\n\t+----+   \n");
            printf("\n\t|    O   \n");
            printf("\n\t|   /|\\  \n");
            printf("\n\t|        \n");
            printf("\n\t=======  \n\n");
            break;
        case 0:
            printf("\n\t+----+   \n");
            printf("\n\t|    O   \n");
            printf("\n\t|   /|\\  \n");
            printf("\n\t|   /    \n");
            printf("\n\t=======  \n\n");
            break;
        case 6:
            printf("\n\t+----+   \n");
            printf("\n\t|    O   \n");
            printf("\n\t|   /|\\  \n");
            printf("\n\t|   / \\  \n");
            printf("\n\t=======  \n\n");
            break;
        case 7:
            printf("\n\t|  (^o^)   \n");
            printf("\n\t|   /|\\  \n");
            printf("\n\t|   / \\  \n");
            printf("\n\t=======  \n\n");
            break;
    }
}
void espacio_palabra(partida *p){
    int i=0;
    printf("\t");
    for(i=0;i<strlen((*p).palabra);i++){
        if((*p).aciertos[i]==1){
            printf("%c", (*p).palabra[i]);
        }else{
            printf("_");
        }
    }
}
