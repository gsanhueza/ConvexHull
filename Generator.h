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
    static vector<Punto<T>> generateRandomCloud(const int numPoints, const int &lower, const int &upper);

private:
    static T getRandomNumber(const int &lower, const int &upper);
};

template<class T>
vector<Punto<T>> Generator<T>::generateRandomCloud(const int numPoints, const int &lower, const int &upper)
{
    srand(time(nullptr));
    vector<Punto<T>> cloud;

    for (int i = 0; i < numPoints; i++)
    {
        cloud.push_back(Punto<T>(getRandomNumber(lower, upper), getRandomNumber(lower, upper)));
    }

    return cloud;
}

template<typename T>
T Generator<T>::getRandomNumber(const int &lower, const int &upper)
{
    return lower + (rand() % upper);
}

#endif // GENERATOR_H
