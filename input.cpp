#include "input.h"
#include "ui_input.h"

Input::Input(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Input)
{
    ui->setupUi(this);
    done = ui->Done;
    time1 = ui->timeStart;
    time2 = ui->timeEnd;
    day = ui->days;
    level1 = ui->levelStart;
    level2 = ui->levelEnd;
    timeS = ui->timeGet;
    levelS = ui->levelGet;
    bias = ui->biasBox;
    levelD = ui->levelDec;
    connect(ui->Done, &QPushButton::clicked, this, &Input::closeButton);
//    startTime = ui->timeStart->time();
//    endTime = ui->timeEnd->time();
//    startLevel = ui->levelStart->value();
//    endLevel = ui->levelEnd->value();
//    connect(ui->timeStart, &QTimeEdit::timeChanged, this, &Input::changeStartTime);
//    connect(ui->timeEnd, &QTimeEdit::timeChanged, this, &Input::changeEndTime);
//    connect(ui->levelStart, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
//          [=](double d){ startLevel = d; });
//    connect(ui->levelEnd, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
//          [=](double d){ endLevel = d;});
//    connect(ui->days, QOverload<int>::of(&QSpinBox::valueChanged),
//          [=](int d){ days = d;});
 //   connect(ui->Done, QPushButton::clicked, this, )

}

void Input::readSettings(QTime sTime, int spTime, QTime eTime, double sLevel, double spLevel, double eLevel){

    ui->timeStart->setTime(sTime);
    ui->timeGet->setValue(spTime);
    ui->timeEnd->setTime(eTime);
    ui->levelStart->setValue(sLevel);
    ui->levelEnd->setValue(eLevel);
    ui->levelGet->setValue(spLevel);


//    if (chartType == "am"){
//        ui->lblStart->setText("Độ ẩm bắt đầu");
//        ui->lblEnd->setText("Độ ẩm kết thúc");
//        ui->lblSpace->setText("Độ ẩm/1 dòng");
//        dialogSetup.setValue("time/start", QTime(6, 30, 0));
//        dialogSetup.setValue("time/space", 15);
//        dialogSetup.setValue("time/end", QTime(8, 30, 0));
//        dialogSetup.setValue("level/start", 0);
//        dialogSetup.setValue("level/space", 2);
//        dialogSetup.setValue("level/end", 100);
////        ui->timeGet->setValue(15);
////        ui->levelGet->setValue(2);
////        ui->timeStart->setTime(QTime(6, 30, 0));
////        ui->timeEnd->setTime(QTime(8, 30, 0));
////        ui->levelStart->setValue(0);
////        ui->levelEnd->setValue(100);
//    }
//    else if (chartType == "ap"){
//        ui->lblStart->setText("Áp suất bắt đầu");
//        ui->lblEnd->setText("Áp suất kết thúc");
//        ui->lblSpace->setText("Áp suất/1 dòng");
//        dialogSetup.setValue("time/start", QTime(11, 15, 0));
//        dialogSetup.setValue("time/space", 15);
//        dialogSetup.setValue("time/end", QTime(13, 15, 0));
//        dialogSetup.setValue("level/start", 946);
//        dialogSetup.setValue("level/space", 1);
//        dialogSetup.setValue("level/end", 1052);
////        ui->timeGet->setValue(15);
////        ui->levelGet->setValue(1);
////        ui->timeStart->setTime(QTime(11, 15, 0));
////        ui->timeEnd->setTime(QTime(13, 15, 0));
////        ui->levelStart->setValue(946);
////        ui->levelEnd->setValue(1052);
//    }
//    else if (chartType == "mua"){
//        ui->lblStart->setText("Lượng mưa bắt đầu");
//        ui->lblEnd->setText("Lượng mưa kết thúc");
//        ui->lblSpace->setText("Lượng mưa/1 dòng");
//        dialogSetup.setValue("time/start", QTime(7, 20, 0));
//        dialogSetup.setValue("time/space", 10);
//        dialogSetup.setValue("time/end", QTime(8, 20, 0));
//        dialogSetup.setValue("level/start", -0.5);
//        dialogSetup.setValue("level/space", 0.1);
//        dialogSetup.setValue("level/end", 10.5);
////        ui->timeGet->setValue(10);
////        ui->levelGet->setValue(0.1);
////        ui->timeStart->setTime(QTime(7, 20, 0));
////        ui->timeEnd->setTime(QTime(8, 20, 0));
////        ui->levelStart->setValue(-0.5);
////        ui->levelEnd->setValue(10.5);
//    }
//    else if (chartType == "nhiet"){
//        ui->lblStart->setText("Nhiệt độ bắt đầu");
//        ui->lblEnd->setText("Nhiệt độ kết thúc");
//        ui->lblSpace->setText("Nhiệt độ/1 dòng");
//        dialogSetup.setValue("time/start", QTime(6, 30, 0));
//        dialogSetup.setValue("time/space", 10);
//        dialogSetup.setValue("time/end", QTime(8, 30, 0));
//        dialogSetup.setValue("level/start", -15);
//        dialogSetup.setValue("level/space", 1);
//        dialogSetup.setValue("level/end", 65);
////        ui->timeGet->setValue(10);
////        ui->levelGet->setValue(1);
////        ui->timeStart->setTime(QTime(6, 30, 0));
////        ui->timeEnd->setTime(QTime(8, 10, 0));
////        ui->levelStart->setValue(-15);
////        ui->levelEnd->setValue(65);
//    }
//    else if (chartType == "nuoc"){
//        ui->lblStart->setText("Lượng nước bắt đầu");
//        ui->lblEnd->setText("Lượng nước kết thúc");
//        ui->lblSpace->setText("Lượng nước/1 dòng");
//        dialogSetup.setValue("time/start", QTime(7, 0, 0));
//        dialogSetup.setValue("time/space", 10);
//        dialogSetup.setValue("time/end", QTime(7, 0, 0));
//        dialogSetup.setValue("level/start", 47190);
//        dialogSetup.setValue("level/space", 0.5);
//        dialogSetup.setValue("level/end", 47390);
////        ui->timeGet->setValue(10);
////        ui->levelGet->setValue(0.5);
////        ui->timeStart->setTime(QTime(7, 0, 0));
////        ui->timeEnd->setTime(QTime(7, 0, 0));
////        ui->levelStart->setValue(47190);
////        ui->levelEnd->setValue(47390);
//    }
}
void Input::writeSettings(){
    QSettings dialogSetup;
    dialogSetup.setValue("time/start", ui->timeStart->time());
    dialogSetup.setValue("time/space", ui->timeGet->value());
    dialogSetup.setValue("time/end", ui->timeEnd->time());
    dialogSetup.setValue("time/shift", ui->biasBox->value());
    dialogSetup.setValue("level/start", ui->levelStart->value());
    dialogSetup.setValue("level/space", ui->levelGet->value());
    dialogSetup.setValue("level/end", ui->levelEnd->value());
    dialogSetup.setValue("level/decrease", ui->levelDec->value());
    dialogSetup.setValue("label/levelS", ui->lblStart->text());
    dialogSetup.setValue("label/levelE", ui->lblEnd->text());
    dialogSetup.setValue("label/levelD", ui->lblDec->text());
    dialogSetup.setValue("label/levelG", ui->lblSpace->text());

//        if (chartType == "am"){
//            ui->lblStart->setText("Độ ẩm bắt đầu");
//            ui->lblEnd->setText("Độ ẩm kết thúc");
//            ui->lblSpace->setText("Độ ẩm/1 dòng");
//            dialogSetup.setValue("time/start", QTime(6, 30, 0));
//            dialogSetup.setValue("time/space", 15);
//            dialogSetup.setValue("time/end", QTime(8, 30, 0));
//            dialogSetup.setValue("level/start", 0);
//            dialogSetup.setValue("level/space", 2);
//            dialogSetup.setValue("level/end", 100);
//    //        ui->timeGet->setValue(15);
//    //        ui->levelGet->setValue(2);
//    //        ui->timeStart->setTime(QTime(6, 30, 0));
//    //        ui->timeEnd->setTime(QTime(8, 30, 0));
//    //        ui->levelStart->setValue(0);
//    //        ui->levelEnd->setValue(100);
//        }
//        else if (chartType == "ap"){
//            ui->lblStart->setText("Áp suất bắt đầu");
//            ui->lblEnd->setText("Áp suất kết thúc");
//            ui->lblSpace->setText("Áp suất/1 dòng");
//            dialogSetup.setValue("time/start", QTime(11, 15, 0));
//            dialogSetup.setValue("time/space", 15);
//            dialogSetup.setValue("time/end", QTime(13, 15, 0));
//            dialogSetup.setValue("level/start", 946);
//            dialogSetup.setValue("level/space", 1);
//            dialogSetup.setValue("level/end", 1052);
//    //        ui->timeGet->setValue(15);
//    //        ui->levelGet->setValue(1);
//    //        ui->timeStart->setTime(QTime(11, 15, 0));
//    //        ui->timeEnd->setTime(QTime(13, 15, 0));
//    //        ui->levelStart->setValue(946);
//    //        ui->levelEnd->setValue(1052);
//        }
//        else if (chartType == "mua"){
//            ui->lblStart->setText("Lượng mưa bắt đầu");
//            ui->lblEnd->setText("Lượng mưa kết thúc");
//            ui->lblSpace->setText("Lượng mưa/1 dòng");
//            dialogSetup.setValue("time/start", QTime(7, 20, 0));
//            dialogSetup.setValue("time/space", 10);
//            dialogSetup.setValue("time/end", QTime(8, 20, 0));
//            dialogSetup.setValue("level/start", -0.5);
//            dialogSetup.setValue("level/space", 0.1);
//            dialogSetup.setValue("level/end", 10.5);
//    //        ui->timeGet->setValue(10);
//    //        ui->levelGet->setValue(0.1);
//    //        ui->timeStart->setTime(QTime(7, 20, 0));
//    //        ui->timeEnd->setTime(QTime(8, 20, 0));
//    //        ui->levelStart->setValue(-0.5);
//    //        ui->levelEnd->setValue(10.5);
//        }
//        else if (chartType == "nhiet"){
//            ui->lblStart->setText("Nhiệt độ bắt đầu");
//            ui->lblEnd->setText("Nhiệt độ kết thúc");
//            ui->lblSpace->setText("Nhiệt độ/1 dòng");
//            dialogSetup.setValue("time/start", QTime(6, 30, 0));
//            dialogSetup.setValue("time/space", 10);
//            dialogSetup.setValue("time/end", QTime(8, 30, 0));
//            dialogSetup.setValue("level/start", -15);
//            dialogSetup.setValue("level/space", 1);
//            dialogSetup.setValue("level/end", 65);
//    //        ui->timeGet->setValue(10);
//    //        ui->levelGet->setValue(1);
//    //        ui->timeStart->setTime(QTime(6, 30, 0));
//    //        ui->timeEnd->setTime(QTime(8, 10, 0));
//    //        ui->levelStart->setValue(-15);
//    //        ui->levelEnd->setValue(65);
//        }
//        else if (chartType == "nuoc"){
//            ui->lblStart->setText("Lượng nước bắt đầu");
//            ui->lblEnd->setText("Lượng nước kết thúc");
//            ui->lblSpace->setText("Lượng nước/1 dòng");
//            dialogSetup.setValue("time/start", QTime(7, 0, 0));
//            dialogSetup.setValue("time/space", 10);
//            dialogSetup.setValue("time/end", QTime(7, 0, 0));
//            dialogSetup.setValue("level/start", 47190);
//            dialogSetup.setValue("level/space", 0.5);
//            dialogSetup.setValue("level/end", 47390);
//    //        ui->timeGet->setValue(10);
//    //        ui->levelGet->setValue(0.5);
//    //        ui->timeStart->setTime(QTime(7, 0, 0));
//    //        ui->timeEnd->setTime(QTime(7, 0, 0));
//    //        ui->levelStart->setValue(47190);
//    //        ui->levelEnd->setValue(47390);
//        }
}
void Input::changeSetup(bool opened, QString chartType){

//    ui->timeStart->setTime(dialogSetup.value("time/start").toTime());
//    ui->timeGet->setValue(dialogSetup.value("time/space").toInt());
//    ui->timeEnd->setTime(dialogSetup.value("time/end").toTime());
//    ui->levelStart->setValue(dialogSetup.value("level/start").toDouble());
//    ui->levelGet->setValue(dialogSetup.value("level/space").toDouble());
//    ui->levelEnd->setValue(dialogSetup.value("level/end").toDouble());
    QSettings dialogSetup;
    if(opened){
        ui->timeStart->setTime(dialogSetup.value("time/start").toTime());
        ui->timeGet->setValue(dialogSetup.value("time/space").toInt());
        ui->timeEnd->setTime(dialogSetup.value("time/end").toTime());
        ui->biasBox->setValue(dialogSetup.value("time/shift").toInt());
        ui->levelStart->setValue(dialogSetup.value("level/start").toDouble());
        ui->levelGet->setValue(dialogSetup.value("level/space").toDouble());
        ui->levelEnd->setValue(dialogSetup.value("level/end").toDouble());
        ui->lblStart->setText(dialogSetup.value("label/levelS").toString());
        ui->lblEnd->setText(dialogSetup.value("label/levelE").toString());
        ui->lblSpace->setText(dialogSetup.value("label/levelG").toString());
        ui->lblDec->setText(dialogSetup.value("label/levelD").toString());
    }
    else{
        if (chartType == "am"){
            ui->lblStart->setText("Độ ẩm bắt đầu");
            ui->lblEnd->setText("Độ ẩm kết thúc");
            ui->lblSpace->setText("Độ ẩm/1 dòng");
            ui->lblDec->setText("Tăng giảm độ ẩm (ml)");
            ui->timeGet->setValue(15);
            ui->levelGet->setValue(2);
            //ui->timeStart->setTime(QTime(6, 30, 0));
            //ui->timeEnd->setTime(QTime(8, 30, 0));
            ui->levelStart->setValue(0);
            ui->levelEnd->setValue(100);
        }
        else if (chartType == "ap"){
            ui->lblStart->setText("Áp suất bắt đầu");
            ui->lblEnd->setText("Áp suất kết thúc");
            ui->lblSpace->setText("Áp suất/1 dòng");
            ui->lblDec->setText("Tăng giảm áp suất (mb)");
            ui->timeGet->setValue(15);
            ui->levelGet->setValue(1);
            //ui->timeStart->setTime(QTime(11, 15, 0));
            //ui->timeEnd->setTime(QTime(13, 15, 0));
            ui->levelStart->setValue(946);
            ui->levelEnd->setValue(1052);
        }
        else if (chartType == "mua"){
            ui->lblStart->setText("Lượng mưa bắt đầu");
            ui->lblEnd->setText("Lượng mưa kết thúc");
            ui->lblSpace->setText("Lượng mưa/1 dòng");
            ui->lblDec->setText("Tăng giảm lượng mưa (ml)");
            ui->timeGet->setValue(10);
            ui->levelGet->setValue(1);
            //ui->timeStart->setTime(QTime(7, 20, 0));
            //ui->timeEnd->setTime(QTime(8, 20, 0));
            ui->levelStart->setValue(-5);
            ui->levelEnd->setValue(105);
        }
        else if (chartType == "nhiet"){
            ui->lblStart->setText("Nhiệt độ bắt đầu");
            ui->lblEnd->setText("Nhiệt độ kết thúc");
            ui->lblSpace->setText("Nhiệt độ/1 dòng");
            ui->lblDec->setText("Tăng giảm nhiệt độ (°C)");
            ui->timeGet->setValue(10);
            ui->levelGet->setValue(10);
            //ui->timeStart->setTime(QTime(6, 30, 0));
            //ui->timeEnd->setTime(QTime(8, 10, 0));
            ui->levelStart->setValue(-150);
            ui->levelEnd->setValue(650);
        }
        else if (chartType == "nuoc"){
            ui->lblStart->setText("Mức nước bắt đầu");
            ui->lblEnd->setText("Mức nước kết thúc");
            ui->lblSpace->setText("Mức nước/1 dòng");
            ui->lblDec->setText("Tăng giảm mức nước (ml)");
            ui->timeGet->setValue(10);
            ui->levelGet->setValue(0.5);
            //ui->timeStart->setTime(QTime(7, 0, 0));
            //ui->timeEnd->setTime(QTime(7, 0, 0));
            ui->levelStart->setValue(47190);
            ui->levelEnd->setValue(47390);
        }

    }

}
void Input::closeButton(){
//    startTime = ui->timeStart->time();
//    spaceTime = ui->timeGet->value();
//    endTime = ui->timeEnd->time();
//    startLevel = ui->levelStart->value();
//    spaceLevel = ui->levelGet->value();
//    endLevel = ui->levelEnd->value();
    writeSettings();
    close();
}
Input::~Input()
{

    delete ui;
}
