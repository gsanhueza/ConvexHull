#include <cmath>
#include <vector>

#include "Punto.h"
#include "Poligono.h"
#include "ConvexHull.h"

#include "Generator.h"
#include "Stopwatch.h"
#include "Logger.h"

using namespace std;

/**
* @brief Main de la tarea.
*
* @return int Código de retorno 0.
*/
int main(void) {
    // Tipo de punto
    typedef int pointType;

    // Creación de nube de puntos
    int numPoints = static_cast<int>(pow(2, 10));
    vector<Punto<pointType>> cloud = Generator<pointType>::generateRandomCloud(numPoints, 1, 10000);

//     TESTING
//     cloud.clear();
//     cloud.push_back(Punto<int>(200, 100));
//     cloud.push_back(Punto<int>(100, 200));
//     cloud.push_back(Punto<int>(200, 200));
//     cloud.push_back(Punto<int>(300, 200));
//     cloud.push_back(Punto<int>(200, 300));

    // Creación de convex hulls
    ConvexHull<pointType> calculator;

    // Tiempo transcurrido
    Stopwatch stopwatch;
    int gwTime;
    int qhTime;

    // Logging
    Logger logger("ANALISIS");

    logger << "Análisis de resultados para " << numPoints << " puntos." << endl << endl;
    cout << endl << endl;

    // Gift Wrapping
    stopwatch.start();
    Poligono<pointType> gw = calculator.giftWrapping(cloud);
    gwTime = stopwatch.end();

    logger << "Tiempo de ejecución de Gift Wrapping: " << gwTime << " microsegundos." << endl;
    cout << endl;

    // Graham Scan
    stopwatch.start();
    Poligono<pointType> qh = calculator.grahamScan(cloud);
    qhTime = stopwatch.end();

    logger << "Tiempo de ejecución de Graham Scan  : " << qhTime << " microsegundos." << endl;
    cout << endl;

    // Chequeo de igualdad
    if (gw != qh)
    {
        logger << "Polígonos no son iguales. " << endl;
        cout << endl;
        logger << "Motivo probable: Colinealidad." << endl;
        cout << endl;
        cout << gw << endl;
        cout << " v/s " << endl;
        cout << qh << endl;
    }
    else
    {
        logger << "Polígonos iguales, ConvexHull creado correctamente." << endl;
    }
    cout << endl;

    logger << "- - - - -" << endl;
    cout << endl;

    logger.close();

    return 0;
}
