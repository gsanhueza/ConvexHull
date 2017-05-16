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
// FIXME Cuando falla:
/*
Punto (404, 161)
Punto (768, 703)
Punto (894, 325)
Punto (503, 711)
Punto (711, 410)
Punto (690, 905)
Punto (841, 88)
Punto (461, 300)
cloud[0] is     Punto (404, 161)
pointOnHull was Punto (404, 161)
and endpoint is Punto (503, 711)

 *** Fallo: .../tarea_2 ha fallado ***
*/
// FIXME Cuando loopea:
/*
+Punto (658, 43)
+Punto (502, 320)
+Punto (298, 876)
+Punto (275, 574)
+Punto (631, 948)
+Punto (743, 159)
+Punto (787, 204)
+Punto (148, 670)
+cloud[0] is     Punto (658, 43)
+pointOnHull was Punto (148, 670)
+and endpoint is Punto (298, 876)
+
+cloud[0] is     Punto (658, 43)
+pointOnHull was Punto (298, 876)
+and endpoint is Punto (275, 574)
+
+cloud[0] is     Punto (658, 43)
+pointOnHull was Punto (275, 574)
+and endpoint is Punto (298, 876)
+
+cloud[0] is     Punto (658, 43)
+pointOnHull was Punto (298, 876)
+and endpoint is Punto (275, 574)
+
+cloud[0] is     Punto (658, 43)
+pointOnHull was Punto (275, 574)
+and endpoint is Punto (298, 876)
+
+cloud[0] is     Punto (658, 43)
+pointOnHull was Punto (298, 876)
+and endpoint is Punto (275, 574)
 */

template<class T>
Poligono<T> ConvexHull<T>::giftWrapping(Punto<T> **cloud, const int numPoints)
{

    Punto<T> *pointOnHull = leftmostPoint(cloud);
    Punto<T> *endpoint = new Punto<T>();
    Punto<T> **P = new Punto<T>*[numPoints];
    int i = 0;

    // Inicializador de puntos nuevos, no se usarán todos
    // FIXME Si no se usan todos, entonces hay que saber cuáles sí se usan, y pasarlos al polígono nuevo!
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
        cout << "cloud[0] is     " << *cloud[0] << endl;
        cout << "pointOnHull was " << *pointOnHull << endl;
        cout << "and endpoint is " << *endpoint << endl << endl;
        *pointOnHull = *endpoint;
    } while (not (*endpoint == *cloud[0]));

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
