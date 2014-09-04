#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <limits>
#include "vector2d.h"
#include "vector3d.h"

enum OrientationType
{
    RIGHT = -1, COLLINEAR = 0, LEFT = 1
};

static OrientationType orientation(const Vector2D& a, const Vector2D& b, const Vector2D& c)
{
    double l = (b.x - a.x) * (c.y - a.y);
    double r = (c.x - a.x) * (b.y - a.y);

    double e = (abs(l) + abs( r)) * std::numeric_limits<double>::epsilon() * 4;

    double det = l - r;

    if (det > e)
    {
       return OrientationType::LEFT;
    }

    if (det < -e)
    {
       return OrientationType::RIGHT;
    }

    return OrientationType::COLLINEAR;
}

static OrientationType orientation(const Vector3D& a, const Vector3D& b, const Vector3D& c)
{

}

#endif // ORIENTATION_H
