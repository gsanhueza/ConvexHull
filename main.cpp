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
    // Creación de nube de puntos
    int numPoints = static_cast<int>(pow(2, 11));
    vector<Punto<int>> cloud = Generator<int>::generateRandomCloud(numPoints, 1, 10000);

//     TESTING
//     cloud.clear();
//     cloud.push_back(Punto<int>(200, 100));
//     cloud.push_back(Punto<int>(100, 200));
//     cloud.push_back(Punto<int>(200, 200));
//     cloud.push_back(Punto<int>(300, 200));
//     cloud.push_back(Punto<int>(200, 300));

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
    Poligono<int> qh = calculator.grahamScan(cloud);
    qhTime = stopwatch.end();

    // Logging
    Logger logger("ANALISIS");

    logger << "Análisis de resultados para " << numPoints << " puntos." << endl << endl;
    cout << endl << endl;

    logger << "Tiempo de ejecución de Gift Wrapping: " << gwTime << " nanosegundos." << endl;
    cout << endl;
    logger << "Tiempo de ejecución de Graham Scan  : " << qhTime << " nanosegundos." << endl;
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
