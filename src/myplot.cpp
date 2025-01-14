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
    auto data = m_reader->data(width(), height());
    const std::vector<double> &maxData = std::get<0>(data);
    const std::vector<double> &minData = std::get<1>(data);
    int i = 0;
    double v0 = maxData.front();
    QPen pen(Qt::yellow);
    p.setPen(pen);
    for (auto pv = std::next(maxData.begin()); pv != maxData.end(); ++pv) {
        p.drawLine(i, v0, i + 1, *pv);
        i++;
        v0 = *pv;
        if (i >= width()) {
            break;
        }
    }
    v0 = minData.front();
    for (auto pv = std::next(minData.begin()); pv != minData.end(); ++pv) {
        p.drawLine(i, v0, i + 1, *pv);
        i++;
        v0 = *pv;
        if (i >= width()) {
            break;
        }
    }
}
