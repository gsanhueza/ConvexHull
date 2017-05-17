#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <vector>
#include <algorithm>

#include "Punto.h"
#include "Vector.h"
#include "Segmento.h"
#include "Poligono.h"

using namespace std;

template<class T>
class ConvexHull
{
public:
    Poligono<T> giftWrapping(vector<Punto<T>> &cloud);
    Poligono<T> grahamScan(vector<Punto<T>> &cloud);

private:
    Punto<T> leftmostPoint(vector<Punto<T>> &cloud);
    Punto<T> lowestPoint(vector<Punto<T>> &cloud, int &lowestPos);
    void swapPoints(vector<Punto<T>> &cloud, const int a, const int b);
    void polarSort(vector<Punto<T>> &cloud, const int targetPos);
    int orientation(Punto<T> p, Punto<T> q, Punto<T> r);
    int distSq(Punto<T> p1, Punto<T> p2);
};

template<class T>
Poligono<T> ConvexHull<T>::giftWrapping(vector<Punto<T>> &cloud)
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

    reverse(P.begin(), P.end());                            // Convertir a CCW

    return Poligono<T>(P.size(), P);
}

template<class T>
Poligono<T> ConvexHull<T>::grahamScan(vector<Punto<T>> &cloud)
{
    int lowestPos = 0;
    lowestPoint(cloud, lowestPos);

    swapPoints(cloud, 0, lowestPos);
    Punto<T> p0(cloud.at(0));
    polarSort(cloud, 1);

    int M = 1;

    for (int i = 1; i < cloud.size(); i++)
    {
        while (i < cloud.size() - 1 and orientation(p0, cloud.at(i), cloud.at(i + 1)) == 0)
        {
            i++;
        }

        cloud.at(M) = cloud.at(i);
        M++;
    }

    vector<Punto<T>> hull;
    hull.push_back(cloud.at(0));
    hull.push_back(cloud.at(1));
    hull.push_back(cloud.at(2));

    for (int i = 3; i < M; i++)
    {
        while (orientation(hull.at(hull.size() - 2), hull.back(), cloud.at(i)) != 2)
        {
            hull.pop_back();
        }

        hull.push_back(cloud.at(i));
    }

    return Poligono<T>(hull.size(), hull);
}

template<class T>
Punto<T> ConvexHull<T>::leftmostPoint(vector<Punto<T>> &cloud)
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

template<class T>
Punto<T> ConvexHull<T>::lowestPoint(vector<Punto<T> >& cloud, int &lowestPos)
{
    Punto<T> lowest = cloud.at(0);
    int i = 0;

    for (i = 1; i < cloud.size(); i++)
    {
        if (cloud.at(i).getY() < lowest.getY())
        {
            lowest = cloud[i];
            lowestPos = i;
        }
        else if (cloud.at(i).getY() == lowest.getY())
        {
            if (cloud.at(i).getX() < lowest.getX())
            {
                lowest = cloud[i];
                lowestPos = i;
            }
        }
    }

    return lowest;
}

template<class T>
void ConvexHull<T>::swapPoints(vector<Punto<T> >& cloud, const int a, const int b)
{
    Punto<T> temp = cloud.at(a);
    cloud.at(a) = cloud.at(b);
    cloud.at(b) = temp;
}

template<class T>
void ConvexHull<T>::polarSort(vector<Punto<T> >& cloud, const int targetPos)
{
    sort(cloud.begin() + 1, cloud.end(), [=](Punto<T> p1, Punto<T> p2) {
        Punto<T> p0(cloud.at(0));
        int o = orientation(p0, p1, p2);
        if (o == 0)
            return (distSq(p0, p2) < distSq(p0, p1));

        return (o == 2);
    });
}

template<class T>
int ConvexHull<T>::orientation(Punto<T> p, Punto<T> q, Punto<T> r)
{
    int val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
                (q.getX() - p.getX()) * (r.getY() - q.getY());

    if (val == 0) return 0;                                 // Colineal
    return (val > 0) ? 1 : 2;                               // CW o CCW
}

template<class T>
int ConvexHull<T>::distSq(Punto<T> p1, Punto<T> p2)
{
    return (p1.getX() - p2.getX()) * (p1.getX() - p2.getX()) +
    (p1.getY() - p2.getY()) * (p1.getY() - p2.getY());
}


#endif // CONVEX_HULL_H
