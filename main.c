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
    int op=0, i=0, letras_acertadas=0;
    char *letra=(char*)malloc(sizeof(char));
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

                /*Bucle dentro de la partida*/
                while((*p).intentos>=0){
                    /*switch((*p).intentos){
                        case 5: dibujo_0(); break;
                        case 4: dibujo_1(); break;
                        case 3: dibujo_2(); break;
                        case 2: dibujo_3(); break;
                        case 1: dibujo_4(); break;
                        case 0: dibujo_5(); break;
                    }*/
                    printf("\t");
                    for(i=0;i<strlen((*p).palabra);i++){
                        if((*p).aciertos[i]==1){
                            printf("%c", (*p).palabra[i]);
                        }else{
                            printf("_");
                        }
                    }

                    printf("\n\t\tIngrese la letra: ");
                    scanf("%c", letra); getchar();
                    /*control de l*/
                    if(insert_letra(p, letra)==0){
                        printf("\n\tPifiaste! Intentos restantes: %d\n\tPuntuacion: %d\n", (*p).intentos, (*p).puntaje);
                    }else{
                        if(insert_letra(p, letra)==1){
                            printf("\n\tLa letra es correcta! Intentos restantes: %d\n\tPuntuacion: %d\n", (*p).intentos, (*p).puntaje);
                        }else{
                            if(insert_letra(p, letra)==2){
                                printf("\n\tYa pusiste esa letra! Intentos restantes: %d\n\tPuntuacion: %d\n", (*p).intentos, (*p).puntaje);
                            }
                        }
                    }
                }

                for(i=0;i<strlen((*p).palabra);i++){
                    if((*p).aciertos[i]==1){
                        letras_acertadas++;
                    }
                }
                if(letras_acertadas==strlen((*p).palabra)){
                    dibujo_7();
                    printf("\n\tGanaste!!!\n");
                }else{
                    dibujo_6();
                    printf("\n\tPerdiste!\n");
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
    printf("\n\t|   /|\\  \n");
    printf("\n\t|        \n");
    printf("\n\t=======  \n\n");
}
void dibujo_5(){
    system("cls");
    printf("\n\t+----+   \n");
    printf("\n\t|    O   \n");
    printf("\n\t|   /|\\  \n");
    printf("\n\t|   /    \n");
    printf("\n\t=======  \n\n");
}
void dibujo_6(){
    system("cls");
    printf("\n\t+----+   \n");
    printf("\n\t|    O   \n");
    printf("\n\t|   /|\\  \n");
    printf("\n\t|   / \\  \n");
    printf("\n\t=======  \n\n");
}
void dibujo_7(){
    system("cls");
    printf("\n\t|   (ヅ)   \n");
    printf("\n\t|   /|\\  \n");
    printf("\n\t|   / \\  \n");
    printf("\n\t=======  \n\n");
}

