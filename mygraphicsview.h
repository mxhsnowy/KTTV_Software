#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QToolTip>
#include <QRubberBand>
#include <QtMath>
#include <QMessageBox>
#include <QScrollBar>
#include <QDebug>
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
    void drawLineTo(const QPoint &endpoint);
    QVector<QPointF> xdraw;
    QPainter painter;
    QImage image;
    bool drawEnabled = 0;
    bool grid = 0;
    bool zoomEnabled = 0;
    bool drag = 0;
    QPointF scenePos;
    QVector<QPointF> fourPoints;
    bool pointsClick = 0;
    explicit MyGraphicsView(QWidget *parent = nullptr);
signals:
    void copyVariable(int x_min, int y_min, int x_max, int y_max);
    void getMouseDrawPoints(const QVector<QPointF> &input);
private:


    bool ignore = 0;
    QRubberBand *rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    QRectF rubberBandRect;
    QPoint startPoint;
    bool isRubberBand;
    int panStartX, panStartY;

};

#endif // MYGRAPHICSVIEW_H
