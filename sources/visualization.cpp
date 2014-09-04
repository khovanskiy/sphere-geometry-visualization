#include "../headers/visualization.h"

#include <math.h>

Visualization::Visualization(QWidget *parent) : QGLWidget(parent)
{
    setWindowTitle("Sphere geometry visualization");
    setMouseTracking(true);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    rotating = 0;
    view_pos.y = 0;
    view_pos.x = M_PI / 4;
    distance = 250;
    timer->start(100);

    radius = 100;
}

Visualization::~Visualization()
{
    delete timer;
}

void Visualization::setRadius(double radius)
{
    this->radius = radius;
}

double Visualization::getRadius() const
{
    return radius;
}

const Vector2D& Visualization::getPosition() const
{
    return view_pos;
}

bool Visualization::addPoint(const Vector2D& point)
{
    return addPoint(point, QColor::fromRgb(0xFF, 0xCC, 0x00, 0xFF));
}

bool Visualization::addPoint(const Vector2D& point, QColor color)
{
    points.push_back(std::make_pair(point, color));
    handleAddingPoint(point);
    return true;
}

int Visualization::removePoints(const Vector2D& point)
{
    return removePoints(point, 1e-8);
}

int Visualization::removePoints(const Vector2D& point, double accuracy)
{
    int count = 0;
    for (int i = 0; i < points.size(); ++i)
    {
        const Vector2D& current = points[i].first;
        if (fabs(current.x - point.x) <= accuracy && fabs(current.y - point.y) <= accuracy)
        {
            handleRemovingPoint(current);
            points[i] = points[points.size() - 1];
            points.pop_back();
            --i;
            ++count;
        }
    }
    return count;
}

bool Visualization::addLine(const Vector2D& start, const Vector2D& end)
{
    return addLine(start, end, QColor::fromRgbF(1,0,0,1));
}

bool Visualization::addLine(const Vector2D& start, const Vector2D& end, QColor color)
{
    lines.push_back(std::make_tuple(start, end, color));
    handleAddingLine(start, end);
    return true;
}

int Visualization::removeLines(const Vector2D& start, const Vector2D& end)
{
    return removeLines(start, end, 1e-8);
}

int Visualization::removeLines(const Vector2D& start, const Vector2D& end, double accuracy)
{
    int count = 0;
    for (int i = 0; i < lines.size(); ++i)
    {
        const Vector2D& first = std::get<0>(lines[i]);
        const Vector2D& second = std::get<1>(lines[i]);
        if (fabs(first.x - start.x) <= accuracy && fabs(first.y - start.y) <= accuracy)
        {
            if (fabs(second.x - end.x) <= accuracy && fabs(second.y - end.y) <= accuracy)
            {
                handleRemovingLine(first, second);
                lines[i] = lines[lines.size() - 1];
                lines.pop_back();
                --i;
                ++count;
            }
        }
    }
    return count;
}

void Visualization::clear()
{
    view_pos.y = 0;
    view_pos.x = M_PI / 4;
    points.clear();
    lines.clear();
}

void Visualization::setLineSegments(int line_segments)
{
    this->line_segments = line_segments;
}

int Visualization::getLineSegments() const
{
    return line_segments;
}

void Visualization::setSpaceSegments(int space_segments)
{
    this->space_segments = space_segments;
}

int Visualization::getSpaceSegments() const
{
    return space_segments;
}

void Visualization::handleAddingPoint(const Vector2D&)
{

}

void Visualization::handleRemovingPoint(const Vector2D&)
{

}

void Visualization::handleAddingLine(const Vector2D&, const Vector2D&)
{

}

void Visualization::handleRemovingLine(const Vector2D&, const Vector2D&)
{

}

void Visualization::perspective(float fovx, float aspect, float zNear, float zFar)
{
    double xmax = zNear * tan(fovx * M_PI / 360.0);
    double xmin = -xmax;

    double ymin = xmin / aspect;
    double ymax = xmax / aspect;


    double m[] = {(2.0 * zNear) / (xmax - xmin),     0,                              (xmax + xmin) / (xmax - xmin),      0,
                  0,                                 (2.0 * zNear) / (ymax - ymin),  (ymax + ymin) / (ymax - ymin),      0,
                  0,                                 0,                              -(zFar + zNear) / (zFar - zNear),   -(2.0 * zFar * zNear) / (zFar - zNear),
                  0,                                 0,                              -1.0,                               0};

    glMultMatrixd(m);
}

void Visualization::lookAt(const Vector3D &camera, const Vector3D &lookAt, const Vector3D &temp)
{
    Vector3D f = lookAt;
    f -= camera;
    f.normalize();
    Vector3D up = temp;
    up.normalize();

    const Vector3D& s = Vector3D::cross(f, up);
    const Vector3D& u = Vector3D::cross(s, f);

    double M[] =
    {
        s.x, u.x, -f.x, 0,
        s.y, u.y, -f.y, 0,
        s.z, u.z, -f.z, 0,
        0, 0, 0, 1
    };

    glMultMatrixd(M);
    glTranslated(-camera.x, -camera.y, -camera.z);
}

void Visualization::initializeGL()
{
    setAutoBufferSwap(true);
    qglClearColor(Qt::black);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void Visualization::resizeGL(int screen_w, int screen_h)
{
    glViewport(0, 0, screen_w, screen_h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    perspective(25.0, (float)screen_w / (float)screen_h, 1.0, 150.0);
    updateGL();
}

void Visualization::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_R:
    {
        clear();
    } break;
    case Qt::Key_V:
    {
        addPoint(view_pos);
    } break;
    case Qt::Key_X:
    {
        removePoints(view_pos);
    } break;
    case Qt::Key_A:
    case Qt::Key_Left:
    {
        view_pos.y -= 0.1f;
    } break;
    case Qt::Key_D:
    case Qt::Key_Right:
    {
        view_pos.y += 0.1f;
    } break;
    case Qt::Key_W:
    case Qt::Key_Up:
    {
        view_pos.x -= 0.1f;
    } break;
    case Qt::Key_S:
    case Qt::Key_Down:
    {
        view_pos.x += 0.1f;
    } break;
    case Qt::Key_Equal:
    case Qt::Key_Plus:
    {
        distance /= 2;
    } break;
    case Qt::Key_Minus:
    {
        distance *= 2;
    } break;
    case Qt::Key_Space:
    {
        rotating = !rotating;
    } break;
    default:
    {
        Console::print(e->key());
    }
    }

    e->accept();
}

void Visualization::mouseReleaseEvent(QMouseEvent *e)
{
    e->accept();
}

void Visualization::mouseMoveEvent(QMouseEvent *e)
{
    e->accept();
}

void Visualization::wheelEvent(QWheelEvent *e)
{
    if (e->delta() > 0)
    {
        if (distance - 20 >= getRadius())
        {
            distance -= 20;
        }
    }
    else
    {
        distance += 20;
    }
    e->accept();
}

Vector3D Visualization::map(const Vector2D &v)
{
    return Vector3D(radius * sin(v.x) * cos(v.y),
                    radius * sin(v.x) * sin(v.y),
                    radius * cos(v.x));
}

void Visualization::drawPoint(const Vector2D& p, const QColor& color)
{
    glColor4f(color.red(), color.greenF(), color.blueF(), color.alphaF());
    float x = radius * sin(p.x) * cos(p.y);
    float y = radius * sin(p.x) * sin(p.y);
    float z = radius * cos(p.x);
    glVertex3d(x, y, z);
}

void Visualization::drawLine(const Vector2D &a, const Vector2D &b, const QColor& color)
{
    Vector3D c = map(a);
    Vector3D d = map(b);

    Vector3D v = Vector3D::cross(c, d);
    double full_angle = Vector3D::angleBetween(c, d);
    if (fabs(full_angle) < 1e-8)
    {
        return;
    }

    glBegin(GL_LINE_STRIP);
    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    v.normalize();
    double dp = full_angle / line_segments;
    double p = 0;
    while (p <= full_angle + dp / 2)
    {
        double cosa = cos(-p);
        double sina = sin(-p);
        double cx = c.x * (cosa + (1 - cosa) * v.x * v.x) + c.y * ((1 - cosa) * v.y * v.x + sina * v.z) + c.z * ((1 - cosa) * v.z * v.x - sina * v.y);
        double cy = c.x * ((1 - cosa) * v.x * v.y - sina * v.z) + c.y * (cosa + (1 - cosa) * v.y * v.y) + c.z * ((1 - cosa) * v.z * v.y + sina * v.x);
        double cz = c.x * ((1 - cosa) * v.x * v.z + sina * v.y) + c.y * ((1 - cosa) * v.y * v.z - sina * v.x) + c.z * (cosa + (1 - cosa) * v.z * v.z);

        glVertex3d(cx, cy, cz);
        p += dp;
    }

    glEnd();
}

void Visualization::paintGL()
{

    if (rotating)
    {
        view_pos.y -= 0.1f;
        if (view_pos.y >= M_PI * 2)
        {
            view_pos.y = 0;
        }
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    const Vector3D& camera = Vector3D(distance * sin(view_pos.x) * cos(view_pos.y), distance * sin(view_pos.x) * sin(view_pos.y), distance * cos(view_pos.x));
    lookAt(camera, Vector3D(0,0,0), Vector3D(0,0,1));

    AxisView axis;
    axis.render();


    //Render
    glEnable( GL_BLEND );
    glEnable(GL_DEPTH_TEST);


    glTranslated(0, 0, 0);
    glRotated(0, 0, 0, 1);

    glPointSize(1);
    glBegin(GL_POINTS);
    glColor4f(0.5, 0.5, 0.5, 0.5);
    int n = 180 / space_segments;

    for (int a = 0; a <= 180; a += n)
    {
        for (int b = 0; b <= 360; b += n)
        {
            float x = radius * sin(a) * cos(b);
            float y = radius * sin(a) * sin(b);
            float z = radius * cos(a);
            glVertex3f(x, y, z);
        }
    }
    glEnd();

    for (int i = 0; i < lines.size(); ++i)
    {
        drawLine(std::get<0>(lines[i]), std::get<1>(lines[i]), std::get<2>(lines[i]));
    }

    glPointSize(3);
    glBegin(GL_POINTS);
    for (int i = 0; i < points.size(); ++i)
    {
        drawPoint(std::get<0>(points[i]), std::get<1>(points[i]));
    }
    glEnd();

}
