/*****************************************************************************************************************
    UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
    FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

    Computadoras y programacion.
    (c)
    Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
******************************************************************************************************************/

#include "stdafx.h"
#include <string.h>
#include "corrector.h"
#include <stdlib.h>
#include <ctype.h>
#define LONGITUD 32
char abecedario[LONGITUD + 6] = "abcdefghijklmnñopqrstuvwxyzáéíóú";

// Funciones públicas del proyecto
/*****************************************************************************************************************
    DICCIONARIO: Esta función crea el diccionario completo
    char * nombreArchivo : Nombre del archivo de donde se sacarán las palabras del diccionario
    char palabrasDiccionario[][TAMTOKEN] : Arreglo con las palabras completas del diccionario
    int frecuencias[] : Arreglo con el número de veces que aparecen las palabras en el diccionario
    int & numElementosDiccionario : Número de elementos en el diccionario
******************************************************************************************************************/
void Diccionario(char* nombreArchivo, char palabrasDiccionario[][TAMTOKEN], int frecuencias[], int& numElementosDiccionario)
{
    FILE* fp;
    numElementosDiccionario = 0;
    int i;
    char lectura, array[TAMTOKEN];
    for (i = 0; i < NUMPALABRAS; i++)
        frecuencias[i] = 0;

    fopen_s(&fp, nombreArchivo, "r");

    int contador = 0;
    char puntuacion[] = " \t\n\r.,;() ";

    if (fp == NULL)
        return;

    while ((lectura = fgetc(fp)) != EOF) {
        bool bandera = true;
        lectura = tolower(lectura);

        for (i = 0; i < strlen(puntuacion); i++)
            if (puntuacion[i] == lectura)
                bandera = false;

        if (contador < TAMTOKEN && bandera) {
            array[contador++] = lectura;
            continue;
        }
        else if (contador == 0)
            continue;
        else if (contador == 1 && bandera) {
            contador = 0;
            continue;
        }
        array[contador] = '\0';

       
            }
        }

        if (!bandera) {
            strcpy_s(palabrasDiccionario[numElementosDiccionario], array);
            frecuencias[numElementosDiccionario++]++;
        }
        contador = 0;
    }
    fclose(fp);

    for (int j = 0; j < numElementosDiccionario - 1; j++) {
        for (i = j + 1; i < numElementosDiccionario; i++) {
            if (strcmp(palabrasDiccionario[j], palabrasDiccionario[i]) > 0) {
                strcpy_s(array, palabrasDiccionario[j]);
                strcpy_s(palabrasDiccionario[j], palabrasDiccionario[i]);
                strcpy_s(palabrasDiccionario[i], array);
                contador = frecuencias[j];
                frecuencias[j] = frecuencias[i];
                frecuencias[i] = contador;
            }
        }
    }
}
/*****************************************************************************************************************
    ListaCandidatas: Esta función recupera desde el diccionario las palabras válidas y su peso
    Regresa las palabras ordenadas por su peso
    char palabrasClonadas[][TAMTOKEN] : Lista de palabras clonadas
    int numPalabrasClonadas : Número de palabras clonadas
    char palabrasDiccionario[][TAMTOKEN] : Lista de palabras del diccionario
    int frecuencias[] : Lista de las frecuencias de las palabras
    int numElementosDiccionario : Número de elementos en el diccionario
    char listaFinal[][TAMTOKEN] : Lista final de palabras a sugerir
    int pesos[] : Peso de las palabras en la lista final
    int & numPalabrasLista : Número de elementos en listaFinal
******************************************************************************************************************/
#include <stdbool.h>
#include <string.h>

void ListaCandidatas(
    char palabrasClonadas[][TAMTOKEN],
    int numPalabrasClonadas,
    char palabrasDiccionario[][TAMTOKEN],
    int frecuencias[],
    int numElementosDiccionario,
    char listaFinal[][TAMTOKEN],
    int pesos[],
    int* numPalabrasLista)
{
    *numPalabrasLista = 0;

    // Utilizar un arreglo de banderas para realizar un seguimiento de las palabras ya procesadas
    bool procesadas[numPalabrasClonadas];
    memset(procesadas, false, sizeof(procesadas));

    for (int i = 0; i < numPalabrasClonadas; ++i) {
        for (int j = 0; j < numElementosDiccionario; ++j) {
            if (strcmp(palabrasClonadas[i], palabrasDiccionario[j]) == 0 && !procesadas[i]) {
                strcpy(listaFinal[*numPalabrasLista], palabrasClonadas[i]);
                pesos[*numPalabrasLista] = frecuencias[j];
                (*numPalabrasLista)++;

                // Marcar la palabra clonada como procesada
                procesadas[i] = true;
            }
        }
    }

    // Ordenar la listaFinal por pesos en orden descendente
    for (int i = 0; i < *numPalabrasLista - 1; ++i) {
        for (int j = i + 1; j < *numPalabrasLista; ++j) {
            if (pesos[i] < pesos[j]) {
                // Intercambiar palabras y pesos
                char tempWord[TAMTOKEN];
                int tempWeight;

                strcpy(tempWord, listaFinal[i]);
                strcpy(listaFinal[i], listaFinal[j]);
                strcpy(listaFinal[j], tempWord);

                tempWeight = pesos[i];
                pesos[i] = pesos[j];
                pesos[j] = tempWeight;
            }
        }
    }
}



/*****************************************************************************************************************
    ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el método
    char * palabraOriginal : Palabra a clonar
    char palabrasClonadas[][TAMTOKEN] : Lista de palabras clonadas
    int & numPalabrasClonadas : Número de elementos en la lista
******************************************************************************************************************/
void ClonaPalabras(
    char* palabraOriginal,
    char palabrasClonadas[][TAMTOKEN],
    int& numPalabrasClonadas)
{
    char aux[TAMTOKEN];
    numPalabrasClonadas = 0;
    strcpy_s(aux, palabraOriginal);

    for (int i = 0; i < strlen(palabraOriginal); i++) {
        for (int j = 0; j < LONGITUD; j++) {
            aux[i] = abecedario[j];
            strcpy_s(palabrasClonadas[numPalabrasClonadas++], aux);
        }
        aux[i] = palabraOriginal[i];
    }

    int k;
    for (k = 1; k < strlen(palabraOriginal) + 1; k++) {
        aux[k] = palabraOriginal[k - 1];
    }
    aux[k] = '\0';

    for (int i = 0; i < strlen(palabraOriginal) + 1; i++) {
        for (int j = 0; j < LONGITUD; j++) {
            aux[i] = abecedario[j];
            strcpy_s(palabrasClonadas[numPalabrasClonadas++], aux);
        }
        aux[i] = palabraOriginal[i];
    }

    int indice = 0;
for (int i = 0; i < strlen(palabraOriginal) - 1; ++i) {
    strcpy(palabrasClonadas[indice++], palabraOriginal);
    palabraOriginal[i] = palabraOriginal[i + 1];
}
strcpy(palabrasClonadas[indice], palabraOriginal);
numPalabrasClonadas = indice + 1;

    for (int i = 0; i < strlen(palabraOriginal) - 1; i++) {
        aux[i] = palabraOriginal[i + 1];
        aux[i + 1] = palabraOriginal[i];
        strcpy_s(palabrasClonadas[numPalabrasClonadas++], aux);
        strcpy_s(aux, palabraOriginal);
    }
    strcpy_s(palabrasClonadas[numPalabrasClonadas++], palabraOriginal);

    for (int j = 0; j < numPalabrasClonadas - 1; j++) {
        for (int i = j + 1; i < numPalabrasClonadas; i++) {
            if (strcmp(palabrasClonadas[j], palabrasClonadas[i]) > 0) {
                strcpy_s(aux, palabrasClonadas[j]);
                strcpy_s(palabrasClonadas[j], palabrasClonadas[i]);
                strcpy_s(palabrasClonadas[i], aux);
            }
        }
    }
}

