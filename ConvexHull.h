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
    Poligono<T> giftWrapping(Punto<T> **cloud);
    Poligono<T> quickHull(Punto<T> **cloud);
};

template<class T>
Poligono<T> ConvexHull<T>::giftWrapping(Punto<T> **cloud)
{
    int i = 0;
    do
    {
        cout << *cloud[i] << endl;
    } while (cloud[++i] != nullptr);

//     Punto<T> pointOnHull = "leftmost point in cloud";
//     int i = 0;
//     Punto<T> endpoint;
//     do
//     {
//         Punto<T> *P = new Punto<T>[sizeof(cloud)]();
//         Punto<T> endpoint = cloud[0];
//         for (int j = 1; j < sizeof(cloud); ++j)
//         {
//             Segmento seg(P[i], endpoint);
//             if (endpoint == pointOnHull or seg.isThisPointAtLeft(cloud[j]))
//             {
//                 endpoint = cloud[j];
//             }
//         }
//         ++i;
//         pointOnHull = endpoint;
//     } while (endpoint != cloud[0]);
//
//     return Polygon(P);

    Poligono<T> wrap(0);
    return wrap;
}

template<class T>
Poligono<T> ConvexHull<T>::quickHull(Punto<T> **cloud)
{
    Poligono<T> hull(0);
    return hull;
}

#endif // CONVEX_HULL_H
