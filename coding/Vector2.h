
#ifndef VECTOR2_H
#define VECTOR2_H

#include <SFML/Graphics.hpp>
#include <cmath>

template <typename T>

class Vector2
{

public:
    T x;
    T y;
    Vector2(T x = 0, T y = 0)
        : x(x), y(y)
    {
    }

    // the following functions use two variables which, for example, will be added to each other.
    // in the return of the function there is a calculation that'll return the right value for the calculation.
    // these can be used in situation where, for example, I want to addup a vector2 with itself and something else (example1 += example2)
    Vector2<T> operator+(const Vector2<T> &other) const
    {
        return Vector2<T>(x + other.x, y + other.y);
    }

    // returns two variables subtracted from each other
    // since this class is declared as const it guarantees that the state of the current object remains unchanged
    Vector2<T> operator-(const Vector2<T> &other) const
    {
        return Vector2<T>(x - other.x, y - other.y);
    }

    // returns two variables multiplied by each other
    Vector2<T> operator*(T scalar) const
    {
        return Vector2<T>(x * scalar, y * scalar);
    }

    // returns two variables devided by each other
    Vector2<T> operator/(T scalar) const
    {
        return Vector2<T>(x / scalar, y / scalar);
    }

    // updates the variable that calls by adding the other to it(example1 += example2)
    Vector2<T> &operator+=(const Vector2<T> &other) const
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2<T> &operator+=(const Vector2<T> &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    // this function is used to restrict the values of the x and y components of the vector2 object within a specifies range
    //  which is defined by the min and max.
    void Clamp(T min, T max)
    {
        if (x < min)
            x = min;
        else if (x > max)
            x = max;

        if (y < min)
            y = min;
        else if (y > max)
            y = max;
    }

    // Overload the subscript operator
    float &operator[](std::size_t index)
    {
        if (index == 0)
            return x;
        if (index == 1)
            return y;
        throw std::out_of_range("Index out of range for CustomVector2f");
    }

    // Overload for const access
    const float &operator[](std::size_t index) const
    {
        if (index == 0)
            return x;
        if (index == 1)
            return y;
        throw std::out_of_range("Index out of range for CustomVector2f");
    }
};

//this allows for vector * scalar.
template <typename T>
Vector2<T> operator*(const T scalar, const Vector2<T> &vec)
{
    return Vector2<T>(scalar * vec.x, scalar * vec.y);
}

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;

class Physics
{
public:
    // because it's static it can be accessed withou creating an object of the physics class.
    static bool circleCol(float shape1Radius, const Vector2f &pos1, float shape2Radius, const Vector2f &pos2);
    static double distance(const Vector2f &pos1, const Vector2f &pos2);
};

// check the distance between the two vectors given and return the dist as a double
inline double Physics::distance(const Vector2f &pos1, const Vector2f &pos2)
{
    double dy = pos1.y - pos2.y;
    double dx = pos1.x - pos2.x;
    double distance = pow(dy, 2) + pow(dx, 2);
    // std::cout << distance << std::endl;
    // std::cout << pos1.y << std::endl;
    // std::cout << pos2.y << std::endl;

    return distance;
}

// check if the two overlap if so it returns true
inline bool Physics::circleCol(float shape1Radius, const Vector2f &pos1, float shape2Radius, const Vector2f &pos2)
{
    double dis = distance(pos1, pos2);
    // std::cout << pow((shape1Radius + shape2Radius), 2) << std::endl;
    // check if the square root of the two radius' is bigger than the bigger or equal to
    return dis <= pow((shape1Radius + shape2Radius), 2);
}

#endif
