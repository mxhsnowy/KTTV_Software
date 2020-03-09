#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpenFolder_triggered()
{
    QString defaultDir = QDir::homePath();
    QSettings lastDir;
    QString loadedDir = QFileDialog::getExistingDirectory(this, tr("Chọn thư mục"),
                                                          lastDir.value(defaultDir).toString());
    if(!loadedDir.isEmpty()){
        QDir loadDir(loadedDir);
        lastDir.setValue(defaultDir, loadDir.path());
        QStringList filter;
        filter<<"*.jpg"<<"*.JPG";
        loadDir.setNameFilters(filter);
        QList<QFileInfo> infoList = loadDir.entryInfoList();
        foreach (const QFileInfo &fileInfo, infoList) {
            QString itemName = fileInfo.fileName();
            QString absPath = fileInfo.absoluteFilePath();
            ui->showFolder->addItem(new QListWidgetItem(QIcon(), itemName));
        }

    }

}
