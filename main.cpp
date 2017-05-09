#include <iostream>
#include <assert.h>

#include "Punto.h"
#include "Vector.h"
#include "Segmento.h"
#include "Poligono.h"
#include "ConvexHull.h"

using namespace std;

/**
* @brief Main de la tarea.
*
* @return int Código de retorno 0.
*/
int main(void) {
    // TODO Hacer las pruebas de tiempo para Convex Hull
    ConvexHull<int> calculator;
    calculator.giftWrapping(nullptr);
    calculator.quickHull(nullptr);

    return 0;
}
