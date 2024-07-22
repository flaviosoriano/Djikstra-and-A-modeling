#include "NoduloAEstrela.hpp"

#include "GrafoL.hpp"

     NodeA::NodeA(Vertex* verticeAtual, Vertex* verticeInicial, Vertex* verticeFinal, float g, int portaisUsados){
          this->verticeAtual = verticeAtual;
          this->g = g;
          this->verticeInicial = verticeInicial;
          this->verticeFinal = verticeFinal;
          this->portaisUsados = portaisUsados;

          this->h = this->verticeAtual->getCord().distancia(this->verticeFinal->getCord());
          this->f = this->g + this->h;
     };

     NodeA::NodeA(){
          Vertex* verticenulo = new Vertex(-1, -1, -1);
          this->verticeAtual = verticenulo;
          this->g = -1;
          this->verticeInicial = verticenulo;
          this->verticeFinal = verticenulo;
          this->portaisUsados = -1;

          this->h = -1;
          this->f = -1;
     }

     NodeA::~NodeA(){
     };

     void NodeA::setF(float f){
          this->f = f;
     };

     float NodeA::getF() const{
          return this->f;
     };

     float NodeA::getG() const{
          return this->g;
     }

     int NodeA::getPortaisUsados() const{
          return this->portaisUsados;
     };

     Vertex* NodeA::getVerticeAtual() const{
          return this->verticeAtual;
     };