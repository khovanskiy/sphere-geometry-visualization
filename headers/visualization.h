#ifndef PROGRAM_H
#define PROGRAM_H

#include <QtOpenGL>
#include <QGLWidget>
#include <QTimer>

#include <tuple>

#include "axisview.h"
#include "console.h"
#include "vector2d.h"
#include "vector3d.h"
//#include "random.h"

class Visualization : public QGLWidget
{
    Q_OBJECT
    
public:
    Visualization(QWidget *parent = 0);
    virtual ~Visualization();
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();
    void keyPressEvent(QKeyEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);

    const Vector2D& getPosition() const;
    void setRadius(double radius);
    double getRadius() const;
    bool addPoint(const Vector2D& point);
    bool addPoint(const Vector2D& point, QColor color);
    int removePoints(const Vector2D& point);
    int removePoints(const Vector2D& point, double accuracy);
    bool addLine(const Vector2D& start, const Vector2D& end);
    bool addLine(const Vector2D& start, const Vector2D& end, QColor color);
    int removeLines(const Vector2D& start, const Vector2D& end);
    int removeLines(const Vector2D& start, const Vector2D& end, double accuracy);
    void clear();

    void setLineSegments(int line_segments);
    int getLineSegments() const;
    void setSpaceSegments(int space_segments);
    int getSpaceSegments() const;

    virtual void handleAddingPoint(const Vector2D& point);
    virtual void handleRemovingPoint(const Vector2D& point);
    virtual void handleAddingLine(const Vector2D& start, const Vector2D& end);
    virtual void handleRemovingLine(const Vector2D& start, const Vector2D& end);

    Vector3D map(const Vector2D &v);
private:
    void perspective(float, float, float, float);
    void lookAt(const Vector3D& eye, const Vector3D& lookAt, const Vector3D& up);
    void drawPoint(const Vector2D& p, const QColor& color);
    void drawLine(const Vector2D &a, const Vector2D &b, const QColor& color);

    float distance;
    Vector2D view_pos;
    bool rotating;
    QTimer* timer;

    std::vector<std::tuple<Vector2D, Vector2D, QColor>> lines;
    std::vector<std::pair<Vector2D, QColor>> points;
    double radius;
    int line_segments;
    int space_segments;
};

#endif // PROGRAM_H
