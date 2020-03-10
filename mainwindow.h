#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QSettings>
#include <QListWidgetItem>
#include <QImageReader>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpenFolder_triggered();



    void on_showFolder_itemClicked(QListWidgetItem *item);

private:
    QGraphicsScene *scene = new QGraphicsScene;
    //QImageReader *reader = nullptr;
    QString chosenDir;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
