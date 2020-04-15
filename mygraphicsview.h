#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QToolTip>
#include <QtMath>
class MyGraphicsView:public QGraphicsView
{
    Q_OBJECT
    //Q_PROPERTY(Qt::KeyboardModifiers Modifiers READ Modifiers WRITE setModifiers)
private:

protected:
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
//    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

public:

    QImage img;
    bool pixelValue = 1;
    bool zoomEnabled = 0;
    QPointF scenePos;
    MyGraphicsView(QWidget *parent = nullptr);
    void tooltip(QPointF point, bool state);
};

#endif // MYGRAPHICSVIEW_H
