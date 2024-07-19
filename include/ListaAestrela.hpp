#ifndef LISTA_A_ESTRELA_HPP
#define LISTA_A_ESTRELA_HPP

#include "NoduloAEstrela.hpp"



class ListaAEstrela{
      private:
          //heap dos nodulos
          NodeA** heap;
          NodeA* copias;
          int tamanhoAtual;
          int tamanhoMax;
          int finalIndex;

          void maxHeapify(int index);
          
     public:
          ListaAEstrela(int capacidade);
          ~ListaAEstrela();

          bool empty() const;
          NodeA* find(NodeA* node) const;

          void inserir(NodeA* node);
          NodeA* retirar();
     
};

#endif