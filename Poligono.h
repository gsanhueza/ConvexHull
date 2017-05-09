#ifndef POLIGONO_H
#define POLIGONO_H

#include <cstdarg>
#include <vector>
#include "Punto.h"

using namespace std;

template <class T>
/**
* @brief Clase Polígono.
*
*/
class Poligono
{
    /**
    * @brief Imprime información de este Poligono.
    *
    * @param U p_U: Tipo del Poligono.
    * @param out p_out: Stream de salida.
    * @param v p_v: Poligono a imprimir.
    * @return std::ostream& Stream de salida.
    */
    template<class U>
    friend ostream& operator<<(ostream &out, const Poligono<U> &p);

public:
    /**
    * @brief Constructor del polígono. Puede recibir una cantidad indeterminada de puntos.
    *
    * @param n p_n: Numero de puntos que tendrá el polígono.
    */
    Poligono(int n, ...);

    /**
    * @brief Destructor del polígono.
    *
    */
    ~Poligono();

    /**
    * @brief Calcula el área del polígono.
    *
    * @return double Área calculada.
    */
    double area(void) const;

    /**
    * @brief Revisa si el polígono está en CCW. Usamos la "Fórmula del área de Gauss"
    *
    * @return bool True si está en CCW. False si no.
    */
    bool isCCW(void) const;

    /**
    * @brief Revisa si el punto p está adentro de este polígono. Se usa Ray-Casting.
    *
    * @param p p_p: Punto a revisar.
    * @return bool True si el punto está adentro. False si está afuera.
    */
    bool isInside(Punto<T> p) const;

private:
    int numLados;
    vector<Punto<T>> listPuntos;

    /**
    * @brief Calcula el área usando Fórmula de Gauss.
    *
    * @return T Área (positiva o negativa según orientación).
    */
    T gaussArea(void) const;                                // Calcula el área de Gauss del polígono
};

template<class T>
Poligono<T>::Poligono(int n, ...) : numLados(n)
{
    va_list ap;
    va_start(ap, n);

    for (int i = 0; i < n; i++)
    {
        listPuntos.push_back(va_arg(ap, Punto<T>));
    }
    va_end(ap);
}

template<class T>
Poligono<T>::~Poligono()
{
}

template<class T>
bool Poligono<T>::isCCW() const
{
    return gaussArea() < 0;
}

template<class T>
double Poligono<T>::area() const
{
    return abs(gaussArea());
}

template<class T>
T Poligono<T>::gaussArea() const
{
    Punto<T> prev_p;
    T sum = 0;
    bool firstIteration = true;

    for (Punto<T> p : listPuntos)
    {
        if (firstIteration)
        {
            prev_p = p;
            firstIteration = false;
            continue;
        }
        sum += ((p.getX() - prev_p.getX()) * (p.getY() + prev_p.getY()));
        prev_p = p;
    }

    // Caso último punto con primer punto
    Punto<T> last_p = listPuntos.back();
    Punto<T> first_p = listPuntos.front();
    sum += ((first_p.getX() - last_p.getX()) * (first_p.getY() + last_p.getY()));

    return sum / 2;
}

template<class T>
bool Poligono<T>::isInside(Punto<T> p) const
{
    int crosses = 0;

    for (int i = 0; i < numLados; i++)
    {
        // Cruce hacia arriba
        if (((listPuntos[i].getY() <= p.getY()) && (listPuntos[i + 1].getY() > p.getY()))
            // Cruce hacia abajo
            || ((listPuntos[i].getY() > p.getY()) && (listPuntos[i + 1].getY() <=  p.getY())))
        {
            // Calculamos rayo correspondiente (coordenada x)
            double vt = (double)(p.getY() - listPuntos[i].getY()) / (listPuntos[i+1].getY() - listPuntos[i].getY());

            if (p.getX() < listPuntos[i].getX() + vt * (listPuntos[i+1].getX() - listPuntos[i].getX()))   // P.getX() < intersección
            {
                // Cruce válido de y = P.getY() a la derecha de P.getX()
                ++crosses;
            }
        }
    }
    return crosses % 2;
}

template<class U>
ostream& operator<<(ostream &out, const Poligono<U> &p)
{
    out << "Polígono de " << p.numLados << " lados." << endl;
    out << "Coordenadas: " << endl;
    for (Punto<U> P : p.listPuntos)
    {
        cout << " (" << P.getX() << ", " << P.getY() << ")" << endl;
    }
    return out;
}

#endif // POLIGONO_H
