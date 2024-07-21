#ifndef GRAFOM_HPP
#define GRAFOM_HPP

#include "ParOrdenado.hpp"
#include "VertexL.hpp"

#define INF 999.0



class GrafoM{
     private:
          int maxVertices;
          //Utilização de um vetor de pares ordenados para representar os Vértices, já que seu ID será sua posição no vetor
          Vertex* vertices;
          float ** AdjMatrix;
          int nVerticesCadastrados;

     public:
          GrafoM(int nVertices);
          ~GrafoM();
          void addVertice(int id, int x, int y);
          void addAresta(int id1, int id2, bool portal);
          
          bool existeAresta(int id1, int id2) const;
          float pesoAresta (int id1, int id2) const;

          int djikstra(int maxEnergia, int maxPortais);
          int AEstrela(int maxEnergia, int maxPortais);
};

#endif
