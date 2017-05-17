#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <vector>

#include "Punto.h"
#include "Segmento.h"
#include "Poligono.h"

using namespace std;

// TODO Implementar los algoritmos de Convex Hull
template<class T>
class ConvexHull
{
public:
    Poligono<T> giftWrapping(vector<Punto<T>> cloud, const int numPoints);
    Poligono<T> quickHull(vector<Punto<T>> cloud, const int numPoints);

private:
    Punto<T> leftmostPoint(vector<Punto<T>> cloud, const int numPoints);
};

// FIXME Está mal implementado, se repiten 2 puntos todo el rato o se cae solo, revisar main...
template<class T>
Poligono<T> ConvexHull<T>::giftWrapping(vector<Punto<T>> cloud, const int numPoints)
{
    Punto<T> pointOnHull = leftmostPoint(cloud, numPoints);
    Punto<T> endpoint;
    vector<Punto<T>> P;

    int i = 0;

    // Algoritmo principal
    do
    {
        cout << "pointOnHull = " << pointOnHull << endl;
        P.push_back(pointOnHull);                           // P[i] = pointOnHull
        endpoint = Punto<T>(cloud.at(0));
        for (int j = 1; j < numPoints; ++j)
        {
            Segmento<T> seg(P.at(i), endpoint);
            cout << "Comparando " << cloud.at(j) << " con " << seg << ": ANS = " << boolalpha << seg.isThisPointAtLeft(cloud.at(j)) << endl;
            if (endpoint == pointOnHull or seg.isThisPointAtLeft(cloud.at(j)))
            {
                endpoint = cloud.at(j);
            }
        }
        ++i;
        pointOnHull = endpoint;
        cout << " UPDATED pointOnHull = " << pointOnHull << endl;
    } while (not (endpoint == cloud.at(0)));

    return Poligono<T>(P.size(), P);
}

template<class T>
Poligono<T> ConvexHull<T>::quickHull(vector<Punto<T>> cloud, const int numPoints)
{
    for (int i = 0; i < numPoints; i++)
    {
        cout << cloud.at(i) << endl;
    }

    Poligono<T> hull(numPoints, cloud);
    return hull;
}

template<class T>
Punto<T> ConvexHull<T>::leftmostPoint(vector<Punto<T>> cloud, const int numPoints)
{
    Punto<T> leftmost = cloud.at(0);
    int i = 0;

    for (i = 1; i < numPoints; i++)
    {
        if (cloud.at(i).getX() < leftmost.getX())
        {
            leftmost = cloud[i];
        }
    }

    return leftmost;
}

#endif // CONVEX_HULL_H
