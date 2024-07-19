#include "GrafoM.hpp"
#include "ParOrdenado.hpp"
#include <iostream>

GrafoM::GrafoM(int maxVertices){
     this->nVerticesCadastrados = 0;
     this->maxVertices = maxVertices;
     this->vertices = new ParOrdenado[maxVertices];

     //Cria a matriz de adjacencia
     this->AdjMatrix = new float*[maxVertices];
     for (int i = 0; i < maxVertices; i++){
          AdjMatrix[i] = new float[maxVertices];
          for(int j = 0; j < maxVertices; j++){
               //inicializa a matriz com valor representante de aresta inexistente
               AdjMatrix[i][j] = INF;
          }
     }
}

GrafoM::~GrafoM(){
     delete[] this->vertices;
     for (int i = 0; i < this->nVerticesCadastrados; i++){
          delete[] this->AdjMatrix[i];
     }
     delete[] AdjMatrix;

}

void GrafoM::addVertice(int x, int y){
     if (this->nVerticesCadastrados <= this->maxVertices){
          this->vertices[this->nVerticesCadastrados] = ParOrdenado(x, y);
          this->nVerticesCadastrados++;
     } else{
          std::cout << "Número máximo de vértices já cadastrado" << std::endl;
     }
}

void GrafoM::addAresta(int id1, int id2){
     this->AdjMatrix[id1][id2] = this->vertices[id1].distancia(this->vertices[id2]);
}

bool GrafoM::existeAresta(int id1, int id2) const{
     if (this->AdjMatrix[id1][id2] != INF){
          return true;
     } else{
          return false;
     }
     
}

float GrafoM::pesoAresta(int id1, int id2) const{
     if (this->existeAresta(id1, id2)){
          return this->AdjMatrix[id1][id2];
     } else{
          std::cout << "Aresta inexistente" << std::endl;
          return 1;
     }
}