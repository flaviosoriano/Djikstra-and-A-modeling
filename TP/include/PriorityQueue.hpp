#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#define INF 999.0

//Par de armazenamento de vetor e sua atual distancia
struct Caminho{
     int verticeId;
     float distancia;
     int portais;

     Caminho() : verticeId(-1), distancia(999.0), portais(0){};
     Caminho(int id, float distancia, int portal): verticeId(id), distancia(distancia), portais(portal){};
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

          void usarPortal();
          void inserir(int id, float distancia, int portaisUsados);
          Caminho retirar();
     };

#endif