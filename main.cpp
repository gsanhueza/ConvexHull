#include <iostream>
#include <assert.h>
#include "Punto.h"
#include "Vector.h"
#include "Segmento.h"
#include "Poligono.h"

using namespace std;

void testPunto(void);
void testVector(void);
void testSegmento(void);
void testPoligono(void);

/**
* @brief Main de la tarea.
*
* @return int Código de retorno 0.
*/
int main(void) {
    testPunto();
    testVector();
    testSegmento();
    testPoligono();
    return 0;
}

/**
* @brief Testea funcionalidad de clase Punto.
*
*/
void testPunto(void)
{
    Punto<int> p1;
    Punto<int> p2(5, 3);
    Punto<int> p3(p2);

    p1.print();
    p2.print();
    p3.print();

    assert(not (p1 == p2));
    assert(not (p1 == p3));
    assert(p2 == p3);
    Punto<int> p4(2, 4);
    Punto<int> p5(7, 7);

    assert((p3 + p4) == p5);
    p3.print();
    assert((p5 - p3) == p4);

    p1 = p2;
    assert(p1 == p2);

    p1 = p2 * 5;
    p1.print();

    Punto<double> p6(5.5, 3.8);
    p6.print();
    cout << endl;
}

/**
* @brief Testea funcionalidad de clase Vector.
*
*/
void testVector(void)
{
    Vector<int> v1;
    Vector<int> v2(1, 1, 2);
    Vector<int> v3(1, 1, 1);

    Vector<int> v4 = v2 + v3;

    int dot23 = v2.dotProduct(v3);
    Vector<int> cross23 = v2 * v3;

    v1.print();
    v2.print();
    v3.print();
    v4.print();

    cout << "Producto punto (int) --> (1, 1, 2) · (1, 1, 1): " << dot23 << endl;
    cout << "Producto cruz (int) --> (1, 1, 2) × (1, 1, 1): ";
    cross23.print();

    Vector<double> dv1;
    Vector<double> dv2(1.1, 1, 2);
    Vector<double> dv3(1.1, 1, 1);

    double ddot23 = dv2.dotProduct(dv3);
    Vector<double> dcross23 = dv2 * dv3;

    cout << "Producto punto (double) --> (1.1, 1, 2) · (1.1, 1, 1): " << ddot23 << endl;
    cout << "Producto cruz (double) --> (1, 1, 2) × (1, 1, 1): ";
    dcross23.print();

    Vector<int> v5(2, 3, 0);
    Vector<int> v6 = v5.normalize();
    cout << "Normalizacion (int) de (2, 3, 0): ";
    v6.print();

    Vector<double> v7(2, 3, 0);
    Vector<double> v8 = v7.normalize();
    cout << "Normalizacion (double) de (2, 3, 0): ";
    v8.print();

    Vector<int> v9(5, 3, 2017);
    Vector<int> v10(19, 23512342, 3);
    Vector<double> dv9(5, 3, 2017);
    Vector<double> dv10(19, 23512342, 3);

    cout << endl;

    cout << "Producto punto (int) numero grande/primo --> (5, 3, 2017) · (19, 23512342, 3): " << v9.dotProduct(v10) << endl;
    cout << "Producto punto (double) numero grande/primo --> (5, 3, 2017) · (19, 23512342, 3): " << dv9.dotProduct(dv10) << endl;

    Vector<int> cross9_10 = v9 * v10;
    Vector<double> dcross9_10 = dv9 * dv10;

    cout << "Producto cruz (int) numero grande/primo --> (5, 3, 2017) × (19, 23512342, 3): ";
    cross9_10.print();
    cout << "Producto cruz (double) numero grande/primo --> (5, 3, 2017) × (19, 23512342, 3): ";
    dcross9_10.print();

    cout << "Normalizacion (int) de (19, 23512342, 3): ";
    v10.normalize().print();
    cout << "Normalizacion (double) de (19, 23512342, 3): ";
    dv10.normalize().print();

    cout << endl;
}

/**
* @brief Testea funcionalidad de clase Segmento.
*
*/
void testSegmento(void)
{
    Punto<int> p1(3, 5);
    Punto<int> p2(6, 3);
    Segmento<int> s1(p1, p2);
    s1.print();
    Punto<int> p3(2, 5);
    assert(s1.isThisPointAtLeft(p3));
    assert(not s1.isThisPointAtRight(p3));
    assert(s1.isThisPointAtBottom(p3));
    assert(not s1.isThisPointAtTop(p3));

    Punto<int> p4(0, 0);
    Punto<int> p5(100000000, 2);
    Segmento<int> s2(p4, p5);

    Punto<int> aboveSegment(50000000, 1);
    assert(not s2.isThisPointAtLeft(aboveSegment));
    assert(not s2.isThisPointAtRight(aboveSegment));
    assert(not s2.isThisPointAtTop(aboveSegment));
    assert(not s2.isThisPointAtBottom(aboveSegment));

    Punto<int> justBelowRight(50000001, 1);
    assert(not s2.isThisPointAtLeft(justBelowRight));
    assert(s2.isThisPointAtRight(justBelowRight));
    assert(not s2.isThisPointAtTop(justBelowRight));
    assert(s2.isThisPointAtBottom(justBelowRight));

    Punto<double> dp4(0, 0);
    Punto<double> dp5(100000000, 2);
    Segmento<double> ds2(dp4, dp5);

    Punto<double> justAboveLeft(49999999, 1);

    assert(ds2.isThisPointAtLeft(justAboveLeft));
    assert(not ds2.isThisPointAtRight(justAboveLeft));
    assert(ds2.isThisPointAtTop(justAboveLeft));
    assert(not ds2.isThisPointAtBottom(justAboveLeft));
}

/**
* @brief Testea funcionalidad de clase Polígono.
*
*/
void testPoligono(void)
{
    Punto<int> p1(5, 0);
    Punto<int> p2(6, 4);
    Punto<int> p3(4, 5);
    Punto<int> p4(1, 5);
    Punto<int> p5(1, 0);
    Poligono<int> pol1(5, &p1, &p2, &p3, &p4, &p5);
    pol1.print();
    assert(pol1.isCCW());
    assert(pol1.area() == 22);

    Poligono<int> pol2(5, &p5, &p4, &p3, &p2, &p1);
    assert(not pol2.isCCW());

    Punto<int> innerPoint(3, 3);
    Punto<int> outerPoint(10, 10);
    assert(pol1.isInside(innerPoint));
    assert(not pol1.isInside(outerPoint));

    innerPoint.print();
    if (pol1.isInside(innerPoint))
    {
        cout << " está adentro del polígono." << endl;
    }
    else
    {
        cout << " está afuera del polígono." << endl;
    }

    cout << endl;

    outerPoint.print();
    if (pol1.isInside(outerPoint))
    {
        cout << " está adentro del polígono." << endl;
    }
    else
    {
        cout << " está afuera del polígono." << endl;
    }

}
