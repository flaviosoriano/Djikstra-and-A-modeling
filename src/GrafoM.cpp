#include "GrafoM.hpp"
#include "ParOrdenado.hpp"
#include "PriorityQueue.hpp"
#include "VertexL.hpp"
#include <iostream>

GrafoM::GrafoM(int maxVertices){
     this->nVerticesCadastrados = 0;
     this->maxVertices = maxVertices;
     this->vertices = new Vertex[maxVertices - 1];

     //Cria a matriz de adjacencia
     this->AdjMatrix = new float*[maxVertices - 1];
     for (int i = 0; i < maxVertices; i++){
          AdjMatrix[i] = new float[maxVertices - 1];
          for(int j = 0; j < maxVertices - 1; j++){
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

void GrafoM::addVertice(int id, int x, int y){
     if (this->nVerticesCadastrados <= this->maxVertices){
          this->vertices[this->nVerticesCadastrados] = Vertex(id, x, y);
          this->nVerticesCadastrados++;
     } else{
          std::cout << "Número máximo de vértices já cadastrado" << std::endl;
     }
}

void GrafoM::addAresta(int id1, int id2, bool portal){
     if (portal){
          this->AdjMatrix[id1][id2] = 0;
     }else{
          this->AdjMatrix[id1][id2] = this->vertices[id1].getCord().distancia(this->vertices[id2].getCord());
     }
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
          return INF;
     }
}

int GrafoM::djikstra(int maxEnergia, int maxPortais){
     float distancias[this->maxVertices][maxPortais];
     for (int i = 0; i <= this->maxVertices; i++){
          for(int j =  0; j <= maxPortais; j++){
               distancias[i][j] = 999.0;
          }
     }

     PriorityQueue pq(this->maxVertices);

     Vertex* vInicial = &this->vertices[0];
     pq.inserir(vInicial, 0, 0);

     while(!pq.empty()){

          Caminho auxCaminho = pq.retirar();
          int id = auxCaminho.verticeId;
          float dist = auxCaminho.distancia;
          int portaisUsados = auxCaminho.portais;

          if (distancias[id][portaisUsados] < dist) {
               continue;
          }

          distancias[id][portaisUsados] = dist;

          if (id == (this->maxVertices - 1)) {
            break;
          }

          Vertex* verticeAtual = auxCaminho.verticeAtual;

          for(int id2 = 0; id2 < this->maxVertices - 1; id2++){   
               if (this->existeAresta(id, id2)){
                    float novaDistancia = dist + this->AdjMatrix[id][id2];
                    int novosPortaisUsados = 0;
                    if(this->AdjMatrix[id][id2] == 0){
                         novosPortaisUsados = portaisUsados + 1;
                    } else {
                         novosPortaisUsados = portaisUsados;
                    }
                    if (novosPortaisUsados <= maxPortais && distancias[id2][novosPortaisUsados] > novaDistancia) {
                         distancias[id2][novosPortaisUsados] = novaDistancia;
                         pq.inserir(&this->vertices[id2], novaDistancia, novosPortaisUsados);
                    }
               }
               else{
                    continue;
               }
          }
     }
     for (int i = 0; i <= maxPortais; i++) {
          if ((distancias[this->maxVertices - 1][i]) <= maxEnergia) {
               return 1;
          }
     }
     return 0;
};

int GrafoM::AEstrela(int maxEnergia, int maxPortais){

     return 0;
};