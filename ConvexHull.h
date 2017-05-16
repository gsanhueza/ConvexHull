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
    Punto<T>* leftmostPoint(Punto<T> **cloud);
};

// FIXME Está mal implementado, se repiten 2 puntos todo el rato...
template<class T>
Poligono<T> ConvexHull<T>::giftWrapping(Punto<T> **cloud, const int numPoints)
{

    Punto<T> *pointOnHull = leftmostPoint(cloud);
    Punto<T> *endpoint = nullptr;
    Punto<T> **P = new Punto<T>*[numPoints];
    int i = 0;

    do
    {
        P[i] = pointOnHull;
        endpoint = cloud[0];
        for (int j = 1; j < numPoints; ++j)
        {
            Segmento<T> seg(*P[i], *endpoint);
            if (endpoint == pointOnHull or seg.isThisPointAtLeft(*cloud[j]))
            {
                endpoint = cloud[j];
            }
        }
        ++i;
        pointOnHull = endpoint;
    } while (endpoint != cloud[0] and i <= numPoints);

    return Poligono<T>(numPoints, P);
}

template<class T>
Poligono<T> ConvexHull<T>::quickHull(Punto<T> **cloud, const int numPoints)
{
    int i = 0;
    do
    {
        cout << *cloud[i] << endl;
    } while (cloud[++i] != nullptr);

    Poligono<T> hull(numPoints, cloud);
    return hull;
}

template<class T>
Punto<T> * ConvexHull<T>::leftmostPoint(Punto<T> **cloud)
{
    Punto<T> *leftmost = cloud[0];
    int i = 0;
    while (cloud[++i] != nullptr)
    {
        if (cloud[i]->getX() < leftmost->getX())
        {
            leftmost = cloud[i];
        }
    }

    return leftmost;
}

#endif // CONVEX_HULL_H
