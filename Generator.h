#ifndef GENERATOR_H
#define GENERATOR_H

#include "Punto.h"

using namespace std;

template<class T>
class Generator
{
public:
    static Punto<T>* generateRandomCloud(int numPoints);
};

template<class T>
Punto<T> * Generator<T>::generateRandomCloud(int numPoints)
{
    return nullptr;
}

#endif // GENERATOR_H
