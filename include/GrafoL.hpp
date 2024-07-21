#ifndef GRAFOL_HPP
#define GRAFOL_HPP

#include <cstddef>
#include "ParOrdenado.hpp"
#include "VertexL.hpp"

#define INF 999.0
class GrafoList{
    private:
        int maxVertices;
        int maxArestas;
        Vertex* verticesHead;
        Vertex* verticesTail;
        int verticesAdicionados;

        Vertex* findVertice(int id) const;

    public:
        GrafoList(int maxVertices, int maxArestas);
        ~GrafoList();

        void addVertice(int id, int x, int y);
        void addAresta(int id1, int id2, bool isPortal = false);

        Vertex* getVerticeInicio() const;
        Vertex* getVerticeFinal() const;

        int djkistra(int energia, int maxPortais) const;
        int aEstrela(int energia, int maxPortais, Vertex* vInicio, Vertex* vFinal) const;
};

#endif