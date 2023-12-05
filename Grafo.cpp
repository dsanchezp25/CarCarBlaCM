#include "Grafo.h"
#include <cfloat>

Grafo::Grafo(){
    N = 0;
    preguntas = 0;
    cantidadPrioridades = 0;

    for (int i=0; i<MAX; i++){
        for (int j=0; j<MAX; j++){
            MatAdyacencia[i][j]=0;
            MatFloyd[i][j]=0;
            MatP[i][j]=-1;
            matPrioridad[i][j] = 0;
        }

    }

}

void Grafo::setRutaGrafo(string origen, string destino, int i) {
    ruta nuevaRuta(origen, destino);
    rutasGrafo.push_back(nuevaRuta);
}

void Grafo::setPreguntas(int prio) {
    this->preguntas = prio;
}

void Grafo::setCantidadPrioridades(int maxPrio) {
    this->cantidadPrioridades = maxPrio;
}

int Grafo::getCantidadPrioridades() {
    return cantidadPrioridades;
}

int Grafo::getPreguntas() {
    return this->preguntas;
}
void Grafo::insertarVertice(string cad1){
    if(N == MAX){
        cout << "El grafo esta lleno. No se puden insertar mas vertices" << endl;
        return;
    }
    Cjtovertices[N]=cad1;
    N++;
}

int Grafo::buscarPosicion (string cad1){
    for(int i = 0; i < N; i++){
        if(Cjtovertices[i] == cad1)
            return i;
    }
    return -1; //no se ha encontrado el vertice en el array
}

void Grafo::insertarArista(string cad1, string cad2, float coste){
    //se buscan las ciuades en el conjunto de vertices y se obtienen los indices
    int pos1 = buscarPosicion(cad1);
    int pos2 = buscarPosicion(cad2);

    if(pos1 != -1 && pos2 != -1){
        MatAdyacencia[pos1][pos2] = coste;
        MatAdyacencia[pos2][pos1] = coste;
    }else
        cout << "Una o las dos ciudades no se encuentran en el grafo" << endl;
}

void Grafo::MostrarMatrizAdy(){
    for(int i = 0; i < N; i++){
        for (int j = 0; j < N; j++)
            cout << MatAdyacencia[i][j] << " ";
        cout << endl;
    }
}

void Grafo::Floyd(){
    // se inicializa MatFloyd con los valores de MatAdyacencia
    for(int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            MatFloyd[i][j] = MatAdyacencia[i][j];

    // Despues se aplica el algoritmo de Floyd
    for(int k = 1; k <= N; k++){
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                if(MatFloyd[i][k] + MatFloyd[k][j] < MatFloyd[i][j]){
                    MatFloyd[i][j] = MatFloyd[i][k] + MatFloyd[k][j];
                    MatP[i][j] = k; // k = vertice intermedio
                }
            }
        }
    }
}

void Grafo::floydCaminosMini(){
    // se inicializa MatFloyd con los valores de MatAdyacencia
    for(int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            MatFloyd[i][j] = matCaminosMin[i][j];

    // Despues se aplica el algoritmo de Floyd
    for(int k = 1; k <= N; k++){
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                if(MatFloyd[i][k] + MatFloyd[k][j] < MatFloyd[i][j]){
                    MatFloyd[i][j] = MatFloyd[i][k] + MatFloyd[k][j];
                    MatP[i][j] = k;// k = vertice intermedio
                }
            }
        }
    }
}

void Grafo::mostrarMatrizP() {
    for(int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cout << MatP[i][j] << " ";
    cout << endl;

}

void Grafo::Camino(int i, int j, ruta ruta){
    // Muestra la matriz de Floyd
    int k;
    k = MatP[i][j];
    if(k != -1){
        Camino(i, k, ruta);
        cout <<Cjtovertices[k] << endl;
        ruta.kilometros += matCaminosMin[i][k];
        Camino(k, j,ruta);
    }
}

bool Grafo::hayCamino(int i, int j) {
    int k = matCaminosMin[i][j];

    if(k != -1)
        return hayCamino(i, k) && hayCamino(k, j); // si hay camino retorna true

    return false; //si no hay camino retorna falso
}

void Grafo::matrizPrioridad(string cad1, string cad2, int prioridad){
    //se buscan las ciuades en el conjunto de vertices y se obtienen los indices
    int pos1 = buscarPosicion(cad1);
    int pos2 = buscarPosicion(cad2);

    matPrioridad[pos1][pos2] = prioridad;
    matPrioridad[pos2][pos1] = prioridad;

}

void Grafo::caminosMinimos(){
    floydCaminosMini();
    for (int i = 0; i < getPreguntas(); ++i){
        int inicio = buscarPosicion(rutasGrafo[i].origen);
        int fin = buscarPosicion(rutasGrafo[i].destino);
        Camino(inicio, fin, rutasGrafo[i]);

        cout << rutasGrafo[i].kilometros << endl;
    }
}


float Grafo::kilometrosArreglados() {
    float kilometros = 0;
    int prioridad = 1;
    while(prioridad <= cantidadPrioridades){
        for(int i =0; i < N && prioridad <= cantidadPrioridades; i++){
            for(int j = 0 ; j < N && prioridad <= cantidadPrioridades; j++){
                if(matPrioridad[i][j] != 0){
                    if(matPrioridad[i][j] == prioridad){
                        if(!hayCamino(i,j)){
                            prioridad++;
                            kilometros += matCaminosMin[i][j];
                        }else{
                            return kilometros;
                        }
                    }
                }
            }
        }
    }
    return kilometros;
}

void Grafo::algoritmoKruskal() {
    int visitados[MAX];
    float nuevoRecorrido[MAX][MAX];

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (j == i)
                nuevoRecorrido[i][j] = -1;
            else
                nuevoRecorrido[i][j] = 9999;
        }
    }

    for (int i = 1; i < MAX; i++)
        visitados[i] = i;

    int vertices = 1, org, dst;

    while (vertices < N) {
        float minimo;

        minimo = arcoMinimo(org,dst,visitados);

        if (visitados[org] != visitados[dst]) {

            nuevoRecorrido[org][dst] = minimo;
            nuevoRecorrido[dst][org] = minimo;

            int aux = visitados[dst];
            visitados[dst] = visitados[org];
            for (int i = 0; i < N; i++)
                if (visitados[i] == aux)
                    visitados[i] = visitados[org];

            vertices++;
        }
    }

    copiarMatriz(nuevoRecorrido);
}



float Grafo::arcoMinimo (int &org, int &dst, int visitados[MAX]) {
    float min = FLT_MAX; //utiliza limite superior float
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (min > MatAdyacencia[i][j] && MatAdyacencia[i][j] != 0 && visitados[i] != visitados[j]) {
                min = MatAdyacencia[i][j];
                org = i;
                dst = j;
            }
    return min;
}

void Grafo::copiarMatriz (float m[MAX][MAX]) {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            matCaminosMin[i][j] = m[i][j];
}

void Grafo::caminosArreglados() {
    int visitados[MAX];
    float nuevoRecorrido[MAX][MAX];

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (j == i)
                nuevoRecorrido[i][j] = -1;
            else
                nuevoRecorrido[i][j] = 9999;
        }
    }

    for (int i = 1; i < MAX; i++)
        visitados[i] = i;

    int vertices = 1, org, dst;

    while (vertices < N) {
        float minimo;

        minimo = arcoMinArreglado(org,dst,visitados);

        if (visitados[org] != visitados[dst]) {

            nuevoRecorrido[org][dst] = minimo;
            nuevoRecorrido[dst][org] = minimo;

            int aux = visitados[dst];
            visitados[dst] = visitados[org];
            for (int i = 0; i < N; i++)
                if (visitados[i] == aux)
                    visitados[i] = visitados[org];

            vertices++;
        }
    }

    copiarMatriz(nuevoRecorrido);
}

float Grafo::arcoMinArreglado(int &org, int &dst, int visitados[MAX]) {
    float min = FLT_MAX; //utiliza limite superior float
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (min > matPrioridad[i][j] && matPrioridad[i][j] != 0 && visitados[i] != visitados[j]) {
                min = matPrioridad[i][j];
                org = i;
                dst = j;
            }
    return min;
}


