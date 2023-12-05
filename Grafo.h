//
// Created by zoro on 5/12/23.
//

#ifndef CARCARBLACM_GRAFO_H
#define CARCARBLACM_GRAFO_H


#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
using namespace std;

static const int MAX = 20;
struct ruta{
    string origen; // origen de la ruta
    string destino; //origen del destino
    int numCiudades; // numero de ciudades que tiene la ruta
    //camino almacenara la ruta a seguir para obtener el camino
    vector<string>camino[MAX]; // vector que contiene las ciudades de la ruta
    float kilometros; // distancia/coste total de la ruta

    //constructor del struct
    ruta(string origen, string destino) :
            origen(origen),
            destino(destino),
            numCiudades(),
            camino(),
            kilometros()
    {}
};
class Grafo {
    int N; // numero de vertices
    string Cjtovertices[MAX]; // vector que contiene el conjunto de vertices
    float MatAdyacencia[MAX][MAX]; //fila(i) = origen, columna(j) = destino
    float MatFloyd [MAX][MAX];
    int MatP [MAX][MAX];
    int matPrioridad[MAX][MAX];
    float matCaminosMin[MAX][MAX];
    int preguntas; // cantidad de preguntas a leer
    vector<ruta>rutasGrafo; // vector de struct ruta
    int cantidadPrioridades; // cantidad de prioridades
    int matArreglados[MAX][MAX]; // matriz de caminos arreglados


public:

    //constructor de grafo
    /*PRE:
     *POST: inicializa las variables
     */
    Grafo();

    /*PRE: 0 < prio <= MAX
     *POST: inicializa el numero de prioridades del grafo
     */
    void setCantidadPrioridades(int maxPrio);

    /*PRE: 0 < prio <= MAX
     *POST: devuelve el numero de prioridades del grafo
     */
    int getCantidadPrioridades();

    /*PRE: string origen, destino y int i deben ser leidos correctamente
     *POST: modifican los valores origen y destino de la ruta i del vector rutasGrafo del grafo
     */
    void setRutaGrafo(string origen, string destino, int i);

    /*PRE: int prio debe ser leido correctamente
     *POST: inicializa el numero de preguntas sobre los caminos minimos
     */
    void setPreguntas(int prio);

    /*PRE:
     *POST: devuelve el numero de preguntas sobre los caminos minimos
     */
    int getPreguntas();

    /*PRE: que el conjunto de vertices no este lleno
     *POST: inserta la ciudad en el conjunto de vertices
     */
    void insertarVertice(string cad1);

    /*PRE: que existan las ciudades en el grafo
     *POST: inserta la distancia entre ciudades (coste) en la matriz de adyacencia, ademas, crea la matriz de adyacencia a partir del conjunto de vertices
     */
    void insertarArista(string cad1, string cad2, float coste);

    /*PRE: que exista el vertice
     *POST: busca la ciudad pasada por parametro en el conjunto de vertices
     */
    int buscarPosicion (string cad1);

    /*PRE: Matriz de adyacencia creada e inicializada
     *POST: crea la matriz de Floyd a partir de la matriz de adyacencia
     */
    void Floyd();

    /*PRE: Matriz de caminos minimos creado e inicializado
     *POST: crea la matriz de Floyd a partir de la matriz de caminos minimos
     */
    void floydCaminosMini();

    /*PRE: Matriz de Floyd creada e inicializada
     *POST: muestra la matriz de Floyd (camino de menor coste)
     */
    void Camino(int i, int j, ruta ruta);

    /*PRE: Matriz de caminos minimos creada e inicializada
     *POST: comprueba si hay camino entre dos vertices a partir de la matriz de caminos minimos
     */
    bool hayCamino(int i, int j);

    /*PRE:Matriz de adyacencia creada e inicializada
     *POST: muestra la matriz de adyacencia
     */
    void MostrarMatrizAdy();

    /*PRE: Matriz P creada e inicializada
     *POST: muestra la matriz P
     */
    void mostrarMatrizP();

    /*PRE: matriz de prioridad creada
     *POST: crea la matriz de prioridades
     */
    void matrizPrioridad(string cad1, string cad2, int prioridad);

    /*PRE: matriz de Floyd(con caminos minimos) creada e inicializada
     *POST: muestra los caminos minimos entre ciudades
     */
    void caminosMinimos();

    /*PRE:matriz de prioridad y de caminos minimos creadas e inicializadas
     *POST: muestra la cantidad minima de carreteras que deben arreglarse por prioridad
     */
    float kilometrosArreglados();

    /*PRE:
     *POST: guarda en una matriz los caminos minimos entre ciudades con carreteras arregladas
     */
    void caminosArreglados();

    /*PRE:
     *POST: guarda en una matriz los caminos monimos entre ciudades
     */
    void algoritmoKruskal();

    /*PRE: matriz de adyacencia creada e inicializada
     *POST: obtiene el arco menor de la matriz de adyacencia
     */
    float arcoMinimo (int &org, int &dst, int visitados[MAX]);

    /*PRE: matriz de prioridad creada e inicializada
     *POST: obtiene el arco menor de la matriz de prioridad
     */
    float arcoMinArreglado(int &org, int &dst, int visitados[MAX]);

    /*PRE: matriz de caminos minimos creada
     *POST: copia en la matriz de caminos minimos la matriz pasada por parametro
     */
    void copiarMatriz (float m[MAX][MAX]);

};



#endif //CARCARBLACM_GRAFO_H
