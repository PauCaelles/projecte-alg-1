#include <iostream>
#include <string>
#include <fstream>
#include "Graph.cpp"

using namespace std;

string graphType;
float n;
float pLow;
float pHigh;
float pSteps;
string percType;
float q;
int reps;

void InputData() {
    cout << "Insert type of graph: " << endl;
    cin >> graphType;
    cout << "Insert N value: " << endl;
    cin >> n;
    cout << "Insert P starting value: ";
    cin >> pLow;
    cout << "Insert P ending value: ";
    cin >> pHigh;
    cout << "Insert P steps value: ";
    cin >> pSteps;
    cout << "Insert percolation type: ";
    cin >> percType;
    cout << "Insert Q value: ";
    cin >> q;
    cout << "Insert number of repetitions: ";
    cin >> reps;
}

void OutputData(vector<vector<float> > results) {
    string csv;

    for (auto result : results) {
        for (auto value : result) {
            csv += to_string(value) + ",";
        }
        csv.pop_back();
        csv += "\n";
    }

    ofstream out("output.txt");
    out << csv;
    out.close();
}

int main() {

    InputData();

    float p = pLow;
    vector<vector<float> > totalResults;

    while(p <= pHigh) {
        float totalConnex = 0, totalComplex = 0;

        for (int i = 0; i < reps; i++) {
            Graph g(graphType, n, p);
            percType == "VERTEX" ? g.VertexPercolation(q) : g.EdgePercolation(q);
            bool connex, complex;
            g.CheckProperties(connex, complex);
            totalConnex += connex;
            totalComplex += complex;
        }

        totalConnex /= reps;
        totalComplex /= reps;

        vector<float> results {p, totalConnex, totalComplex};
        totalResults.push_back(results);

        p += pSteps;
    }

    OutputData(totalResults);
}

