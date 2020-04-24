#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QSettings>
#include <QListWidgetItem>
#include <QImageReader>
#include <QSize>
#include <QScrollBar>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QLabel>
#include <QVector>
#include <QDebug>
#include <QMessageBox>
#include <QJsonDocument>
#include <QDateTime>
#include <QComboBox>
#include <QTextEdit>
#include <QGraphicsPixmapItem>
#include "linechart.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //QString getTime(double , double);
    QString getLitters(double, double);
    void extractData();
    QImage createImageWithOverlay(const QImage& baseImage, const QImage& overlayImage);
    void pointToValue(double x, double y);
    void removeDuplicate(QVector<double> litter, QVector<int> time, QVector<double> &rLitter, QVector<int> &rTime);
    void drawToImage();
    void cropImage();
    void readJson();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:

    bool eventFilter(QObject *object, QEvent *event);

private slots:
    void switchMode(int);
    void exportNow();
    void nextDay();
    void prevDay();
    void overlap();
    void zoomToggled(bool enabled);
    void quitApp();
    void openFolder();
    void itemClicked(QListWidgetItem *item);

private:
    QLabel *modeLabel = new QLabel;
    QTextEdit *edit = new QTextEdit;
    QComboBox *modeBox = new QComboBox;
    QString boxName = "Chọn chế độ  ";
    QStringList modeList = {"Ẩm", "Áp", "Mưa", "Nhiệt", "Nước"};
    QString thinned = "2.thinned";
    QString itemPath;
    QString exportPath;
    QString chosenDir;
    QString exportDir;
    int sizeHeight;
    int sizeWidth;
    QSize iconSize;
    double gridWidth;
    double gridHeight;
    int pixelLitter;

    QTime time;

    QImage image;
    QImage mask;

    int dayCount = 0;

    bool water = 0;
    bool moisture = 1;
    bool rain = 0;
    bool pressure = 0;
    bool tempature = 0;

    bool isMode = 0;
    QGraphicsScene *scene = new QGraphicsScene;
    //QImageReader *reader = nullptr;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
