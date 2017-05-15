#include <iostream>
#include <cmath>

#include "Punto.h"
#include "Poligono.h"
#include "ConvexHull.h"
#include "Generator.h"
#include "Stopwatch.h"

using namespace std;

/**
* @brief Main de la tarea.
*
* @return int Código de retorno 0.
*/
int main(void) {
    // Creación de nube de puntos
    Punto<int> *cloud = Generator<int>::generateRandomCloud(static_cast<int>(pow(2, 10)));

    // Creación de convex hulls
    ConvexHull<int> calculator;

    // Tiempo transcurrido
    Stopwatch stopwatch;
    int gwTime;
    int qhTime;

    stopwatch.start();
    Poligono<int> gw = calculator.giftWrapping(cloud);
    gwTime = stopwatch.end();

    stopwatch.start();
    Poligono<int> qh = calculator.quickHull(cloud);
    qhTime = stopwatch.end();

    cout << "Tiempo de ejecución de Gift Wrapping: " << gwTime << " milisegundos." << endl;
    cout << "Tiempo de ejecución de Quick Hull   : " << qhTime << " milisegundos." << endl;

    // Chequeo de igualdad
    if (gw != qh)
    {
        cout << "Polígonos no son iguales." << endl;
    }
    else
    {
        cout << "Polígonos iguales, ConvexHull creado correctamente." << endl;
    }

    delete [] cloud;

    return 0;
}
