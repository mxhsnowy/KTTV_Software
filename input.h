#ifndef INPUT_H
#define INPUT_H

#include <QDialog>
#include <QTime>
#include <QTimeEdit>
#include <QDoubleSpinBox>
#include <QSettings>
namespace Ui {
class Input;
}

class Input : public QDialog
{
    Q_OBJECT

public:
    explicit Input(QWidget *parent = nullptr, int chartType = 0, bool opened = 0);
    ~Input();
    void writeParamsfromSettings();


    void writeNewParams(QString chartName, int timeGet, int levelStart,
                             double levelGet, int levelEnd, QString unit);
    void writeSettings(QTime, int, QTime, double,
                       double, double, int);
public slots:
    void changeCharts(int chartType);
    void closeButton();
signals:
    void passParams(QTime, int, QTime, double,
                    double, double, int);
private:
    QStringList chartLabels = {"Độ ẩm", "Áp suất",
                             "Lượng mưa", "Nhiệt độ",
                             "Mực nước"};
    QStringList units = {"(ml)", "(mb)", "(ml)", "(°C)", "(ml)"};
    QList<int> timeGets = {60, 60, 60, 60, 60};
    QList<int> levelStarts = {0, 946, -5, -150, 47190};
    QList<double> levelGets = {2, 1, 1, 10, 0.5};
    QList<int> levelEnds = {100, 1052, 105, 650, 47390};

    Ui::Input *ui;

};

#endif // INPUT_H
