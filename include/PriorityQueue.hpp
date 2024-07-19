#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "GrafoL.hpp"

#define INF 999.0

//Par de armazenamento de vetor e sua atual distancia
struct Caminho{    

     Vertex* verticeAtual;
     int verticeId;
     float distancia;
     int portais;

     Caminho() : verticeAtual(nullptr),verticeId(-1), distancia(-1), portais(0){};
     Caminho(Vertex* verticeAtual, float distancia, int portal):
     verticeAtual(verticeAtual), distancia(distancia), portais(portal){
          verticeId = verticeAtual->getId();
     };
};



class PriorityQueue{
     private:
          //heap incluindo os vertices e suas distâncias
          Caminho* heap;
          int tamanhoAtual;
          int tamanhoMax;
          int finalIndex;
          int portaisUsados;

          void maxHeapify(int index);
          
     public:
          PriorityQueue(int capacidade);
          ~PriorityQueue();

          bool empty() const;

          void inserir(Vertex* vertice, float distancia, int portaisUsados);
          Caminho retirar();
     };

#endif