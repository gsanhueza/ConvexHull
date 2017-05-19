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
    template<class U>
    /**
    * @brief Imprime información de este Segmento.
    *
    * @param U p_U: Tipo del Segmento.
    * @param out p_out: Stream de salida.
    * @param s p_s: Segmento a imprimir.
    * @return std::ostream& Stream de salida.
    */
    friend ostream& operator<<(ostream &out, const Segmento<U> &s);

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
    * @brief Retorna el largo del segmento.
    *
    * @return double Largo.
    */
    double getLength(void);

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
    bool isThisPointAtTop(const Punto<T>& p);

    /**
    * @brief Chequea si el punto está abajo del segmento.
    *
    * @param p p_p: Punto a revisar.
    * @return bool True si el punto está abajo. False si no.
    */
    bool isThisPointAtBottom(const Punto<T>& p);

    /**
    * @brief Chequea si el punto pertenece al segmento.
    *
    * @param p p_p: Punto a revisar.
    * @return bool True si pertenece al segmento. False si no.
    */
    bool isThisPointOnSeg(const Punto<T>& p);

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
Segmento<T>::Segmento(const Segmento<T>& other) : m_a(other.m_a), m_b(other.m_b), length(other.length)
{
}

template<class T>
Segmento<T>::~Segmento()
{
}

template<class T>
double Segmento<T>::getLength()
{
    return length;
}

template<class T>
Segmento<T> & Segmento<T>::operator=(const Segmento<T>& s)
{
    m_a = s.m_a;
    m_b = s.m_b;
    length = s.m_length;
    return *this;
}

template<class T>
bool Segmento<T>::operator==(const Segmento<T>& s) const
{
    return m_a == s.m_a and m_b == s.m_b;
}

template<class U>
ostream& operator<<(ostream &out, const Segmento<U> &s)
{
    out << "Segmento (" << s.m_a.getX() << ", " << s.m_a.getY() << ") --- (" << s.m_b.getX() << ", " << s.m_b.getY() << ")";
    return out;
}

template<class T>
bool Segmento<T>::isThisPointAtLeft(const Punto<T>& p)
{
    vector<Punto<T>> points;
    points.push_back(m_a);
    points.push_back(m_b);
    points.push_back(p);
    Poligono<T> tester(3, points);

    return tester.isCCW();
}

template<class T>
bool Segmento<T>::isThisPointAtRight(const Punto<T>& p)
{
    vector<Punto<T>> points;
    points.push_back(m_a);
    points.push_back(m_b);
    points.push_back(p);
    Poligono<T> tester(3, points);

    return not tester.isCCW() and tester.area() > 0;
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

template<class T>
bool Segmento<T>::isThisPointOnSeg(const Punto<T>& p)
{
    vector<Punto<T>> points;
    points.push_back(m_a);
    points.push_back(m_b);
    points.push_back(p);
    Poligono<T> tester(3, points);

    return tester.gaussArea() == 0;
}


#endif // SEGMENTO_H
