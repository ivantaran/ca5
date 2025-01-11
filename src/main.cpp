#include "myplot.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MyPlot window;
    window.show();
    return app.exec();
}
