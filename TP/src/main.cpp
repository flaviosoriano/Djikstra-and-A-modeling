#include <iostream>
#include <bits/stdc++.h>
#include "GrafoL.hpp"
#include "GrafoM.hpp"

int main(){
     int nVertices, nArestas, nPortais;
     std::cin >> nVertices >> nArestas >> nPortais;

     GrafoList floresta(nVertices, nArestas + nPortais);

     for (int i = 0; i < nVertices; i++){
          int x, y;
          std:: cin >> x >> y;
          floresta.addVertice(i, x, y);
     }
     for(int i = 0; i < nArestas; i++){
          int id1, id2;
          std::cin >> id1 >> id2;
          floresta.addAresta(id1, id2, 0);
     }
     for(int i = 0; i < nPortais; i++){
          int id1, id2;
          std::cin >> id1 >> id2;
          floresta.addAresta(id1, id2, 1);
     }
     int energia, maxPortais;
     std::cin >> energia >> maxPortais;
     int resultado = floresta.djkistra(energia, maxPortais);
     std::cout << resultado << std::endl;
}