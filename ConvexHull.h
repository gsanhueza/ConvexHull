#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include "Punto.h"
#include "Poligono.h"

using namespace std;

// TODO Implementar los algoritmos de Convex Hull
template<class T>
class ConvexHull
{
public:
    ConvexHull<T>();
    ~ConvexHull<T>();

    Poligono<T> giftWrapping(Punto<T> *cloud);
    Poligono<T> quickHull(Punto<T> *cloud);
};

template<class T>
ConvexHull<T>::ConvexHull()
{
}

template<class T>
ConvexHull<T>::~ConvexHull()
{
}

template<class T>
Poligono<T> ConvexHull<T>::giftWrapping(Punto<T>* cloud)
{
    Poligono<T> wrap(0);
    return wrap;
}

template<class T>
Poligono<T> ConvexHull<T>::quickHull(Punto<T>* cloud)
{
    Poligono<T> hull(0);
    return hull;
}

#endif // CONVEX_HULL_H
