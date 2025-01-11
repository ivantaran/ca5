#ifndef MYPLOT_H
#define MYPLOT_H

#include <QWidget>

class MyPlot : public QWidget {
    Q_OBJECT
public:
    MyPlot(QWidget *parent = nullptr);
    virtual ~MyPlot();

protected:
    void paintEvent(QPaintEvent *event);
signals:
private:
};

#endif /* MYPLOT_H */
