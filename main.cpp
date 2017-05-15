#include <fstream>
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
    int numPoints = static_cast<int>(pow(2, 8));
    Punto<int> **cloud = Generator<int>::generateRandomCloud(numPoints);

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

    // Logging
    ofstream output("ANALISIS", ios::out);

    output << "Análisis de resultados para " << numPoints << " puntos." << endl << endl;

    output << "Tiempo de ejecución de Gift Wrapping: " << gwTime << " nanosegundos." << endl;
    output << "Tiempo de ejecución de Quick Hull   : " << qhTime << " nanosegundos." << endl;

    // Chequeo de igualdad
    if (gw != qh)
    {
        output << "Polígonos no son iguales." << endl;
    }
    else
    {
        output << "Polígonos iguales, ConvexHull creado correctamente." << endl;
    }

    output << "- - - - -" << endl;

    delete [] cloud;
    output.close();

    // Lectura de logging
    ifstream input("ANALISIS", ios::in);

    for (string line; getline(input, line);)
    {
        cout << line << endl;
    }

    input.close();

    return 0;
}
