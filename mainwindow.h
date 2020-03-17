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
#include <QGraphicsPixmapItem>
#include "linechart.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    bool eventFilter(QObject *object, QEvent *event);

private slots:
    void on_actionOpenFolder_triggered();


    void on_showFolder_itemClicked(QListWidgetItem *item);


    void on_actionZoom_toggled(bool arg1);

private:
    QLabel *name = new QLabel;
    QPixmap image;
    enum Type{moisture = 0,
                pressure = 1,
                rain = 2,
                tempature = 3,
                water = 4};
    LineChart *l = nullptr;
    QGraphicsScene *scene = new QGraphicsScene;
    //QImageReader *reader = nullptr;
    QString chosenDir;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
