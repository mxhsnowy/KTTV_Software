/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mygraphicsview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenFolder;
    QAction *actionZoom;
    QAction *actionHelp;
    QAction *actionQuit;
    QAction *actionSetting;
    QAction *actionRotate;
    QAction *actionMarking;
    QAction *actionCutGrid;
    QAction *actionRotateBack;
    QAction *actionPicking_Points;
    QAction *actionlimitLine;
    QAction *actionDraw;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QListWidget *showFolder;
    MyGraphicsView *Mask;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *dataView;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *timeUD;
    QDoubleSpinBox *levelUD;
    QPushButton *change;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *IDchart;
    QHBoxLayout *horizontalLayout;
    QLineEdit *daychart;
    QLineEdit *dayInput;
    QComboBox *stationBox;
    QComboBox *stationID;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *prevDay;
    QPushButton *nextDay;
    QPushButton *digitalize;
    QPushButton *save;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1297, 961);
        MainWindow->setLocale(QLocale(QLocale::Vietnamese, QLocale::Vietnam));
        actionOpenFolder = new QAction(MainWindow);
        actionOpenFolder->setObjectName(QString::fromUtf8("actionOpenFolder"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icons/openFolder.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenFolder->setIcon(icon);
        actionZoom = new QAction(MainWindow);
        actionZoom->setObjectName(QString::fromUtf8("actionZoom"));
        actionZoom->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/icons/zoomOff.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/icon/icons/zoomOn.png"), QSize(), QIcon::Normal, QIcon::On);
        actionZoom->setIcon(icon1);
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/icons/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon2);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/icons/quit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon3);
        actionSetting = new QAction(MainWindow);
        actionSetting->setObjectName(QString::fromUtf8("actionSetting"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/icons/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSetting->setIcon(icon4);
        actionRotate = new QAction(MainWindow);
        actionRotate->setObjectName(QString::fromUtf8("actionRotate"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/icons/imgRotate.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRotate->setIcon(icon5);
        actionMarking = new QAction(MainWindow);
        actionMarking->setObjectName(QString::fromUtf8("actionMarking"));
        actionMarking->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/icons/curveoff.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon6.addFile(QString::fromUtf8(":/icon/icons/clicking.png"), QSize(), QIcon::Normal, QIcon::On);
        actionMarking->setIcon(icon6);
        actionCutGrid = new QAction(MainWindow);
        actionCutGrid->setObjectName(QString::fromUtf8("actionCutGrid"));
        actionCutGrid->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icon/icons/handCrop.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon7.addFile(QString::fromUtf8(":/icon/icons/rectcrop.png"), QSize(), QIcon::Normal, QIcon::On);
        actionCutGrid->setIcon(icon7);
        actionRotateBack = new QAction(MainWindow);
        actionRotateBack->setObjectName(QString::fromUtf8("actionRotateBack"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icon/icons/imgRotateBack.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRotateBack->setIcon(icon8);
        actionPicking_Points = new QAction(MainWindow);
        actionPicking_Points->setObjectName(QString::fromUtf8("actionPicking_Points"));
        actionPicking_Points->setCheckable(true);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icon/icons/addPoints.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPicking_Points->setIcon(icon9);
        actionlimitLine = new QAction(MainWindow);
        actionlimitLine->setObjectName(QString::fromUtf8("actionlimitLine"));
        actionlimitLine->setCheckable(true);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icon/icons/limitLine.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon10.addFile(QString::fromUtf8(":/icon/icons/clicking.png"), QSize(), QIcon::Normal, QIcon::On);
        actionlimitLine->setIcon(icon10);
        actionDraw = new QAction(MainWindow);
        actionDraw->setObjectName(QString::fromUtf8("actionDraw"));
        actionDraw->setCheckable(true);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icon/icons/draw.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon11.addFile(QString::fromUtf8(":/icon/icons/drawing.png"), QSize(), QIcon::Normal, QIcon::On);
        actionDraw->setIcon(icon11);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_4 = new QHBoxLayout(centralwidget);
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, -1, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        showFolder = new QListWidget(centralwidget);
        showFolder->setObjectName(QString::fromUtf8("showFolder"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(showFolder->sizePolicy().hasHeightForWidth());
        showFolder->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        showFolder->setFont(font);
        showFolder->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        showFolder->setIconSize(QSize(0, 0));
        showFolder->setMovement(QListView::Static);
        showFolder->setFlow(QListView::TopToBottom);
        showFolder->setProperty("isWrapping", QVariant(false));
        showFolder->setResizeMode(QListView::Adjust);
        showFolder->setGridSize(QSize(0, 0));
        showFolder->setViewMode(QListView::IconMode);

        verticalLayout_2->addWidget(showFolder);


        horizontalLayout_4->addLayout(verticalLayout_2);

        Mask = new MyGraphicsView(centralwidget);
        Mask->setObjectName(QString::fromUtf8("Mask"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Mask->sizePolicy().hasHeightForWidth());
        Mask->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(Mask);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(2);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        dataView = new QTableWidget(centralwidget);
        if (dataView->columnCount() < 2)
            dataView->setColumnCount(2);
        dataView->setObjectName(QString::fromUtf8("dataView"));
        sizePolicy.setHeightForWidth(dataView->sizePolicy().hasHeightForWidth());
        dataView->setSizePolicy(sizePolicy);
        dataView->setColumnCount(2);
        dataView->verticalHeader()->setVisible(false);

        verticalLayout_5->addWidget(dataView);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        gridLayout_3->addWidget(label_5, 1, 1, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);

        timeUD = new QSpinBox(centralwidget);
        timeUD->setObjectName(QString::fromUtf8("timeUD"));
        timeUD->setFont(font);
        timeUD->setMinimum(-10000);
        timeUD->setMaximum(10000);

        gridLayout_3->addWidget(timeUD, 2, 0, 1, 1);

        levelUD = new QDoubleSpinBox(centralwidget);
        levelUD->setObjectName(QString::fromUtf8("levelUD"));
        levelUD->setFont(font);
        levelUD->setMinimum(-10000.000000000000000);
        levelUD->setMaximum(10000.000000000000000);

        gridLayout_3->addWidget(levelUD, 2, 1, 1, 1);


        verticalLayout_5->addLayout(gridLayout_3);

        change = new QPushButton(centralwidget);
        change->setObjectName(QString::fromUtf8("change"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(change->sizePolicy().hasHeightForWidth());
        change->setSizePolicy(sizePolicy2);
        change->setFont(font);

        verticalLayout_5->addWidget(change);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        label->setFont(font);

        verticalLayout->addWidget(label);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        verticalLayout->addWidget(label_4);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        IDchart = new QLineEdit(centralwidget);
        IDchart->setObjectName(QString::fromUtf8("IDchart"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(IDchart->sizePolicy().hasHeightForWidth());
        IDchart->setSizePolicy(sizePolicy4);
        IDchart->setFont(font);

        verticalLayout_3->addWidget(IDchart);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        daychart = new QLineEdit(centralwidget);
        daychart->setObjectName(QString::fromUtf8("daychart"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(daychart->sizePolicy().hasHeightForWidth());
        daychart->setSizePolicy(sizePolicy5);
        daychart->setMaximumSize(QSize(41, 16777215));
        daychart->setFont(font);
        daychart->setReadOnly(true);

        horizontalLayout->addWidget(daychart);

        dayInput = new QLineEdit(centralwidget);
        dayInput->setObjectName(QString::fromUtf8("dayInput"));
        sizePolicy3.setHeightForWidth(dayInput->sizePolicy().hasHeightForWidth());
        dayInput->setSizePolicy(sizePolicy3);
        dayInput->setFont(font);

        horizontalLayout->addWidget(dayInput);


        verticalLayout_3->addLayout(horizontalLayout);

        stationBox = new QComboBox(centralwidget);
        stationBox->setObjectName(QString::fromUtf8("stationBox"));
        sizePolicy4.setHeightForWidth(stationBox->sizePolicy().hasHeightForWidth());
        stationBox->setSizePolicy(sizePolicy4);
        stationBox->setMinimumSize(QSize(172, 0));
        stationBox->setFont(font);
        stationBox->setEditable(true);

        verticalLayout_3->addWidget(stationBox);

        stationID = new QComboBox(centralwidget);
        stationID->setObjectName(QString::fromUtf8("stationID"));
        sizePolicy4.setHeightForWidth(stationID->sizePolicy().hasHeightForWidth());
        stationID->setSizePolicy(sizePolicy4);
        stationID->setMinimumSize(QSize(172, 0));
        stationID->setFont(font);
        stationID->setEditable(true);

        verticalLayout_3->addWidget(stationID);


        horizontalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_5->addLayout(horizontalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        prevDay = new QPushButton(centralwidget);
        prevDay->setObjectName(QString::fromUtf8("prevDay"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(prevDay->sizePolicy().hasHeightForWidth());
        prevDay->setSizePolicy(sizePolicy6);
        prevDay->setFont(font);

        horizontalLayout_3->addWidget(prevDay);

        nextDay = new QPushButton(centralwidget);
        nextDay->setObjectName(QString::fromUtf8("nextDay"));
        sizePolicy6.setHeightForWidth(nextDay->sizePolicy().hasHeightForWidth());
        nextDay->setSizePolicy(sizePolicy6);
        nextDay->setFont(font);

        horizontalLayout_3->addWidget(nextDay);


        verticalLayout_4->addLayout(horizontalLayout_3);

        digitalize = new QPushButton(centralwidget);
        digitalize->setObjectName(QString::fromUtf8("digitalize"));
        QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(digitalize->sizePolicy().hasHeightForWidth());
        digitalize->setSizePolicy(sizePolicy7);
        digitalize->setFont(font);

        verticalLayout_4->addWidget(digitalize);

        save = new QPushButton(centralwidget);
        save->setObjectName(QString::fromUtf8("save"));
        sizePolicy7.setHeightForWidth(save->sizePolicy().hasHeightForWidth());
        save->setSizePolicy(sizePolicy7);
        save->setFont(font);

        verticalLayout_4->addWidget(save);


        verticalLayout_5->addLayout(verticalLayout_4);


        horizontalLayout_4->addLayout(verticalLayout_5);

        MainWindow->setCentralWidget(centralwidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setIconSize(QSize(36, 36));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setFont(font);
        MainWindow->setStatusBar(statusBar);

        toolBar->addAction(actionOpenFolder);
        toolBar->addSeparator();
        toolBar->addAction(actionRotateBack);
        toolBar->addAction(actionRotate);
        toolBar->addAction(actionCutGrid);
        toolBar->addSeparator();
        toolBar->addAction(actionZoom);
        toolBar->addAction(actionSetting);
        toolBar->addAction(actionMarking);
        toolBar->addAction(actionlimitLine);
        toolBar->addAction(actionDraw);
        toolBar->addAction(actionQuit);
        toolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Ph\341\272\247n m\341\273\201m S\341\273\221 h\303\263a \304\221\341\273\223 th\341\273\213 kh\303\255 t\306\260\341\273\243ng th\341\273\247y v\304\203n", nullptr));
        actionOpenFolder->setText(QCoreApplication::translate("MainWindow", "M\341\273\237 Th\306\260 M\341\273\245c", nullptr));
#if QT_CONFIG(tooltip)
        actionOpenFolder->setToolTip(QCoreApplication::translate("MainWindow", "M\341\273\237 Th\306\260 M\341\273\245c", nullptr));
#endif // QT_CONFIG(tooltip)
        actionZoom->setText(QCoreApplication::translate("MainWindow", "Thu ph\303\263ng", nullptr));
#if QT_CONFIG(tooltip)
        actionZoom->setToolTip(QCoreApplication::translate("MainWindow", "Ph\303\263ng to, thu nh\341\273\217 b\341\272\261ng con l\304\203n chu\341\273\231t", nullptr));
#endif // QT_CONFIG(tooltip)
        actionHelp->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
#if QT_CONFIG(tooltip)
        actionHelp->setToolTip(QCoreApplication::translate("MainWindow", "Tr\341\273\243 gi\303\272p", nullptr));
#endif // QT_CONFIG(tooltip)
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
#if QT_CONFIG(tooltip)
        actionQuit->setToolTip(QCoreApplication::translate("MainWindow", "Tho\303\241t", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSetting->setText(QCoreApplication::translate("MainWindow", "Setting", nullptr));
#if QT_CONFIG(tooltip)
        actionSetting->setToolTip(QCoreApplication::translate("MainWindow", "Ch\341\273\211nh s\341\273\255a tham s\341\273\221 \304\221\341\273\223 th\341\273\213", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRotate->setText(QCoreApplication::translate("MainWindow", "autorotating", nullptr));
#if QT_CONFIG(tooltip)
        actionRotate->setToolTip(QCoreApplication::translate("MainWindow", "Xoay \341\272\243nh theo chi\341\273\201u kim \304\221\341\273\223ng h\341\273\223", nullptr));
#endif // QT_CONFIG(tooltip)
        actionMarking->setText(QCoreApplication::translate("MainWindow", "Marking", nullptr));
#if QT_CONFIG(tooltip)
        actionMarking->setToolTip(QCoreApplication::translate("MainWindow", "\304\220\303\241nh d\341\272\245u 3 \304\221i\341\273\203m thu\341\273\231c \304\221\341\273\223 th\341\273\213 cong", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCutGrid->setText(QCoreApplication::translate("MainWindow", "CutGrid", nullptr));
#if QT_CONFIG(tooltip)
        actionCutGrid->setToolTip(QCoreApplication::translate("MainWindow", "Khoanh v\303\271ng \304\221\341\273\223 th\341\273\213", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRotateBack->setText(QCoreApplication::translate("MainWindow", "RotateBack", nullptr));
#if QT_CONFIG(tooltip)
        actionRotateBack->setToolTip(QCoreApplication::translate("MainWindow", "Xoay \341\272\243nh ng\306\260\341\273\243c chi\341\273\201u kim \304\221\341\273\223ng h\341\273\223", nullptr));
#endif // QT_CONFIG(tooltip)
        actionPicking_Points->setText(QCoreApplication::translate("MainWindow", "Picking Points", nullptr));
#if QT_CONFIG(tooltip)
        actionPicking_Points->setToolTip(QCoreApplication::translate("MainWindow", "Th\303\252m \304\221i\341\273\203m c\341\272\247n trong b\341\272\243ng", nullptr));
#endif // QT_CONFIG(tooltip)
        actionlimitLine->setText(QCoreApplication::translate("MainWindow", "limitLine", nullptr));
#if QT_CONFIG(tooltip)
        actionlimitLine->setToolTip(QCoreApplication::translate("MainWindow", "Gi\341\273\233i h\341\272\241n \304\221i\341\273\203m \304\221\341\272\247u cu\341\273\221i c\341\273\247a \304\221\306\260\341\273\235ng line", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDraw->setText(QCoreApplication::translate("MainWindow", "Draw", nullptr));
#if QT_CONFIG(tooltip)
        actionDraw->setToolTip(QCoreApplication::translate("MainWindow", "V\341\272\275 \304\221\306\260\341\273\235ng \304\221\341\272\267c t\303\255nh \304\221\341\273\203 ph\341\272\247n m\341\273\201m nh\341\272\255n bi\341\272\277t", nullptr));
#endif // QT_CONFIG(tooltip)
        label_5->setText(QCoreApplication::translate("MainWindow", "+/- l\306\260\341\273\243ng", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "+/- th\341\273\235i gian", nullptr));
        change->setText(QCoreApplication::translate("MainWindow", "\304\220i\341\273\201u ch\341\273\211nh", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "M\303\243 t\303\240i li\341\273\207u", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Ng\303\240y th\303\241ng", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "T\303\252n tr\341\272\241m", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "M\303\243 tr\341\272\241m", nullptr));
        prevDay->setText(QCoreApplication::translate("MainWindow", "Ng\303\240y tr\306\260\341\273\233c", nullptr));
        nextDay->setText(QCoreApplication::translate("MainWindow", "Ng\303\240y sau", nullptr));
        digitalize->setText(QCoreApplication::translate("MainWindow", "T\341\272\241o b\303\241o c\303\241o ", nullptr));
        save->setText(QCoreApplication::translate("MainWindow", "L\306\260u k\341\272\277t qu\341\272\243", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
