#ifndef SEGMENTO_H
#define SEGMENTO_H
#include "Punto.h"
#include <math.h>

using namespace std;

template <class T>
/**
* @brief Clase Segmento.
*
*/
class Segmento
{
public:
    /**
    * @brief Constructor de segmento con coordenadas dadas.
    *
    * @param x p_x: Punto X.
    * @param y p_y: Punto Y.
    */
    Segmento(Punto<T> x, Punto<T> y);

    /**
    * @brief Constructor de copia.
    *
    * @param other p_other: Segmento a copiar.
    */
    Segmento(const Segmento& other);

    /**
    * @brief Destructor de la clase.
    *
    */
    ~Segmento();

    /**
    * @brief Overload del operador de asignación.
    *
    * @param s p_s: Segmento recibido.
    * @return Segmento< T >& Referencia a este segmento modificado.
    */
    Segmento& operator= (const Segmento& s);

    /**
    * @brief Overload del operador de igualdad.
    *
    * @param s p_s: Segmento de quien chequear igualdad.
    * @return bool True si son el mismo segmento. False si no.
    */
    bool operator== (const Segmento& s) const;

    /**
    * @brief Chequea si el punto está a la izquierda del segmento.
    *
    * @param p p_p: Punto a revisar.
    * @return bool True si el punto está a la izquierda. False si no.
    */
    bool isThisPointAtLeft(const Punto<T>& p);

    /**
    * @brief Chequea si el punto está a la derecha del segmento.
    *
    * @param p p_p: Punto a revisar.
    * @return bool True si el punto está a la derecha. False si no.
    */
    bool isThisPointAtRight(const Punto<T>& p);

    /**
    * @brief Chequea si el punto está arriba del segmento.
    *
    * @param p p_p: Punto a revisar.
    * @return bool True si el punto está arriba. False si no.
    */
    bool isThisPointAtTop(const Punto<T>& p);               // Detecta si punto está arriba

    /**
    * @brief Chequea si el punto está abajo del segmento.
    *
    * @param p p_p: Punto a revisar.
    * @return bool True si el punto está abajo. False si no.
    */
    bool isThisPointAtBottom(const Punto<T>& p);            // Detecta si punto está abajo

    /**
    * @brief Imprime información de este segmento.
    *
    */
    void print(void) const;                                 // Imprime detalles

private:
    Punto<T> m_a;
    Punto<T> m_b;
    double length;
};

template<class T>
Segmento<T>::Segmento(Punto<T> x, Punto<T> y) : m_a(x), m_b(y)
{
    length = sqrt(pow(m_a.getX() - m_b.getX(), 2.0) + pow(m_a.getY() - m_b.getY(), 2.0));
}

template<class T>
Segmento<T>::Segmento(const Segmento<T>& other) : m_a(other.m_a), m_b(other.m_b)
{
}

template<class T>
Segmento<T>::~Segmento()
{
}

template<class T>
Segmento<T> & Segmento<T>::operator=(const Segmento<T>& s)
{
    m_a = s.m_a;
    m_b = s.m_b;
    return *this;
}

template<class T>
bool Segmento<T>::operator==(const Segmento<T>& s) const
{
    return m_a == s.m_a and m_b == s.m_b;
}

template<class T>
void Segmento<T>::print() const
{
    cout << "Segmento (" << m_a.getX() << ", " << m_a.getY() << ") --- (" << m_b.getX() << ", " << m_b.getY() << ")" << endl;
}

template<class T>
bool Segmento<T>::isThisPointAtLeft(const Punto<T>& p)
{
    if (abs(m_a.getX() - m_b.getX()) < 0.001)               // epsilon magic
        return p.getX() < m_b.getX();

    // Usando ecuación de la recta
    double m = 1.0 * (m_b.getY() - m_a.getY()) / (m_b.getX() - m_a.getX());
    double b = m_b.getY() - (m * m_b.getX());
    double expected_y = m * p.getX() + b;

    // Si el punto P está arriba de lo esperado para el mismo X
    // y la pendiente es positiva, está a la izquierda
    return ((m > 0 ? 1 : -1) * expected_y < p.getY());
}

template<class T>
bool Segmento<T>::isThisPointAtRight(const Punto<T>& p)
{
    if (abs(m_a.getX() - m_b.getX()) < 0.001)               // epsilon magic
        return p.getX() > m_b.getX();

    // Usando ecuación de la recta
    double m = 1.0 * (m_b.getY() - m_a.getY()) / (m_b.getX() - m_a.getX());
    double b = m_b.getY() - (m * m_b.getX());
    double expected_y = m * p.getX() + b;

    // Si el punto P está debajo de lo esperado para el mismo X
    // y la pendiente es positiva, está a la derecha
    return ((m > 0 ? 1 : -1) * expected_y > p.getY());
}

template<class T>
bool Segmento<T>::isThisPointAtTop(const Punto<T>& p)
{
    if (abs(m_a.getX() - m_b.getX()) < 0.001)               // epsilon magic
        return false;

    // Usando ecuación de la recta
    double m = 1.0 * (m_b.getY() - m_a.getY()) / (m_b.getX() - m_a.getX());
    double b = m_b.getY() - (m * m_b.getX());
    double expected_y = m * p.getX() + b;

    // Si el punto P está arriba de lo esperado para el mismo X,
    // claramente está arriba
    return (expected_y < p.getY());
}

template<class T>
bool Segmento<T>::isThisPointAtBottom(const Punto<T>& p)
{
    if (abs(m_a.getX() - m_b.getX()) < 0.001)               // epsilon magic
        return false;

    // Usando ecuación de la recta
    double m = 1.0 * (m_b.getY() - m_a.getY()) / (m_b.getX() - m_a.getX());
    double b = m_b.getY() - (m * m_b.getX());
    double expected_y = m * p.getX() + b;

    // Si el punto P está abajo de lo esperado para el mismo X,
    // claramente está abajo
    return (expected_y > p.getY());
}

#endif // SEGMENTO_H
