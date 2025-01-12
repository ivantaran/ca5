#include "myplot.h"

#include <QPainter>

MyPlot::MyPlot(MyReader *reader, QWidget *parent) : QWidget(parent) {
    setWindowTitle("CA5");
    m_reader = reader;
}

MyPlot::~MyPlot() {
}

void MyPlot::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.fillRect(0, 0, width(), height(), Qt::black);
    const auto data = m_reader->data(width(), height());
    int i = 0;
    double v0 = 0.0;
    QPen pen(Qt::yellow);
    p.setPen(pen);
    for (const double &v : data) {
        p.drawLine(i, v0, i + 1, v);
        i++;
        v0 = v;
        if (i >= width()) {
            break;
        }
    }
}
