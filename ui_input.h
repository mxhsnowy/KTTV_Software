/********************************************************************************
** Form generated from reading UI file 'input.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUT_H
#define UI_INPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Input
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *lbtStart;
    QHBoxLayout *horizontalLayout_2;
    QTimeEdit *timeStart;
    QLabel *lbtEnd;
    QHBoxLayout *horizontalLayout_5;
    QTimeEdit *timeEnd;
    QSpinBox *days;
    QLabel *lbtSpace;
    QDoubleSpinBox *timeGet;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblStart;
    QDoubleSpinBox *levelStart;
    QLabel *lblEnd;
    QDoubleSpinBox *levelEnd;
    QLabel *lblSpace;
    QDoubleSpinBox *levelGet;
    QPushButton *Done;

    void setupUi(QDialog *Input)
    {
        if (Input->objectName().isEmpty())
            Input->setObjectName(QString::fromUtf8("Input"));
        Input->resize(449, 273);
        verticalLayout_3 = new QVBoxLayout(Input);
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lbtStart = new QLabel(Input);
        lbtStart->setObjectName(QString::fromUtf8("lbtStart"));
        QFont font;
        font.setPointSize(12);
        lbtStart->setFont(font);

        verticalLayout->addWidget(lbtStart);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        timeStart = new QTimeEdit(Input);
        timeStart->setObjectName(QString::fromUtf8("timeStart"));
        timeStart->setFont(font);
        timeStart->setMinimumTime(QTime(0, 0, 0));
        timeStart->setTime(QTime(7, 0, 0));

        horizontalLayout_2->addWidget(timeStart);


        verticalLayout->addLayout(horizontalLayout_2);

        lbtEnd = new QLabel(Input);
        lbtEnd->setObjectName(QString::fromUtf8("lbtEnd"));
        lbtEnd->setFont(font);

        verticalLayout->addWidget(lbtEnd);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        timeEnd = new QTimeEdit(Input);
        timeEnd->setObjectName(QString::fromUtf8("timeEnd"));
        timeEnd->setFont(font);
        timeEnd->setTime(QTime(7, 0, 0));

        horizontalLayout_5->addWidget(timeEnd);

        days = new QSpinBox(Input);
        days->setObjectName(QString::fromUtf8("days"));
        days->setFont(font);
        days->setValue(1);

        horizontalLayout_5->addWidget(days);


        verticalLayout->addLayout(horizontalLayout_5);

        lbtSpace = new QLabel(Input);
        lbtSpace->setObjectName(QString::fromUtf8("lbtSpace"));
        lbtSpace->setFont(font);

        verticalLayout->addWidget(lbtSpace);

        timeGet = new QDoubleSpinBox(Input);
        timeGet->setObjectName(QString::fromUtf8("timeGet"));
        timeGet->setFont(font);

        verticalLayout->addWidget(timeGet);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lblStart = new QLabel(Input);
        lblStart->setObjectName(QString::fromUtf8("lblStart"));
        lblStart->setFont(font);

        verticalLayout_2->addWidget(lblStart);

        levelStart = new QDoubleSpinBox(Input);
        levelStart->setObjectName(QString::fromUtf8("levelStart"));
        levelStart->setFont(font);
        levelStart->setMinimum(-1000000.000000000000000);
        levelStart->setMaximum(1000000.000000000000000);

        verticalLayout_2->addWidget(levelStart);

        lblEnd = new QLabel(Input);
        lblEnd->setObjectName(QString::fromUtf8("lblEnd"));
        lblEnd->setFont(font);

        verticalLayout_2->addWidget(lblEnd);

        levelEnd = new QDoubleSpinBox(Input);
        levelEnd->setObjectName(QString::fromUtf8("levelEnd"));
        levelEnd->setFont(font);
        levelEnd->setMaximum(1000000.000000000000000);

        verticalLayout_2->addWidget(levelEnd);

        lblSpace = new QLabel(Input);
        lblSpace->setObjectName(QString::fromUtf8("lblSpace"));
        lblSpace->setFont(font);

        verticalLayout_2->addWidget(lblSpace);

        levelGet = new QDoubleSpinBox(Input);
        levelGet->setObjectName(QString::fromUtf8("levelGet"));
        levelGet->setFont(font);

        verticalLayout_2->addWidget(levelGet);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        Done = new QPushButton(Input);
        Done->setObjectName(QString::fromUtf8("Done"));
        Done->setFont(font);

        verticalLayout_3->addWidget(Done);


        retranslateUi(Input);

        QMetaObject::connectSlotsByName(Input);
    } // setupUi

    void retranslateUi(QDialog *Input)
    {
        Input->setWindowTitle(QCoreApplication::translate("Input", "Ch\341\273\211nh s\341\273\255a th\303\264ng s\341\273\221", nullptr));
        lbtStart->setText(QCoreApplication::translate("Input", "Th\341\273\235i gian b\341\272\257t \304\221\341\272\247u", nullptr));
        timeStart->setDisplayFormat(QCoreApplication::translate("Input", "h:mm ", nullptr));
        lbtEnd->setText(QCoreApplication::translate("Input", "Th\341\273\235i gian k\341\272\277t th\303\272c + s\341\273\221 ng\303\240y", nullptr));
        timeEnd->setDisplayFormat(QCoreApplication::translate("Input", "h:mm ", nullptr));
        lbtSpace->setText(QCoreApplication::translate("Input", "Th\341\273\235i gian l\341\272\245y m\341\272\253u (ph\303\272t)", nullptr));
        lblStart->setText(QCoreApplication::translate("Input", "L\306\260\341\273\243ng b\341\272\257t \304\221\341\272\247u", nullptr));
        lblEnd->setText(QCoreApplication::translate("Input", "L\306\260\341\273\243ng k\341\272\277t th\303\272c", nullptr));
        lblSpace->setText(QCoreApplication::translate("Input", "L\306\260\341\273\243ng/1 d\303\262ng", nullptr));
        Done->setText(QCoreApplication::translate("Input", "\303\201p d\341\273\245ng", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Input: public Ui_Input {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUT_H
