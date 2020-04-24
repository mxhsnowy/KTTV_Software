#include "mainwindow.h"
#include <QSplashScreen>
#include <QApplication>
#include <QThread>
int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    a.setOrganizationName("AI Academy");
    a.setApplicationName("Phần mềm khí tượng thủy văn");
    MainWindow w;
    QPixmap ss(":/icon/icons/splash.jpeg");
    QSplashScreen splash(ss);
    splash.show();
    splash.showMessage("Khởi tạo chương trình .");
    a.thread()->sleep(1);
    splash.showMessage("Khởi tạo chương trình ..");
    a.thread()->sleep(1);
    splash.showMessage("Khởi tạo chương trình ...");
    a.processEvents();
    QPalette pal = a.palette();
    pal.setColor(QPalette::Window,Qt::GlobalColor::cyan);

    a.setPalette(pal);
    w.show();
    w.setWindowState(Qt::WindowMaximized);
    return a.exec();
}
