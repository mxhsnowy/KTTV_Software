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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
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
    QAction *actionpdf2png;
    QAction *actionDrawingLine;
    QAction *actionreport;
    QAction *actionHelp;
    QAction *actionQuit;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QListWidget *showFolder;
    MyGraphicsView *Mask;
    QVBoxLayout *verticalLayout;
    QTableWidget *dataView;
    QGridLayout *gridLayout;
    QPushButton *nextDay;
    QLabel *label;
    QLabel *label_2;
    QLabel *imgName;
    QPushButton *prevDay;
    QLabel *imgType;
    QLabel *label_3;
    QLabel *day;
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
        actionpdf2png = new QAction(MainWindow);
        actionpdf2png->setObjectName(QString::fromUtf8("actionpdf2png"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/icons/splitImg.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionpdf2png->setIcon(icon2);
        actionDrawingLine = new QAction(MainWindow);
        actionDrawingLine->setObjectName(QString::fromUtf8("actionDrawingLine"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/icons/drawLine.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDrawingLine->setIcon(icon3);
        actionreport = new QAction(MainWindow);
        actionreport->setObjectName(QString::fromUtf8("actionreport"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/icons/export.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionreport->setIcon(icon4);
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/icons/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon5);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/icons/quit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon6);
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

        gridLayout->addWidget(nextDay, 3, 1, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        imgName = new QLabel(centralwidget);
        imgName->setObjectName(QString::fromUtf8("imgName"));
        imgName->setFont(font);
        imgName->setFrameShape(QFrame::Panel);

        gridLayout->addWidget(imgName, 0, 1, 1, 1);

        prevDay = new QPushButton(centralwidget);
        prevDay->setObjectName(QString::fromUtf8("prevDay"));
        sizePolicy2.setHeightForWidth(prevDay->sizePolicy().hasHeightForWidth());
        prevDay->setSizePolicy(sizePolicy2);
        prevDay->setFont(font);

        gridLayout->addWidget(prevDay, 3, 0, 1, 1);

        imgType = new QLabel(centralwidget);
        imgType->setObjectName(QString::fromUtf8("imgType"));
        sizePolicy2.setHeightForWidth(imgType->sizePolicy().hasHeightForWidth());
        imgType->setSizePolicy(sizePolicy2);
        imgType->setFont(font);
        imgType->setFrameShape(QFrame::Panel);

        gridLayout->addWidget(imgType, 2, 1, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        day = new QLabel(centralwidget);
        day->setObjectName(QString::fromUtf8("day"));
        day->setFont(font);
        day->setFrameShape(QFrame::Panel);

        gridLayout->addWidget(day, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setIconSize(QSize(36, 36));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionOpenFolder);
        toolBar->addSeparator();
        toolBar->addAction(actionZoom);
        toolBar->addAction(actionpdf2png);
        toolBar->addAction(actionDrawingLine);
        toolBar->addAction(actionreport);
        toolBar->addAction(actionHelp);
        toolBar->addAction(actionQuit);
        toolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Ph\341\272\247n m\341\273\201m kh\303\255 t\306\260\341\273\243ng th\341\273\247y v\304\203n", nullptr));
        actionOpenFolder->setText(QCoreApplication::translate("MainWindow", "M\341\273\237 Th\306\260 M\341\273\245c", nullptr));
#if QT_CONFIG(tooltip)
        actionOpenFolder->setToolTip(QCoreApplication::translate("MainWindow", "M\341\273\237 Th\306\260 M\341\273\245c", nullptr));
#endif // QT_CONFIG(tooltip)
        actionZoom->setText(QCoreApplication::translate("MainWindow", "Thu ph\303\263ng", nullptr));
#if QT_CONFIG(tooltip)
        actionZoom->setToolTip(QCoreApplication::translate("MainWindow", "Ph\303\263ng to, thu nh\341\273\217 b\341\272\261ng con l\304\203n chu\341\273\231t", nullptr));
#endif // QT_CONFIG(tooltip)
        actionpdf2png->setText(QCoreApplication::translate("MainWindow", "T\303\241ch \304\221\341\273\223 th\341\273\213", nullptr));
        actionDrawingLine->setText(QCoreApplication::translate("MainWindow", "V\341\272\275 \304\221\306\260\341\273\235ng \304\221\341\273\223 th\341\273\213", nullptr));
        actionreport->setText(QCoreApplication::translate("MainWindow", "report", nullptr));
#if QT_CONFIG(tooltip)
        actionreport->setToolTip(QCoreApplication::translate("MainWindow", "Xu\341\272\245t d\341\273\257 li\341\273\207u ra t\341\272\255p tin.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionHelp->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
#if QT_CONFIG(tooltip)
        actionHelp->setToolTip(QCoreApplication::translate("MainWindow", "Tr\341\273\243 gi\303\272p", nullptr));
#endif // QT_CONFIG(tooltip)
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
#if QT_CONFIG(tooltip)
        actionQuit->setToolTip(QCoreApplication::translate("MainWindow", "Tho\303\241t", nullptr));
#endif // QT_CONFIG(tooltip)
        nextDay->setText(QCoreApplication::translate("MainWindow", "Ng\303\240y ti\341\272\277p theo", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "T\303\252n \341\272\243nh", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Lo\341\272\241i \304\221\341\273\223 th\341\273\213", nullptr));
        imgName->setText(QString());
        prevDay->setText(QCoreApplication::translate("MainWindow", "Ng\303\240y tr\306\260\341\273\233c \304\221\303\263", nullptr));
        imgType->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "Ng\303\240y", nullptr));
        day->setText(QString());
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
