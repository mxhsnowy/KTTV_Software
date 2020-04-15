#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Mask->setMouseTracking(true);


    connect(ui->actionZoom, &QAction::triggered, this, &MainWindow::zoomToggled);
    connect(ui->actionOpenFolder, &QAction::triggered, this, &MainWindow::openFolder);
    connect(ui->showFolder, &QListWidget::itemClicked, this, &MainWindow::itemClicked);
    connect(ui->actionDrawingLine, &QAction::triggered, this, &MainWindow::overlap);


    //ui->Mask->scene()->installEventFilter(this);
}
//QVector<int> MainWindow::pixelToGrid(double x, double y){
//    QVector<int> gridPos;
//    gridPos.replace(x/8, 0);
//    gridPos.replace(y/16,1);
//    return gridPos;
//}
QString MainWindow::getTime(double minutes, double start = 7){
    double hour = minutes/60;
    double hours = hour + start;
    if(hours>=24){
        hours = hour - 17;
    }
    int rpH = int(hours);
    int rpM = (hours - rpH) * 60;
    QString time = QString("%1:%2").arg(QString::number(rpH), QString::number(rpM));
    return time;
}
void MainWindow::pointToValue(double x, double y){
    //bool water = chosenDir.contains("nuoc", Qt::CaseSensitive);
    //bool moisture = chosenDir.contains("am", Qt::CaseSensitive);
    //if (water){

//        y = -(y - 3200);

//        valX = x/16.0;
//        valY = y/8.0;


//        //valY = valY * 430;
//        //valX = valX * 10;

//        //time = getTime(valX, 7);
//    }
    //else if (moisture) {
//        //!
//        double iX = x/133.0;

//        double modX = 7.232 * qPow(10, -5) * qPow(y, 2) - 0.289 * y + 133 * iX;
//        //double modX2 = 7.232 * qPow(10, -5) * qPow(y, 2) - 0.289 * y + 133 * (iX + 1);
//        valX = modX / 133.0;
//        //valX = iX;
//        //! Each X equal 15 mins
//        valX = valX * 15;
//        time = getTime(valX, 6.5);
//        //! each horizontal grid represents 80 ml
//        y = -(y - 4000);
//        valY = y/80.0;
//        valY = valY * 2;
//    }
}
bool MainWindow::eventFilter(QObject *object, QEvent *event){
    if (event->type() ==  QEvent::GraphicsSceneMouseMove ) {
       QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);

       QPointF img_coord_pt = mouseEvent->scenePos();

       double x = img_coord_pt.x();
       double y = img_coord_pt.y();

       y = -(y - imgSize.height());
       int gridX = int(x/valX);
       int gridY = int(y/valY);


       //pointToValue(x, y);
//       QColor color = QColor(image.toImage().pixel(x,y));
//       int average = (color.red()+color.green()+color.blue())/3;
       ui->Mask->toolTip();
       ui->Mask->setToolTip(QString("row %1\ncol %2").arg(gridY + 1).arg(gridX + 1));

       return true;
     } else {
       return QObject::eventFilter(object, event);
     }
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::next(){

}
void MainWindow::prev(){

}
void MainWindow::openFolder(){
    QString defaultDir = QDir::homePath();
    QSettings lastDir;
    chosenDir = QFileDialog::getExistingDirectory(this, tr("Chọn thư mục"),
                                                          lastDir.value(defaultDir).toString());
    if(!chosenDir.isEmpty()){
        bool water = chosenDir.contains("nuoc", Qt::CaseInsensitive);
        if (water){
            ui->showFolder->setGridSize(QSize(250, 370));
            ui->showFolder->setIconSize(QSize(250, 350));
        }
        else {
            ui->showFolder->setGridSize(QSize(250, 195));
            ui->showFolder->setIconSize(QSize(250, 175));
        }
        ui->showFolder->clear();
        QIcon icon;
        QDir loadDir(chosenDir);
        lastDir.setValue(defaultDir, loadDir.path());
        QStringList filter;
        filter<<"*.jpg"<<"*.JPG"<<"*.png";
        loadDir.setNameFilters(filter);
        QList<QFileInfo> infoList = loadDir.entryInfoList();

        foreach (const QFileInfo &fileInfo, infoList) {

            QString itemName = fileInfo.fileName();
            QString absPath = fileInfo.absoluteFilePath();
            QImageReader reader(absPath);
            //reader.setScaledSize(QSize(250, 70));
            icon = QIcon(QPixmap::fromImage(reader.read()));
            QListWidgetItem *item = new QListWidgetItem(icon, itemName);
            ui->showFolder->addItem(item);
        }

    }

}
QImage MainWindow::createImageWithOverlay(const QImage& baseImage, const QImage& overlayImage)
{
    QImage imageWithOverlay = QImage(baseImage.size(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&imageWithOverlay);

    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(imageWithOverlay.rect(), Qt::transparent);

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, baseImage);

    painter.setCompositionMode(QPainter::CompositionMode_Plus);
    painter.drawImage(0, 0, overlayImage);

    painter.end();

    return imageWithOverlay;

}

void MainWindow::overlap(){
    QString maskPath = itemPath.replace("1.chart", thinned);
    QImage overlayImg(itemPath);
    QImage resultImg = createImageWithOverlay(image.toImage(), overlayImg);
    scene->clear();
    scene->installEventFilter(this);
    QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(resultImg));
    scene->addItem(it);
    ui->Mask->setScene(scene);
    ui->Mask->fitInView(it, Qt::KeepAspectRatioByExpanding);
}

void MainWindow::itemClicked(QListWidgetItem *item){
    itemPath = chosenDir + "\\" + item->text();
    if(image.load(itemPath)){
        //image = image.scaled(2304, 3200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        //qDebug()<<image.size()<<endl;

        scene->clear();
        scene->installEventFilter(this);
        QGraphicsPixmapItem *it = new QGraphicsPixmapItem(image);
        scene->addItem(it);
        ui->Mask->setScene(scene);
        ui->Mask->fitInView(it, Qt::KeepAspectRatioByExpanding);
    }
    ui->Mask->setCursor(Qt::CrossCursor);

    imgSize = image.size();
    bool water = chosenDir.contains("nuoc", Qt::CaseSensitive);
    if (water){
        valY = imgSize.width()/144;
        valX = imgSize.height()/400;
    }
    else {
        valY = imgSize.width()/133;
        valX = imgSize.height()/80;
    }
}

void MainWindow::zoomToggled(bool enabled){
    ui->Mask->zoomEnabled = enabled;
}


