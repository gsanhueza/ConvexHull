#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include "Punto.h"
#include "Segmento.h"
#include "Poligono.h"

using namespace std;

// TODO Implementar los algoritmos de Convex Hull
template<class T>
class ConvexHull
{
public:
    Poligono<T> giftWrapping(Punto<T> **cloud, const int numPoints);
    Poligono<T> quickHull(Punto<T> **cloud, const int numPoints);

private:
    Punto<T>* leftmostPoint(Punto<T> **cloud, const int numPoints);
};

// FIXME Está mal implementado, se repiten 2 puntos todo el rato o se cae solo, revisar main...
template<class T>
Poligono<T> ConvexHull<T>::giftWrapping(Punto<T> **cloud, const int numPoints)
{

    Punto<T> *pointOnHull = leftmostPoint(cloud, numPoints);
    Punto<T> *endpoint = new Punto<T>();
    Punto<T> **P = new Punto<T>*[numPoints];
    int i = 0;

    // Inicializador de puntos nuevos, no se usarán todos
    for (int k = 0; k < numPoints; k++)
    {
        P[k] = nullptr;
    }

    do
    {
        P[i] = new Punto<T>(*pointOnHull);
        *endpoint = *cloud[0];
        for (int j = 1; j < numPoints; ++j)
        {
            Segmento<T> seg(*P[i], *endpoint);
            if (*endpoint == *pointOnHull or seg.isThisPointAtLeft(*cloud[j]))
            {
                *endpoint = *cloud[j];
            }
        }
        ++i;
        *pointOnHull = *endpoint;
    } while (not (*endpoint == *cloud[0]));

    // Detectamos puntos en ConvexHull
    int k = 0;
    for (; k < numPoints; k++)
    {
        if (P[k] == nullptr)
        {
            break;
        }
    }

    return Poligono<T>(k, P);
}

template<class T>
Poligono<T> ConvexHull<T>::quickHull(Punto<T> **cloud, const int numPoints)
{
    for (int i = 0; i < numPoints; i++)
    {
        cout << *cloud[i] << endl;
    }

    Poligono<T> hull(numPoints, cloud);
    return hull;
}

template<class T>
Punto<T> * ConvexHull<T>::leftmostPoint(Punto<T> **cloud, const int numPoints)
{
    Punto<T> *leftmost = cloud[0];
    int i = 0;

    for (i = 1; i < numPoints; i++)
    {
        if (cloud[i]->getX() < leftmost->getX())
        {
            *leftmost = *cloud[i];
        }
    }

    return leftmost;
}

#endif // CONVEX_HULL_H
