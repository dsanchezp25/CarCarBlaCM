/*
 * CarCarBla proyect by Daniel Sanchez Parra & Gonzalo Megias
 * Created by dsanchezp25 on 23/11/23.
*/
#include <iostream>
#include <vector>
#include <string>
#include "Grafo.h"
using namespace std;

const int MAX_CITIES = 20;
const int MAX_CITY_NAME = 15;

//aqui se ejecutan los metodos del grafo
void ejecucionGrafo(Grafo& g){
    g.Floyd();
    g.algoritmoKruskal();

    //	caminos minimos entre las ciudades
    g.caminosMinimos();

    //	kilometros de carretas que deben arreglarse
    g.kilometrosArreglados();

    /*
     * camino minimo entre cada par de ciudades de las
     * p cuestiones.
     * Solo considera carreteras arregladas
     */
    g.caminosArreglados();
}

int main(){

    Grafo G = *new Grafo(); //creamos el grafo G

    // Lectura del número de ciudades
    int n;
    cin >> n;

    // Validar el rango de ciudades
    if (n < 2 || n > MAX_CITIES) {

        cerr << "El número de ciudades debe estar entre 2 y " << MAX_CITIES << "." <<endl;
        return 1; // Código de error

    }

    // Lectura de los nombres de las ciudades
    vector<string> cities(n);

    for (int i = 0; i < n; ++i) {

        string city;
        cin >> city;

        //se comprueba que el nombre este dentro del rango de caracteres
        while (city.length() > MAX_CITY_NAME){

            cout << "Vuelve a introducir un nombre de como maximo" << MAX_CITY_NAME << endl;
            cin >> city;

        }

        cities[i] = city;

        //insertamos las ciudades en los vertices
        G.insertarVertice(cities[i]);

    }

    // Lectura del número de arcos
    int d;
    cin >> d;

    // Validar el numero de arcos
    if (d < 1 || d > (n*n)) {

        cerr << "El número de arcos debe estar entre 1 y " << n*n << "." <<endl;
        return 1; // Código de error

    }

    // Lectura de los arcos y distancias (no se almacenan en este ejemplo)
    for (int i = 0; i < d; ++i) {

        string city1, city2;
        float distance;

        //extrameos los datos de la linea
        cin >> city1 >> city2 >> distance;

        //insertamos los datos de distancias entre ciudades
        G.insertarArista(city1, city2, distance);

    }

    //Lectura de preguntas de caminos minimos
    int p;
    cin >> p;

    if(p < 1 || p > (n*n)){

        cerr << "El número de caminos minimos debe estar entre 1 y " << n*n << "." <<endl;
        return 1; // Código de error

    }

    G.setPreguntas(p);

    for(int i = 0; i < p; i++){

        string origen, destino;
        cin >> origen >> destino;

        //Da valor a los atributo origen y destino de la ruta
        G.setRutaGrafo(origen, destino,i);

    }

    //prioridades
    string prio;
    cin >> prio;

    //Lectura de la prioridad que da la Junta
    for (int i = 0; i < d; ++i) {

        string city1, city2;
        int prioridad;

        //extrameos los datos de la linea
        cin >> city1 >> city2 >> prioridad;

        //insertamos los datos de prioridad de la carreta entre las ciudades
        G.matrizPrioridad(city1, city2, prioridad);

        if(prioridad > G.getCantidadPrioridades())

            G.setCantidadPrioridades(prioridad);

    }

    //ejecutamos los metodos de los grafos
    ejecucionGrafo(G);

    return 0;
}
