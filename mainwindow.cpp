#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "convert.h"
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
    timeLabel->setFrameShape(QFrame::Box);
    timeLabel->setFont(font);
    colNum->setFont(font);
    icon1->setPixmap(QPixmap(":/icon/icons/KttvIconCrop.jpg").scaled(48, 40));
    icon2->setPixmap(QPixmap(":/icon/icons/logo.jpg").scaled(48, 40));
    rowNum->setFont(font);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    modeBox->setFont(font);
    modeBox->addItems(modeList);

    modeLabel->setText(boxName);

    //! adding widgets to toolbar
    ui->Mask->setMouseTracking(true);
    ui->showFolder->verticalScrollBar()->setSingleStep(8);
    ui->toolBar->addWidget(modeLabel);
    ui->toolBar->addWidget(modeBox);


    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(timeLabel);
    ui->toolBar->addWidget(spacer);
    ui->toolBar->addWidget(icon1);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(icon2);
    installEventFilter(this);

    stationsName = loadTxtToStringList(sNPath);
    stationsID = loadTxtToStringList(sIPath);
    stationsNameW = loadTxtToStringList(sNPathW);
    stationsIDW = loadTxtToStringList(sIPathW);

    connect(ui->Mask, &MyGraphicsView::copyVariable, this, &MainWindow::getNewVariables);
    connect(ui->actionZoom, &QAction::triggered, this, &MainWindow::zoomToggled);
    connect(ui->actionOpenFolder, &QAction::triggered, this, &MainWindow::openFolder);
    connect(ui->showFolder, &QListWidget::itemClicked, this, &MainWindow::itemClicked);
    connect(ui->actionCutGrid, &QAction::triggered, this, &MainWindow::cropGridToggled);
    connect(ui->save, &QPushButton::clicked, this, &MainWindow::saveToTxt);
    connect(ui->digitalize, &QPushButton::clicked, this, &MainWindow::exportNow);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::quitApp);
    connect(ui->nextDay, &QPushButton::clicked, this, &MainWindow::nextDay);
    connect(ui->prevDay, &QPushButton::clicked, this, &MainWindow::prevDay);
    connect(ui->actionSetting, &QAction::triggered, this, &MainWindow::inputDialog);
    connect(ui->Mask, &MyGraphicsView::getMouseDrawPoints, this, &MainWindow::mouseDrawLineToMask);
    connect(ui->actiondrawMask, &QAction::triggered, this, &MainWindow::drawToggled);
    connect(modeBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index){ switchMode(index); });
    connect(ui->stationBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index){ NameToID(index); });
    connect(ui->stationID, QOverload<int>::of(&QComboBox::currentIndexChanged),
                    [=](int index){ IDToName(index); });
    connect(ui->actionrotateAndCrop, &QAction::triggered, this, &MainWindow::enableRotateandCrop);
    switchMode(0);
    opened = 0;
}
void MainWindow::NameToID(int idx){
    ui->stationID->setCurrentIndex(idx);
}
void MainWindow::IDToName(int idx){
    ui->stationBox->setCurrentIndex(idx);
}
QStringList MainWindow::loadTxtToStringList(const QString &txtpath){
    QStringList list;
    QString line;
    QFile textFile(txtpath);
    QTextStream stream(&textFile);
    stream.setCodec("UTF-8");
    if(textFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        while (!stream.atEnd()) {
            list<<stream.readLine();
        }
    }
    else{
        qDebug()<<"file is not existed"<<endl;
    }
    textFile.close();
    qDebug()<<list<<endl;
    return list;
}
void MainWindow::mouseDrawLineToMask(const QVector<QPointF> &input){

    qDebug()<<"Drew vector is"<<input<<endl;
    QImage newMask(image.width(), image.height(), QImage::Format_RGB32);
    qDebug()<<"width of image is"<<newMask.width()<<endl;
    qDebug()<<"height of image is"<<newMask.height()<<endl;
    newMask.fill(Qt::black);
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(1);
    pen.setCapStyle(Qt::RoundCap);
    QPainter painter(&newMask);
    painter.setPen(pen);
    painter.drawPolyline(input.data(), static_cast<int>(input.size()));
    //painter.drawLines(input);
//    for (QPointF x: input) {
//        painter.drawPoint(x);
//    }
//    for (int i = 1; i<input.size(); i++) {
//        painter.drawLine(input.at(i-1), input.at(i));
//    }
    //painter.drawLines(input);
    //painter.end();
    mask = newMask;
    QImage resultImg = createImageWithOverlay(image, mask);
    scene->clear();
    scene->installEventFilter(this);
    QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(resultImg));
    scene->addItem(it);
    ui->Mask->setScene(scene);
    ui->Mask->fitInView(it, Qt::KeepAspectRatio);
}
void MainWindow::getNewVariables(int xmin, int ymin, int xmax, int ymax){
//    qDebug()<<"xmin:"<<x_min<<endl;
//    qDebug()<<"ymin:"<<y_min<<endl;
//    qDebug()<<"xmax:"<<x_max<<endl;
//    qDebug()<<"ymax:"<<y_max<<endl;
    //QImage nImage = image.copy();
    //QPainter painter(&nImage);
    if (ui->actionZoom->isChecked()){
        ui->actionZoom->toggle();
    }
    x_min = xmin;
    y_min = ymin;
    x_max = xmax;
    y_max = ymax;
    ratio = 1;
    cropped = true;
    QMessageBox msgBox;
    msgBox.setText("Đã lấy được tọa độ grid.");
    msgBox.setIcon(QMessageBox::Information);
    int ret = msgBox.exec();
    if(ret != 0){
        //QImage nImage = image;
        image = cropOnly(image);
        QPainter painter(&image);
        QPen pen;
        pen.setWidth(0.0015 * (y_max - y_min));
        pen.setColor(Qt::blue);
        pen.setCapStyle(Qt::RoundCap);
        painter.setPen(pen);
        //painter.drawRect(x_min, y_min, x_max - x_min, y_max-y_min);
        painter.drawLine(0, y_min, x_max, y_min);
        painter.drawLine(0, y_max, x_max, y_max);
        painter.end();
        if(!mask.isNull()){
            mask = cropOnly(mask);
            QImage resultImg = createImageWithOverlay(image, mask);
            scene->clear();
            scene->installEventFilter(this);
            QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(resultImg));
            scene->addItem(it);
            ui->Mask->setScene(scene);
            ui->Mask->fitInView(it, Qt::KeepAspectRatio);
        }
        else {
            scene->clear();
            scene->installEventFilter(this);
            QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(image));
            scene->addItem(it);
            ui->Mask->setScene(scene);
            ui->Mask->fitInView(it, Qt::KeepAspectRatio);
        }
    }
    //ui->actionCutGrid->toggle();
}

int MainWindow::timeToCols(){
    int diff = startTime.secsTo(endTime);
    int cols = 0;
    if (days>0){
        diff = 86400*days + diff;
    }
    cols = diff/(timeSpace*60);
//    if (chartType == "am"){
//       cols = std::round(diff/900);
//    }
//    else if (chartType == "ap") {
//       cols = std::round(diff/900);
//    }
//    else if (chartType == "mua"){
//       cols = std::round(diff/600);
//    }
//    else if (chartType == "nhiet"){
//       cols = std::round(diff/600);
//    }
//    else if (chartType == "nuoc"){
//       cols = std::round(diff/600);
//    }
    return cols;
}
int MainWindow::levelToRows(){
    double diff = endLevel - startLevel;
    int rows = diff/levelSpace;
//    if (chartType == "am"){
//        rows = diff/2;
//    }
//    else if (chartType == "ap") {
//        rows = diff/1;
//    }
//    else if (chartType == "mua"){
//        rows = diff/0.1;
//    }
//    else if (chartType == "nhiet"){
//        rows = diff/1;
//    }
//    else if (chartType == "nuoc"){
//        rows = diff/0.5;
//    }
    return rows;
}
void MainWindow::changeSetup(){
    //if(!opened){
        startTime = dialog->time1->time();
        endTime = dialog->time2->time();
        timeSpace = dialog->timeS->value();
        days = dialog->day->value();
        startLevel = dialog->level1->value();
        endLevel = dialog->level2->value();
        levelSpace = dialog->levelS->value();
        bias = dialog->bias->value();
        addUp = dialog->levelD->value();
        numCols = timeToCols();
        numRows = levelToRows();

        //gridWidth = (x_max-x_min)*ratio/numCols + bias/*154*/;
        //gridHeight = (y_max-y_min)*ratio/numRows/*80*/;

    //}
    //else {
//        dialog->time2->setTime(endTime);
//        dialog->time1->setTime(startTime);
//        dialog->timeS->setValue(timeSpace);
//        dialog->day->setValue(days);
//        dialog->level1->setValue(startLevel);
//        dialog->level2->setValue(endLevel);
//        dialog->levelS->setValue(levelSpace);
//        numCols = timeToCols();
//        numRows = levelToRows();
//        addUp = startLevel;
    //}
    timeLabel->setText(QString("%1: %2->%3+%9h %10 phút(%4) || %5: %6->%7 %11 %13(%8) %12 %14").arg("Thời gian").arg(startTime.toString("HH:mm")).arg(endTime.toString("HH:mm")).arg(QString::number(numCols))
                       .arg(colNames[1]).arg(QString::number(startLevel)).arg(QString::number(endLevel)).arg(QString::number(numRows)).arg(days*24).arg(timeSpace).arg(levelSpace).arg(addUp).arg(bubble[2]).arg(bias));


}
void MainWindow::saveToTxt(){
    QString exportFile = exportDir+"/"+ui->IDchart->text()+"_"+ui->daychart->text()+".csv";
    //exportFile.remove(".jpg");
    QFile f(exportFile);
    exportFile = exportImgs+"/"+ui->IDchart->text()+"_"+ui->daychart->text()+".jpg";

    if (f.open(QFile::WriteOnly | QFile::Truncate) && !image.isNull())
    {
        QTextStream stream(&f);
        stream.setCodec("UTF-8");
        QString conTents;
        QHeaderView * header = ui->dataView->horizontalHeader() ;
        if (header)
        {
            conTents += "Mã trạm, Tên trạm, Ngày tháng,";
            for ( int i = 0; i < header->count(); i++ )
            {
                QTableWidgetItem *item = ui->dataView->horizontalHeaderItem(i);
                if (!item)
                {
                    continue;
                }
                conTents += item->text()+ ",";
            }
            conTents += "\n";
        }

        for ( int i = 0 ; i < ui->dataView->rowCount(); i++ )
        {
            conTents += ui->stationID->currentText()+ ","+ ui->stationBox->currentText()+ "," + ui->daychart->text() + ",";
            for ( int j = 0; j < ui->dataView->columnCount(); j++ )
            {
                QTableWidgetItem* item = ui->dataView->item(i, j);
                if ( !item )
                    continue;
                QString str = item->text();
                str.replace(","," ");
                conTents += str + ",";
            }
            conTents += "\n";
        }
        stream << conTents;
        f.close();
        addStringToFile(ui->stationBox->currentText(), ui->stationID->currentText());
        imagePr.save(exportFile);
        QMessageBox msgBox;
        msgBox.setText("Đã xuất dữ liệu");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Chưa xuất được dữ liệu do thiếu dữ liệu");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }

}


void MainWindow::pointToValue(double x, double y){
    //qDebug()<<"Old x:"<<x<<endl;

    //x = x/qCos(angle);
    //y = y/qCos(angle);
    y = (y_max - y_min)*ratio - y;
    //qDebug()<<"Old y:"<<y<<endl;
    //converting angle from degrees to radians
    //Computer graphics rotation
//    if(water || rain){
//        x = x*cos + y*sin;
//        y = -x*sin + y*cos;
//    }....

    //Mathematics rotation
//    x = x*cos - y*sin;
//    y = x*sin + y*cos;
//    qDebug()<<"New x:"<<x<<endl;
//    qDebug()<<"New y:"<<y<<endl;
    gridnX = int(x/gridWidth);
    gridnY = int(y/gridHeight);
    //qDebug()<<x<<endl;
    //qDebug()<<gridnX<<endl;
    //qDebug()<<gridnY<<endl;
    time = startTime;
    if (chartType == "nuoc"){
        //int gridX = int(x/gridWidth);
        //int gridY = int(y/gridHeight);


        time = time.addSecs(gridnX*timeSpace*60);
    }
    else if(chartType == "mua"){
        //pixelLitter = gridnY * levelSpace + addUp;
        //time.setHMS(7, 20, 0);
        //time = time.addSecs(gridnX*timeSpace*60);
        time = time.addSecs(gridnX*timeSpace*60);
    }
    else if (chartType == "am"){
        //pixelLitter = gridnY * 2 + addUp;
        parabolPos = 7.4085 * qPow(10, -5) * qPow(y, 2) - 0.3195316*y + gridWidth*(gridnX+1);

        //time.setHMS(6, 30, 0);
        timeX = parabolGrid(x, parabolPos, gridnX);
        //timeX = -int(x/parabolPos);
        //qDebug()<<timeX<<endl;
        time = time.addSecs(timeX*timeSpace*60);
    }
    else if (chartType == "ap"){
        //pixelLitter = gridnY + addUp;
        parabolPos = 16.179*qPow(10, -5) * qPow(y, 2) - 0.34026 * y + gridWidth*(gridnX+1);
        //time.setHMS(11, 15, 0);
        timeX = parabolGrid(x, parabolPos, gridnX);
        time = time.addSecs(timeX*timeSpace*60);
    }
    else if (chartType == "nhiet"){
        //pixelLitter = gridnY +addUp;
        parabolPos = 28.3179*qPow(10, -5) * qPow(y, 2) - 0.31458 * y + gridWidth*(gridnX+1);
        //time.setHMS(6, 30, 0);
        timeX = parabolGrid(x, parabolPos, gridnX);
        time = time.addSecs(timeX*timeSpace*60);
    }
    pixelLitter = gridnY*levelSpace + addUp;

}

int MainWindow::parabolGrid(int mousePos, double parabolPos, int nx){
    if(mousePos>=parabolPos){
        return nx+1;
    }
    else {
        return nx;
    }
}

void MainWindow::detectRainOver(int x, int y, int w, int h){
    //int overflow;
//    QPainter painter(&image);
//    QPen pen;
//    pen.setWidth(20);
//    pen.setColor(Qt::green);
//    painter.setPen(pen);
//    painter.drawRect(x, y, w, h);
//    painter.end();
    QRect cropRectRain(x, y, w, h);
    cropMaskRain = mask.copy(cropRectRain);
    cropRain = cvert::QImageToCvMat(cropMaskRain);
    if(cropRain.channels()>1){
        cv::cvtColor(cropRain, cropRain, cv::COLOR_RGB2GRAY);
    }
    //qDebug()<<cropRain.type()<<endl;
    //cv::imshow("debug"+std::to_string(x), cropRain);
    //cv::HoughLines(cropRain, lines, 1, PI/180, 30, 0, 0);
    cv::threshold(cropRain, cropRain, 10, 255, cv::THRESH_BINARY);
    cv::findContours(cropRain, contours, cv::noArray(), cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    overFlow = contours.size();
    overFlow = 100*overFlow;

    qDebug()<<"Overflow at "<<x<<" is:"<<overFlow<<endl;
    qDebug()<<"Result is:"<<overFlow<<endl;
    qDebug()<<"------------------"<<endl;

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
    //vectors for extracted data from mask
    if(cropped){
        gridWidth = (x_max-x_min)*ratio/numCols+bias;
        gridHeight = (y_max-y_min)*ratio/numRows;
    }
    else{
        gridWidth=sizeWidth/numCols+bias;
        gridHeight=sizeHeight/numRows;
    }
    qDebug()<<"gridWidth is"<<gridWidth<<endl;
    qDebug()<<"width of image"<<image.width()<<endl;
    qDebug()<<"height of image"<<image.height()<<endl;

    qDebug()<<"width of json"<<(x_max-x_min)*ratio<<endl;
    qDebug()<<"height of json"<<(y_max-y_min)*ratio<<endl;
    ui->dataView->clearContents();
    ui->dataView->setRowCount(0);
    QProgressDialog loading("Đang phân tích", "Dừng", 1, 100, this);
    loading.setWindowModality(Qt::WindowModal);
    loading.setValue(0);
    std::vector<int> ml;
    std::vector<int> ts;
    //vectors for storing
    int timeSize = int(gridWidth);

    std::vector<int> ts10; //time vector->reduced time vector
    std::vector<int> ts10l;//time vector
    std::vector<double> ml10; //quantity vector
    std::vector<double> ml10s;//reduced quantity vector

    for (int i = 0; i < mask.width(); ++i) {
        for (int j = 0; j < mask.height(); ++j) {
            if(mask.pixelColor(i, j) == QColor(255, 255, 255)){
                ml.push_back(mask.height() - j);
                ts.push_back(i);
            }
        }
    }
    loading.setValue(20);
    //qDebug()<<"Time pixels are "<<ts<<endl;
    //! case for water
    if(chartType == "nuoc") {
//        for (int i = 0; i < ts.size(); i++) {
//            ts.at(i) = int(ts.at(i)*cos+ml.at(i)*sin);
//            ml.at(i) = int(-ts.at(i)*sin+ml.at(i)*cos);
//        }
        for (int i = 0; i < ts.size(); i++) {
            if(ts.at(i)%timeSize == 0){
                ts10.push_back(ts.at(i));
                ml10.push_back(ml.at(i));
                //ml.at(i) = ml[i]*430 / gridHeight;
                //ts[i] = int(ts[i]*10 / gridWidth);
            }
        }
        loading.setValue(40);
        ts10l = ts10;
        //qDebug()<<"Raw time:"<<ts10l<<endl;
        //qDebug()<<"Raw level:"<<ml10<<endl;
        std::vector<int>::iterator itt;
        itt = std::unique(ts10.begin(), ts10.end());
        ts10.resize(std::distance(ts10.begin(), itt));
        ml10s = removeDuplicate(ts10, ts10l, ml10);
        drawPointDebug(ts10, ml10s, Qt::green);
        //qDebug()<<"Reduced time:"<<ts10<<endl;
        //qDebug()<<"Reduced level:"<<ml10s<<endl;
        //qDebug()<<ts10.size()<<endl;
        //qDebug()<<ml10s.size()<<endl;
        //correcting points' location
//        for (int i = 0; i < ts10.size(); i++) {
//            ts10.at(i) = int(ts10.at(i)*cos+ml10s.at(i)*sin);
//            ml10s.at(i) = int(-ts10.at(i)*sin+ml10s.at(i)*cos);
//        }
//        qDebug()<<"time size:"<<timeSize<<endl;
//        qDebug()<<"Time vector:"<<ts10<<endl;
//        qDebug()<<"Raw vector:"<<ml10s<<endl;

        for (int i = 0; i < ts10.size(); i++) {
            ts10.at(i) = ts10.at(i)*timeSpace*60/int(gridWidth);
            ml10s.at(i) = qRound(ml10s.at(i)*levelSpace/int(gridHeight));
        }
        loading.setValue(60);
        //qDebug()<<"Time vector:"<<ts10<<endl;
        QTime rptime;
        //if(data.open(QFile::WriteOnly|QFile::Truncate)){
        //    QTextStream text(&data);
            for (int i = 0; i < ml10s.size(); i++) {

                rptime = startTime.addSecs(ts10.at(i));

      //          text << rptime.toString("HH:mm")<<" "<< ml10s.at(i) << "\n";

                QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(rptime.toString("HH:mm")));
                QTableWidgetItem *item2 = new QTableWidgetItem(QString("%1").arg(QString::number(ml10s.at(i) + addUp +startLevel)));
                ui->dataView->insertRow(ui->dataView->rowCount());
                ui->dataView->setItem(ui->dataView->rowCount() - 1, 0, item);
                ui->dataView->setItem(ui->dataView->rowCount() - 1, 1, item2);
            }
            loading.setValue(80);
        }
    //}
    else if (chartType == "mua"){

//        for (int i = 0; i < ts.size(); i++) {
//            ts.at(i) = int(ts.at(i)*cos+ml.at(i)*sin);
//            ml.at(i) = int(-ts.at(i)*sin+ml.at(i)*cos);
//        }
        for (int i = 0; i < ts.size(); i++) {
            if((ts.at(i) % timeSize) == 0){
                ts10.push_back(ts.at(i));
                ml10.push_back(ml.at(i));
            }
        }
        loading.setValue(40);
        //qDebug()<<"First lit: "<<ml10<<endl;
        //*10/int(gridWidth)
        //        *10/gridHeight
        //store ts10 before change
        ts10l = ts10;
        //qDebug()<<"Ori vector:"<<ts10l<<endl;
        //transform ts10 to unique elements
        std::vector<int>::iterator itt;
        itt = std::unique(ts10.begin(), ts10.end());
        ts10.resize(std::distance(ts10.begin(), itt));



        //qDebug()<<"Mod vector:"<<ts10l<<endl;
        ml10s = removeDuplicate(ts10, ts10l, ml10);
        //storing after finding all uniques
        ts10l = ts10;
        drawPointDebug(ts10, ml10s, Qt::green);
        for(int i = 0; i < ts10.size(); i++){
            ts10.at(i) = ts10.at(i)*timeSpace*60/int(gridWidth);
            ml10s.at(i) = ml10s.at(i)*levelSpace/int(gridHeight);
        }
        loading.setValue(60);
        //qDebug()<<"Size of time:"<<ts10.size()<<endl;
        //qDebug()<<"time:"<<ts10<<endl;
        //qDebug()<<"lit:"<<ml10s<<endl;


        QTime rptime;
        //if(data.open(QFile::WriteOnly)|QFile::Truncate){
        //    QTextStream text(&data);

        for (int i = 0; i < ts10.size(); i++) {
            rptime = startTime.addSecs(ts10.at(i));
            lit = int(ml10s.at(i));
            litp = lit;
            if(i>0){
                litp = int(ml10s.at(i-1));
                detectRainOver(ts10l.at(i-1), int(gridHeight)*15, gridWidth, int(gridHeight)*4);//testing for only image 7.0
            }
            difL = lit - litp;
            total = difL+overFlow;
            total = total > 0 ? total:0;
            QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(rptime.toString("HH:mm")));
            QTableWidgetItem *item2 = new QTableWidgetItem(QString("%1").arg(QString::number(total)));
            ui->dataView->insertRow(ui->dataView->rowCount());
            ui->dataView->setItem(ui->dataView->rowCount() - 1, 0, item);
            ui->dataView->setItem(ui->dataView->rowCount() - 1, 1, item2);

        }
        loading.setValue(80);
    }
    //}
    else if (chartType == "am") {
        std::vector<double> para;
        std::vector<double> para10;
        std::vector<int> pos;
        //parabolPos = 7.23 * qPow(10, -5) * qPow(y, 2) + 0.28921*y + (gridnX + 1)*gridWidth;
//        for (int i = 0; i < ts.size(); i++) {
//            if((ts.at(i) % timeSize) == 0){
//                ts10.push_back(ts.at(i));
//                ml10.push_back(ml.at(i));
//            }
//        }
        for (int i = 0; i < ts.size(); i++) {
            para.push_back(ts.at(i) - 7.4085*qPow(10, -5)*qPow(ml.at(i), 2) - (-0.3195316*ml.at(i)));
        }
        //qDebug()<<"Cvec:"<<cv<<endl;
        for (int i = 0; i < para.size(); i++) {
            if(int(para.at(i)) % timeSize==0){
                pos.push_back(i);
                para10.push_back(para.at(i)-timeSize);
            }
        }
        for (int j = 0; j < pos.size(); j++) {
            ts10.push_back(ts.at(pos.at(j)));
            ml10.push_back(ml.at(pos.at(j)));
        }

        loading.setValue(40);
        ts10l = ts10;
        //qDebug()<<"Ori vector:"<<ts10l<<endl;
        //transform ts10 to unique elements
        std::vector<int>::iterator itt;
        itt = std::unique(ts10.begin(), ts10.end());
        ts10.resize(std::distance(ts10.begin(), itt));

//        //qDebug()<<"Mod vector:"<<ts10l<<endl;
        ml10s = removeDuplicate(ts10, ts10l, ml10);
        para10 = removeDuplicate(ts10, ts10l, para10);
//        for (int i = 0; i < ts10.size(); i++) {
//            Cvec.push_back(ts10.at(i) - 7.232*qPow(10, -5)*qPow(ml10s.at(i), 2) - (-0.28921*ml10s.at(i)));
//        }

//        qDebug()<<"Pos:"<<Cvec10.size()<<endl;
        qDebug()<<"Old time:"<<ts10l.size()<<endl;
        qDebug()<<"New time:"<<ts10.size()<<endl;
        qDebug()<<"Old level:"<<ml10.size()<<endl;
        qDebug()<<"New level:"<<ml10s.size()<<endl;
        //std::vector<double> ml10ss;
//        for (int i = 0; i < ml10s.size();i++) {
//            paraVec10.push_back(7.232*qPow(10, -5)*qPow(ml10s.at(i), 2)-0.28921*ml10s.at(i)+ts10.at(i)+timeSize);
//        }
//        for (int i = 0; i < ml10s.size(); i++) {
//            ml10s.at(i) = (0.28291 +  qSqrt(qPow(0.28291, 2) - 4*(7.232*qPow(10, -5))*(ts10.at(i)+timeSize-paraVec10.at(i))))/(2*7.232*qPow(10, -5));
//        }
//        for (int i = 0; i < paraVec10.size();i++) {
//            paraVec10.at(i) = paraVec10.at(i)+ts10.at(i);
//        }
//        qDebug()<<"Time(x) vector:"<<ts10<<endl;
        //qDebug()<<"Raw(y) vector:"<<ml10s<<endl;
//        qDebug()<<"Para(xn) vector:"<<paraVec10<<endl;
        //std::vector<double> zeros(para10.size(), 0.0);
        //qDebug()<<ts10<<endl;
//        for (int i = 0; i < ts10.size();i++) {
//            ts10.at(i) = ts10.at(i) - int(ml10s.at(i)*gridWidth/gridHeight);
//        }
        //qDebug()<<ts10<<endl;
        drawPointDebug(ts10, ml10s, Qt::green);
        //drawPointDebug(para10, zeros, Qt::black);
        for(int i = 0; i < para10.size(); i++){
            para10.at(i) = para10.at(i)*timeSpace*60/int(gridWidth);
            ml10s.at(i) = qRound(ml10s.at(i)*levelSpace/int(gridHeight));
        }
        loading.setValue(60);

        QTime rptime;

        //if(data.open(QFile::WriteOnly|QFile::Truncate)){
        //    QTextStream text(&data);
        for (int i = 0; i < ml10s.size(); i++) {
            rptime = startTime.addSecs(para10.at(i));
    //        text << rptime.toString("HH:mm")<<" "<< ml10s.at(i) << "\n";
            QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(rptime.toString("HH:mm")));
            QTableWidgetItem *item2 = new QTableWidgetItem(QString("%1").arg(QString::number(ml10s.at(i)+addUp+startLevel)));
            ui->dataView->insertRow(ui->dataView->rowCount());
            ui->dataView->setItem(ui->dataView->rowCount() - 1, 0, item);
            ui->dataView->setItem(ui->dataView->rowCount() - 1, 1, item2);
        }
        //}
        loading.setValue(80);
    }
    else if (chartType == "ap") {
        std::vector<double> para;
        std::vector<double> para10;
        std::vector<int> pos;
        for (int i = 0; i < ts.size(); i++) {
            para.push_back(ts.at(i) - 16.179*qPow(10, -5)*qPow(ml.at(i), 2) - (-0.34026*ml.at(i)));
        }
        //qDebug()<<"Cvec:"<<cv<<endl;
        for (int i = 0; i < para.size(); i++) {
            if(int(para.at(i)) % timeSize==0){
                pos.push_back(i);
                para10.push_back(para.at(i)-timeSize);
            }
        }
        for (int j = 0; j < pos.size(); j++) {
            ts10.push_back(ts.at(pos.at(j)));
            ml10.push_back(ml.at(pos.at(j)));
        }

        loading.setValue(40);
        ts10l = ts10;
        //qDebug()<<"Ori vector:"<<ts10l<<endl;
        //transform ts10 to unique elements
        std::vector<int>::iterator itt;
        itt = std::unique(ts10.begin(), ts10.end());
        ts10.resize(std::distance(ts10.begin(), itt));

        //qDebug()<<"Mod vector:"<<ts10l<<endl;
        ml10s = removeDuplicate(ts10, ts10l, ml10);
        para10 = removeDuplicate(ts10, ts10l, para10);
        //std::vector<double> zeros(para10.size(), 0.0);
        drawPointDebug(ts10, ml10s, Qt::green);
        //drawPointDebug(para10, zeros, Qt::black);
        //        for (int i = 0; i < ml10s.size();i++) {
        //            paraVec10.push_back(33.4*qPow(10, -5)*qPow(ml10s.at(i), 2) - 0.2479*ml10s.at(i) + ts10.at(i) +timeSize);
        //        }
        for(int i = 0; i < para10.size(); i++){
            para10.at(i) = para10.at(i)*timeSpace*60/int(gridWidth);
            ml10s.at(i) = qRound(ml10s.at(i)*levelSpace/int(gridHeight));
        }
        loading.setValue(60);

        QTime rptime;

        //if(data.open(QFile::WriteOnly|QFile::Truncate)){
        //    QTextStream text(&data);
        for (int i = 0; i < ml10s.size(); i++) {

            rptime = startTime.addSecs(para10.at(i));

    //        text << rptime.toString("HH:mm")<<" "<< ml10s.at(i) << "\n";

            QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(rptime.toString("HH:mm")));
            QTableWidgetItem *item2 = new QTableWidgetItem(QString("%1").arg(QString::number(ml10s.at(i)+addUp+startLevel)));
            ui->dataView->insertRow(ui->dataView->rowCount());
            ui->dataView->setItem(ui->dataView->rowCount() - 1, 0, item);
            ui->dataView->setItem(ui->dataView->rowCount() - 1, 1, item2);
        }
        loading.setValue(80);
        }

    //}
    else if (chartType == "nhiet") {
        std::vector<double> para;
        std::vector<double> para10;
        std::vector<int> pos;

        for (int i = 0; i < ts.size(); i++) {
            para.push_back(ts.at(i) - 28.3179*qPow(10, -5)*qPow(ml.at(i), 2) - (-0.31458*ml.at(i)));
        }
        //qDebug()<<"Cvec:"<<cv<<endl;
        for (int i = 0; i < para.size(); i++) {
            if(int(para.at(i)) % timeSize==0){
                pos.push_back(i);
                para10.push_back(para.at(i)-timeSize);
            }
        }
        for (int j = 0; j < pos.size(); j++) {
            ts10.push_back(ts.at(pos.at(j)));
            ml10.push_back(ml.at(pos.at(j)));
        }

        loading.setValue(40);
        ts10l = ts10;
        //qDebug()<<"Ori vector:"<<ts10l<<endl;
        //transform ts10 to unique elements
        std::vector<int>::iterator itt;
        itt = std::unique(ts10.begin(), ts10.end());
        ts10.resize(std::distance(ts10.begin(), itt));//qDebug()<<"Mod vector:"<<ts10l<<endl;
        ml10s = removeDuplicate(ts10, ts10l, ml10);
        para10 = removeDuplicate(ts10, ts10l, para10);

        drawPointDebug(ts10, ml10s, Qt::green);
        //std::vector<double> zeros(para10.size(), 0.0);
        //drawPointDebug(para10, zeros, Qt::black);
//        for (int i = 0; i < ml10s.size();i++) {
//            paraVec10.push_back(31.6*qPow(10, -5)*qPow(ml10s.at(i), 2) + 0.21933*ml10s.at(i) + ts10.at(i) + timeSize);
//        }
        for(int i = 0; i < ts10.size(); i++){
            para10.at(i) = para10.at(i)*timeSpace*60/int(gridWidth);
            ml10s.at(i) = qRound(ml10s.at(i)*levelSpace/int(gridHeight));
        }
        loading.setValue(60);
        qDebug()<<ml10s<<endl;
        QTime rptime;

      //  if(data.open(QFile::WriteOnly|QFile::Truncate)){
      //      QTextStream text(&data);
            for (int i = 0; i < ml10s.size(); i++) {

                rptime = startTime.addSecs(para10.at(i));

      //          text << rptime.toString("HH:mm")<<" "<< ml10s.at(i) << "\n";

                QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(rptime.toString("HH:mm")));
                QTableWidgetItem *item2 = new QTableWidgetItem(QString("%1").arg(QString::number(ml10s.at(i)+addUp+startLevel)));
                ui->dataView->insertRow(ui->dataView->rowCount());
                ui->dataView->setItem(ui->dataView->rowCount() - 1, 0, item);
                ui->dataView->setItem(ui->dataView->rowCount() - 1, 1, item2);
            }
            loading.setValue(80);
        }
    loading.setValue(100);
    //}


}
std::vector<int> MainWindow::vectorThreshold(std::vector<int> input, QTime threshTime, int day){
    threshTime.setHMS(7, 0, 0);
    int threshHold = startTime.secsTo(threshTime);
    threshHold = threshHold + 86400*day;
    for (auto i = input.begin(); i != input.end(); ++i) {
            if (*i > threshHold) {
                input.erase(i);
            }
        }
    return input;
}

void MainWindow::drawPointDebug(std::vector<double> xP, std::vector<double> yP, const QColor &color){
    //QImage bgImage = image.copy();
    //imagePr = image;
    QPainter painter(&image);
    QPen pen;
    pen.setWidth(0.0015*sizeWidth);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(color);
    painter.setPen(pen);
    for (int i = 0; i < xP.size(); i++) {
        painter.drawPoint(int(xP.at(i)), /*(y_max - y_min)*ratio*/sizeHeight - int(yP.at(i)) /*+ cutoff*/);
    }
    painter.end();
    scene->clear();
    scene->installEventFilter(this);
    QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(it);
    ui->Mask->setScene(scene);
    ui->Mask->fitInView(it, Qt::KeepAspectRatio);
}
void MainWindow::drawPointDebug(std::vector<int> xP, std::vector<double> yP, const QColor &color){
    //QImage bgImage = image.copy();
    //imagePr = image;
    QPainter painter(&image);
    QPen pen;
    pen.setWidth(0.0015*sizeWidth);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(color);
    painter.setPen(pen);
    for (int i = 0; i < xP.size(); i++) {
        painter.drawPoint(xP.at(i), /*(y_max-y_min)*ratio*/sizeHeight - int(yP.at(i)) /*+ cutoff*/);
    }
    painter.end();
    scene->clear();
    scene->installEventFilter(this);
    QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(it);
    ui->Mask->setScene(scene);
    ui->Mask->fitInView(it, Qt::KeepAspectRatio);
}

void MainWindow::drawPointDebug(std::vector<int> xP, std::vector<int> yP, const QColor &color){
    //imagePr= image;
    QPainter painter(&image);
    QPen pen;
    pen.setWidth(0.0015*sizeWidth);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(color);
    painter.setPen(pen);
    for (int i = 0; i < xP.size(); i++) {
        painter.drawPoint(xP.at(i), /*(y_max-y_min)*ratio */sizeHeight- int(yP.at(i)) /*+ cutoff*/);
    }
    painter.end();
    scene->clear();
    scene->installEventFilter(this);
    QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(it);
    ui->Mask->setScene(scene);
    ui->Mask->fitInView(it, Qt::KeepAspectRatio);
}
int MainWindow::first(std::vector<int> input, int n, int x)
{

    // search space is arr[low..high]
        int low = 0;
        int high = n - 1;

        // initialize the result by -1
        int result = -1;

        // iterate till search space contains at-least one element
        while (low <= high)
        {
            // find the mid value in the search space and
            // compares it with target value
            int mid = (low + high)/2;

            // if target is found, update the result and
            // go on searching towards left (lower indices)
            if (x == input[mid])
            {
                result = mid;
                high = mid - 1;
            }

            // if target is less than the mid element, discard right half
            else if (x < input[mid])
                high = mid - 1;

            // if target is more than the mid element, discard left half
            else
                low = mid + 1;
        }

        // return the leftmost index or -1 if the element is not found
        return result;
}
int MainWindow::last(std::vector<int> input, int n, int x)
{

    // search space is A[low..high]
    int low = 0;
    int high = n - 1;

    // initialize the result by -1
    int result = -1;

    // iterate till search space contains at-least one element
    while (low <= high)
    {
        // find the mid value in the search space and
        // compares it with target value
        int mid = (low + high)/2;

        // if target is found, update the result and
        // go on searching towards right (higher indices)
        if (x == input[mid])
        {
            result = mid;
            low = mid + 1;
        }

        // if target is less than the mid element, discard right half
        else if (x < input[mid])
            high = mid - 1;

        // if target is more than the mid element, discard left half
        else
            low = mid + 1;
    }

    // return the leftmost index or -1 if the element is not found
    return result;
}
std::vector<int> MainWindow::removeDuplicate(std::vector<int> uniqueVector, std::vector<int> rawVector, std::vector<int> findVector){
    int index;

    std::vector<int> forward;
    std::vector<int> output;
    for (int x:uniqueVector) {

        index = first(rawVector, rawVector.size(), x);
        forward.push_back(index);

    }

    for(int x:forward){
        output.push_back(findVector.at(x));
    }
    return output;
}
std::vector<double> MainWindow::removeDuplicate(std::vector<int> uniqueVector, std::vector<int> rawVector, std::vector<double> findVector){
    int index;

    std::vector<int> forward;
    std::vector<double> output;
    for (int x:uniqueVector) {

        index = first(rawVector, rawVector.size(), x);
        forward.push_back(index);

    }

    for(int x:forward){
        output.push_back(findVector.at(x));
    }
    return output;
}
void MainWindow::readJson(QString jsonPath){
    QFile jsonfile(jsonPath);
    if(!jsonfile.open(QIODevice::ReadOnly|QIODevice::Text)){
      qDebug()<<"Read failed "<<jsonPath;
    }
    QTextStream jsonText(&jsonfile);
    QString jsonString = jsonText.readAll();
    jsonfile.close();
    QByteArray data = jsonString.toLocal8Bit();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    if(doc.isNull()){
        qDebug()<<"Parse failed"<<endl;
    }
    QJsonObject jsonObj = doc.object();
    if(jsonObj.isEmpty()){
        qDebug()<<"Json object is empty"<<endl;
    }
    QVariantMap jsonMap = jsonObj.toVariantMap();
    angle = jsonMap["angle"].toDouble();
    x_min = jsonMap["x_min"].toInt();
    y_min = jsonMap["y_min"].toInt();
    x_max = jsonMap["x_max"].toInt();
    y_max = jsonMap["y_max"].toInt();
    column = jsonMap["column"].toInt();
    cos = qCos(angle);
    sin = qSin(angle);
}
bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() ==  QEvent::GraphicsSceneMouseMove ) {
       QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
       QPointF img_coord_pt = mouseEvent->scenePos();
       double x = img_coord_pt.x();
       double y = img_coord_pt.y();
       pointToValue(x, y);
       //ui->Mask->toolTip();
       ui->Mask->setToolTip(QString("%1 %2\n%3 %4").arg(bubble[1]).arg(pixelLitter).arg(bubble[0]).arg(time.toString("HH:mm")));
       return true;
     }
    else if(event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Delete){
            removeTableRows();
        }
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
    ui->daychart->setText(QString::number(dayCount));
    ui->dataView->clearContents();
    ui->dataView->setRowCount(0);
    QString maskPath;
    maskPath = itemPath.replace(jsonFolder, lineFolder);
    maskPath.insert(maskPath.size() - 4, QString("_%1").arg(QString::number(dayCount)));
    maskPath.replace(".jpg", ".png");

    //mask = QImage();
    mask.load(maskPath);

    if(!mask.isNull()){
        if(cropped){
            mask = RotateAndCrop(mask);
        }
        QImage resultImg = createImageWithOverlay(image, mask);
        scene->clear();
        QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(resultImg));
        scene->addItem(it);
        ui->Mask->setScene(scene);
        ui->Mask->fitInView(it, Qt::KeepAspectRatio);

    }
    else {

        scene->clear();
        QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        scene->addItem(it);
        ui->Mask->setScene(scene);
        ui->Mask->fitInView(it, Qt::KeepAspectRatio);
        QMessageBox msgBox;
        msgBox.setText("Đã hết ngày trên đồ thị.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}
void MainWindow::prevDay(){
    dayCount = dayCount - 1;
    ui->daychart->setText(QString::number(dayCount));
    ui->dataView->clearContents();
    ui->dataView->setRowCount(0);
    QString maskPath;
    maskPath = itemPath.replace(jsonFolder, lineFolder);
    maskPath.insert(maskPath.size() - 4, QString("_%1").arg(QString::number(dayCount)));
    maskPath.replace(".jpg", ".png");
    //mask = QImage();
    mask.load(maskPath);
    if(!mask.isNull()){
        if(cropped){
            mask = RotateAndCrop(mask);
        }
        QImage resultImg = createImageWithOverlay(image, mask);
        scene->clear();
        QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(resultImg));
        scene->addItem(it);
        ui->Mask->setScene(scene);
        ui->Mask->fitInView(it, Qt::KeepAspectRatio);

    }
    else{

        scene->clear();
        QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        scene->addItem(it);
        ui->Mask->setScene(scene);
        ui->Mask->fitInView(it, Qt::KeepAspectRatio);
        QMessageBox msgBox;
        msgBox.setText("Đã hết ngày trên đồ thị.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();

    }

}
void MainWindow::switchMode(int index){
    startTime.setHMS(7, 0, 0);
    endTime.setHMS(7, 0, 0);
    switch (index) {
    case 0:
        chartType = "am";
        iconSize = QSize(250, 70);
        colNames = {"Giờ phút", "Độ ẩm"};
        bubble= {"Giờ phút:", "Độ ẩm:", "ml"};
        ui->showFolder->setGridSize(QSize(250, 100));
        ui->showFolder->setIconSize(iconSize);
        ui->dataView->setHorizontalHeaderLabels(colNames);
        //startTime.setHMS(6, 30, 0);
        timeSpace = 15;
        //endTime.setHMS(8, 30, 0);
        ui->stationBox->clear();
        ui->stationID->clear();
        ui->stationBox->addItems(stationsName);
        ui->stationID->addItems(stationsID);
        days = 1;
        startLevel = 0;
        levelSpace = 2;
        endLevel = 100;
        break;
    case 1:
        chartType = "ap";
        iconSize = QSize(250, 70);
        colNames = {"Giờ phút", "Áp suất"};
        bubble = {"Giờ phút:", "Áp suất:", "mb"};
        ui->showFolder->setGridSize(QSize(250, 100));
        ui->showFolder->setIconSize(iconSize);
        ui->dataView->setHorizontalHeaderLabels(colNames);
        //startTime.setHMS(11, 15, 0);
        timeSpace = 15;
        //endTime.setHMS(13, 15, 0);
        ui->stationBox->clear();
        ui->stationID->clear();
        ui->stationBox->addItems(stationsName);
        ui->stationID->addItems(stationsID);
        days = 1;
        startLevel = 946;
        levelSpace = 1;
        endLevel = 1052;
        break;
    case 2:
        chartType = "mua";
        iconSize = QSize(250, 70);
        colNames = {"Giờ phút", "So với 10 phút trước"};
        bubble = {"Giờ phút:", "Lượng mưa:", "ml"};
        ui->showFolder->setGridSize(QSize(250, 100));
        ui->showFolder->setIconSize(iconSize);
        ui->dataView->setHorizontalHeaderLabels(colNames);
        //startTime.setHMS(7, 20, 0);
        timeSpace = 10;
        //endTime.setHMS(8, 20, 0);
        days = 1;
        ui->stationBox->clear();
        ui->stationID->clear();
        ui->stationBox->addItems(stationsName);
        ui->stationID->addItems(stationsID);
        startLevel = -5;
        levelSpace = 1;
        endLevel = 105;
        break;
    case 3:
        chartType = "nhiet";
        iconSize = QSize(250, 70);
        colNames = {"Giờ phút", "Nhiệt độ"};
        bubble = {"Giờ phút:", "Nhiệt độ:", "°C"};
        ui->showFolder->setGridSize(QSize(250, 100));
        ui->showFolder->setIconSize(iconSize);
        ui->dataView->setHorizontalHeaderLabels(colNames);
        //startTime.setHMS(6, 30, 0);
        timeSpace = 10;
        //endTime.setHMS(8, 10, 0);
        ui->stationBox->clear();
        ui->stationID->clear();
        ui->stationBox->addItems(stationsName);
        ui->stationID->addItems(stationsID);
        days = 1;
        startLevel = -150;
        levelSpace = 10;
        endLevel = 650;
        break;
    case 4:
        chartType = "nuoc";
        iconSize = QSize(250, 350);
        colNames = {"Giờ phút", "Mức nước"};
        bubble = {"Giờ phút:", "Mức nước:", "ml"};
        ui->showFolder->setGridSize(QSize(250, 380));
        ui->showFolder->setIconSize(QSize(iconSize));
        ui->dataView->setHorizontalHeaderLabels(colNames);
        //startTime.setHMS(7, 0, 0);
        timeSpace = 10;
        //endTime.setHMS(7, 0, 0);
        days = 1;
        startLevel = 47190;
        levelSpace = 0.5;
        endLevel = 47390;
        ui->stationBox->clear();
        ui->stationID->clear();
        ui->stationBox->addItems(stationsNameW);
        ui->stationID->addItems(stationsIDW);
//        min10->setText("10 phút");
//        min5->setText("5 phút");

//        numRows = 400;
//        numCols = 144;
        break;
    }
    opened = 0;
    addUp = 0;

    numCols = timeToCols();
    numRows = levelToRows();
    timeLabel->setText(QString("%1: %2->%3+%9h %10 phút(%4) || %5: %6->%7 %11 %13(%8) || %12 %14").arg("Thời gian").arg(startTime.toString("HH:mm")).arg(endTime.toString("HH:mm")).arg(QString::number(numCols))
                       .arg(colNames[1]).arg(QString::number(startLevel)).arg(QString::number(endLevel)).arg(QString::number(numRows)).arg(days*24).arg(timeSpace).arg(levelSpace).arg(addUp).arg(bubble[2]).arg(bias));
}
void MainWindow::openFolder(){
    QString defaultDir = QDir::homePath();
    QSettings lastDir;

    QString Dir = QFileDialog::getExistingDirectory(this, "Chọn thư mục",
                                                           lastDir.value(defaultDir).toString());

    if(!Dir.isEmpty()){
        chosenDir = Dir;
        QDir loadDir(Dir);
        exportDir = Dir.replace("Anh goc", "Thu muc bao cao");
        QDir().mkdir(exportDir);
        exportImgs = Dir.replace("Thu muc bao cao", "Anh da so hoa");
        exportImgs.remove(".jpg");
        QDir().mkdir(Dir);
        ui->showFolder->clear();
        QIcon icon;

        lastDir.setValue(defaultDir, loadDir.path());
        QStringList filter;
        filter<<"*.jpg"<<"*.JPG";
        loadDir.setNameFilters(filter);
        QList<QFileInfo> infoList = loadDir.entryInfoList();
        QProgressDialog loading("Đang mở thư mục", "Dừng mở", 0, infoList.length(), this);
        loading.setWindowModality(Qt::WindowModal);
        int i = 0;
        foreach (const QFileInfo &fileInfo, infoList) {
            loading.setValue(i);
            QString itemName = fileInfo.fileName();
            QString absPath = fileInfo.absoluteFilePath();
            QImageReader *reader = new QImageReader(absPath);
            reader->setScaledSize(iconSize);
            icon = QIcon(QPixmap::fromImageReader(reader));
            QListWidgetItem *item = new QListWidgetItem(icon, itemName);
            ui->showFolder->addItem(item);
            delete reader;
            i++;
            if(loading.wasCanceled()){
                break;
            }
        }
        loading.setValue(infoList.length());
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
void MainWindow::inputDialog(){
    dialog = new Input;

    connect(dialog->done, &QPushButton::clicked, this, &MainWindow::changeSetup);


    dialog->changeSetup(opened, chartType);
    opened = 1;

    dialog->exec();
}


void MainWindow::quitApp(){
    int ret = QMessageBox::question(this, "Thoát", "Bạn có muốn thoát hay không?",
                          QMessageBox::Yes|QMessageBox::No);
    if(ret == QMessageBox::Yes){
        QCoreApplication::quit();
    }
}
QImage MainWindow::cropOnly(QImage input){
    QRect crop;
    crop.setCoords(x_min*ratio, 0, x_max*ratio, sizeHeight);
    input = input.copy(crop);

    return input;
}
QImage MainWindow::RotateAndCrop(QImage input){
    QTransform rotation;
    rotation.rotate(angle);
    input = input.transformed(rotation);
    QRect crop;
    crop.setCoords(x_min*ratio, 0, x_max*ratio, sizeHeight);
    qDebug()<<"x_min is"<<x_min<<"x max is"<<x_max<<"ratio is"<<ratio<<endl;
    input = input.copy(crop);
    qDebug()<<"input width is"<<input.width()<<endl;
    return input;
}

void MainWindow::itemClicked(QListWidgetItem *item){
    itemPath = chosenDir + "\\" + item->text();
    dayCount = 0;
    ui->IDchart->setText(item->text());
    ui->daychart->setText(QString::number(dayCount));
    ui->dataView->clearContents();
    ui->dataView->setRowCount(0);

    if(image.load(itemPath)){
        mask = QImage();
        QString json = itemPath.replace("Anh goc", "json");
        json = json.replace(".jpg", ".json");
        if (chartType == "nuoc"){
            readJson(json);
        }
        else if (chartType == "mua"){
            readJson(json);
        }
        else if (chartType == "am"){
            readJson(json);
        }
        else if (chartType == "ap"){
            readJson(json);
        }
        else if (chartType == "nhiet"){
            readJson(json);
        }
        ratio = 1;
        QSize imgSize = image.size();
        sizeWidth = imgSize.width();
        sizeHeight = imgSize.height();
        gridWidth = sizeWidth/numCols+bias;
        gridHeight = sizeHeight/numRows+bias;
        cropped = false;
        scene->clear();
        scene->installEventFilter(this);
        QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        scene->addItem(it);
        ui->Mask->setScene(scene);
        ui->Mask->fitInView(it, Qt::KeepAspectRatio);
    }
}
void MainWindow::removeTableRows(){
    int row;
    for (QTableWidgetItem *x: ui->dataView->selectedItems()) {
        row = x->row();
        ui->dataView->removeRow(row);
    }
}
void MainWindow::addStringToFile(const QString &name, const QString &id){
    bool isPresent;
    if(chartType == "nuoc"){
        isPresent = stationsNameW.contains(name)&&stationsIDW.contains(id);
        if(!isPresent){
            QMessageBox msgBox;
            msgBox.setText(QString("Bạn có muốn thêm trạm tên %1 với mã %2 không").arg(name).arg(id));
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            int ret = msgBox.exec();
            if(ret == QMessageBox::Ok){
                QFile txtFile(sNPathW);
                QFile idFile(sIPathW);
                if(txtFile.open(QIODevice::Append|QIODevice::WriteOnly)&&idFile.open(QIODevice::Append|QIODevice::WriteOnly)){
                    QTextStream stream(&txtFile);
                    QTextStream streami(&idFile);
                    stream<<"\n"<<name;
                    streami<<"\n"<<id;
                    txtFile.close();
                    idFile.close();
                    stationsNameW = loadTxtToStringList(sNPathW);
                    stationsIDW = loadTxtToStringList(sIPathW);
                    ui->stationBox->clear();
                    ui->stationID->clear();
                    ui->stationBox->addItems(stationsNameW);
                    ui->stationBox->setCurrentIndex(ui->stationBox->count()-1);
                    ui->stationID->addItems(stationsIDW);
                    ui->stationID->setCurrentIndex(ui->stationID->count()-1);
                    qDebug()<<"done"<<endl;
                }
                else{
                    qDebug()<<"fail"<<endl;
                }
            }
        }
    }
    else{
        isPresent = stationsName.contains(name)&&stationsID.contains(id);
        if(!isPresent){
            QMessageBox msgBox;

            msgBox.setText(QString("Bạn có muốn thêm trạm tên %1 với mã %2 không").arg(name).arg(id));
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            int ret = msgBox.exec();
            if(ret == QMessageBox::Ok){
                QFile txtFile(sNPath);
                QFile idFile(sIPath);
                if(txtFile.open(QIODevice::Append|QIODevice::WriteOnly)&&idFile.open(QIODevice::Append|QIODevice::WriteOnly)){
                    QTextStream stream(&txtFile);
                    QTextStream streami(&idFile);
                    stream<<"\n"<<name;
                    streami<<"\n"<<id;
                    txtFile.close();
                    idFile.close();
                    stationsName = loadTxtToStringList(sNPath);
                    stationsID = loadTxtToStringList(sIPath);
                    ui->stationBox->clear();
                    ui->stationID->clear();
                    ui->stationBox->addItems(stationsName);
                    ui->stationBox->setCurrentIndex(ui->stationBox->count()-1);
                    ui->stationID->addItems(stationsID);
                    ui->stationID->setCurrentIndex(ui->stationID->count()-1);
                    qDebug()<<"done"<<endl;
                }
                else{
                    qDebug()<<"fail"<<endl;
                }
            }
        }
    }
}
void MainWindow::enableRotateandCrop(){
    image = RotateAndCrop(image);
    QPainter painter(&image);
    QPen pen;
    pen.setWidth(0.0015 * (y_max - y_min));
    pen.setColor(Qt::blue);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    painter.drawLine(0, y_min, x_max, y_min);
    painter.drawLine(0, y_max, x_max, y_max);
    painter.end();
    gridWidth = (x_max-x_min)*ratio/numCols + bias;
    gridHeight = (y_max-y_min)*ratio/numRows;
    cropped = true;
    scene->clear();
    scene->installEventFilter(this);
    QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(it);
    ui->Mask->setScene(scene);
    ui->Mask->fitInView(it, Qt::KeepAspectRatio);
}
void MainWindow::cropGridToggled(bool enabled){
     ui->Mask->grid = enabled;
    if(ui->actionZoom->isChecked()){
        ui->Mask->zoomEnabled = !enabled;

        ui->actionZoom->setChecked(!enabled);
    }
}
void MainWindow::zoomToggled(bool enabled){
    ui->Mask->zoomEnabled = enabled;

    if(ui->actionCutGrid->isChecked()){
        ui->Mask->grid = !enabled;
        ui->actionCutGrid->setChecked(!enabled);
    }
//    if(enabled){
//        ui->Mask->setCursor(Qt::CrossCursor);
//    }
//    else {
//        ui->Mask->setCursor(Qt::ArrowCursor);
//    }
}
void MainWindow::drawToggled(bool enabled){
    ui->Mask->drawEnabled = enabled;
}

