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
    int x = 0;
    auto y = data.front().at(1);
    QPen pen(Qt::yellow);
    p.setPen(pen);
    for (auto pd = std::next(data.begin()); pd != data.end(); ++pd) {
        p.drawLine(x, y, pd->at(0), pd->at(1));
        x = pd->at(0);
        y = pd->at(1);
    }

    y = data.front().at(2);
    x = 0;
    for (auto pd = std::next(data.begin()); pd != data.end(); ++pd) {
        p.drawLine(x, y, pd->at(0), pd->at(2));
        x = pd->at(0);
        y = pd->at(2);
    }
}
