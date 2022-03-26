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

int main(int argc, char** argv) {

    graphType = argv[1];
    n = atof(argv[2]);
    pLow = atof(argv[3]);
    pHigh = atof(argv[4]);
    pSteps = atof(argv[5]);
    percType = argv[6];
    q = atof(argv[7]);
    reps = atoi(argv[8]);

    float p = pLow;
    vector<vector<float> > totalResults;

    while(p < pHigh + pSteps) {
        float totalConnex = 0, totalComplex = 0;

        for (int i = 0; i < reps; i++) {
            Graph g(graphType, n, p);
            cout <<endl<<endl<<endl<< "ABANS DE LA PERCOLACIO" << pHigh<< endl;
            g.PrintGraph();
            cout << endl <<  "DESPRES DE LA PERCOLACIO" << p<< endl;
            percType == "VERTEX" ? g.VertexPercolation(q) : g.EdgePercolation(q);
            bool connex, complex;
            g.CheckProperties(connex, complex);
            g.PrintGraph();
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

