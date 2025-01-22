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
    const auto &data = m_reader->data(width(), height());
    QPen pen(Qt::yellow);
    pen.setWidthF(0.5);
    p.setPen(pen);
    auto p0 = &data.front();
    for (auto pd = std::next(data.begin()); pd != data.end(); ++pd) {
        p.drawLine(p0->at(0), p0->at(1), pd->at(0), pd->at(1));
        p.drawLine(p0->at(0), p0->at(2), pd->at(0), pd->at(2));
        p0 = &(*pd);
    }
}
