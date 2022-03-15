
#include <stack>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;


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