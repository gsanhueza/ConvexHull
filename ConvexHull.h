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
    Poligono<T> grahamScan(vector<Punto<T>> cloud);

private:
    Punto<T> leftmostPoint(vector<Punto<T>> &cloud);
    Punto<T> lowestPoint(vector<Punto<T>> &cloud, int &lowestPos);
    void swapPoints(vector<Punto<T>> &cloud, const int a, const int b);
    void polarSort(vector<Punto<T>> &cloud, const int targetPos);
    int orientation(Punto<T> p, Punto<T> q, Punto<T> r);
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

    return Poligono<T>(P.size(), P);
}

// TODO grahamScan
template<class T>
Poligono<T> ConvexHull<T>::grahamScan(vector<Punto<T>> cloud)
{
    int lowestPos = 0;
    lowestPoint(cloud, lowestPos);
    swapPoints(cloud, 0, lowestPos);

    // sort points by polar angle with points[1]
    polarSort(cloud, 1);

    // We want points[0] to be a sentinel point that will stop the loop.
    swapPoints(cloud, 0, cloud.size() - 1);
    cout << "Test1" << endl;

    // M will denote the number of points on the convex hull.
    int M = 1;
    for (int i = 1; i < cloud.size(); i++)
    {
        vector<Punto<T>> temp;
        temp.push_back(cloud.at(M - 1));
        temp.push_back(cloud.at(M ));
        temp.push_back(cloud.at(i));

        while (not (Poligono<T>(3, temp).isCCW()))
        {
            if (M > 1)
            {
                M -= 1;
                continue;
            }
            else if (i == cloud.size())
            {
                break;
            }
            else
            {
                i++;
            }
        }

        M += 1;
        cloud.at(M) = cloud.at(i);
    }

    vector<Punto<T>> hull;
    hull.push_back(cloud[0]);
    hull.push_back(cloud[1]);
    hull.push_back(cloud[2]);

    for (int i = 3; i < M; i++)
    {
        while (orientation(hull.at(1), hull.front(), cloud.at(i)) != 2)
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

// FIXME polarSort
template<class T>
void ConvexHull<T>::polarSort(vector<Punto<T> >& cloud, const int targetPos)
{
    sort(cloud.begin(), cloud.end(), [=](Punto<T> a, Punto<T> b) {
        Vector<T> xCoordVec(1, 0, 0);
        Vector<T> testerA(a.getX() - cloud.at(targetPos).getX(), a.getY() - cloud.at(targetPos).getY(), 0);
        Vector<T> testerB(b.getX() - cloud.at(targetPos).getX(), b.getY() - cloud.at(targetPos).getY(), 0);

        return testerA.dotProduct(xCoordVec) > testerB.dotProduct(xCoordVec);
    });
}

template<class T>
int ConvexHull<T>::orientation(Punto<T> p, Punto<T> q, Punto<T> r)
{
    int val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
                (q.getX() - p.getX()) * (r.getY() - q.getY());

    if (val == 0) return 0;                                 // colinear
    return (val > 0)? 1: 2;                                 // clock or counterclock wise
}

#endif // CONVEX_HULL_H
