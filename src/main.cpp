#include "myplot.h"
#include "myreader.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    MyReader reader("data.txt");
    // for (const auto &p : data) {
    // std::cout << std::put_time(&p.tm, "%c\t") << p.v[2] << '\n';
    // }
    QApplication app(argc, argv);
    MyPlot window(&reader);
    window.show();
    return app.exec();
}
