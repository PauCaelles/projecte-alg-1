#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <algorithm> // binary_search

using namespace std;

enum Model{BINOMIAL, GEOMETRIC};

class Graph {
    public:
        Graph();

        Graph(int n, int p, Model m) {
            if (m == BINOMIAL) GenerateBinomialRandom(n, p);
            if (m == GEOMETRIC) GenerateGeometricRandom(n, p);
        }

        void GenerateBinomialRandom(int n, int p) {
            PopulateNVertices(n);
            vector<bool> checked(n, false);  
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    float r = rand()/RAND_MAX;
                    if (i != j and !checked[j] and (r <= p)) AddEdge(i, j);
                }
            }  
        }

        map<int, vector<int> > GenerateGeometricRandom(int n, int r);

        void AddVertice(int i) {
            adjList.insert( pair<int, vector<int> > (i, vector<int>()));
        }

        void AddEdge(int u, int v) {
            AddAdjacency(adjList[u], v);
            AddAdjacency(adjList[v], u);
        }



    private:
        map<int, vector<int> > adjList;

        void AddAdjacency(vector<int> adj, int u) {
            if (find(adj.begin(), adj.end(), u) == adj.end()) adj.push_back(u);
        }

        void PopulateNVertices(int n) {
            adjList.clear();
            for (int i = 0; i < n; i++) AddVertice(i);
        }

        void DFS(vector<bool>& visitats, int& c_candidat, int& count_visited) {
                int mida = adjList.size();
                stack<int> pila;
                for(c_candidat; visitats[c_candidat] == true; c_candidat++);
                int inici = c_candidat;

                visitats[inici] = true;
                ++count_visited;

                pila.push(inici);
                while (not(pila.empty())) {
                    int element = pila.top();
                    pila.pop(); 
                    for(int i = 0; i < adjList[element].size(); i++) {
                        int contingut = adjList[element][i];
                        if( !visitats[contingut] ){
                            visitats[contingut]; // marcar como visitado
                            ++count_visited;     // elemento visitado nuevo
                            pila.push(contingut); // Añadirlo en la pila
                        }
                    }
                }
            }
        
        // Pre: graf != buit
        // Post: 0 si no conex, 1 si conex
        int componentsConexes() {
            int mida = adjList.size();
            vector<bool> visitats(mida, false);
            int count_visited = 0;
            int c_inicial = 0; // node candidat a ser l'inicial a per continuar visitant al DFS (els anteriors ja estan visitats)
            int cc = 0; // components conexes
            // Si hi ha vertex sense visitar => G no es conex i encara hi ha vertex per visitar
            do{
                DFS(visitats, c_inicial, count_visited); // Donat un vertex v, aplicar un DFS per a saber quins nodes hi ha conectats (= visitats)
                cc++;
            } while(count_visited < mida);  // Si no hi ha vertex sense visitar => G conex
            int total;
            if(cc == 1) return 0;
            else return 1;
        }
};





