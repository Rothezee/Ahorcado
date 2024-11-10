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
    float puntaje_letras[MAX_PALABRA]; /*Arreglo en donde cada posicion es 0 o 100/cant de letras, dependiendo si acerto esa letra*/
    int intentos;
    persona jugador;
    time_t tiempo_finalizacion;
}partida;

/*PROTOTIPOS*/

void init(partida *p);
void cargar_una_partida(partida *p);
void cargar_n_partidas(partida *p, int n); /*n es la cantidad de partidas que se desean cargar*/
void palabra_aleatoria(partida *p); /*Le asigna una palabra aleatoria de un archivo a partida.palabra*/
int insert_letra(partida *p, char letra); /*Ingresa una letra y comprueba si esta en la palabra*/
float calcular_puntaje(partida *p, int i); /*Funcion recursiva que calcula el puntaje*/
int escribirEnArchivo(char *texto); /*Escribe en el archivo la palabra que ingreso el usuario*/
int leer_partidas(const char *nombre, partida p[]); /*lee un archivo y guarda los datos en un arreglo*/
float calcular_puntaje_total(partida *p, const char *n); /*calcula el puntaje entre todos los juegos de un jugador*/
int borrar_partida (partida *);

/*GET y SET*/

void set_jugador_nombre(persona *p, char n[]);
char* get_jugador_nombre(persona p);
void set_jugador_nombre_avatar(persona *p, char n[]);
char* get_jugador_nombre_avatar(persona p);
void set_palabra(partida *p, char c[]);
char* get_palabra(partida p);
int get_intentos(partida p);
void set_intentos(partida *p, int n);
float get_puntaje(partida p);
void set_puntaje(partida *p, float pje);
int get_aciertos(partida p, int i);
void set_aciertos(partida *p, int i, int valor);
float get_puntajes_letras(partida p, int i);
void set_puntajes_letras(partida *p, int i, float valor);

/*FUNCIONES*/

void cargar_una_partida(partida *p) {

    FILE *F = fopen("PartidasG.txt", "a+");
    if (F == NULL) {
        return;
    }

    struct tm *tiempo_local = localtime(&(p->tiempo_finalizacion));

    fprintf(F, "Nombre %s - Avatar: %s - Palabra a adivinar: %s - Puntaje: %.2f - Fecha: %02d/%02d/%04d\n", p->jugador.jugador_nombre,
    p->jugador.jugador_nombre_avatar, p->palabra, calcular_puntaje(p,0), tiempo_local->tm_mday, tiempo_local->tm_mon + 1,
    tiempo_local->tm_year + 1900);

    fclose(F);

}


int borrar_partida(partida *p) {
    FILE *F = fopen("jugadores.txt", "r");
    if (F == NULL) {
        perror("No se pudo abrir el archivo jugadores.txt");
        return 1;
    }
    FILE *F_AUX = fopen("temp.txt", "w");
    if (F_AUX == NULL) {
        perror("No se pudo crear el archivo temporal");
        fclose(F);
        return 1;
    }

    char linea[256];
    int dia, mes, anio, encontrado = 0;
    char avatar[MAX_NOMBRE];
    char fecha_archivo[11];  /* Fecha en formato DD/MM/YYYY + \0 */
    char fecha_buscar[11];   /* Fecha en formato DD/MM/YYYY + \0 */

    /* Formatear la fecha de búsqueda */
    struct tm *fecha_eliminar = localtime(&(p->tiempo_finalizacion));
    snprintf(fecha_buscar, sizeof(fecha_buscar), "%02d/%02d/%04d", fecha_eliminar->tm_mday, fecha_eliminar->tm_mon + 1,
             fecha_eliminar->tm_year + 1900);

    while (fgets(linea, sizeof(linea), F)) {
        // Ajustar el formato para leer correctamente del archivo
        if (sscanf(linea, "%*s %s %d/%d/%d %*s %*f", avatar, &dia, &mes, &anio) == 4) {
            snprintf(fecha_archivo, sizeof(fecha_archivo), "%02d/%02d/%04d", dia, mes, anio);

            // Comparar el avatar y la fecha
            if (strcmp(avatar, p->jugador.jugador_nombre_avatar) == 0 &&
                strcmp(fecha_archivo, fecha_buscar) == 0) {
                encontrado = 1; // Se encontró la partida
                continue; // Saltar esta línea (eliminarla)
            }
        }
        fputs(linea, F_AUX); // Escribir la línea en el archivo temporal
    }

    fclose(F);
    fclose(F_AUX);

    if (encontrado == 1) {
        remove("jugadores.txt"); // Eliminar el archivo original
        rename("temp.txt", "jugadores.txt"); // Renombrar el archivo temporal
        return(1);
    } else {
        remove("temp.txt"); // Eliminar el archivo temporal si no se encontró la partida
        return(0);
    }
}
/*ESTE BLOQUE GUARDA LAS PALABRAS INGRESADAS POR EL USUARIO*/
int escribirEnArchivo(char *texto) { //devuelve 0 si se escribio en el archivo o 1 si ya esta cargada
    FILE *archivo;
    int ultimoNumero = 0;
    char palabra[MAX_PALABRA];

    archivo = fopen("precarga.txt", "r");
    if (archivo != NULL) {
        int numero;
        // Leer el archivo l�nea por l�nea
        while(fscanf(archivo,"%d %s",&numero,palabra)== 2){
            if(strcmp(strupr(palabra),strupr(texto)) == 0){ //Control para ver si la palabra ya existe en el archivo (pase las dos a mayusculas)
                fclose(archivo);
                return 1; //Si ya existe sale de la funcion
            }
        }
        ultimoNumero = numero;  // Actualizar el ultimo numero encontrado
        fclose(archivo);
    }

    int nuevoNumero = ultimoNumero + 1;

    archivo = fopen("precarga.txt", "a");
    if (archivo == NULL) {
        return 1;
    }

    fprintf(archivo,"%d %s\n", nuevoNumero, texto);
    fclose(archivo);
    return 0;
}
/*FIN DEL BLOQUE*/

void init(partida *p){
    int i=0;
    (*p).intentos = 6;
    for(i=0; i<MAX_PALABRA; i++){
        (*p).puntaje_letras[i]=0;
        (*p).palabra[i]='\0';
    }
    strncpy(p->palabra,"",MAX_NOMBRE-1);
}
int insert_letra(partida *p, char letra){
    int i=0, correct=0; //repetido=0;
    float puntos = 100.0 / strlen(p->palabra);
    for(i=0;i<strlen((*p).palabra);i++){
        if((((*p).palabra[i] == letra)||((*p).palabra[i] == letra+32)||((*p).palabra[i] == letra-32)) && (*p).puntaje_letras[i] == 0){/*Si la letra esta en la palabra y no fue acertada antes*/
                (*p).puntaje_letras[i] = puntos;
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
void palabra_aleatoria(partida *p) {
    FILE *file = fopen("precarga.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error al abrir el archivo de palabras.\n");
        strcpy(p->palabra, "No encontrado");
        return;
    }

    // Contar cuántas palabras hay en el archivo
    char buffer[MAX_PALABRA];
    int count = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }

    // Volver al inicio del archivo
    rewind(file);

    // Si no hay palabras, manejar el error
    if (count == 0) {
        fclose(file);
        strcpy(p->palabra, "No encontrado");
        return;
    }

    // Crear un arreglo para almacenar las palabras
    char **palabras = malloc(count * sizeof(char *));
    if (palabras == NULL) {
        fprintf(stderr, "Error al asignar memoria.\n");
        fclose(file);
        return;
    }

    // Leer las palabras en el arreglo
    int i = 0;
    int numero;
    while (fscanf(file, "%d %s", &numero, buffer) == 2 && i < count) {
        // Eliminar el salto de línea
        buffer[strcspn(buffer, "\n")] = 0; // Esto es redundante aquí, ya que fscanf no lo incluye
        palabras[i] = malloc((strlen(buffer) + 1) * sizeof(char));
        if (palabras[i] == NULL) {
            fprintf(stderr, "Error al asignar memoria para la palabra.\n");
            // Liberar memoria previamente asignada
            for (int j = 0; j < i; j++) {
                free(palabras[j]);
            }
            free(palabras);
            fclose(file);
            return;
        }
        strcpy(palabras[i], buffer);
        i++;
    }

    // Cerrar el archivo
    fclose(file);

    // Generar un índice aleatorio
    srand(time(NULL));
    int random_index = rand() % count;

    // Asignar la palabra aleatoria a la partida
    strcpy(p->palabra, palabras[random_index]);

    // Liberar la memoria
    for (int j = 0; j < count; j++) {
        free(palabras[j]);
    }
    free(palabras);
}

float calcular_puntaje(partida *p, int i){
    if (i > strlen((*p).palabra)) {
        return 0.0;
    }
    return (calcular_puntaje(p, i + 1) + (*p).puntaje_letras[i]);
}
int letras_acert(partida *p){
    int i=0, letras_acertadas=0;
    for(i=0;i<strlen(get_palabra(*p));i++){
        if((*p).puntaje_letras[i]>0){
            letras_acertadas++;
        }
    }
    return(letras_acertadas);
}
int leer_partidas(const char *nombre, partida p[]){
    FILE *archivo = fopen(nombre,"r");
    char fecha[20];
    int i = 0,j,flag;
    if(archivo == NULL){
        return 1;
    }
    while(fscanf(archivo,"%s %s %s %s %f\n",p[i].jugador.jugador_nombre,p[i].jugador.jugador_nombre_avatar,fecha,fecha,&p[i].puntaje_letras[0]) == 5){
        struct tm t;
        flag=0;
        if (sscanf(fecha, "%d-%d-%d %d:%d:%d", &t.tm_year, &t.tm_mon, &t.tm_mday, &t.tm_hour, &t.tm_min, &t.tm_sec) == 6) {
            t.tm_year -= 1900;  // Ajuste para tm_year (es años desde 1900)
            t.tm_mon -= 1;      // Ajuste para tm_mon (es 0-indexado)
            p[i].tiempo_finalizacion = mktime(&t);  // Convertir a time_t
        }
        for(j=0;j<i;j++){
            if(strcmp(p[i].jugador.jugador_nombre_avatar,p[j].jugador.jugador_nombre_avatar) == 0){ /*Si ya hay un avatar con ese nombre se suman los puntajes (serian la misma persona)*/
                p[j].puntaje_letras[0] += p[i].puntaje_letras[0];
                flag=1;
            }
        }
        if(flag==0){
            i++;
        }
    }
    fclose(archivo);
    return i;
}
int tamanio_archivo(const char *nombre, partida p[], char avatar[]){
    FILE *archivo = fopen(nombre,"r");
    char fecha[20];
    int i = 0;
    if(archivo == NULL){
        return 1;
    }
    while(fscanf(archivo,"%s %s %s %s %f\n",p[i].jugador.jugador_nombre,p[i].jugador.jugador_nombre_avatar,fecha,fecha,&p[i].puntaje_letras[0]) == 5){
        struct tm t;
        if (sscanf(fecha, "%d-%d-%d %d:%d:%d", &t.tm_year, &t.tm_mon, &t.tm_mday, &t.tm_hour, &t.tm_min, &t.tm_sec) == 6) {
            t.tm_year -= 1900;  // Ajuste para tm_year (es años desde 1900)
            t.tm_mon -= 1;      // Ajuste para tm_mon (es 0-indexado)
            p[i].tiempo_finalizacion = mktime(&t);  // Convertir a time_t
        }
        if(strcmp(p[i].jugador.jugador_nombre_avatar, avatar) == 0){
            i++;
        }
    }
    fclose(archivo);
    return i;
}
float calcular_puntaje_total(partida *p, const char *n){
    FILE *archivo = fopen(n,"r");
    char nombre[MAX_NOMBRE];
    float total = 0, e;
    if(archivo == NULL){
        return 1;
    }
    while(fscanf(archivo,"%*s %s %*s %*s %f\n",nombre, &e) == 2){
        if(strcmp(p->jugador.jugador_nombre_avatar,nombre)==0){
            total = total + e;
        }
    }
    fclose(archivo);
    return total;

}

/*GET y SET*/
void set_jugador_nombre(persona *p, char n[]){
    strcpy(p->jugador_nombre,n);
}
char* get_jugador_nombre(persona p){
    char *n;
    n=(char *)malloc(strlen(p.jugador_nombre)+1);
    if(n==NULL) exit(1);
    else{
        strcpy(n,p.jugador_nombre);
        return n;
    }
}
void set_jugador_nombre_avatar(persona *p, char n[]){
    strcpy(p->jugador_nombre_avatar,n);
}
char* get_jugador_nombre_avatar(persona p){
    char *n = (char*)malloc(strlen(p.jugador_nombre_avatar)+1);
    if(n==NULL) exit(1);
    else{
        strcpy(n,p.jugador_nombre_avatar);
        return n;
    }
}
void set_palabra(partida *p, char c[]){
    strncpy(p->palabra,c,MAX_NOMBRE-1);
}
char* get_palabra(partida p){
    char *n = (char*)malloc(strlen(p.palabra)+1);
    if(n==NULL) exit(1);
    else{
        strcpy(n,p.palabra);
        return n;
    }
}
int get_intentos(partida p){
    return p.intentos;
}
void set_intentos(partida *p, int n){
    p->intentos = n;
}
float get_puntajes_letras(partida p, int i){
    if(i >= 0 && i < MAX_PALABRA){
        return p.puntaje_letras[i];
    }else return -1;
}
void set_puntajes_letras(partida *p, int i, float valor){
    p->puntaje_letras[i] = valor;
}

#endif // PARTIDA_H_INCLUDED
