#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


using namespace std;

class Graph {
    public:
        Graph();

        Graph(string m, int n, float p) {
            if (m == "GRID") GenerateGrid(n);
            if (m == "BINOMIAL") GenerateBinomialRandom(n, p);
            if (m == "GEOMETRIC") GenerateGeometricRandom(n, p);
        }

        void GenerateGrid(int n) {
            int size = n * n;
            for (int i = 0; i < size; i++) {
                vector<int> temp;
                int col = i % n;
                if (col == 0) temp.push_back(i+1);
                else if (col == n - 1)temp.push_back(i - 1);
                else {
                    temp.push_back(i + 1);
                    temp.push_back(i - 1);
                }
                int row = i / n;
                if (row == 0) temp.push_back(i + n); 
                else if (row == n - 1) temp.push_back(i - n);
                else {
                    temp.push_back(i + n);
                    temp.push_back(i - n);
                }
                adjList[i] = temp;
            }
        }

        void GenerateBinomialRandom(int n, float p) {
            struct timespec ts;
            clock_gettime(CLOCK_MONOTONIC, &ts);
            srand((time_t)ts.tv_nsec);
            PopulateNVertices(n);
            vector<bool> checked(n, false);  
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    float r = ((float)rand()/RAND_MAX);
                    if (i != j and !checked[j] and (r <= p)) AddEdge(i, j);
                }
            checked[i] = true;
            }  
        }
    
        void GenerateGeometricRandom(int n, float r) {
            struct timespec ts;
            clock_gettime(CLOCK_MONOTONIC, &ts);
            srand((time_t)ts.tv_nsec);
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
            struct timespec ts;
            clock_gettime(CLOCK_MONOTONIC, &ts);
            srand((time_t)ts.tv_nsec);
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
            struct timespec ts;
            clock_gettime(CLOCK_MONOTONIC, &ts);
            srand((time_t)ts.tv_nsec);
            for (auto it = adjList.begin(); it != adjList.end(); it++) {
                for (int j = 0; j < it->second.size();) {
                    if (it->first < it->second[j]) {
                        double i = ((double)rand() / RAND_MAX);
                        if (i >= p) {
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

        void CheckProperties(bool& connex, bool& totComplex) {
            int mida = adjList.size();
            vector<bool> visitats(mida, false);
            int count_visited = 0; 
            int c_candidat = (*adjList.begin()).first; 
            bool propComplexes = true;
            if(mida > 0) DFS(visitats, c_candidat, count_visited, propComplexes);
            bool propConex = true;
            if(mida > 0 && count_visited < mida) {
                propConex = false;
                while(propComplexes && count_visited < mida){
                    DFS(visitats, c_candidat, count_visited, propComplexes);
                }
            } 
            connex = propConex;
            totComplex = propComplexes;
        }
        
        void PrintGraph() {
            int i = 0;
            for (auto it = adjList.begin(); it != adjList.end(); it++) {
                cout << it -> first << ": ";
                for (auto v : it -> second) cout << v << " ";
                cout << endl;
            }
        }
        
    private:
        map<int, vector<int> > adjList;

        void AddAdjacency(vector<int>& adj, int u) {
            if (find(adj.begin(), adj.end(), u) == adj.end()) adj.push_back(u);
        }

        void PopulateNVertices(int n) {
            adjList.clear();
            for (int i = 0; i < n; i++) AddVertex(i);
        }

        vector<pair<float, float> > SetVertexPositions(int n) {
            struct timespec ts;
            clock_gettime(CLOCK_MONOTONIC, &ts);
            srand((time_t)ts.tv_nsec);
            vector<pair<float, float> > v;
            for (int i = 0; i < n; i++) {
                float x = ((float)rand()/RAND_MAX);
                float y = ((float)rand()/RAND_MAX);
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
                while(visitats[c_candidat] == true) ++c_candidat;
                int inici = c_candidat;
                ++c_candidat;
                visitats[inici] = true;
                ++count_visited;

                stack<int> pila;
                pila.push(inici);
                while (not(pila.empty())) {
                    int element = pila.top();
                    pila.pop();
                    vector<int> vec = adjList[element];
                    for(int i = 0; i < vec.size(); i++) {
                        int contingut = vec[i];
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
};
