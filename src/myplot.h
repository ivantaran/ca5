#ifndef MYPLOT_H
#define MYPLOT_H

#include "myreader.h"

#include <QBrush>
#include <QColor>
#include <QPen>
#include <QWidget>

class MyPlot : public QWidget {
    Q_OBJECT
public:
    MyPlot(MyReader *reader, QWidget *parent = nullptr);
    virtual ~MyPlot();

protected:
    void paintEvent(QPaintEvent *event);
signals:
private:
    MyReader *m_reader;
    const QPen MY_PEN = QPen(Qt::yellow, 0.5);
    const QPen MY_PEN1 = QPen(Qt::red, 0.5);
    const QBrush MY_BRUSH = QBrush(QColor(255, 255, 0, 32));
    const QColor BORDER_COLOR = QColor(20, 20, 20);
    const double PLOT_SCALE = 0.9;
};

#endif /* MYPLOT_H */
