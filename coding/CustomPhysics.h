#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

namespace CustomPhysics
{
    template <typename V>
    class Vector2
    {
    private:
        /* data */

    public:
        Vector2();
        Vector2(V x, V y);
        template <typename W>
        explicit Vector2(const Vector2<W> &vector);
        V x, y;
    };

    typedef Vector2<float> Vector2f;
    typedef Vector2<int> Vector2i;

    template <typename V>
    inline Vector2<V>::Vector2() : x(0),
                                   y(0)
    {
    }

    template <typename V>
    inline Vector2<V>::Vector2(V x, V y) : x(x),
                                           y(y)
    {
    }
    template <typename V>
    inline Vector2<V> &operator+=(Vector2<V> &left, const Vector2<V> &right)
    {
        left.x += right.x;
        left.y += right.y;
        return left;
    }

    class Physics
    {
    private:
        /* data */
    public:
        bool static circleCol(float shape1Radius, Vector2f pos1, float shape2Radius, Vector2f pos2);
        double static distance(Vector2f pos1, Vector2f pos2);
    };

    inline double CustomPhysics::Physics::distance(Vector2f pos1, Vector2f pos2)
    {
        double dy = pos1.y - pos2.y;
        double dx = pos1.x - pos2.x;
        double distance = pow(dy, 2) + pow(dx, 2);
        //std::cout << distance << std::endl;
        //std::cout << pos1.y << std::endl;
        //std::cout << pos2.y << std::endl;

        return distance;
    }

    inline bool CustomPhysics::Physics::circleCol(float shape1Radius, Vector2f pos1, float shape2Radius, Vector2f pos2)
    {
        double dis = distance(pos1, pos2);
        //std::cout << pow((shape1Radius + shape2Radius), 2) << std::endl;
        return dis <= pow((shape1Radius + shape2Radius), 2);
    }
}
