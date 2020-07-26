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
    explicit Input(QWidget *parent = nullptr);
    ~Input();
    void changeSetup(bool, QString chartType);

 //   bool opened = 0;
//    QTime startTime;
//    int spaceTime;
//    QTime endTime;
//    double startLevel;
//    double spaceLevel;
//    double endLevel;
//    int days;
    QPushButton *done;
    QTimeEdit *time1;
    QTimeEdit *time2;
    QDoubleSpinBox *timeS;
    QSpinBox *day;
    QSpinBox *bias;
    QDoubleSpinBox *level1;
    QDoubleSpinBox *level2;
    QDoubleSpinBox *levelS;
    QDoubleSpinBox *levelD;
    void readSettings(QTime, int, QTime, double, double, double);
    void writeSettings();
public slots:
    void closeButton();

//    void changeStartTime(const QTime &time);
//    void changeEndTime(const QTime &time);
//    void changeStartLevel();
//    void changeEndLevel();
private:
    //QSettings dialogSetup;
    Ui::Input *ui;

};

#endif // INPUT_H
