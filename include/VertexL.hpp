#ifndef VERTEXL_HPP
#define VERTEXL_HPP

#include <cstddef>
#include "ParOrdenado.hpp"

#define INF 999.0

class Vertex;

struct Aresta{
    Vertex* verticeConectado;
    float tamanhoAresta;
    bool portal;
    Aresta* next;

    Aresta(Vertex* v, float distancia, bool portal): verticeConectado(v), tamanhoAresta(distancia),
    portal(portal), next(nullptr) {};
    ~Aresta() = default;
};

class Vertex{

    private:
        int id;
        ParOrdenado cord;
        Vertex* next;
        Aresta* arestaHead;
        Aresta* arestaTail;
        int nArestas;
    public:
        Vertex(int id, int x, int y);
        Vertex();
        ~Vertex();

        int getId() const;
        int getNArestas() const;
        ParOrdenado getCord() const;
        Aresta* getArestas() const;
        Vertex* getNext() const;

        void addAresta(Vertex* v, bool isPortal);
        void addNextVertex(Vertex* v);
};

#endif