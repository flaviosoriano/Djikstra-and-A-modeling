#ifndef NODULO_A_ESTRELA_HPP
#define NODULO_A_ESTRELA_HPP

#include "GrafoL.hpp"


class NodeA{
private:
     float f;
     float h;
     float g;
     int portaisUsados;

     Vertex* verticeAtual;
     Vertex* verticeInicial;
     Vertex* verticeFinal;

public:
     NodeA(Vertex* vertice, Vertex* verticeInicial, Vertex* verticeFinal, float g, int portaisUsados);
     NodeA();
     ~NodeA();

     void setF(float f);

     float getF() const;
     float getG() const;
     int getPortaisUsados() const;
     Vertex* getVerticeAtual() const;
};






#endif