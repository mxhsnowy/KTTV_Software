#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont font;
    font.setPointSize(12);
    modeLabel->setFont(font);
    modeBox->setMinimumHeight(36);
    modeBox->setFont(font);
    modeBox->addItems(modeList);
    modeLabel->setText(boxName);
    ui->Mask->setMouseTracking(true);
    ui->showFolder->verticalScrollBar()->setSingleStep(8);
    ui->toolBar->addWidget(modeLabel);
    ui->toolBar->addWidget(modeBox);
    QList<QString> labels = {"Thời gian", "Giá trị"};
    ui->dataView->setHorizontalHeaderLabels(labels);

    connect(ui->actionZoom, &QAction::triggered, this, &MainWindow::zoomToggled);
    connect(ui->actionOpenFolder, &QAction::triggered, this, &MainWindow::openFolder);
    connect(ui->showFolder, &QListWidget::itemClicked, this, &MainWindow::itemClicked);
    //connect(ui->actionDrawingLine, &QAction::triggered, this, &MainWindow::overlap);
    connect(ui->actionreport, &QAction::triggered, this, &MainWindow::exportNow);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::quitApp);
    connect(ui->nextDay, &QPushButton::clicked, this, &MainWindow::nextDay);
    connect(ui->prevDay, &QPushButton::clicked, this,&MainWindow::prevDay);
    connect(modeBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index){ switchMode(index); });

    //connect(modeBox, &QComboBox::currentIndexChanged, this, &MainWindow::switchMode);
    //ui->Mask->scene()->installEventFilter(this);
}
void MainWindow::pointToValue(double x, double y){

    if (water){
        y =  sizeHeight - y;
        int gridX = int(x/gridWidth);
        int gridY = int(y/gridHeight);


        pixelLitter = gridY * 430;
        time.setHMS(7, 0, 0);
        time = time.addSecs(gridX*600);
        //time = getTime(pixelTime, 7);
    }
    else if(rain){
        y =  sizeHeight - y;
        int gridX = int(x/gridWidth);
        int gridY = int(y/gridHeight);

        pixelLitter = gridY * 10;
        time.setHMS(7, 20, 0);
        time = time.addSecs(gridX*600);
    }
    else if (moisture){

    }
}
void MainWindow::exportNow(){

    if(!mask.isNull()){
        extractData();
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Bạn chưa vẽ đường đồ thị");
        msgBox.exec();
    }
}

void MainWindow::extractData(){
    //if (rain){
    //    QRect crop(0, sizeHeight, sizeWidth, sizeHeight-130);
    //    mask = mask.copy(crop);
    //}

    QFile data(exportPath);
    QVector<double> ml;
    QVector<int> ts;
    QVector<double> ts10;
    QVector<double> ml10;
    for (int i = 0; i < mask.width(); ++i) {
        for (int j = 0; j < mask.height(); ++j) {
            if(mask.pixelColor(i, j) == QColor(255, 255, 255)){
                ml.append(mask.height() - j);
                ts.append(i);
            }
        }
    }
    //qDebug()<<"Time pixels are "<<ts<<endl;
    //! case for water
    if(water) {

        for (int i = 0; i < ts.size(); i++) {
            ml[i] = ml[i]*430 / gridHeight;
            ts[i] = int(ts[i]*10 / gridWidth);
        }
        QTime ctime(7 ,0, 0);
        QTime rptime;
        if(data.open(QFile::WriteOnly)|QFile::Truncate){
            QTextStream item(&data);
            for (int i = 0; i < ml.size(); i = i + int(gridWidth)) {

                rptime = ctime.addSecs(ts.at(i)*60);

                item << ctime.toString("HH:mm")<<" "<< ml.at(i) << "\n";

                QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(rptime.toString("HH:mm")));
                QTableWidgetItem *item2 = new QTableWidgetItem(QString("%1").arg(QString::number(ml.at(i))));
                ui->dataView->insertRow(ui->dataView->rowCount());
                ui->dataView->setItem(ui->dataView->rowCount() - 1, 0, item);
                ui->dataView->setItem(ui->dataView->rowCount() - 1, 1, item2);
            }
        }
    }
    else if (moisture) {

    }
    //! case for rain
    else if (rain){
        for (int i = 0; i < ts.size(); i++) {

            if((ts.at(i) % int(gridWidth)) == 0){
                ts10.append(ts.at(i)*10/int(gridWidth));
                ml10.append(ml.at(i)*10/gridHeight);
            }
        }
        qDebug()<<"Time vector:"<<ts10<<endl;
        qDebug()<<"Litter vector:"<<ml10<<endl;
        QTime ctime(7 , 20, 0);
        QTime rptime;
        if(data.open(QFile::WriteOnly)|QFile::Truncate){
            QTextStream item(&data);
            for (int i = 0; i < ts10.size(); i++) {
                rptime = ctime.addSecs(ts10.at(i)*60);
                int lit = int(ml10.at(i)+50);
                int litp = lit;
                if(i>1){
                    litp = int(ml10.at(i-1)+50);
                }
                item << rptime.toString("HH:mm")<<" "<< lit-litp << "\n";
                QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(rptime.toString("HH:mm")));
                QTableWidgetItem *item2 = new QTableWidgetItem(QString("%1").arg(QString::number(lit-litp)));
                ui->dataView->insertRow(ui->dataView->rowCount());
                ui->dataView->setItem(ui->dataView->rowCount() - 1, 0, item);
                ui->dataView->setItem(ui->dataView->rowCount() - 1, 1, item2);
            }
        }
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *event){
    if (event->type() ==  QEvent::GraphicsSceneMouseMove ) {
       QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);

       QPointF img_coord_pt = mouseEvent->scenePos();

       double x = img_coord_pt.x();
       double y = img_coord_pt.y();


       pointToValue(x, y);
       ui->Mask->toolTip();
       ui->Mask->setToolTip(QString("Lượng nước: %1\nThời gian: %2").arg(pixelLitter).arg(time.toString("HH:mm")));

       return true;
     }
    else {

       return QObject::eventFilter(object, event);
     }
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::nextDay(){
    dayCount = dayCount + 1;
    ui->day->setText(QString::number(dayCount));
    ui->dataView->clearContents();
    ui->dataView->setRowCount(0);
    QString maskPath = itemPath.replace("1.chart", thinned);
    if(rain){
        maskPath.insert(maskPath.size() - 4, QString("_%1").arg(QString::number(dayCount)));
        maskPath = maskPath.replace(".jpg", ".png");
        exportPath = maskPath.replace(thinned, "Thư mục báo cáo");
        exportPath = exportPath.replace(".png", ".txt");
    }
    mask.load(maskPath);
    QImage resultImg = createImageWithOverlay(image, mask);
    scene->clear();
    scene->installEventFilter(this);
    QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(resultImg));
    scene->addItem(it);
    ui->Mask->setScene(scene);
    ui->Mask->fitInView(it, Qt::KeepAspectRatioByExpanding);
}
void MainWindow::prevDay(){
    dayCount = dayCount - 1;
    ui->day->setText(QString::number(dayCount));
    ui->dataView->clearContents();
    ui->dataView->setRowCount(0);
    QString maskPath = itemPath.replace("1.chart", thinned);
    if(rain){
        maskPath.insert(maskPath.size() - 4, QString("_%1").arg(QString::number(dayCount)));
        maskPath = maskPath.replace(".jpg", ".png");
        exportPath = maskPath.replace(thinned, "Thư mục báo cáo");
        exportPath = exportPath.replace(".png", ".txt");
    }
    mask.load(maskPath);
    if(!mask.isNull()){
        QImage resultImg = createImageWithOverlay(image, mask);
        scene->clear();
        scene->installEventFilter(this);
        QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(resultImg));
        scene->addItem(it);
        ui->Mask->setScene(scene);
        ui->Mask->fitInView(it, Qt::KeepAspectRatioByExpanding);
    }
}
void MainWindow::switchMode(int index){
    QList<QString> labels = {"Thời gian", "Tăng so với lúc trước"};
    switch (index) {
    case 0:
        moisture = 1;
        water = 0;
        pressure = 0;
        rain = 0;
        tempature = 0;
        iconSize = QSize(250, 70);
        ui->showFolder->setGridSize(QSize(250, 100));
        ui->showFolder->setIconSize(iconSize);
        break;
    case 1:
        pressure = 1;
        water = 0;
        moisture = 0;
        rain = 0;
        tempature = 0;
        iconSize = QSize(250, 70);
        ui->showFolder->setGridSize(QSize(250, 100));
        ui->showFolder->setIconSize(iconSize);
        break;
    case 2:
        rain = 1;
        water = 0;
        pressure = 0;
        moisture = 0;
        tempature = 0;
        iconSize = QSize(250, 70);
        ui->showFolder->setGridSize(QSize(250, 100));
        ui->showFolder->setIconSize(iconSize);
        ui->dataView->setHorizontalHeaderLabels(labels);
        break;
    case 3:
        tempature = 1;
        water = 0;
        pressure = 0;
        moisture = 0;
        rain = 0;
        iconSize = QSize(250, 70);
        ui->showFolder->setGridSize(QSize(250, 100));
        ui->showFolder->setIconSize(iconSize);
        break;
    case 4:
        water = 1;
        pressure = 0;
        moisture = 0;
        rain = 0;
        tempature = 0;
        iconSize = QSize(250, 350);
        ui->showFolder->setGridSize(QSize(250, 380));
        ui->showFolder->setIconSize(QSize(iconSize));
        break;
    }
}
void MainWindow::openFolder(){
    QString defaultDir = QDir::homePath();
    QSettings lastDir;
    chosenDir = QFileDialog::getExistingDirectory(this, tr("Chọn thư mục"),
                                                           lastDir.value(defaultDir).toString());

    if(!chosenDir.isEmpty()){
        exportDir = chosenDir.replace("1.chart", "Thư mục báo cáo");
        QDir().mkdir(exportDir);
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
            QImageReader *reader = new QImageReader(absPath);
            reader->setScaledSize(iconSize);
            icon = QIcon(QPixmap::fromImageReader(reader));
            QListWidgetItem *item = new QListWidgetItem(icon, itemName);
            ui->showFolder->addItem(item);
            delete reader;
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
    if(rain){
        maskPath.insert(maskPath.size() - 4, QString("_%1").arg(QString::number(dayCount)));
        maskPath = maskPath.replace(".jpg", ".png");
    }
    mask.load(maskPath);
    QImage resultImg = createImageWithOverlay(image, mask);
    scene->clear();
    scene->installEventFilter(this);
    QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(resultImg));
    scene->addItem(it);
    ui->Mask->setScene(scene);
    ui->Mask->fitInView(it, Qt::KeepAspectRatioByExpanding);
}
void MainWindow::quitApp(){
    int ret = QMessageBox::question(this, "Thoát", "Bạn có muốn thoát hay không?",
                          QMessageBox::Yes|QMessageBox::No);
    if(ret == QMessageBox::Yes){
        QCoreApplication::quit();
    }
}
void MainWindow::itemClicked(QListWidgetItem *item){
    itemPath = chosenDir + "\\" + item->text();
    dayCount = 0;
    ui->imgName->setText(item->text());
    ui->day->setText(QString::number(dayCount));
    ui->dataView->clearContents();
    if(image.load(itemPath)){
        //image = image.scaled(2304, 3200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        //qDebug()<<image.size()<<endl;

        scene->clear();
        scene->installEventFilter(this);
        QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        scene->addItem(it);
        ui->Mask->setScene(scene);
        ui->Mask->fitInView(it, Qt::KeepAspectRatioByExpanding);
    }

    QSize imgSize = image.size();
    if (water){
        sizeWidth = imgSize.width();
        sizeHeight = imgSize.height();
        gridWidth = sizeWidth/144;
        gridHeight = sizeHeight/400;
    }
    else if (rain){
        sizeWidth = imgSize.width();
        sizeHeight = imgSize.height() - 130;
        gridWidth = sizeWidth/150;
        gridHeight = sizeHeight/110;
        qDebug()<<"grid width is "<<gridWidth<<endl;
        qDebug()<<"grid height is "<<gridHeight<<endl;
    }
    else if (moisture){
        sizeWidth = imgSize.width();
        sizeHeight = imgSize.height();
        gridWidth = sizeWidth/104;
        gridHeight = sizeHeight/50;
    }
}

void MainWindow::zoomToggled(bool enabled){
    ui->Mask->zoomEnabled = enabled;
    ui->Mask->setCursor(Qt::CrossCursor);
}


