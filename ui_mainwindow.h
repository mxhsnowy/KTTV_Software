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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenFolder;
    QAction *actionDraw;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QListWidget *showFolder;
    QVBoxLayout *verticalLayout;
    QGraphicsView *Image;
    QGraphicsView *Mask;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1297, 961);
        MainWindow->setLocale(QLocale(QLocale::Vietnamese, QLocale::Vietnam));
        actionOpenFolder = new QAction(MainWindow);
        actionOpenFolder->setObjectName(QString::fromUtf8("actionOpenFolder"));
        actionDraw = new QAction(MainWindow);
        actionDraw->setObjectName(QString::fromUtf8("actionDraw"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(4, 4, 4, 4);
        showFolder = new QListWidget(centralwidget);
        showFolder->setObjectName(QString::fromUtf8("showFolder"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(showFolder->sizePolicy().hasHeightForWidth());
        showFolder->setSizePolicy(sizePolicy);
        showFolder->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        showFolder->setIconSize(QSize(250, 70));
        showFolder->setMovement(QListView::Static);
        showFolder->setFlow(QListView::TopToBottom);
        showFolder->setProperty("isWrapping", QVariant(false));
        showFolder->setResizeMode(QListView::Adjust);
        showFolder->setGridSize(QSize(260, 95));
        showFolder->setViewMode(QListView::IconMode);

        horizontalLayout->addWidget(showFolder);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        Image = new QGraphicsView(centralwidget);
        Image->setObjectName(QString::fromUtf8("Image"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Image->sizePolicy().hasHeightForWidth());
        Image->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(Image);

        Mask = new QGraphicsView(centralwidget);
        Mask->setObjectName(QString::fromUtf8("Mask"));
        sizePolicy1.setHeightForWidth(Mask->sizePolicy().hasHeightForWidth());
        Mask->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(Mask);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionOpenFolder);
        toolBar->addSeparator();
        toolBar->addAction(actionDraw);

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
        actionDraw->setText(QCoreApplication::translate("MainWindow", "V\341\272\275 \304\221\306\260\341\273\235ng b\303\241m", nullptr));
#if QT_CONFIG(tooltip)
        actionDraw->setToolTip(QCoreApplication::translate("MainWindow", "V\341\272\275 \304\221\306\260\341\273\235ng b\303\241m \304\221\341\273\223 th\341\273\213 m\303\240u xanh", nullptr));
#endif // QT_CONFIG(tooltip)
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
