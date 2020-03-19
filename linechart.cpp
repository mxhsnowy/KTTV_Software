#include "linechart.h"
#include "callout.h"

#include <QResizeEvent>
#include <QGraphicsScene>
#include <QChart>
#include <QGraphicsTextItem>
#include <QMouseEvent>

LineChart::LineChart(QWidget *parent)
    : QGraphicsView(new QGraphicsScene, parent),
      m_coordX(nullptr),
      m_coordY(nullptr),
      m_chart(nullptr),
      m_tooltip(nullptr)
{
    setDragMode(QGraphicsView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_chart = new QChart;
    m_chart->setPreferredWidth(2304);
    m_chart->setPreferredHeight(3200);
    m_chart->setTitle("Di chuyển để xem vị trí, chuột trái để giữ.");
    m_chart->legend()->hide();

    QLineSeries *series = getLine("F:\\Weathering with you\\kttv-phase1\\kttv_am\\2.thinned\\am_0_0.jpg");
    m_chart->addSeries(series);
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

    this->setMouseTracking(true);
}
void LineChart::callChart(){
//    m_chart->setMinimumSize(640, 480);
//    QLineSeries *series = getLine("F:\\Weathering with you\\kttv-phase1\\kttv_am\\2.thinned\\am_0_0.jpg");
//    m_chart->addSeries(series);
//    m_chart->createDefaultAxes();
//    m_chart->setAcceptHoverEvents(true);

//    setRenderHint(QPainter::Antialiasing);
//    scene()->addItem(m_chart);

//    m_coordX = new QGraphicsSimpleTextItem(m_chart);
//    m_coordX->setPos(m_chart->size().width()/2 - 50, m_chart->size().height());
//    m_coordX->setText("X: ");

//    m_coordY = new QGraphicsSimpleTextItem(m_chart);
//    m_coordY->setPos(m_chart->size().width()/2 + 50, m_chart->size().height());
//    m_coordY->setText("Y: ");

//    connect(series, &QLineSeries::clicked, this, &LineChart::keepCallout);
//    connect(series, &QLineSeries::hovered, this, &LineChart::tooltip);

//    this->setMouseTracking(true);
}

QLineSeries* LineChart::getLine(const QString &path){
    QImage inputImg(path);
    QLineSeries *series = new QLineSeries;
    for (int i = 0; i < inputImg.width(); ++i) {
        for (int j = 0; j < inputImg.height(); ++j) {
            if(inputImg.pixelColor(i, j) == QColor(255, 255, 255)){
                series->append(i, j);
            }
        }
    }
    return series;
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
    if (m_tooltip == nullptr)
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
