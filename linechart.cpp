#include "linechart.h"

#include <QResizeEvent>
#include <QGraphicsScene>
#include <QChart>
#include <QLineSeries>
#include <QSplineSeries>
#include <QGraphicsTextItem>
#include "callout.h"
#include "linechart.h"
#include <QMouseEvent>

LineChart::LineChart(QWidget *parent)
    : QGraphicsView(new QGraphicsScene, parent),
      m_coordX(0),
      m_coordY(0),
      m_chart(0),
      m_tooltip(0)
{
    setDragMode(QGraphicsView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // chart
    m_chart = new QChart;
    m_chart->setMinimumSize(640, 480);
    m_chart->setTitle("Hover the line to show callout. Click the line to make it stay");
    m_chart->legend()->hide();
    QLineSeries *series = new QLineSeries;
    series->append(1, 3);
    series->append(4, 5);
    series->append(5, 4.5);
    series->append(7, 1);
    series->append(11, 2);
    m_chart->addSeries(series);

    QSplineSeries *series2 = new QSplineSeries;
    series2->append(1.6, 1.4);
    series2->append(2.4, 3.5);
    series2->append(3.7, 2.5);
    series2->append(7, 4);
    series2->append(10, 2);
    m_chart->addSeries(series2);

    m_chart->createDefaultAxes();
    m_chart->setAcceptHoverEvents(true);

    setRenderHint(QPainter::Antialiasing);
    scene()->addItem(m_chart);

    m_coordX = new QGraphicsSimpleTextItem(m_chart);
    m_coordX->setPos(m_chart->size().width()/2 - 50, m_chart->size().height());
    m_coordX->setText("X: ");
    m_coordY = new QGraphicsSimpleTextItem(m_chart);
    m_coordY->setPos(m_chart->size().width()/2 + 50, m_chart->size().height());
    m_coordY->setText("Y: ");

    connect(series, &QLineSeries::clicked, this, &LineChart::keepCallout);
    connect(series, &QLineSeries::hovered, this, &LineChart::tooltip);

    connect(series2, &QSplineSeries::clicked, this, &LineChart::keepCallout);
    connect(series2, &QSplineSeries::hovered, this, &LineChart::tooltip);

    this->setMouseTracking(true);
}

void LineChart::resizeEvent(QResizeEvent *event)
{
    if (scene()) {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
         m_chart->resize(event->size());
         m_coordX->setPos(m_chart->size().width()/2 - 50, m_chart->size().height() - 20);
         m_coordY->setPos(m_chart->size().width()/2 + 50, m_chart->size().height() - 20);
         const auto callouts = m_callouts;
         for (Callout *callout : callouts)
             callout->updateGeometry();
    }
    QGraphicsView::resizeEvent(event);
}

void LineChart::mouseMoveEvent(QMouseEvent *event)
{
    m_coordX->setText(QString("X: %1").arg(m_chart->mapToValue(event->pos()).x()));
    m_coordY->setText(QString("Y: %1").arg(m_chart->mapToValue(event->pos()).y()));
    QGraphicsView::mouseMoveEvent(event);
}

void LineChart::keepCallout()
{
    m_callouts.append(m_tooltip);
    m_tooltip = new Callout(m_chart);
}

void LineChart::tooltip(QPointF point, bool state)
{
    if (m_tooltip == 0)
        m_tooltip = new Callout(m_chart);

    if (state) {
        m_tooltip->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));
        m_tooltip->setAnchor(point);
        m_tooltip->setZValue(11);
        m_tooltip->updateGeometry();
        m_tooltip->show();
    } else {
        m_tooltip->hide();
    }
}
