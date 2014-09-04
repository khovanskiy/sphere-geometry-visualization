#include "../headers/exampleclass.h"

ExampleClass::ExampleClass()
{
    setLineSegments(20);
    setSpaceSegments(35);

    // 1 spherical right triangle
    addLine(Vector2D(0, 0), Vector2D(M_PI / 2, 0));
    addLine(Vector2D(M_PI / 2, 0), Vector2D(M_PI / 2, M_PI / 2));
    //this line will be green
    addLine(Vector2D(0, M_PI / 2), Vector2D(M_PI / 2, M_PI / 2), QColor::fromRgb(0x0, 0xFF, 0));

    // Add point and remove equal points
    addPoint(Vector2D(5,5));
    removePoints(Vector2D(5,5));

    // Add point and remove equal lines
    addLine(Vector2D(6,7), Vector2D(8, 9.1));
    removeLines(Vector2D(6,7), Vector2D(8, 9.1));

    // 30 random points
    for (int i = 0; i < 30; ++i)
    {
        Vector2D v;
        //v.x = Random::nextDouble(0, M_PI);
        //v.y = Random::nextDouble(0, M_PI);
        addPoint(v);
    }
}
