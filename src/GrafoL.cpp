#include "GrafoL.hpp"
#include "VertexL.hpp"
#include "ParOrdenado.hpp"
#include "PriorityQueue.hpp"
#include "NoduloAEstrela.hpp"
#include "ListaAestrela.hpp"
#include <iostream>

GrafoList::GrafoList(int maxVertices, int maxArestas): maxVertices(maxVertices), maxArestas(maxArestas)
, verticesHead(nullptr), verticesTail(nullptr), verticesAdicionados(0) {};

GrafoList::~GrafoList() {
    Vertex* current = verticesHead;
    while (current != nullptr) {
        Vertex* next = current->getNext();
        delete current;
        current = next;
    }
}

void GrafoList::addVertice(int id, int x, int y){
     Vertex* novoVertice = new Vertex(id, x, y);
     if (this->verticesHead == nullptr){
          this->verticesHead = novoVertice;
     } else{
          this->verticesTail->addNextVertex(novoVertice);
     }
     this->verticesTail = novoVertice;

};

Vertex* GrafoList::findVertice(int id) const{
     Vertex* aux = this->verticesHead;
     while(aux != nullptr){
          if(aux->getId() == id){
               return aux;
          }
          aux = aux->getNext();
     }
     return nullptr;
};


void GrafoList::addAresta(int id1, int id2, bool isPortal){
     Vertex* v1 = findVertice(id1);
     Vertex* v2 = findVertice(id2);

     if(v1 && v2){
          v1->addAresta(v2, isPortal);
     } else if (!v2){
          std::cout << "Erro: Vertice " << id2 << "não encontrado" << std::endl;
     } else if (!v1){
          std::cout << "Erro: Vertice " << id1 << "não encontrado" << std::endl;
     }
};

Vertex* GrafoList::getVerticeInicio() const{
     return this->verticesHead;
};
Vertex* GrafoList::getVerticeFinal() const{
     return this->verticesTail;
};

int GrafoList::djkistra(int energia, int maxPortais) const{
    int n = this->maxVertices;

    float distancias[n][maxPortais + 1];
     for (int i = 0; i <= this->maxVertices; i++){
          for(int j =  0; j <= maxPortais; j++){
               distancias[i][j] = 999.0;
          }
     }

    PriorityQueue pq(this->maxArestas);
    Vertex* vInicial = this->findVertice(0);
    pq.inserir(vInicial, 0, 0);

    std::cout << "Inicializando Dijkstra com energia " << energia <<" e portais: "<< maxPortais << std::endl;

    while (!pq.empty()) {
        Caminho auxCaminho = pq.retirar();
        int id = auxCaminho.verticeId;
        float dist = auxCaminho.distancia;
        int portaisUsados = auxCaminho.portais;

        std::cout << "Retirado da fila: id=" << id << ", dist=" << dist << ", portaisUsados=" << portaisUsados << std::endl;

        if (distancias[id][portaisUsados] < dist) {
            std::cout << "Distância armazenada(" << distancias[id][portaisUsados] <<")é menor que " << dist <<", continuando..." << std::endl;
            continue;
        }

        distancias[id][portaisUsados] = dist;

          if (id == (n - 1)) {
            std::cout << "Chegou ao último vértice: " << id << std::endl;
            break;
          }

        Vertex* verticeAtual = auxCaminho.verticeAtual;
        Aresta* auxAresta = verticeAtual->getArestas();

        std::cout << "Explorando arestas do vértice: " << id << std::endl;

        while (auxAresta != nullptr) {
            float novaDistancia = dist + auxAresta->tamanhoAresta;
            int novosPortaisUsados = portaisUsados + (auxAresta->portal ? 1 : 0);

            std::cout << "Verificando aresta para vértice: " << auxAresta->verticeConectado->getId()
                      << ", novaDistancia=" << novaDistancia
                      << ", novosPortaisUsados=" << novosPortaisUsados << std::endl;
               
            if (novosPortaisUsados <= maxPortais && distancias[auxAresta->verticeConectado->getId()][novosPortaisUsados] > novaDistancia) {
                distancias[auxAresta->verticeConectado->getId()][novosPortaisUsados] = novaDistancia;
                pq.inserir(auxAresta->verticeConectado, novaDistancia, novosPortaisUsados);

                std::cout << "Atualizando distância do vértice " << auxAresta->verticeConectado->getId()
                          << " para " << novaDistancia << " com " << novosPortaisUsados << " portais usados" << std::endl;
            }
            auxAresta = auxAresta->next;
        }
    }

    std::cout << "Finalizando Dijkstra" << std::endl;

     for (int i = 0; i <= maxPortais; i++) {
          std::cout << "distancia ate o final com "<<i<< " portais: " << distancias[n - 1][i] << std::endl;
     }
     for (int i = 0; i <= maxPortais; i++) {
          if ((distancias[n - 1][i]) <= energia) {
               return 1;
          }
     }
    return 0;
};

int GrafoList::aEstrela(int maxEnergia, int maxPortais, Vertex* vInicio, Vertex* vFinal) const{

     ListaAEstrela abertos(this->maxArestas);
     ListaAEstrela fechados(this->maxArestas);

     std::cout << "listas aberto e fechado criadas" << std::endl;

     NodeA nodeInicio(vInicio, vInicio, vFinal, 0, 0);
     abertos.inserir(nodeInicio);

     std::cout << "Nodeinicio criado e inserido na lista abertos" << std::endl;

     while(!abertos.empty()){
          //pode ser pointer?
          NodeA current = abertos.retirar();
          std::cout << "aberto atualmente: " << current.getVerticeAtual()->getId() << std::endl;

          int arestasAtuais = current.getVerticeAtual()->getNArestas();
          PriorityQueue adjacentes(arestasAtuais);
          std::cout << "ListaAdjacentes criada" << std::endl;
          Aresta* auxAresta = current.getVerticeAtual()->getArestas();

          for (int i = 0; i < arestasAtuais; i++){
               //tamanho aresta + current Tamanho sem heuristica == Distancia da aresta + distancia do vertice fonte até o inicio
               float dist = auxAresta->tamanhoAresta + current.getG();
               adjacentes.inserir(auxAresta->verticeConectado, dist, current.getPortaisUsados() + (auxAresta->portal ? 1 : 0));
               std::cout << "Aresta " << i + 1 << "do vertice " << current.getVerticeAtual()->getId()<< "inserida" << std::endl;
               auxAresta = auxAresta->next;
          }

          while (!adjacentes.empty()){
          
               Caminho adjacente = adjacentes.retirar();
               std::cout << "aresta " << adjacente.verticeId << "retirada" << std::endl;
               NodeA adjacenteNode(adjacente.verticeAtual, vInicio, vFinal, adjacente.distancia, adjacente.portais);
               if(adjacente.verticeAtual->getId() == vFinal->getId()){
                    std::cout << " distancia encontrada: " << adjacenteNode.getF() << " energia maxima é: " << maxEnergia << std::endl;
                    if (adjacenteNode.getF() <= maxEnergia && adjacenteNode.getPortaisUsados() <= maxPortais){
                         std::cout << "Deu certo" << std::endl;
                         return 1;
                    } else{
                         std::cout << "deu errado" << std::endl;
                         return 0;
                    }
               }
               std::cout << "AdjacenteNode criado com sucesso" << std::endl;
               NodeA* nodeAtualAberto = abertos.find(&adjacenteNode);
               if (nodeAtualAberto != nullptr){
                    if (nodeAtualAberto->getF() < adjacenteNode.getF()){
                         std::cout << "node atual ja esta aberto e com distancia menor" << std::endl;
                         continue;
                    }
               } 
               delete nodeAtualAberto;
               NodeA* nodeAtualFechado = fechados.find(&adjacenteNode);
               if (nodeAtualFechado != nullptr){
                    if (nodeAtualFechado->getF() < adjacenteNode.getF()){
                         std::cout << "node ja esta fechado e com distancia menor" << std::endl;
                         continue;
                    }
               }
               delete nodeAtualFechado;
               abertos.inserir(adjacenteNode);
          }
          fechados.inserir(current);
     }
     return 0;
}
