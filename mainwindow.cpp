#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Mask->setMouseTracking(true);

    ui->toolBar->addWidget(name);
    //ui->Mask->scene()->installEventFilter(this);
}
bool MainWindow::eventFilter(QObject *object, QEvent *event){
    if (event->type() ==  QEvent::GraphicsSceneMouseMove ) {
       QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);

       QPointF img_coord_pt = mouseEvent->scenePos();

       double x = img_coord_pt.x();
       double y = img_coord_pt.y();

       QColor color = QColor(image.toImage().pixel(x,y));
       int average = (color.red()+color.green()+color.blue())/3;
       ui->Mask->toolTip();
       ui->Mask->setToolTip(QString("%1, %2, %3").arg(QString::number(x), QString::number(y), QString::number(average)));
       //ui->label_X->setText(QString::number(x));
       //ui->label_Y->setText(QString::number(y));
       name->setText(QString::number(average));

       return true;
     } else {
       return QObject::eventFilter(object, event);
     }
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

    if(image.load(chosenDir + "\\" + item->text())){
        scene->clear();
        scene->installEventFilter(this);
        QGraphicsPixmapItem *it = new QGraphicsPixmapItem(image);
        scene->addItem(it);
        ui->Mask->setScene(scene);
        ui->Mask->fitInView(it, Qt::KeepAspectRatioByExpanding);
    }

}



void MainWindow::on_actionZoom_toggled(bool enabled)
{
    ui->Mask->zoomEnabled = enabled;
}
