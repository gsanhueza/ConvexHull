#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <vector>
#include <algorithm>

#include "Punto.h"
#include "Segmento.h"
#include "Vector.h"
#include "Poligono.h"

using namespace std;

template<class T>
class ConvexHull
{
public:
    Poligono<T> giftWrapping(vector<Punto<T>> &cloud);
    Poligono<T> grahamScan(vector<Punto<T>> &cloud);

private:
    void leftmostPoint(vector<Punto<T>> &cloud, int &leftmostPos);
    void lowestPoint(vector<Punto<T>> &cloud, int &lowestPos);
    void swapPoints(vector<Punto<T>> &cloud, const int a, const int b);
    void polarSort(vector<Punto<T>> &cloud);
    int orientation(Punto<T> p, Punto<T> q, Punto<T> r);
    int distSq(Punto<T> p1, Punto<T> p2);
};

template<class T>
Poligono<T> ConvexHull<T>::giftWrapping(vector<Punto<T>> &cloud)
{
    vector<Punto<T>> hull;
    int l = 0;
    leftmostPoint(cloud, l);
    int p = l;

    // Algoritmo principal
    do
    {
        hull.push_back(cloud.at(p));
        int q = (p + 1) % cloud.size();
        for (int i = 0; i < cloud.size(); i++)
        {
            if (Poligono<T>(3, cloud.at(p), cloud.at(i), cloud.at(q)).isCCW())
            {
                q = i;
            }
        }
        p = q;
    } while (p != l);

    return Poligono<T>(hull.size(), hull);
}

template<class T>
Poligono<T> ConvexHull<T>::grahamScan(vector<Punto<T>> &cloud)
{
    int lowestPos = 0;
    lowestPoint(cloud, lowestPos);

    swapPoints(cloud, 0, lowestPos);
    Punto<T> p0(cloud.at(0));
    polarSort(cloud);                                       // FIXME Esta wea se demora más que la conchetumare xddxdxd

    int M = 1;

    for (int i = 1; i < cloud.size(); i++)
    {
        while (i < cloud.size() - 1 and Poligono<T>(3, p0, cloud.at(i), cloud.at(i + 1)).area() == 0)
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
        while (not Poligono<T>(3, hull.at(hull.size() - 2), hull.back(), cloud.at(i)).isCCW())
        {
            hull.pop_back();
        }

        hull.push_back(cloud.at(i));
    }

    return Poligono<T>(hull.size(), hull);
}

template<class T>
void ConvexHull<T>::leftmostPoint(vector<Punto<T>> &cloud, int &lowestPos)
{
    Punto<T> leftmost = cloud.at(0);
    int i = 0;

    for (i = 1; i < cloud.size(); i++)
    {
        if (cloud.at(i).getX() < leftmost.getX())
        {
            leftmost = cloud[i];
            lowestPos = i;
        }
        else if (cloud.at(i).getX() == leftmost.getX())
        {
            if (cloud.at(i).getY() < leftmost.getY())
            {
                leftmost = cloud[i];
                lowestPos = i;
            }
        }
    }
}

template<class T>
void ConvexHull<T>::lowestPoint(vector<Punto<T> >& cloud, int &lowestPos)
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
}

template<class T>
void ConvexHull<T>::swapPoints(vector<Punto<T> >& cloud, const int a, const int b)
{
    Punto<T> temp = cloud.at(a);
    cloud.at(a) = cloud.at(b);
    cloud.at(b) = temp;
}

template<class T>
void ConvexHull<T>::polarSort(vector<Punto<T> >& cloud)
{
    sort(cloud.begin() + 1, cloud.end(), [=](Punto<T> p1, Punto<T> p2) {
        Punto<T> p0(cloud.at(0));
        Poligono<T> tester(3, p0, p1, p2);
        if (tester.area() == 0)
            return (distSq(p0, p2) >= distSq(p0, p1));

        return (tester.isCCW());
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
    return  (p1.getX() - p2.getX()) * (p1.getX() - p2.getX()) +
            (p1.getY() - p2.getY()) * (p1.getY() - p2.getY());
}


#endif // CONVEX_HULL_H
