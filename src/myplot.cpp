#include "myplot.h"

#include <QPainter>
#include <QPainterPath>

MyPlot::MyPlot(MyReader *reader, QWidget *parent) : QWidget(parent) {
    setWindowTitle("CA5");
    m_reader = reader;
}

MyPlot::~MyPlot() {
}

void MyPlot::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    // QRect rect(100, 100, width() - 200, height() - 200);
    // painter.setClipRegion(rect);
    // painter.setClipping(false);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(0, 0, width(), height(), Qt::black);
    QPen pen(Qt::yellow);
    QPen pen1(Qt::darkYellow);
    QBrush brush(QColor(255, 255, 0, 32));
    pen.setWidthF(0.5);
    pen1.setWidthF(0.5);
    painter.setPen(pen);
    const auto &data = m_reader->data(width(), height());
    if (data.size()) {
        const auto &p0 = data.front();
        QPainterPath path;
        path.moveTo(p0.at(0), p0.at(1));
        for (const auto &p : data) {
            path.lineTo(p.at(0), p.at(1));
        }
        for (auto pd = data.rbegin(); pd != data.rend(); ++pd) {
            path.lineTo(pd->at(0), pd->at(2));
        }
        path.lineTo(p0.at(0), p0.at(1));
        path.setFillRule(Qt::WindingFill);
        painter.setBrush(brush);
        painter.drawPath(path);
    }
}
