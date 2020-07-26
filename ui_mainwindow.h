/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
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
    QAction *actionCutGrid;
    QAction *actiondrawMask;
    QAction *actionrotateAndCrop;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QListWidget *showFolder;
    MyGraphicsView *Mask;
    QVBoxLayout *verticalLayout;
    QTableWidget *dataView;
    QGridLayout *gridLayout;
    QPushButton *nextDay;
    QLineEdit *daychart;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *IDchart;
    QComboBox *stationBox;
    QPushButton *prevDay;
    QLabel *label_2;
    QLabel *label_4;
    QComboBox *stationID;
    QPushButton *digitalize;
    QPushButton *save;
    QToolBar *toolBar;

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
        actionCutGrid = new QAction(MainWindow);
        actionCutGrid->setObjectName(QString::fromUtf8("actionCutGrid"));
        actionCutGrid->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/icons/cropGrid.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon5.addFile(QString::fromUtf8(":/icon/icons/rectcrop.png"), QSize(), QIcon::Normal, QIcon::On);
        actionCutGrid->setIcon(icon5);
        actiondrawMask = new QAction(MainWindow);
        actiondrawMask->setObjectName(QString::fromUtf8("actiondrawMask"));
        actiondrawMask->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/icons/draw.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon6.addFile(QString::fromUtf8(":/icon/icons/drawEnabled.png"), QSize(), QIcon::Normal, QIcon::On);
        actiondrawMask->setIcon(icon6);
        actionrotateAndCrop = new QAction(MainWindow);
        actionrotateAndCrop->setObjectName(QString::fromUtf8("actionrotateAndCrop"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icon/icons/rotateandcrop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionrotateAndCrop->setIcon(icon7);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
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


        horizontalLayout->addLayout(verticalLayout_2);

        Mask = new MyGraphicsView(centralwidget);
        Mask->setObjectName(QString::fromUtf8("Mask"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Mask->sizePolicy().hasHeightForWidth());
        Mask->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(Mask);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        dataView = new QTableWidget(centralwidget);
        if (dataView->columnCount() < 2)
            dataView->setColumnCount(2);
        dataView->setObjectName(QString::fromUtf8("dataView"));
        sizePolicy.setHeightForWidth(dataView->sizePolicy().hasHeightForWidth());
        dataView->setSizePolicy(sizePolicy);
        dataView->setColumnCount(2);
        dataView->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(dataView);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setHorizontalSpacing(4);
        gridLayout->setVerticalSpacing(2);
        nextDay = new QPushButton(centralwidget);
        nextDay->setObjectName(QString::fromUtf8("nextDay"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(nextDay->sizePolicy().hasHeightForWidth());
        nextDay->setSizePolicy(sizePolicy2);
        nextDay->setFont(font);

        gridLayout->addWidget(nextDay, 4, 1, 1, 1);

        daychart = new QLineEdit(centralwidget);
        daychart->setObjectName(QString::fromUtf8("daychart"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(daychart->sizePolicy().hasHeightForWidth());
        daychart->setSizePolicy(sizePolicy3);
        daychart->setFont(font);

        gridLayout->addWidget(daychart, 1, 1, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        IDchart = new QLineEdit(centralwidget);
        IDchart->setObjectName(QString::fromUtf8("IDchart"));
        sizePolicy3.setHeightForWidth(IDchart->sizePolicy().hasHeightForWidth());
        IDchart->setSizePolicy(sizePolicy3);
        IDchart->setFont(font);

        gridLayout->addWidget(IDchart, 0, 1, 1, 1);

        stationBox = new QComboBox(centralwidget);
        stationBox->setObjectName(QString::fromUtf8("stationBox"));
        stationBox->setFont(font);
        stationBox->setEditable(true);

        gridLayout->addWidget(stationBox, 2, 1, 1, 1);

        prevDay = new QPushButton(centralwidget);
        prevDay->setObjectName(QString::fromUtf8("prevDay"));
        sizePolicy2.setHeightForWidth(prevDay->sizePolicy().hasHeightForWidth());
        prevDay->setSizePolicy(sizePolicy2);
        prevDay->setFont(font);

        gridLayout->addWidget(prevDay, 4, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        stationID = new QComboBox(centralwidget);
        stationID->setObjectName(QString::fromUtf8("stationID"));
        stationID->setFont(font);
        stationID->setEditable(true);

        gridLayout->addWidget(stationID, 3, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        digitalize = new QPushButton(centralwidget);
        digitalize->setObjectName(QString::fromUtf8("digitalize"));
        digitalize->setFont(font);

        verticalLayout->addWidget(digitalize);

        save = new QPushButton(centralwidget);
        save->setObjectName(QString::fromUtf8("save"));
        save->setFont(font);

        verticalLayout->addWidget(save);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setIconSize(QSize(36, 36));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionOpenFolder);
        toolBar->addSeparator();
        toolBar->addAction(actionrotateAndCrop);
        toolBar->addAction(actionZoom);
        toolBar->addAction(actionCutGrid);
        toolBar->addAction(actionSetting);
        toolBar->addAction(actionHelp);
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
        actionCutGrid->setText(QCoreApplication::translate("MainWindow", "CutGrid", nullptr));
#if QT_CONFIG(tooltip)
        actionCutGrid->setToolTip(QCoreApplication::translate("MainWindow", "Khoanh v\303\271ng t\303\255nh to\303\241n", nullptr));
#endif // QT_CONFIG(tooltip)
        actiondrawMask->setText(QCoreApplication::translate("MainWindow", "drawMask", nullptr));
#if QT_CONFIG(tooltip)
        actiondrawMask->setToolTip(QCoreApplication::translate("MainWindow", "V\341\272\275 \304\221\306\260\341\273\235ng \304\221\341\272\267c t\303\255nh thay th\341\272\277", nullptr));
#endif // QT_CONFIG(tooltip)
        actionrotateAndCrop->setText(QCoreApplication::translate("MainWindow", "rotateAndCrop", nullptr));
#if QT_CONFIG(tooltip)
        actionrotateAndCrop->setToolTip(QCoreApplication::translate("MainWindow", "C\341\272\257t v\303\240 xoay \341\272\243nh t\341\273\261 \304\221\341\273\231ng", nullptr));
#endif // QT_CONFIG(tooltip)
        nextDay->setText(QCoreApplication::translate("MainWindow", "Ng\303\240y ti\341\272\277p", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "M\303\243 t\303\240i li\341\273\207u", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Ng\303\240y th\303\241ng", nullptr));
        prevDay->setText(QCoreApplication::translate("MainWindow", "Ng\303\240y tr\306\260\341\273\233c", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "T\303\252n tr\341\272\241m", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "M\303\243 tr\341\272\241m", nullptr));
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
