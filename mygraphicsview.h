#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QToolTip>
#include <QRubberBand>
#include <QtMath>
class MyGraphicsView:public QGraphicsView
{
    Q_OBJECT
    //Q_PROPERTY(Qt::KeyboardModifiers Modifiers READ Modifiers WRITE setModifiers);
protected:
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
public:


    bool zoomEnabled = 0;
    QPointF scenePos;
    explicit MyGraphicsView(QWidget *parent = nullptr);
private:
    QRubberBand *rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    QRectF rubberBandRect;
    QPoint startPoint;
    bool isRubberBand;

};

#endif // MYGRAPHICSVIEW_H
