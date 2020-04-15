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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
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
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QListWidget *showFolder;
    QHBoxLayout *horizontalLayout;
    QPushButton *prev;
    QPushButton *next;
    QVBoxLayout *verticalLayout;
    MyGraphicsView *Mask;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1297, 961);
        MainWindow->setLocale(QLocale(QLocale::Vietnamese, QLocale::Vietnam));
        actionOpenFolder = new QAction(MainWindow);
        actionOpenFolder->setObjectName(QString::fromUtf8("actionOpenFolder"));
        actionZoom = new QAction(MainWindow);
        actionZoom->setObjectName(QString::fromUtf8("actionZoom"));
        actionZoom->setCheckable(true);
        actionpdf2png = new QAction(MainWindow);
        actionpdf2png->setObjectName(QString::fromUtf8("actionpdf2png"));
        actionDrawingLine = new QAction(MainWindow);
        actionDrawingLine->setObjectName(QString::fromUtf8("actionDrawingLine"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        showFolder = new QListWidget(centralwidget);
        showFolder->setObjectName(QString::fromUtf8("showFolder"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(showFolder->sizePolicy().hasHeightForWidth());
        showFolder->setSizePolicy(sizePolicy);
        showFolder->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        showFolder->setIconSize(QSize(0, 0));
        showFolder->setMovement(QListView::Static);
        showFolder->setFlow(QListView::TopToBottom);
        showFolder->setProperty("isWrapping", QVariant(false));
        showFolder->setResizeMode(QListView::Adjust);
        showFolder->setGridSize(QSize(0, 0));
        showFolder->setViewMode(QListView::IconMode);

        verticalLayout_2->addWidget(showFolder);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        prev = new QPushButton(centralwidget);
        prev->setObjectName(QString::fromUtf8("prev"));

        horizontalLayout->addWidget(prev);

        next = new QPushButton(centralwidget);
        next->setObjectName(QString::fromUtf8("next"));

        horizontalLayout->addWidget(next);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        Mask = new MyGraphicsView(centralwidget);
        Mask->setObjectName(QString::fromUtf8("Mask"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Mask->sizePolicy().hasHeightForWidth());
        Mask->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(Mask);


        horizontalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionOpenFolder);
        toolBar->addSeparator();
        toolBar->addAction(actionZoom);
        toolBar->addAction(actionpdf2png);
        toolBar->addAction(actionDrawingLine);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
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
        prev->setText(QCoreApplication::translate("MainWindow", "Tr\306\260\341\273\233c", nullptr));
        next->setText(QCoreApplication::translate("MainWindow", "Ti\341\272\277p", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
