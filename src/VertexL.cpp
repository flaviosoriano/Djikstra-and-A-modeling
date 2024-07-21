#include "VertexL.hpp"
#include "ParOrdenado.hpp"


Vertex::Vertex(int id, int x, int y): id(id), cord(x, y), next(nullptr),
arestaHead(nullptr), arestaTail(nullptr), nArestas(0){};

Vertex::Vertex(): id(-1), cord(-1, -1), next(nullptr),
arestaHead(nullptr), arestaTail(nullptr), nArestas(0){};

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
     this->nArestas++;
};

void Vertex::addNextVertex(Vertex* v){
     this->next = v;
};

Aresta* Vertex::getArestas() const{
     return this->arestaHead;
};

int Vertex::getNArestas() const{
     return this->nArestas;
};

int Vertex::getId() const{
     return this->id;
};

ParOrdenado Vertex::getCord() const{
     return this->cord;
};

Vertex* Vertex::getNext() const{
     return this->next;
};