#include "input.h"
#include "ui_input.h"
#include <QDebug>
#include <QCloseEvent>
Input::Input(QWidget *parent, int chartType, bool opened) :
    QDialog(parent),
    ui(new Ui::Input)
{
    ui->setupUi(this);
    if(opened){
        writeParamsfromSettings();
    }
    else{
       changeCharts(chartType);
    }
    connect(ui->Done, &QPushButton::clicked, this, &Input::closeButton);
}


void Input::changeCharts(int chartType){
    writeNewParams(chartLabels[chartType], timeGets[chartType],
                   levelStarts[chartType], levelGets[chartType],
                   levelEnds[chartType], units[chartType]);

}
void Input::writeSettings(QTime sTime, int spTime, QTime eTime,
                          double sLevel, double spLevel, double eLevel,
                          int day, bool keepPara, bool keepStartEnd){
    QSettings dialogSetup;
    dialogSetup.setValue("time/start", sTime);
    dialogSetup.setValue("time/space", spTime);
    dialogSetup.setValue("time/day", day);
    dialogSetup.setValue("time/end", eTime);
    dialogSetup.setValue("level/start", sLevel);
    dialogSetup.setValue("level/space", spLevel);
    dialogSetup.setValue("level/end", eLevel);
    dialogSetup.setValue("label/levelS", ui->lblStart->text());
    dialogSetup.setValue("label/levelE", ui->lblEnd->text());
    dialogSetup.setValue("label/levelG", ui->lblSpace->text());
    dialogSetup.setValue("check/keepPara", ui->keepPara->isChecked());
    dialogSetup.setValue("check/keepStartEnd", ui->keepStartEnd->isChecked());
    emit passParams(sTime, spTime, eTime,
                    sLevel, spLevel, eLevel,
                    day, keepPara, keepStartEnd);
}


void Input::writeNewParams(QString chartName, int timeGet, int levelStart,
                           double levelGet, int levelEnd, QString unit){
    QString stringStart = " bắt đầu";
    QString stringEnd = " kết thúc";
    QString stringget = "/1 dòng kẻ";
    ui->lblStart->setText(chartName+stringStart);
    ui->lblEnd->setText(chartName+stringEnd);
    ui->lblSpace->setText(chartName+stringget);
    ui->timeGet->setValue(timeGet);
    ui->levelGet->setValue(levelGet);
    ui->levelStart->setValue(levelStart);
    ui->levelEnd->setValue(levelEnd);
}
void Input::writeParamsfromSettings(){

    QSettings dialogSetup;
    ui->timeStart->setTime(dialogSetup.value("time/start").toTime());
    ui->timeGet->setValue(dialogSetup.value("time/space").toInt());
    ui->timeEnd->setTime(dialogSetup.value("time/end").toTime());
    ui->days->setValue(dialogSetup.value("time/day").toInt());
    ui->levelStart->setValue(dialogSetup.value("level/start").toDouble());
    ui->levelGet->setValue(dialogSetup.value("level/space").toDouble());
    ui->levelEnd->setValue(dialogSetup.value("level/end").toDouble());
    ui->lblStart->setText(dialogSetup.value("label/levelS").toString());
    ui->lblEnd->setText(dialogSetup.value("label/levelE").toString());
    ui->lblSpace->setText(dialogSetup.value("label/levelG").toString());
    ui->keepPara->setChecked(dialogSetup.value("check/keepPara").toBool());
    ui->keepStartEnd->setChecked(dialogSetup.value("check/keepStartEnd").toBool());
}

void Input::closeButton(){
    writeSettings(ui->timeStart->time(), ui->timeGet->value(), ui->timeEnd->time(),
                  ui->levelStart->value(), ui->levelGet->value(), ui->levelEnd->value(),
                  ui->days->value(), ui->keepPara->isChecked(), ui->keepStartEnd->isChecked());
    close();
    emit passOk(1);
}

void Input::closeEvent(QCloseEvent *e){
    emit passOk(0);
}

Input::~Input()
{

    delete ui;
}
