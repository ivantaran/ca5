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
    int w = PLOT_SCALE * width();
    int h = PLOT_SCALE * height();
    int x = 0.5 * (width() - w);
    int y = 0.5 * (height() - h);
    QRect rect(x, y, w, h);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(0, 0, width(), height(), BORDER_COLOR);
    painter.fillRect(rect, Qt::black);
    painter.setClipRegion(rect);
    painter.setPen(MY_PEN1);
    painter.drawLine(0, height() * 0.5, width(), height() * 0.5);
    painter.setPen(MY_PEN);
    const auto &data = m_reader->plotData(rect.x(), rect.y(), rect.width(), rect.height());
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
        painter.setBrush(MY_BRUSH);
        painter.drawPath(path);
    }
    painter.setClipping(false);
}
