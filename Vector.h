#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>

using namespace std;

template<class T>
/**
* @brief Clase Vector.
*
*/
class Vector
{
    template<class U>
    /**
    * @brief Imprime información de este Vector.
    *
    * @param U p_U: Tipo del Vector.
    * @param out p_out: Stream de salida.
    * @param v p_v: Vector a imprimir.
    * @return std::ostream& Stream de salida.
    */
    friend ostream& operator<<(ostream &out, const Vector<U> &v);

public:
    /**
    * @brief Constructor vacío.
    *
    */
    Vector();

    /**
    * @brief Constructor con coordenadas dadas.
    *
    * @param x p_x: Coordenada X.
    * @param y p_y: Coordenada Y.
    * @param z p_z: Coordenada Z.
    */
    Vector(T x, T y, T z);

    /**
    * @brief Constructor de copia.
    *
    * @param other p_other: Vector a copiar.
    */
    Vector(const Vector& other);

    /**
    * @brief Destructor de la clase.
    *
    */
    ~Vector();

    /**
    * @brief Overload del operador de asignación.
    *
    * @param v p_v: Vector recibido.
    * @return Vector< T >& Referencia a este vector modificado.
    */
    Vector& operator= (const Vector& v);

    /**
    * @brief Overload del operador de igualdad.
    *
    * @param v p_v: Vector de quien chequear igualdad.
    * @return bool True si son el mismo vector (Por coordenadas). False si no.
    */
    bool operator== (const Vector& v) const;

    /**
    * @brief Overload del operador de suma.
    *
    * @param v p_v: Vector de quien calcular la suma de coordenadas.
    * @return Vector< T > Nuevo vector con la suma de las coordenadas de este vector y del vector recibido.
    */
    Vector<T> operator+ (const Vector<T>& v) const;

    /**
    * @brief Overload del operador de resta.
    *
    * @param v p_v: Vector de quien calcular la resta de coordenadas.
    * @return Vector< T > Nuevo vector con la resta de las coordenadas de este vector y del vector recibido.
    */
    Vector<T> operator- (const Vector<T>& v) const;

    /**
    * @brief Calcula el producto punto entre este vector y uno recibido.
    *
    * @param v p_v: Vector de quien calcular el producto punto.
    * @return T Producto punto.
    */
    T dotProduct(const Vector<T>& v) const;

    /**
    * @brief Calcula el producto cruz entre este vector y uno recibido.
    *
    * @param v p_v: Vector de quien calcular el producto cruz.
    * @return Vector< T > Vector resultado del producto cruz.
    */
    Vector<T> operator* (const Vector<T>& v) const;

    /**
    * @brief Normaliza el vector para que tenga largo 1.
    *
    * @return Vector< T > Nuevo vector, normalización de este vector.
    */
    Vector<T> normalize(void) const;

    /**
    * @brief Getter de X.
    *
    * @return T Coordenada X.
    */
    T getX() const;

    /**
    * @brief Getter de Y.
    *
    * @return T Coordenada Y.
    */
    T getY() const;

    /**
    * @brief Getter de Z.
    *
    * @return T Coordenada Z.
    */
    T getZ() const;

private:
    T m_x;
    T m_y;
    T m_z;
};

template<class T>
Vector<T>::Vector() : m_x(0), m_y(0), m_z(0)
{
}

template<class T>
Vector<T>::Vector(T x, T y, T z) : m_x(x), m_y(y), m_z(z)
{
}

template<class T>
Vector<T>::Vector(const Vector<T>& other) : m_x(other.m_x), m_y(other.m_y), m_z(other.m_z)
{
}

template<class T>
Vector<T>::~Vector()
{
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v)
{
    m_x = v.m_x;
    m_y = v.m_y;
    m_z = v.m_z;
    return *this;
}

template<class T>
bool Vector<T>::operator==(const Vector<T>& v) const
{
    return m_x == v.m_x and m_y == v.m_y and m_z == v.m_z;
}

template<class T>
Vector<T> Vector<T>::operator+ (const Vector<T>& v) const
{
    Vector<T> temp = *this;
    temp.m_x += v.m_x;
    temp.m_y += v.m_y;
    temp.m_z += v.m_z;
    return temp;
}

template<class T>
Vector<T> Vector<T>::operator-(const Vector<T>& v) const
{
    Vector<T> temp = *this;
    temp.m_x -= v.m_x;
    temp.m_y -= v.m_y;
    temp.m_z -= v.m_z;
    return temp;
}

template<class T>
T Vector<T>::dotProduct(const Vector<T>& v) const
{
    return (m_x * v.m_x) + (m_y * v.m_y) + (m_z * v.m_z);
}

template<class T>
Vector<T> Vector<T>::operator*(const Vector<T>& v) const
{
    T coord_x = (m_y * v.m_z) - (m_z * v.m_y);
    T coord_y = (- (m_z * v.m_x) - (m_x * v.m_z));
    T coord_z = (m_x * v.m_y) - (m_y * v.m_x);

    Vector<T> temp(coord_x, coord_y, coord_z);
    return temp;
}

template<class T>
Vector<T> Vector<T>::normalize() const
{
    Vector<T> temp = *this;
    double length = sqrt(pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2));
    temp.m_x = m_x / length;
    temp.m_y = m_y / length;
    temp.m_z = m_z / length;
    return temp;
}

template<class U>
ostream& operator<<(ostream &out, const Vector<U> &v)
{
    out << "Vector (" << v.m_x << ", " << v.m_y << ", " << v.m_z << ")";
    return out;
}

template<class T>
T Vector<T>::getX() const
{
    return m_x;
}

template<class T>
T Vector<T>::getY() const
{
    return m_y;
}

template<class T>
T Vector<T>::getZ() const
{
    return m_z;
}

#endif // VECTOR_H
