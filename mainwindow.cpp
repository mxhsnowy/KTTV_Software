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
    chosenDir = QFileDialog::getExistingDirectory(this, tr("Chọn thư mục"),
                                                          lastDir.value(defaultDir).toString());
    if(!chosenDir.isEmpty()){
        QIcon icon;
        QDir loadDir(chosenDir);
        lastDir.setValue(defaultDir, loadDir.path());
        QStringList filter;
        filter<<"*.jpg"<<"*.JPG";
        loadDir.setNameFilters(filter);
        QList<QFileInfo> infoList = loadDir.entryInfoList();

        foreach (const QFileInfo &fileInfo, infoList) {

            QString itemName = fileInfo.fileName();
            QString absPath = fileInfo.absoluteFilePath();
            QImageReader reader(absPath);
            reader.setScaledSize(QSize(250, 70));
            icon = QIcon(QPixmap::fromImage(reader.read()));
            ui->showFolder->addItem(new QListWidgetItem(icon, itemName));
        }

    }

}



void MainWindow::on_showFolder_itemClicked(QListWidgetItem *item)
{
    QPixmap image;
    if(image.load(chosenDir + "\\" + item->text())){
        scene->clear();
        QGraphicsPixmapItem *it = new QGraphicsPixmapItem(image);
        scene->addItem(it);
        ui->Image->setScene(scene);
        ui->Image->fitInView(it, Qt::KeepAspectRatio);
    }

}
