#ifndef MYPLOT_H
#define MYPLOT_H

#include "myreader.h"

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
};

#endif /* MYPLOT_H */
