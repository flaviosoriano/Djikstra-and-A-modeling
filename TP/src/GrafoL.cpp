#include "GrafoL.hpp"
#include "ParOrdenado.hpp"
#include "PriorityQueue.hpp"
#include <math.h>
#include <iostream>


Vertex::Vertex(int id, int x, int y): id(id), cord(x, y), next(nullptr),
arestaHead(nullptr), arestaTail(nullptr){};

Vertex::~Vertex() {
    Aresta* current = arestaHead;
    while (current != nullptr) {
        Aresta* next = current->next;
        delete current;
        current = next;
    }
}

void Vertex::addAresta(Vertex* v, bool isPortal){
     float dist = -1;
     if (isPortal){
          dist = 0;
     }else{
          dist = this->cord.distancia(v->cord);
     }

     Aresta* novaAresta = new Aresta(v, dist, isPortal);
     if (this->arestaHead == nullptr){
          this->arestaHead = novaAresta;
     } else{
          this->arestaTail->next = novaAresta;
     }
     this->arestaTail = novaAresta;
};

Aresta* Vertex::getArestas() const{
     return this->arestaHead;
};



GrafoList::GrafoList(int maxVertices, int maxArestas): maxVertices(maxVertices), maxArestas(maxArestas)
, verticesHead(nullptr), verticesTail(nullptr), verticesAdicionados(0) {};

GrafoList::~GrafoList() {
    Vertex* current = verticesHead;
    while (current != nullptr) {
        Vertex* next = current->next;
        delete current;
        current = next;
    }
}

void GrafoList::addVertice(int id, int x, int y){
     Vertex* novoVertice = new Vertex(id, x, y);
     if (this->verticesHead == nullptr){
          this->verticesHead = novoVertice;
     } else{
          this->verticesTail->next = novoVertice;
     }
     this->verticesTail = novoVertice;

};

Vertex* GrafoList::findVertice(int id){
     Vertex* aux = this->verticesHead;
     while(aux != nullptr){
          if(aux->id == id){
               return aux;
          }
          aux = aux->next;
     }
     return nullptr;
};


void GrafoList::addAresta(int id1, int id2, bool isPortal){
     Vertex* v1 = findVertice(id1);
     Vertex* v2 = findVertice(id2);

     if(v1 && v2){
          v1->addAresta(v2, isPortal);
     } else if (!v2){
          std::cout << "Erro: Vertice " << id2 << "não encontrado" << std::endl;
     } else if (!v1){
          std::cout << "Erro: Vertice " << id1 << "não encontrado" << std::endl;
     }
};

int GrafoList::djkistra(int energia, int maxPortais) {
    int n = this->maxVertices;

    float distancias[n][maxPortais + 1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= maxPortais; j++) {
            distancias[i][j] = 999.0;
            distancias[0][j] = 0;
        }
    }

    PriorityQueue pq(this->maxArestas);
    pq.inserir(0, 0, 0);

    std::cout << "Inicializando Dijkstra" << std::endl;

    while (!pq.empty()) {
        Caminho auxCaminho = pq.retirar();
        int id = auxCaminho.verticeId;
        float dist = auxCaminho.distancia;
        int portaisUsados = auxCaminho.portais;

        std::cout << "Retirado da fila: id=" << id << ", dist=" << dist << ", portaisUsados=" << portaisUsados << std::endl;

        if (id == (n - 1)) {
            std::cout << "Chegou ao último vértice: " << id << std::endl;
            break;
        }

        if (distancias[id][portaisUsados] < dist) {
            std::cout << "Distância armazenada é menor, continuando..." << std::endl;
            continue;
        }
        distancias[id][portaisUsados] = dist;

        Vertex* verticeAtual = this->findVertice(id);
        Aresta* auxAresta = verticeAtual->arestaHead;

        std::cout << "Explorando arestas do vértice: " << id << std::endl;

        while (auxAresta != nullptr) {
            float novaDistancia = dist + auxAresta->tamanhoAresta;
            int novosPortaisUsados = portaisUsados + (auxAresta->portal ? 1 : 0);

            std::cout << "Verificando aresta para vértice: " << auxAresta->verticeConectado->id
                      << ", novaDistancia=" << novaDistancia
                      << ", novosPortaisUsados=" << novosPortaisUsados << std::endl;
               
            if (novosPortaisUsados <= maxPortais && distancias[auxAresta->verticeConectado->id][novosPortaisUsados] > novaDistancia) {
                distancias[auxAresta->verticeConectado->id][novosPortaisUsados] = novaDistancia;
                pq.inserir(auxAresta->verticeConectado->id, -novaDistancia, novosPortaisUsados);

                std::cout << "Atualizando distância do vértice " << auxAresta->verticeConectado->id
                          << " para " << novaDistancia << " com " << novosPortaisUsados << " portais usados" << std::endl;
            }
            auxAresta = auxAresta->next;
        }
    }

    std::cout << "Finalizando Dijkstra" << std::endl;

     for (int i = 0; i <= maxPortais; ++i) {
          std::cout << "distancia ate o final com "<<i<< " portais: " << distancias[n - 1][i] << std::endl;
     }
     for (int i = 0; i <= maxPortais; ++i) {
          if ((distancias[n - 1][i]) <= energia) {
               return 1;
          }
     }
    

    return 0;
}
