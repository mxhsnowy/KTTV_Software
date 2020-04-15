#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QSettings>
#include <QListWidgetItem>
#include <QImageReader>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QLabel>
#include <QVector>
#include <QDebug>
#include <QJsonDocument>
#include <QDateTime>
#include <QGraphicsPixmapItem>
#include "linechart.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString getTime(double , double);
    QImage createImageWithOverlay(const QImage& baseImage, const QImage& overlayImage);
    void pointToValue(double x, double y);
    void drawToImage();
    void cropImage();
    void readJson();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:

    bool eventFilter(QObject *object, QEvent *event);

private slots:
    void next();
    void prev();
    void overlap();
    void zoomToggled(bool enabled);

    void openFolder();
    void itemClicked(QListWidgetItem *item);

private:
    QString thinned = "2.thinned";
    QString itemPath;
    QSize imgSize = QSize(0, 0);
    double valX;
    double valY;
    QString time;
    QPixmap image;
//    enum Type{moisture = 0,
//                pressure = 1,
//                rain = 2,
//                tempature = 3,
//                water = 4};
    LineChart *l = nullptr;
    QGraphicsScene *scene = new QGraphicsScene;
    //QImageReader *reader = nullptr;
    QString chosenDir;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
