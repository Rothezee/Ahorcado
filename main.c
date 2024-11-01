#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partida.h"
#define MAX_DIBUJO 15


/*PROTOTIPOS*/
void menu_inicio();
void menu_jugar();
void menu_dentro_juego();
void dibujo_0();
void dibujo_1();
void dibujo_2();
void dibujo_3();
void dibujo_4();
void dibujo_5();
void dibujo_6();

/*MAIN*/
int main()
{
    int op=0, i=0;
    char l;
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

                /*Dibujo de ahorcado inicial y espacios para las letras*/
                dibujo_0();
                printf("\t");
                for(i=0;i<strlen((*p).palabra);i++){
                    printf("_");
                }
                printf("\n");
                printf("\t%s", (*p).palabra);

                /*Bucle dentro de la partida*/
                while((*p).intentos!=0){
                    printf("\n\t\tIngrese la letra: ");
                    scanf("%c", &l); getchar();
                    /*control de l*/
                    if(insert_letra(p, l)==0){
                        printf("\n\tPifiaste! Intentos restantes: %d\n\tPuntuacion: %d", (*p).intentos, (*p).puntaje);
                    }else{
                        if(insert_letra(&p, l)==1){
                        printf("la letra es correcta! : %c", l);
                        }else{
                            printf("\nError!!!!!!!!\n");
                        }
                    }
                }
                break;

            case 2:
                /*tabla_de_puntuacion();*/
                break;

            case 3:
                printf("\n\t\tOprima cualquier letra para salir!\n");
        }
    }while(op!=3);
    return 0;
}

/*FUNCIONES*/
void menu_inicio(){
    printf("\n\t\tBienvenido al juego del Ahorcado!\n");
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
void dibujo_0(){
    system("cls");
    printf("\n\t+----+   \n");
    printf("\n\t|        \n");
    printf("\n\t|        \n");
    printf("\n\t|        \n");
    printf("\n\t=======  \n\n");
}
void dibujo_1(){
    system("cls");
    printf("\n\t+----+   \n");
    printf("\n\t|    O   \n");
    printf("\n\t|        \n");
    printf("\n\t|        \n");
    printf("\n\t=======  \n\n");
}
void dibujo_2(){
    system("cls");
    printf("\n\t+----+   \n");
    printf("\n\t|    O   \n");
    printf("\n\t|    |   \n");
    printf("\n\t|        \n");
    printf("\n\t=======  \n\n");
}
void dibujo_3(){
    system("cls");
    printf("\n\t+----+   \n");
    printf("\n\t|    O   \n");
    printf("\n\t|   /|   \n");
    printf("\n\t|        \n");
    printf("\n\t=======  \n\n");
}
void dibujo_4(){
    system("cls");
    printf("\n\t+----+   \n");
    printf("\n\t|    O   \n");
    printf("\n\t|   /|\  \n");
    printf("\n\t|        \n");
    printf("\n\t=======  \n\n");
}
void dibujo_5(){
    system("cls");
    printf("\n\t+----+   \n");
    printf("\n\t|    O   \n");
    printf("\n\t|   /|\  \n");
    printf("\n\t|   /    \n");
    printf("\n\t=======  \n\n");
}
void dibujo_6(){
    system("cls");
    printf("\n\t+----+   \n");
    printf("\n\t|    O   \n");
    printf("\n\t|   /|\  \n");
    printf("\n\t|   / \  \n");
    printf("\n\t=======  \n\n");
}


