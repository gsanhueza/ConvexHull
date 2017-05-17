#ifndef GENERATOR_H
#define GENERATOR_H
#include <ctime>
#include <vector>
#include "Punto.h"

using namespace std;

template<class T>
class Generator
{
public:
    static vector<Punto<T>> generateRandomCloud(const int numPoints);

private:
    static T getRandomNumber(const int lower, const int upper);
};

template<class T>
vector<Punto<T>> Generator<T>::generateRandomCloud(const int numPoints)
{
    srand(time(0));
    vector<Punto<T>> cloud;

    for (int i = 0; i < numPoints; i++)
    {
        cloud.push_back(Punto<T>(getRandomNumber(0, 1000), getRandomNumber(0, 1000)));
    }

    return cloud;
}

template<typename T>
T Generator<T>::getRandomNumber(const int lower, const int upper)
{
    return lower + (rand() % upper);
}

#endif // GENERATOR_H
