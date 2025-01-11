#include "myplot.h"

#include <QPainter>

MyPlot::MyPlot(QWidget *parent) : QWidget(parent) {
    this->setWindowTitle("CA5");
}

MyPlot::~MyPlot() {
}

void MyPlot::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.fillRect(0, 0, width(), height(), Qt::black);
}
