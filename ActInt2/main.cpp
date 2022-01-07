/*
Actividad Integradora 2

Escrito por Javier Prieto y Luis Cano
para el curso de Programacion de
Estructuras de Datos y Algoritmos
Fundamentales

Matriculas: A01610324
            A00827178
Fecha de creacion: 		04/10/2021
Fecha de actualizacion:	14/11/2021

Lenguaje: C++11

main.cpp
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <climits>
#include <cfloat>
#include <math.h>
#include <tuple>
using namespace std;

#define INF INT_MAX

struct Punto {
    float x, y;
    Punto() {
        x = 0;
        y = 0;
    }
    Punto(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

std::istream& operator>>(std::istream& is, Punto& p){
    int x;
    int y;
    is >> x >> y;
    p.x=x;
    p.y=y;
    return is;
}

// Convierte un número a ASCII
char vertexIndexToChar(int a){
	return (char)('A'+a);
}

// 1.
// Determina la forma optima de
// conectar los nodos de un grafo
vector< pair<char, char> > floydWarshallOptimalGraph(vector< vector<int> > graph){
	int n=graph.size();
	vector< vector<int> > adjM;
	vector< vector<int> > next;
	
	for(int i=0;i<n;i++){
		adjM.push_back(graph[i]);
		next.push_back(vector<int>(n,-1));
	}
	
	for(int diag=0; diag<n; diag++){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				if((adjM[diag][j]+adjM[i][diag]) <= adjM[i][j] && i != diag && j != diag){
					adjM[i][j] = (adjM[diag][j] + adjM[i][diag]);
					// solo las rutas indirectas van a
					// ser marcadas con el indice del siguiente
					// nodo que se debe visitar para llegar
					// con la distancia minima al nodo destino
					
					// las rutas indirectas toman preferencia para
					// ahorrar los recursos de una conexion directa
					// a la colonia destino (para esto se utiliza la
					// comparacion '<=' )
					next[i][j] = j;
				}
			}
		}
	}
	vector< pair<char,char> > res;
	vector<bool> defaultConnection;
	for(int i=0; i<n; i++){
	    defaultConnection.clear();
		for(int j=0; j<n; j++){
		    defaultConnection.push_back(next[i][j]==-1);
		}
		for(int j=0; j<n; j++)
		    if(i!=j && defaultConnection[j])
		        res.push_back(make_pair(vertexIndexToChar(i),vertexIndexToChar(j)));
	}
	
	return res;
}

int minTSP = INF;

void backtrackingTS(vector< vector<int> >& graph, vector<bool>& used,
	int previous,int count, int cost,
	vector< Punto >& path,
	vector< Punto >& res) {
	
	int n = graph.size();
	
	// Podar las ramas que exceden
	// el costo minimo
	if(cost >= minTSP)
		return;
	
	if(count == n-1){
	    
		if(cost+graph[previous][0] < minTSP){
			minTSP = cost + graph[previous][0];
			path[count] = Punto(previous,0);
			// copiar el resultado a res
			for(int i=0;i<n;i++){
				res[i] = path[i];
			}
			// cout << minTSP << endl;
		}
		return;
	}
	
	for(int i=1;i<n;i++){
		if(!used[i]){
			path[count] = Punto(previous,i);
			used[i] = true;
			backtrackingTS(graph,used,i,count+1, cost+graph[previous][i], 
			path, res);
			used[i] = false;	
		}
	}
}

// 2.
// Este es el problema de "travelling salesman" 
// (se resuelve encontrando el Minimum
// Spanning Tree de un grafo [ya que contiene
// las conexiones minimas entre todos los nodos
// de un grafo]).
vector< Punto > travellingSalesman(vector< vector<int> >& graph){
	int n = graph.size();
	vector< Punto > res(n);
	vector< Punto > path(n);
	vector<bool> visited(n,false);
	backtrackingTS(graph, visited, 0, 0, 0,  path, res);
	
	return res;
}

// Recorido BFS para hallar el camino
// aumentante en flujoMaximo()
int BFS(vector< vector<int> > residual, vector<int> &camino, int N) {
    // Lista para guardar qué nodos
    // han sido visitados
    vector<int> visitado(N,0);
        
    // Queue para checar cada arista
    queue<int> q;
    q.push(0);
    
    visitado[0] = INF;
    camino[0] = -1;
        
    // Checar todas las aristas
    while(q.empty() == false) {
        int u = q.front();
        q.pop();
        
        for(int i = 0; i < N; i++) {           
            // Si no ha sido visitado y la
            // capacidad es > 0
            if(visitado[i] == 0 && residual[u][i] > 0) {
                q.push(i);
                visitado[i] = 1;
                camino[i] = u;
                // Si llegamos al último nodo
                // un arco terminó saturado.
                // El valor que regresamos es
                // igual al flujo del camino
                // que usamos en flujoMaximo()
                if (i == N-1)
                    return visitado[N-1];
            }
        }
    }

    return 0;
}

// 3.
// Función que regresa el flujo máximo en
// un grafo del nodo inicial al nodo final
int flujoMaximo(vector< vector<int> > capacidades, int N) {
    int f, flujoC, v;
    // Inicializar flujo f a 0
    f = 0;
    
    // Red residual
    // Es el conjunto de aristas/arcos
    // que pueden admitir más flujo
    vector< vector<int> > residual;
    residual = capacidades;
    
    // Lista para guardar el camino
    // aumentante del BFS
    vector<int> camino(N,-1);
    
    // Buscar el flujo máximo de la
    // fuente = 0 al sumidero = N-1
    while(true) {
        // Mientras exista un camino aumentante
        // aumentar flujo f a través del camino
        // flujoC = Flujo a través del camino
        int flujoC = BFS(residual, camino, N);
        if (flujoC == 0)
            break;
        
        // Sumar el flujo del camino al flujo máximo
        f += flujoC;

        // Iterar por el camino
        v = N-1;
        while(v > 0) {
            // Actualizar capacidades en la
            // red residual            
            residual[camino[v]][v] -= flujoC;
            residual[v][camino[v]] += flujoC;
            
            // Arista anterior
            v = camino[v];
        }
    }
    
    return f;
}

// Obtener la distancia entre 2 puntos
float distanciaCuadrada(Punto a, Punto b){
    return (pow((float)(a.x-b.x),2)+pow((float)(a.y-b.y),2));
}

// 4.
// Implementacion de busqueda  del punto
// más cercano de un conjunto
tuple<Punto,float> minDist(vector<Punto>& puntos, int lowerBound, int upperBound, Punto nc){
    int n=(upperBound-lowerBound+1);
    
    // Caso base
    // Regresa el punto más cercano a nc
    if(n<=3){
        float minD = FLT_MAX;
        int minI = 0;
        for(int i=0;i<n;i++){
            float d = distanciaCuadrada(puntos[lowerBound+i],nc);
            if (d < minD) {
                minD = d;
                minI = i;
            }
        }
        return {puntos[lowerBound+minI],minD};
    }

    // encontrar las distancias menores a nc
    Punto pIzq, pDer;
    float distIzq, distDer;
    tie(pIzq, distIzq) = minDist(puntos, lowerBound, lowerBound+n/2-1, nc);
    tie(pDer, distDer) = minDist(puntos, lowerBound+n/2, upperBound, nc);

    if (distIzq < distDer)
        return {pIzq, distIzq};
    return {pDer, distDer};
}

int main()
{
    // Número de colonias
    int N;
    cin >> N;

    // Archivo de entrada con info de dos grafos
    // ponderados
    ifstream grafoTxt;
    grafoTxt.open("grafo.txt");

    // Matriz representado grafo con distancias
    // entre los nodos
    vector< vector<int> > distancias;


    
    // Matriz representado capacidades maximas de
    // flujo de datos entre nodos
    vector< vector<int> > capacidades;
    // Lista con coordenadas (x,y) representando
    // la ubicación de los nodos en un plano
    vector< Punto > posiciones;
    
    string s;
    vector<int> line;
    int i = 0;

    // Leer y guardar datos que representan 
    // a una ciudad, con colonias en forma
    // de un grafo
    if (grafoTxt.is_open()) {
        while (!grafoTxt.eof()) {
            line.clear();
            getline(grafoTxt, s, '\n');

            if (s == "")
                continue;

            istringstream is( s );
            int x;
            while(is >> x) {
                line.push_back(x);
            }
            if (i < N)
                distancias.push_back(line);
            else
                capacidades.push_back(line);

            i++;
        }
    }
    
    // Ubicaciones de las centrales
    int A, B;
    for (int j=0; j<N; j++) {
        Punto pt;
        cin >> pt;
        posiciones.push_back(pt);
    }

    // // Coordenadas de nueva contratación
    Punto nc;
    cin >> nc;
    
    // Llenar los espacios en 0's
    // con un valor grande
    for(int i=0; i<N; i++){
      for(int j=0; j<N; j++){
        if(i!=j && distancias[i][j]==0)
          distancias[i][j]=INF/4;
      }
    }
    // Aplicar Floyd-Warshall a la matriz
    // de distancias
    for(int diag=0; diag<N; diag++){
      for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
          if((distancias[diag][j]+distancias[i][diag]) <= distancias[i][j] && i != diag && j != diag){
            distancias[i][j] = (distancias[diag][j] + distancias[i][diag]);
          }
        }
      }
	}

    // Punto 1.
    // Determinar la forma óptima de cablear con
    // fibra óptica para que se pueda compartir
    // información entre cuales quiera dos colonias.
    // posibles soluciones: Floyd Warshall
    cout << "1." << endl;
    vector< pair<char,char> > minimumDistanceGraph = floydWarshallOptimalGraph(distancias);
    cout << "Forma optima de cablear con fibra optica las colonias:" << endl;
	for(int i=0; i<minimumDistanceGraph.size(); i++)
	    cout << "(" << minimumDistanceGraph[i].first << ", " << minimumDistanceGraph[i].second << ")" << endl;
	
    // Punto 2.
    // Determinar la ruta más corta posible que
    // visita todos los nodos una vez y regresa
    // al punto inicial
    // posibles soluciones: Travelling Salesman/Held-Karp
    cout << "2." << endl;
    vector< Punto > minimumCyclicTraversal = travellingSalesman(distancias);
    cout << "La ruta mas corta posible que visita cada colonia exactamente una vez y al finalizar regresa a la colonia origen:" << endl;
	for(int i=0; i<N; i++) {
	    cout << vertexIndexToChar(minimumCyclicTraversal[i].x) << "-" << vertexIndexToChar(minimumCyclicTraversal[i].y);
        if (i != N-1)
            cout << ", ";
    }
    cout << endl;
    for(int i=0; i<N; i++) {
	    cout << distancias[minimumCyclicTraversal[i].x][minimumCyclicTraversal[i].y];
        if (i != minimumCyclicTraversal.size()-1)
            cout << ", ";
    }
    cout << " = " << minTSP << endl;

    // Punto 3.
    // Determinar el flujo máximo de información
    // del nodo inicial (A) al nodo final
    // posibles soluciones: Ford-Flukerson/Edmonds-Karp
    cout << "3." << endl;
    int flujoMax = flujoMaximo(capacidades, N);
    cout << "El flujo maximo de A a " << vertexIndexToChar(N-1) << " es de " << flujoMax << endl;

    // Punto 4.
    // Determinar cuál es la central más cercana
    // geográficamente a la nueva contratación
    // posibles soluciones: Calcular distancias/Voronoi
    cout << "4." << endl;
    Punto pMin;
    float distMin;
    tie(pMin, distMin) = minDist(posiciones,0,N-1,nc);
    cout << "La central mas cercana esta ubicada en (" << pMin.x << "," << pMin.y << ") " << endl; 

    return 0;
}
