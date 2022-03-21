#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <math.h>

using namespace std;

enum Model{BINOMIAL, GEOMETRIC};

class Graph {
    public:
        Graph();

        Graph(int n, float p, Model m) {
            if (m == BINOMIAL) GenerateBinomialRandom(n, p);
            if (m == GEOMETRIC) GenerateGeometricRandom(n, p);
        }

        void GenerateBinomialRandom(int n, float p) {
            srand(time(NULL));
            PopulateNVertices(n);
            vector<bool> checked(n, false);  
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    float r = rand()/RAND_MAX;
                    if (i != j and !checked[j] and (r <= p)) AddEdge(i, j);
                }
            checked[i] = true;
            }  
        }
    
        void GenerateGeometricRandom(int n, float r) {
            srand(time(NULL));
            PopulateNVertices(n);
            vector<pair<float, float> > pos = SetVertexPositions(n);
            vector<bool> checked(n, false);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i != j and !checked[j] and Distance(pos[i], pos[j]) <= r) AddEdge(i, j);
                }
            checked[i] = true;
            }  
        }

        void AddVertex(int i) {
            adjList.insert( pair<int, vector<int> > (i, vector<int>()));
        }

        void AddEdge(int u, int v) {
            AddAdjacency(adjList[u], v);
            AddAdjacency(adjList[v], u);
        }

        void VertexPercolation(double p) {
            srand(time(NULL));
            for (auto it = adjList.begin(); it != adjList.end();) {
                double i = ((double)rand() / RAND_MAX);
                if (i > p) {
                    vector<int> temp = it->second;
                    for (int j = 0; j < temp.size(); j++) {
                        auto it2 = adjList.find(temp[j]);
                        for (int k = 0; k < it2->second.size(); k++) {
                            if (it2->second[k] == it->first) it2->second.erase(it2->second.begin() + k);
                        }
                    }
                    it = adjList.erase(it);
                }
                else ++it;
            }
        }

        void EdgePercolation(double p) {
            srand(time(NULL));
            for (auto it = adjList.begin(); it != adjList.end(); it++) {
                for (int j = 0; j < it->second.size();) {
                    if (it->first < it->second[j]) {
                        double i = ((double)rand() / RAND_MAX);
                        if (i < p) {
                            auto it2 = adjList.find(it->second[j]);
                            for (int k = 0; k < it2->second.size(); k++) {
                                if (it2->second[k] == it->first) it2->second.erase(it2->second.begin() + k);
                            }
                            it->second.erase(it->second.begin() + j);
                        }
                        else j++;
                    }
                    else j++;
                }
            }
        }
        
    private:
        map<int, vector<int> > adjList;

        void AddAdjacency(vector<int> adj, int u) {
            if (find(adj.begin(), adj.end(), u) == adj.end()) adj.push_back(u);
        }

        void PopulateNVertices(int n) {
            adjList.clear();
            for (int i = 0; i < n; i++) AddVertex(i);
        }

        vector<pair<float, float> > SetVertexPositions(int n) {
            srand(time(NULL));
            vector<pair<float, float> > v;
            for (int i = 0; i < n; i++) {
                float x = rand()/RAND_MAX;
                float y = rand()/RAND_MAX;
                v.push_back(pair<float,float>(x,y));
            } 
            return v;
        }

        float Distance(pair<float,float> a, pair<float,float> b) { 
            return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
        }

        void DFS(vector<bool>& visitats, int& c_candidat, int& count_visited, bool& ccComplexa) {
                int mida = adjList.size();
                int count_cicles = 0;
                stack<int> pila;
                for(c_candidat; visitats[c_candidat] == true; c_candidat++);
                int inici = c_candidat;

                ++c_candidat;
                visitats[inici] = true;
                ++count_visited;

                pila.push(inici);
                while (not(pila.empty())) {
                    int element = pila.top();
                    pila.pop(); 
                    for(int i = 0; i < adjList[element].size(); i++) {
                        int contingut = adjList[element][i];
                        if( !visitats[contingut] ){
                            visitats[contingut] = true;
                            ++count_visited;
                            pila.push(contingut);
                        }
                        else {
                            ++count_cicles;
                        }
                    }
                }
                if(count_cicles < 1) ccComplexa = false; 
            }
        
        // Post:    conex    no complex      resultat
        //            No        No              0
        //            No        Si              1
        //            Si        No              2
        //            Si        Si              3        
        int CheckProperties() {
            int mida = adjList.size();
            vector<bool> visitats(mida, false);
            int count_visited = 0; 
            int c_inicial = 0; 
            bool propComplexes = true;
            DFS(visitats, c_inicial, count_visited, propComplexes);
            bool propConex = true;
            if(count_visited == mida) propConex = true;
            else {
                propConex = false;
                while(propComplexes && count_visited < mida){
                    DFS(visitats, c_inicial, count_visited, propComplexes);
                }
            } 
            if(not(propConex)) {
                if(propComplexes) return 1;
                else return 0;
            }
            else{
                if(propComplexes) return 3;
                else return 2;
            }
        }
        
        void DeleteVertex(double p) {
            srand(time(NULL));
            for (auto it = adjList.begin(); it != adjList.end();) {
                double i = ((double)rand() / RAND_MAX);
                if (i > p) {
                    vector<int> temp = it->second;
                    for (int j = 0; j < temp.size(); j++) {
                        auto it2 = adjList.find(temp[j]);
                        for (int k = 0; k < it2->second.size(); k++) {
                            if (it2->second[k] == it->first) it2->second.erase(it2->second.begin() + k);
                        }
                    }
                    it = adjList.erase(it);
                }
                else ++it;
            }
        }

        void DeleteEdge(double p) {
            srand(time(NULL));
            for (auto it = adjList.begin(); it != adjList.end(); it++) {
                for (int j = 0; j < it->second.size();) {
                    if (it->first < it->second[j]) {
                        double i = ((double)rand() / RAND_MAX);
                        if (i < p) {
                            auto it2 = adjList.find(it->second[j]);
                            for (int k = 0; k < it2->second.size(); k++) {
                                if (it2->second[k] == it->first) it2->second.erase(it2->second.begin() + k);
                            }
                            it->second.erase(it->second.begin() + j);
                        }
                        else j++;
                    }
                    else j++;
                }
            }
        }
};





