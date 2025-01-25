#include "myplot.h"
#include "myreader.h"

#include <QApplication>
#include <QFileDialog>
#include <QStringList>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QStringList argList = app.arguments();
    QString fileName;
    if (argList.length() < 2) {
        QFileDialog dialog;
        fileName = QFileDialog::getOpenFileName(nullptr, "Open Data", "",
                                                "CSV or Text Files (*.csv *.txt)", nullptr,
                                                QFileDialog::Options(QFileDialog::ExistingFile));
    } else {
        fileName = argList[1];
    }
    MyReader reader(fileName.toStdString());
    MyPlot window(&reader);
    window.show();
    return app.exec();
}
