#include <QApplication>

#include "../headers/exampleclass.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ExampleClass p;
    p.show();

    return app.exec();
}
