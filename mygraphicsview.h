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
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
public:
//    void drawLineTo(const QPoint &endpoint);
//    QImage image;
    explicit MyGraphicsView(QWidget *parent = nullptr);

public slots:
    void addReportedPoint(bool enabled);
    void enableZoom(bool enabled);
    void enableCutGrid(bool enabled);
    void enablePickPoints(bool enabled);
    void enableLimitLine(bool enabled);
    void enableDraw(bool enabled);
signals:
    void passAddingPoint(QPointF);
    void copyVariable(int x_min, int y_min, int x_max, int y_max);
    void passPoint(QPointF);
    void passRectPoint(QPointF);
    void passLimitPoint(QPointF);
    void passDrewPoints(const QVector<QPoint>& pointsVec);
private:
    bool draw = 0;
    bool drawing = 0;
    bool limitLine = 0;
    bool addingPoints = 0;
    bool zoomEnabled = 0;
    bool drag = 0;
    bool grid = 0;
    bool pickingPoints = 0;
    bool ignore = 0;
    int rad;
    QRubberBand *rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    QRectF rubberBandRect;
    QVector<QPoint> drewPoints;
    bool isRubberBand;
    int panStartX, panStartY;

};

#endif // MYGRAPHICSVIEW_H
