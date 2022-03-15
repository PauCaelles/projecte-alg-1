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

        void DFS(vector<int>& visitats) {
                int mida = adjList.size();
                vector<int> visitats;
                visitats.push_back(0);
                stack<int> pila;
                int inici;
                for(inici = 0; inici < mida || visitats[inici] != inici; inici++); // 1r node no visitat O(n²)
                pila.push(inici);
                while (not(pila.empty())) {
                    int element = pila.top();
                    pila.pop(); 
                    for(int i = 0; i < adjList[element].size(); i++) {
                        int contingut = adjList[element][i];
                        if( not(binary_search(visitats.begin(), visitats.end(), contingut)) ){
                            for(auto it = visitats.begin(); it < visitats.end(); ++it) if(*it > contingut) visitats.insert(it, contingut); // marcar como visitado INEFICIENTE O(n²)
                            pila.push(contingut); // Añadirlo en la pila
                        }
                    }
                }
            }

        int componentsConexes() {
        // escollir si es site (nodes) o bond (arestes) percolation
            vector<int> visitats;
            int cc = 0; // components conexes
            // Si hi ha vertex sense visitar => G no es conex i encara hi ha vertex per visitar
            do{
                DFS(visitats); // Donat un vertex v, aplicar un DFS per a saber quins nodes hi ha conectats (= visitats)
                cc++;
            } while(visitats.size() < adjList.size());  // Si no hi ha vertex sense visitar => G conex
            return cc;
        }
};





