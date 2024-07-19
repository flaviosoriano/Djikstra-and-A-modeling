#include "PriorityQueue.hpp"
#include <iostream>

PriorityQueue::PriorityQueue(int capacidade){
     //capacidade + 1 para compensar ter de começar no indice 1
     this->tamanhoMax = capacidade + 1;
     this->heap = new Caminho[this->tamanhoMax];
     for (int i = 0; i < capacidade; i++){
          this->heap[i] = Caminho();
     }
     this->tamanhoAtual = 0;
     this->finalIndex = 0;
};

PriorityQueue::~PriorityQueue(){
     delete[] this->heap;
};

void PriorityQueue::maxHeapify(int index) {
    int largest = index;
    int left = 2 * index;
    int right = (2 * index) + 1;

     std::cout << "maxHeapify: " << "parent" << this->heap[index].verticeId << ":" << this->heap[index].distancia << " left" << this->heap[left].verticeId << ":" << this->heap[left].distancia << " right" << this->heap[right].verticeId << ":" << this->heap[right].distancia << std::endl;  
     std::cout << "finalIndex: " << this->finalIndex << std::endl;
    // Verifica se o filho da esquerda é maior que o nó atual
    if (left <= this->finalIndex && this->heap[left].distancia > this->heap[largest].distancia) {
        largest = left;
    }
    // Verifica se o filho da direita é maior que o maior atual
    if (right <= this->finalIndex && this->heap[right].distancia > this->heap[largest].distancia) {
        largest = right;
    }
    std::cout <<"Heapify maior: " << this->heap[largest].distancia << std::endl;
    // Se o maior não for o nó atual, troca e chama recursivamente
    if (largest != index) {
        Caminho temp = this->heap[index];
        this->heap[index] = this->heap[largest];
        this->heap[largest] = temp;
        maxHeapify(largest);
    }
}

bool PriorityQueue::empty() const{
     return (this->tamanhoAtual == 0);
}

void PriorityQueue::inserir(Vertex* vertice, float distancia, int portaisUsados){
     Caminho novoCaminho (vertice, -distancia, portaisUsados);
     
     this->finalIndex++;

     if (this->tamanhoAtual >= this->tamanhoMax){
         std::cout << "Erro: capacidade máxima já atingida" << std::endl;
         return;
     }    
     
     int index = (this->finalIndex);
     this->heap[index] = novoCaminho;

     this->tamanhoAtual++;

     int parentIndex = -1;
     if (index % 2 == 0){
          parentIndex = (index/2);
     } else{
          parentIndex = ((index - 1)/2);
     }
     if (index != 1){
     this->maxHeapify(parentIndex);
     }
     

     for(int i = 0; i <= finalIndex; i++){
          std::cout << "fila tem:" << this->heap[i].verticeId <<" com disyancia: "<< this->heap[i].distancia << std::endl;
     }
}

//teste para ver se retornar um ponteiro para o maior elemento funciona
Caminho PriorityQueue::retirar(){
     if (empty()){
          std::cout << "lista vazia" << std::endl;
     }

     Caminho menorCaminho = this->heap[1];

     std::cout << "alocando: "<< this->heap[this->finalIndex].verticeId << "para 1 lugar" << std::endl;

     this->heap[1] = this->heap[this->finalIndex];
     this->heap[this->finalIndex] = Caminho();
     this->tamanhoAtual--;
     this->finalIndex--;
     menorCaminho.distancia = -(menorCaminho.distancia);
     maxHeapify(1);

     std::cout << "1 lugar por heapfy na retirada: " << this->heap[1].verticeId << std::endl;
     return menorCaminho;
}