#ifndef GRAFOM_HPP
#define GRAFOM_HPP

#include "ParOrdenado.hpp"

#define INF 999.0



class GrafoM{
     private:
          int maxVertices;
          //Utilização de um vetor de pares ordenados para representar os Vértices, já que seu ID será sua posição no vetor
          ParOrdenado* vertices;
          float ** AdjMatrix;
          int nVerticesCadastrados;
     public:
          GrafoM(int nVertices);
          ~GrafoM();
          void addVertice(int x, int y);
          void addAresta(int id1, int id2);
          bool existeAresta(int id1, int id2) const;
          float pesoAresta (int id1, int id2) const;
};

#endif

