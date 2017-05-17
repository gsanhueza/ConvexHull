#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <vector>

#include "Punto.h"
#include "Segmento.h"
#include "Poligono.h"

using namespace std;

template<class T>
class ConvexHull
{
public:
    Poligono<T> giftWrapping(vector<Punto<T>> cloud);
    Poligono<T> quickHull(vector<Punto<T>> cloud);

private:
    Punto<T> leftmostPoint(vector<Punto<T>> cloud);
};

template<class T>
Poligono<T> ConvexHull<T>::giftWrapping(vector<Punto<T>> cloud)
{
    Punto<T> pointOnHull = leftmostPoint(cloud);
    Punto<T> endpoint;
    vector<Punto<T>> P;

    int i = 0;

    // Algoritmo principal
    do
    {
        P.push_back(pointOnHull);                           // P[i] = pointOnHull
        endpoint = Punto<T>(cloud.at(0));
        for (int j = 1; j < cloud.size(); ++j)
        {
            Segmento<T> seg(P.at(i), endpoint);
            if (endpoint == pointOnHull or seg.isThisPointAtLeft(cloud.at(j)))
            {
                endpoint = cloud.at(j);
            }
        }
        ++i;
        pointOnHull = endpoint;
    } while (not (endpoint == P.at(0)));

    return Poligono<T>(P.size(), P);
}

// TODO quickHull
template<class T>
Poligono<T> ConvexHull<T>::quickHull(vector<Punto<T>> cloud)
{
    return giftWrapping(cloud);
}

template<class T>
Punto<T> ConvexHull<T>::leftmostPoint(vector<Punto<T>> cloud)
{
    Punto<T> leftmost = cloud.at(0);
    int i = 0;

    for (i = 1; i < cloud.size(); i++)
    {
        if (cloud.at(i).getX() < leftmost.getX())
        {
            leftmost = cloud[i];
        }
    }

    return leftmost;
}

#endif // CONVEX_HULL_H
