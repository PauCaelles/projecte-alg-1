# projecte-alg-1
# Instrucciones per compilar:
1. Executar la comanda "g++ -std=c++11 -c Graph.cpp Experiment.cpp" per compilar els dos fitxers.
2. Executar la comanda "g++ -std=c++11 -o Experiment Experiment.o Graph.o" per generar els fitxers objecte
3. Executar "./Experiment graphType N pLow pHigh pSteps percType q reps"  On:
    - graphType indica quin tipus de graf s'ha de possar.
                - GRID         pel graf graella
                - GEOMETRIC    pel graf geomètric
                - BINOMIAL     pel graf binomial
    - N és el nombre de nodes que tindrà el graf
    - pLow és el valor de p inicial més baix en el que es començarà a executar per a generar  el graf 
    - pMax és el valor de p que obtindrà com a màxim a l'hora de generar o percolar el graf
    - pSteps és el número que s'hanirà incrementant p desde pLow fins a pMax
    On en els 3 casos anteriors, p seria el valor de p pel graf  binomial random  i r pel graf geometric random
    - percType és el tipus de percolació on:
                - VERTEX    seria per fer la percolació per vertex
                - ARESTES   seria per fer la percolació per arestes
    - q és el valor que s'utilitzarà per la percolacio per vertex o nodes
    - reps és el número de repeticons que s'executarà el mateix graf

Els fitxers que es poden trobar són:
    - Graph.cpp on està tota la implementació per generar els grafs i mirar les seves propietats
    - Experiments.cpp on està l'automatització per a fer els experiments utilitzant la informació obtinguda dels paràmetres i guardar els resultats en un .csv