#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "partida.h"
#include "listaP.h"
#define MAX_DIBUJO 15
#define MAX_PARTIDAS 100


/*PROTOTIPOS*/
void menu_inicio();
void menu_jugar();
void menu_dentro_juego();
void menu_volver_a_jugar();
void dibujo();
void espacio_palabra();
int control(int, int, int);
void imprimir_fecha_formato(time_t tiempo);


/*MAIN*/
int main()
{
    int op=0, op_aux=0, i=0, j, letras_acertadas, cant_partidas;
    char letras_erradas[5],auxc[MAX_PALABRA+1], avatar_buscar[MAX_NOMBRE], fecha_Borrar[20];
    char *letra=(char*)malloc(sizeof(char));
    *letra = 'a';
    partida *p = (partida*)malloc(sizeof(partida));
    partida partidas[MAX_PARTIDAS], auxp;
    persona *persona_mostrar = (persona*)malloc(sizeof(persona));
    Lista *l = (Lista*)malloc(sizeof(Lista));
    initLP(l);
    cargar_jugadores(l,"jugadores.txt");

    do{
        /*Menu de opciones*/
        system("cls");
        menu_inicio();
        printf("\t");scanf("%d", &op); getchar();
        op=control(op, 1, 5); /*Control de opcion*/
        /*control de op*/

        switch(op){
            case 1:
                /*Informacin del jugador*/
                system("cls");
                printf("\n\tIngrese su nombre:\n\t");
                scanf("%s", p->jugador.jugador_nombre); getchar();
                while(strlen(p->jugador.jugador_nombre)>=MAX_NOMBRE){ /*Control tamanio de la palabra*/
                    printf("\n\t\tNombre demasiado largo! Ingrese otro!\n\t");
                    scanf("%s", p->jugador.jugador_nombre);getchar();
                }

                printf("\n\tIngrese su avatar:\n\t");
                scanf("%s", p->jugador.jugador_nombre_avatar); getchar();
                while(strlen(p->jugador.jugador_nombre_avatar)>=MAX_NOMBRE){ /*Control tamanio de la palabra*/
                    printf("\n\t\tNombre de avatar demasiado largo! Ingrese otro!\n\t");
                    scanf("%s", p->jugador.jugador_nombre_avatar);getchar();
                }
                op_aux = 0;
                while(isOss(*l) != 0 && op_aux != 1){

                    if((strcmp(copyLP(l).jugador_nombre_avatar,p->jugador.jugador_nombre_avatar) == 0)){ /*Validacion para que el avatar no se repita*/
                        printf("\n\tUsted es %s? [1]Si [2]No\n\t",copyLP(l).jugador_nombre);
                        scanf("%d",&op);getchar();
                        op=control(op, 1, 2); /*Control de opcion*/
                        if(op == 1){
                            op_aux = 1;
                            printf("\tBienvenido de vuelta!\n\tTu puntaje total es de %.2f\n",calcular_puntaje_total(p,"jugadores.txt"));
                            system("pause");

                        } else{
                            printf("\tEl nombre de avatar ya esta ocupado! Elige otro: ");
                            scanf("%s", p->jugador.jugador_nombre_avatar);getchar();
                            resetLP(l);
                            op_aux = 0;
                        }
                    }
                    forwardLP(l);
                }
                insertLP(l, p->jugador);
                *persona_mostrar = copyLP(l);
                /*Loop en donde es el mismo jugador*/
                do{
                    /*Inicializaci�n*/
                    init(p);
                    letras_acertadas=0;
                    for(i=0;i<6;i++){
                        letras_erradas[i]='\0';
                    }
                    system("cls");
                    menu_jugar();
                    printf("\t");scanf("%d", &op);
                    op =control(op, 1, 2); /*Control de opcion*/
                    /*Palabra aleatoria o una palabra ingresada*/
                    if(op==1){
                        system("cls");
                        palabra_aleatoria(p);
                    }else{
                        system("cls");
                        printf("\n\t\tQue palabra desea ingresar?\n");
                        printf("\t");scanf("%s", auxc);getchar();
                        while(strlen(auxc)>=MAX_PALABRA){ /*Control tamanio de la palabra*/
                            printf("\n\t\tPalabra demasiado larga! Ingrese otra!\n\t");
                            scanf("%s", auxc);getchar();
                        }
                        if(escribirEnArchivo(auxc) == 0){
                            printf("\tTodo listo!\n");
                        }else{
                            printf("\tLa palabra %s ya se encuentra cargada.\n",auxc);
                        }
                        set_palabra(p,auxc);
                        system("pause");
                    }
                    system("cls");
                    printf("\n\n\n");

                    /*Bucle dentro de la partida*/
                    while(get_intentos(*p)>0 && letras_acertadas<strlen(get_palabra(*p))){
                        /*Dibujo de ahorcado inicial y espacios para las letras*/
                        dibujo(get_intentos(*p));
                        /*Linea donde se mustra la plabra*/
                        espacio_palabra(*p);
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
                            printf("\n\tPifiaste! Intentos restantes: %d\n\tPuntuacion: %.2f\n", get_intentos(*p), calcular_puntaje(p,0));
                            letras_erradas[5 - get_intentos(*p)]=*letra;
                        }else{
                            printf("\n\tLa letra es correcta! Intentos restantes: %d\n\tPuntuacion: %.2f\n", get_intentos(*p), calcular_puntaje(p,0));
                        }
                        printf("\tLetras erradas: ");
                        for(i=0;i<5;i++){
                            printf("%c ", letras_erradas[i]);
                        }
                        letras_acertadas=letras_acert(p);
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
                    imprimir_fecha_formato(p->tiempo_finalizacion);
                    printf("\t Nombre del Jugador: %s \n\t  Avatar del Jugador: %s\n\t", persona_mostrar->jugador_nombre, persona_mostrar->jugador_nombre_avatar);
                    getchar();
                    system("cls");

                    cargar_al_archivo(l,"jugadores.txt",*p);
                    cargar_una_partida(p);

                    menu_volver_a_jugar();
                    scanf("%d", &op_aux); getchar();
                    op_aux=control(op_aux, 1, 2);

                }while(op_aux!=2);
                liberar_lista(l);
                break;

            case 2:
                /*tabla_de_puntuacion();*/
                system("cls");
                printf("\tPosicion\tNombre de Avatar\tPuntaje\n");
                cant_partidas = leer_partidas("jugadores.txt",partidas);
                for (i = 0; i < cant_partidas - 1; i++) { /*Ordena el arreglo del mayor puntaje al menor*/
                    for (j = i + 1; j < cant_partidas; j++) { /*Para tener acceso a la posicion i + 1*/
                        if (calcular_puntaje(&partidas[i], 0) < calcular_puntaje(&partidas[j], 0)) { /* Si lo que esta en la posicion i es menor a lo que esta en j entonces se intercambian*/
                            auxp = partidas[i];
                            partidas[i] = partidas[j]; /*Queda el mayor valor primero*/
                            partidas[j] = auxp;
                        }
                    }
                }
                for(i=0; i<cant_partidas; i++){
                    printf("\t%d\t\t%s\t\t\t%.2f\n",i+1,partidas[i].jugador.jugador_nombre_avatar,calcular_puntaje(&partidas[i],0));
                }
                system("pause");
                break;

            case 3:
                system("cls");
                    system("cls");
                    printf("\n\tIngrese el nombre del avatar del jugador: ");
                    scanf("%s", avatar_buscar);getchar();
                    if((cant_partidas = tamanio_archivo("jugadores.txt", partidas, avatar_buscar)) > 0 ){
                        printf("\t\tPuntaje\n", avatar_buscar);
                        for (i = 0; i < cant_partidas - 1; i++) { /*Ordena el arreglo del mayor puntaje al menor*/
                            for (j = i + 1; j < cant_partidas; j++) { /*Para tener acceso a la posicion i + 1*/
                                if (calcular_puntaje(&partidas[i], 0) < calcular_puntaje(&partidas[j], 0)) { /* Si lo que esta en la posicion i es menor a lo que esta en j entonces se intercambian*/
                                    auxp = partidas[i];
                                    partidas[i] = partidas[j]; /*Queda el mayor valor primero*/
                                    partidas[j] = auxp;
                                }
                            }
                        }
                        for(i=0; i<cant_partidas; i++){
                            printf("\t%d\t\t%s\t\t\t%.2f\n",i+1,partidas[i].jugador.jugador_nombre_avatar,calcular_puntaje(&partidas[i],0));
                        }
                    }else{
                        printf("\n\tNo se encontro al avatar %s\n", avatar_buscar);
                    }

                //}

                //fclose(arc);
                system("pause");
                break;

            case 4:
                    system("cls");
                    printf("\n\tIngrese el nombre del avatar del jugador: ");
                    scanf("%s", avatar_buscar);getchar();

                    /* Crea una partida temporal para la búsqueda*/
                    partida partida_borrar;
                    strcpy(partida_borrar.jugador.jugador_nombre_avatar, avatar_buscar);

                    printf("\n\tIngrese la fecha de la partida (DD/MM/YYYY): ");
                    scanf("%19[^\n]", fecha_Borrar);getchar();


                    /* Convierte la fecha ingresada a time_t*/
                    struct tm tm_fecha = {0};
                    if (sscanf(fecha_Borrar, "%d/%d/%d", &tm_fecha.tm_mday, &tm_fecha.tm_mon, &tm_fecha.tm_year) == 3){

                        tm_fecha.tm_year -= 1900;
                        tm_fecha.tm_mon -= 1;

                        partida_borrar.tiempo_finalizacion = mktime(&tm_fecha);
                        if(borrar_partida(&partida_borrar)==1){
                            printf("\n\tPartida eliminada exitosamente.\n");
                        }else{
                            printf("\n\tNo se encontro ninguna partida con ese avatar y fecha.\n");
                        }
                    }
                    else{

                        printf("\n\tError en el formato de fecha ingresado!\n");

                    }

                    system("pause");
                    break;

            case 5: printf("\n\t\tOprima cualquier letra para salir!\n");

        }

    }while(op!=5);
    free((void*)p);
    free((void*)letra);
    free((void*)l);
    free((void*)persona_mostrar);
    return 0;
}

/*FUNCIONES*/
void menu_inicio(){
    printf("\n\t\t\tBienvenido al juego del Ahorcado!\n");
    printf("\n\t\t\tSeleccione una opcion!\n");
    printf("\n\t[1] - Jugar\n");
    printf("\t[2] - Ver tabla de puntuacion\n");
    printf("\t[3] - Ver puntuacion de jugador\n");
    printf("\t[4] - Eliminar una partida\n");
    printf("\t[5] - Salir\n");
}
void menu_jugar(){
    printf("\n\t\tElija con que palabra desea jugar!\n");
    printf("\n\t[1] - Palabra aleatoria\n");
    printf("\t[2] - Ingresar una palabra\n");
}
void menu_volver_a_jugar(){
    printf("\n\t\tQuiere jugar otra partida?\n");
    printf("\n\t[1] - Si!\n");
    printf("\t[2] - No, muchas gracias por la oferta. \n");
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
void espacio_palabra(partida p){
    int i=0;
    printf("\t");
    for(i=0;i<strlen(p.palabra);i++){
        if(p.puntaje_letras[i]>0){
            printf("%c ", p.palabra[i]);
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
void imprimir_fecha_formato(time_t tiempo) {
    struct tm *tiempo_local = localtime(&tiempo);
    printf("%02d/%02d/%04d %02d:%02d:%02d\n",
        tiempo_local->tm_mday,
        tiempo_local->tm_mon + 1,
        tiempo_local->tm_year + 1900,
        tiempo_local->tm_hour,
        tiempo_local->tm_min,
        tiempo_local->tm_sec);
}

