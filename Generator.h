#ifndef GENERATOR_H
#define GENERATOR_H
#include <ctime>
#include "Punto.h"

using namespace std;

template<class T>
class Generator
{
public:
    static Punto<T>** generateRandomCloud(const int numPoints);

private:
    static T getRandomNumber(const int lower, const int upper);
};

template<class T>
Punto<T> ** Generator<T>::generateRandomCloud(const int numPoints)
{
    srand(time(0));
    Punto<T> **cloud = new Punto<T>*[numPoints];

    for (int i = 0; i < numPoints; i++)
    {
        cloud[i] = new Punto<T>(getRandomNumber(0, 1000), getRandomNumber(0, 1000));
    }

    return cloud;
}

// TODO Aleatorizador
template<typename T>
T Generator<T>::getRandomNumber(const int lower, const int upper)
{
    return lower + (rand() % upper);
}

#endif // GENERATOR_H
