#ifndef PAR_ORDENADO_HPP
#define PAR_ORDENADO_HPP

#include <math.h>

struct ParOrdenado{
     int x;
     int y;

     ParOrdenado();
     ParOrdenado(int x, int y);

     float distancia(ParOrdenado b) const;
};

#endif