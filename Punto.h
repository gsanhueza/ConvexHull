#ifndef PUNTO_H
#define PUNTO_H

using namespace std;

template<class T>
/**
* @brief Clase Punto.
*
*/
class Punto
{
public:
    /**
    * @brief Constructor vacío. Crea un punto en (0, 0)
    *
    */
    Punto();

    /**
    * @brief Constructor con coordenadas dadas.
    *
    * @param x p_x: Coordenada X
    * @param y p_y: Coordenada Y
    */
    Punto(T x, T y);

    /**
    * @brief Constructor de copia.
    *
    * @param other p_other: El punto a copiar.
    */
    Punto(const Punto& other);

    /**
    * @brief Destructor de la clase.
    *
    */
    ~Punto();

    /**
    * @brief Overload del operador de asignación.
    *
    * @param p p_p: Punto recibido.
    * @return Punto< T >& Referencia a este punto modificado.
    */
    Punto& operator= (const Punto& p);

    /**
    * @brief Overload del operador de igualdad.
    *
    * @param p p_p: Punto de quien chequear igualdad.
    * @return bool True si los puntos comparten coordenadas. False si no.
    */
    bool operator== (const Punto& p) const;

    /**
    * @brief Overload del operador de suma.
    *
    * @param p p_p: Punto de quien calcular la suma de coordenadas.
    * @return Punto< T > Nuevo punto con la suma de las coordenadas de este punto y del punto recibido.
    */
    Punto<T> operator+ (const Punto<T>& p) const;

    /**
    * @brief Overload del operador de resta.
    *
    * @param p p_p: Punto de quien calcular la resta de coordenadas.
    * @return Punto< T > Nuevo punto con la resta de las coordenadas de este punto y del punto recibido.
    */
    Punto<T> operator- (const Punto<T>& p) const;

    /**
    * @brief Overload del operador de multiplicación. Escala este punto.
    *
    * @param T p_T: Tipo del punto.
    * @param U p_U: Tipo del escalador.
    * @param scale p_scale: Escala.
    * @return Punto< T > Nuevo punto escalado.
    */
    template<typename U>
    Punto<T> operator* (const U scale) const;

    /**
    * @brief Imprime información de este punto.
    *
    */
    void print(void) const;

    /**
    * @brief Getter de X.
    *
    * @return T Coordenada X.
    */
    T getX(void) const;

    /**
    * @brief Getter de Y.
    *
    * @return T Coordenada Y.
    */
    T getY(void) const;

private:
    T m_x;
    T m_y;
};

template<class T>
Punto<T>::Punto() : m_x(0), m_y(0)
{
}

template<class T>
Punto<T>::Punto(T x, T y) : m_x(x), m_y(y)
{
}

template<class T>
Punto<T>::Punto(const Punto<T>& other) : m_x(other.m_x), m_y(other.m_y)
{
}

template<class T>
Punto<T>::~Punto()
{
}

template<class T>
Punto<T>& Punto<T>::operator=(const Punto<T>& p)
{
    m_x = p.m_x;
    m_y = p.m_y;
    return *this;
}

template<class T>
bool Punto<T>::operator==(const Punto<T>& p) const
{
    return m_x == p.m_x and m_y == p.m_y;
}

template<class T>
Punto<T> Punto<T>::operator+ (const Punto<T>& p) const
{
    Punto<T> temp = *this;
    temp.m_x += p.m_x;
    temp.m_y += p.m_y;
    return temp;
}

template<class T>
Punto<T> Punto<T>::operator-(const Punto<T>& p) const
{
    Punto<T> temp = *this;
    temp.m_x -= p.m_x;
    temp.m_y -= p.m_y;
    return temp;
}

template<class T>
template<typename U>
Punto<T> Punto<T>::operator*(const U scale) const
{
    Punto<T> temp = *this;
    temp.m_x *= scale;
    temp.m_y *= scale;
    return temp;
}

template<class T>
void Punto<T>::print() const
{
    cout << "Punto (" << m_x << ", " << m_y << ")" << endl;
}

template<class T>
T Punto<T>::getX() const
{
    return m_x;
}

template<class T>
T Punto<T>::getY() const
{
    return m_y;
}

#endif // PUNTO_H
