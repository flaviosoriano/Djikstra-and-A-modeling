#include "ParOrdenado.hpp"
#include <cmath>

ParOrdenado::ParOrdenado() : x(0), y(0) {}

ParOrdenado::ParOrdenado(int x, int y) : x(x), y(y) {}

float ParOrdenado::distancia(ParOrdenado b) const{
    float dist;
    dist = std::sqrt((std::pow((this->x - b.x), 2)) + (std::pow((this->y - b.y), 2)));
    return dist;
}
