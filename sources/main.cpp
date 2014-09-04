#include <QApplication>
#include <gl/gl.h>

#include "../headers/exampleclass.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ExampleClass p;
    p.show();

    //glPopMatrix();

    return app.exec();
}
