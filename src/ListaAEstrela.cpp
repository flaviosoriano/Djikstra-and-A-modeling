#include "ListaAestrela.hpp"

#include <iostream>

ListaAEstrela::ListaAEstrela(int capacidade){
     //capacidade + 1 para compensar ter de começar no indice 1
     this->tamanhoMax = capacidade + 1;
     this->heap = new NodeA[this->tamanhoMax];
     this->tamanhoAtual = 0;
     this->finalIndex = 0;
};

ListaAEstrela::~ListaAEstrela(){
     this->heap->~NodeA();
};

void ListaAEstrela::maxHeapify(int index) {

    int largest = index;
    int left = 2 * index;
    int right = 2 * index + 1;

    // Verifica se o filho da esquerda é maior que o nó atual
    if (left < this->finalIndex && this->heap[left].getF() > this->heap[largest].getF()) {
        largest = left;
    }
    // Verifica se o filho da direita é maior que o maior atual
    if (right < this->finalIndex && this->heap[right].getF() > this->heap[largest].getF()) {
        largest = right;
    }
    // Se o maior não for o nó atual, troca e chama recursivamente
    if (largest != index) {
        NodeA temp = this->heap[index];
        this->heap[index] = this->heap[largest];
        this->heap[largest] = temp;
        temp.~NodeA();
        maxHeapify(largest);
    }
}

bool ListaAEstrela::empty() const{
     return (this->tamanhoAtual == 0);
}

NodeA* ListaAEstrela::find(NodeA* node) const{
     std::cout << "entrou no find" << std::endl;
     for (int i = 0; i < this->finalIndex; i++){
          if (this->heap[i].getVerticeAtual()->getId() == node->getVerticeAtual()->getId()){
               std::cout << "achou igual e retornou" << std::endl;
               return &this->heap[i];
          }
     }
     std::cout << "retornou null" << std::endl;
     return nullptr;
};


void ListaAEstrela::inserir(NodeA node){
     
     //invertendo valot de F para lista retornar o menor valor
     node.setF(-node.getF());

     this->finalIndex++;

     std::cout << "aaaaaa" << std::endl;

     if (this->tamanhoAtual >= this->tamanhoMax){
         std::cout << "Erro: capacidade máxima já atingida" << std::endl;
         return;
     }    
     
     int index = (this->finalIndex);

     this->heap[index] = node;

     this->tamanhoAtual++;

     int parentIndex = -1;
     if (index % 2 == 0){
          parentIndex = (index/2);
     } else{
          parentIndex = ((index - 1)/2);
     }

     this->maxHeapify(parentIndex);

     for(int i = 1; i <= this->finalIndex; i++){
          std::cout << "fila aberta/fechada tem:" << this->heap[i].getVerticeAtual()->getId() << std::endl;
     }
}

//teste para ver se retornar um ponteiro para o maior elemento funciona
NodeA ListaAEstrela::retirar(){
     if (empty()){
          std::cout << "lista vazia" << std::endl;
     }

     NodeA menorCaminho = this->heap[1];

     std::cout << "alocando: "<< this->heap[this->finalIndex].getVerticeAtual()->getId() << "para 1 lugar" << std::endl;

     this->heap[1] = this->heap[this->finalIndex];
     this->heap[this->finalIndex] = NodeA();
     this->tamanhoAtual--;
     this->finalIndex--;
     //menorCaminho.setF(-menorCaminho.getF());
     maxHeapify(1);

     std::cout << "1 lugar por heapfy na retirada: " << this->heap[1].getVerticeAtual()->getId() << std::endl;
     return menorCaminho;
}