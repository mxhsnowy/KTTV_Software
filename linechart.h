#ifndef LINECHART_H
#define LINECHART_H


#include <QGraphicsView>
#include <QChart>
#include <QLineSeries>
QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QMouseEvent;
class QResizeEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

class Callout;

QT_CHARTS_USE_NAMESPACE

class LineChart: public QGraphicsView
{
    Q_OBJECT

public:
    LineChart(QWidget *parent = 0);
    QLineSeries* getLine(const QString &path);
    void callChart();

protected:
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void keepCallout();
    void tooltip(QPointF point, bool state);

private:

    //int height;
    //int width;
    QGraphicsSimpleTextItem *m_coordX = nullptr;
    QGraphicsSimpleTextItem *m_coordY = nullptr;
    QChart *m_chart;
    Callout *m_tooltip;
    QList<Callout *> m_callouts;
};


#endif // LINECHART_H
