#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "convert.h"
#include "somefuntions.h"
#include <numeric>
#include <QList>
/**
 * @brief MainWindow::MainWindow
 * @param parent: parent widget
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //! Preparing widgets 
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
    modeBox->setItemIcon(0, QIcon(":/icon/icons/humidity.png"));
    modeBox->setItemIcon(1, QIcon(":/icon/icons/pressure.png"));
    modeBox->setItemIcon(2, QIcon(":/icon/icons/rain.png"));
    modeBox->setItemIcon(3, QIcon(":/icon/icons/temperature.png"));
    modeBox->setItemIcon(4, QIcon(":/icon/icons/water.png"));

    modeLabel->setText(boxName);

    ui->Mask->setMouseTracking(true);
    ui->showFolder->verticalScrollBar()->setSingleStep(8);
    ui->toolBar->addWidget(modeLabel);
    ui->toolBar->addWidget(modeBox);

    //! Adding these to the toolbar
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(timeLabel);
    ui->toolBar->addWidget(spacer);
    ui->toolBar->addWidget(icon1);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(icon2);
    installEventFilter(this);
    //! Creating list of stations
    stationsName = loadTxtToStringList(sNPath);
    stationsID = loadTxtToStringList(sIPath);
    // Water charts have their own sations
    stationsNameW = loadTxtToStringList(sNPathW);
    stationsIDW = loadTxtToStringList(sIPathW);

    //! Connecting necessary components 
    // Connect actions from MW to the Graphics View
    connect(ui->actionZoom, &QAction::triggered, ui->Mask, &MyGraphicsView::enableZoom);
    connect(ui->actionZoom, &QAction::triggered,
            [=](bool triggered){statusMessage(triggered, "Zoom to nhỏ bằng con lăn chuột.");});

    connect(ui->actionMarking, &QAction::triggered, ui->Mask, &MyGraphicsView::enablePickPoints);
    connect(ui->actionMarking, &QAction::triggered,
            [=](bool triggered){statusMessage(triggered, "Đánh dấu 3 điểm mà parabol đi qua.");});

    connect(ui->actionCutGrid, &QAction::triggered, ui->Mask, &MyGraphicsView::enableCutGrid);
    connect(ui->actionCutGrid, &QAction::triggered,
            [=](bool triggered){statusMessage(triggered, "Đánh dấu 2 điểm trái trên và phải dưới để khoanh vùng đồ thị.");});

    connect(ui->actionlimitLine, &QAction::triggered, ui->Mask, &MyGraphicsView::enableLimitLine);
    connect(ui->actionlimitLine, &QAction::triggered,
            [=](bool triggered){statusMessage(triggered, "Đánh dấu 2 điểm đầu cuối của đường line để giới hạn khoảng tính toán.");});

    connect(ui->actionDraw, &QAction::triggered, ui->Mask, &MyGraphicsView::enableDraw);
    connect(ui->actionDraw, &QAction::triggered, this, &MainWindow::createMask);
    connect(ui->actionDraw, &QAction::triggered,
            [=](bool triggered){statusMessage(triggered, "Vẽ đường đặc tính cho biểu đồ.");});

    // Opening a folder
    connect(ui->actionOpenFolder, &QAction::triggered, this, &MainWindow::openFolder);

    connect(ui->showFolder, &QListWidget::itemClicked, this, &MainWindow::itemClicked);
    connect(ui->save, &QPushButton::clicked, this, &MainWindow::saveToTxt);

    connect(ui->digitalize, &QPushButton::clicked, this, &MainWindow::exportNow);
    connect(ui->actionPicking_Points, &QAction::triggered, ui->Mask, &MyGraphicsView::addReportedPoint);
    connect(ui->actionPicking_Points, &QAction::triggered, ui->statusBar,
            [=](){ui->statusBar->showMessage("Chọn thêm điểm trên đồ thị");});

    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::quitApp);
    connect(ui->nextDay, &QPushButton::clicked, this, &MainWindow::nextDay);
    connect(ui->prevDay, &QPushButton::clicked, this, &MainWindow::prevDay);
    connect(ui->actionSetting, &QAction::triggered, this, &MainWindow::inputDialog);
    connect(modeBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index){ switchMode(index); });
    connect(ui->stationBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index){ NameToID(index); });
    connect(ui->stationID, QOverload<int>::of(&QComboBox::currentIndexChanged),
                    [=](int index){ IDToName(index); });
    connect(ui->actionRotate, &QAction::triggered, this, &MainWindow::rotForward);
    connect(ui->actionRotateBack, &QAction::triggered, this, &MainWindow::rotBackward);

    connect(ui->change, &QPushButton::clicked, this, &MainWindow::changeTable);
    connect(ui->Mask, &MyGraphicsView::passPoint, this, &MainWindow::receivePoint);
    connect(ui->Mask, &MyGraphicsView::passAddingPoint, this, &MainWindow::addingRpPoint);
    connect(ui->Mask, &MyGraphicsView::passRectPoint, this, &MainWindow::addingRectPoint);
    connect(ui->Mask, &MyGraphicsView::passLimitPoint, this, &MainWindow::changeStartEndPoint);
    connect(ui->Mask, &MyGraphicsView::passDrewPoints, this, &MainWindow::addToMask);
    switchMode(0);
    opened = 0;


}
void MainWindow::statusMessage(bool is_on, const QString& message){
    if(is_on){
        ui->statusBar->showMessage(message);
    }
    else{
        ui->statusBar->showMessage("");
    }
}
void MainWindow::createMask(bool is_on){
    if(is_on){
        mask = QImage(image.width(), image.height(), image.format());
        mask.fill(Qt::black);
        showImage(image);
    }
//    else{
//        QImage resImage = createImageWithOverlay(image, mask);
//        showImage(mask);
//    }
}

void MainWindow::addToMask(const QVector<QPoint>& pointsVec){
    QPainter painter(&mask);
    painter.setPen(QPen(Qt::white, 1));
    for(int i = 1; i<pointsVec.size(); i++){
        painter.drawLine(pointsVec[i-1], pointsVec[i]);
    }
    painter.end();
}

void MainWindow::changeTable(){
    int timeUD = ui->timeUD->value();
    int valUD = ui->levelUD->value();
    QTableWidgetItem *itemTime;
    QTableWidgetItem *itemLevel;
    QTime t;
    int val;
    for(int i = 0; i<ui->dataView->rowCount(); i++){
        itemTime = ui->dataView->item(i, 0);
        itemLevel = ui->dataView->item(i, 1);
        t = QTime::fromString(itemTime->text(), "hh:mm");

        val = itemLevel->text().toInt();
        t = t.addSecs(60*timeUD);

        val += valUD;
        itemTime->setText(t.toString("hh:mm"));
        itemLevel->setText(QString::number(val));
    }

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
    textFile.close();
    return list;
}
void MainWindow::addingRectPoint(QPointF point){
    rectPoints.append(point);
    if(rectPoints.size() == 2){
        getNewVariables(rectPoints[0].x(),rectPoints[0].y(),
                        rectPoints[1].x()-rectPoints[0].x(),
                        rectPoints[1].y()-rectPoints[0].y());
        rectPoints = {};

    }
}


void MainWindow::changeStartEndPoint(QPointF point){
    limitPoints.append(point);
    if(limitPoints.size() == 2){
        x_mincut = limitPoints[0].x();
        x_maxcut = limitPoints[1].x();
        limitPoints = {};
        QMessageBox msgBox;
        msgBox.setText("Đã điều chỉnh được điểm bắt đầu và kết thúc của đường line.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
        getNewStartEnd = true;
        ui->actionlimitLine->trigger();
    }
}


void MainWindow::getNewVariables(int xmin, int ymin, int w, int h){
    x_minc = xmin;
    x_maxc = xmin+w;
    y_min = ymin;
    y_max = ymin+h;
    ui->actionCutGrid->trigger();
    QMessageBox msgBox;
    autoCropped = true;
    msgBox.setText("Đã khoanh vùng đồ thị.");
    msgBox.setIcon(QMessageBox::Information);
    int ret = msgBox.exec();
    if(ret != 0){
        image = cropping(image, xmin, ymin, w, h, true);
        if(!mask.isNull()){
            mask = cropping(mask, xmin, ymin, w, h, false);
            QImage resultImg = createImageWithOverlay(image, mask);
            showImage(resultImg);
        }
        else{
            showImage(image);
        }

    }
}

void MainWindow::calculateParabolafrom3points(QPointF p1, QPointF p2, QPointF p3){
    double x1 = p1.x();
    double x2 = p2.x();
    double x3 = p3.x();
    double y1 = p1.y();
    double y2 = p2.y();
    double y3 = p3.y();
    double denom = (x1 - x2)*(x1 - x3)*(x2 - x3);
    aPara = (x3 * (y2 - y1) + x2 * (y1 - y3) + x1 * (y3 - y2))/denom;
    bPara = (qPow(x3, 2) * (y1 - y2) + qPow(x2, 2) * (y3 - y1) + qPow(x1, 2) * (y2 - y3))/denom;
}

void MainWindow::receivePoint(QPointF point){
    neededPoints.append(point);
    if(neededPoints.size() == 3){
       ui->actionMarking->trigger();
       calculateParabol(neededPoints);
       neededPoints = {};
       QMessageBox msgBox;
       msgBox.setText("Bạn đã chọn xong 3 điểm quan trọng của parabol");
       msgBox.exec();
       ui->statusBar->showMessage("Đã khởi tạo tham số của parabol, có thể tạo báo cáo hoặc tiếp tục chỉnh sửa.");
    }

}
void MainWindow::addingRpPoint(QPointF point){

//    int xLineWidth = qAbs(x_max - x_min);
//    int blockWidthPx = xLineWidth/numCols;
//    int blockHeightPx = gridHeight/numRows;
//    int rpPointX;
//    int rpPointY;
//    if(chartType == 4|| chartType == 2){
//        rpPointX = (point.x()-x_min)*timeExtract*60/blockWidthPx;
//        rpPointY = (gridHeight - (point.y()-y_min))*levelExtract/blockHeightPx;
//    }
//    else{
//        int c = point.x()-aPara*qPow(point.y(), 2)-bPara*point.y();
//        int xPara = aPara*qPow(y_min, 2)+bPara*y_min+c;
//        rpPointX = ((xPara-x_min)*timeExtract*60)/blockWidthPx;
//        rpPointY = (gridHeight - (point.y() - y_min))*levelExtract/blockHeightPx;
//    }

//    QTime rpTime;
//    if(chartType!=2){
//        rpTime = startTime.addSecs(rpPointX);
//        rpTime = rpTime.addSecs(timeUD*60);
//        QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(rpTime.toString("HH:mm")));
//        QTableWidgetItem *item2 = new QTableWidgetItem(QString("%1").arg(QString::number(rpPointY+startLevel+valUD)));
//        ui->dataView->insertRow(ui->dataView->rowCount());
//        ui->dataView->setItem(ui->dataView->rowCount() - 1, 0, item);
//        ui->dataView->setItem(ui->dataView->rowCount() - 1, 1, item2);
//    }
//    else {
//        rpTime = startTime.addSecs(rpPointX);
//        rpTime = rpTime.addSecs(timeUD*60);
//        QTableWidgetItem *itembf = ui->dataView->item(ui->dataView->rowCount() - 1, 1);
//        int levelDiff = rpPointY - itembf->text().toInt();
//        QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(rpTime.toString("HH:mm")));
//        QTableWidgetItem *item2 = new QTableWidgetItem(QString("%1").arg(QString::number(levelDiff)));
//        ui->dataView->insertRow(ui->dataView->rowCount());
//        ui->dataView->setItem(ui->dataView->rowCount() - 1, 0, item);
//        ui->dataView->setItem(ui->dataView->rowCount() - 1, 1, item2);
//    }
}
void MainWindow::calculateParabol(QVector<QPointF> pointsVt){
    //Check size
    if(pointsVt.size() != 3){
        return;
    }
    // Top parabol, mid parabol, bot para
    gridHeight = qAbs(pointsVt[2].y() - pointsVt[0].y());
    // image = image.copy(QRect(0, pointsVt[0].y(), image.width(), gridHeight)
    y_min = pointsVt[0].y();
    y_max = pointsVt[2].y();
    calculateParabolafrom3points(QPointF(pointsVt[0].y(), pointsVt[0].x()),
                                 QPointF(pointsVt[1].y(), pointsVt[1].x()),
                                 QPointF(pointsVt[2].y(), pointsVt[2].x()));
}

int MainWindow::timeToCols(QTime startTime, double timeExtractinMin, QTime endTime, int days){
    int diff = startTime.secsTo(endTime) + 86400*days;
    int numcols = diff/(timeExtractinMin*60);
    return numcols;
}

int MainWindow::levelToRows(int startLevel, double levelExtract, int endLevel){
    double diff = endLevel - startLevel;
    int numrows = diff/levelExtract;
    return numrows;
}

void MainWindow::changeParams(QTime start_time, int time_extract, QTime end_time,
                              double start_level, double level_extract, double end_level,
                              int day){
    startTime = start_time;
    timeExtract = time_extract;
    endTime = end_time;
    startLevel = start_level;
    levelExtract = level_extract;
    endLevel = end_level;
    days = day;
    qDebug()<<startTime<<timeExtract<<endTime<<startLevel<<levelExtract<<endLevel<<days;
    numCols = timeToCols(startTime, timeExtract, endTime, days);
    numRows = levelToRows(startLevel, levelExtract, endLevel);
    qDebug()<<"New params"<<numCols<<numRows;

    timeLabel->setText(QString("%1: %2->%3+%9h %10 phút(%4) || %5: %6->%7 %11 %12(%8)").
                       arg("Thời gian"). //1
                       arg(startTime.toString("HH:mm")). //2
                       arg(endTime.toString("HH:mm")). //3
                       arg(QString::number(numCols)).//4
                       arg(colNames[1]).//5
                       arg(QString::number(startLevel)).//6
                       arg(QString::number(endLevel)).//7
                       arg(QString::number(numRows)).//8
                       arg(days*24). //9
                       arg(timeExtract).//10
                       arg(levelExtract).//11
//                       arg(addUp).//12
                       arg(bubble[2]));//12
//                       arg(bias));//14

}
void MainWindow::saveToTxt(){
    QString exportFile = exportDir+"/"+ui->IDchart->text()+"_"+ui->daychart->text()+".csv";
    QFile f(exportFile);
    exportFile = exportImgs+"/"+ui->IDchart->text()+"_"+ui->daychart->text()+".jpg";

    if (f.open(QFile::WriteOnly | QFile::Truncate) && !image.isNull())
    {
        QTextStream stream(&f);
        stream.setCodec("UTF-8");
        QString conTent;
        QHeaderView * header = ui->dataView->horizontalHeader() ;
        if (header)
        {
            conTent += "Mã trạm, Tên trạm, Ngày tháng,";
            for ( int i = 0; i < header->count(); i++ )
            {
                QTableWidgetItem *item = ui->dataView->horizontalHeaderItem(i);
//                QTableWidgetItem *item{ui->dataView->horizontalHeaderItem(i)};
                if (!item)
                {
                    continue;
                }
                conTent += item->text()+ ",";
            }
            conTent += "\n";
        }

        for ( int i = 0 ; i < ui->dataView->rowCount(); i++ )
        {
            conTent += ui->stationID->currentText()+ ","+ ui->stationBox->currentText()+ "," + ui->daychart->text() + ",";
            for ( int j = 0; j < ui->dataView->columnCount(); j++ )
            {
                QTableWidgetItem* item = ui->dataView->item(i, j);
                if ( !item )
                    continue;
                QString str = item->text();
                str.replace(","," ");
                conTent += str + ",";
            }
            conTent += "\n";
        }
        stream << conTent;
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


int MainWindow::detectRainOver(int x, int y, int w, int h){
    int overFlow;
    QRect cropRectRain(x, y, w, h);
    cropMaskRain = mask.copy(cropRectRain);
    cropRain = cvert::QImageToCvMat(cropMaskRain);
//    cv::imshow("Pos x:"+std::to_string(x), cropRain);
    if(cropRain.channels()>1){
        cv::cvtColor(cropRain, cropRain, cv::COLOR_RGB2GRAY);
    }

    cv::threshold(cropRain, cropRain, 10, 255, cv::THRESH_BINARY);
    cv::findContours(cropRain, contours, cv::noArray(),
                     cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    overFlow = contours.size();
    overFlow = 100*overFlow;

    return overFlow;

}
void MainWindow::exportNow(){
    if(!mask.isNull()){ 
        extractDataFromLine(mask);

    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Bạn chưa vẽ đường đồ thị");
        msgBox.exec();
    }
}



/**
 * @brief MainWindow::extractDataFromLine: Extracting value from the mask with the given minute
 * @param inputMask: the input mask which contains the line
 * @param totalTime: the total time that the line stretch
 * @param cutMinutes: given minutes to extract(eg. 15, 60)
 * TODO: Need to review
 */
bool point_smaller_x(const cv::Point &p1, const cv::Point &p2){
    return p1.x < p2.x;
}
bool MainWindow::isWithin(cv::Point p){
    return x_mincut<p.x<x_maxcut;
}

QImage MainWindow::performDilation(const QImage& input){
    cv::Mat maskcv = cvert::QImageToCvMat(input);
//    cv::Mat maskcv = QImage2Mat(input);
    qDebug()<<maskcv.type()<<"\n";
    if(maskcv.channels()!=1){
        cv::cvtColor(maskcv, maskcv, cv::COLOR_RGB2GRAY);
    }
    cv::Mat outputmask;
    qDebug()<<"2"<<"\n";
    int k_size = input.width()*25/13900;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT,
                                                cv::Size(k_size, k_size));
    qDebug()<<"3"<<"\n";
    cv::threshold(maskcv, maskcv, 10, 255, cv::THRESH_BINARY);
    cv::dilate(maskcv, outputmask, element);
    QImage res = cvert::MatToQImage(outputmask);
    qDebug()<<"5"<<"\n";
    return res;
}
std::vector<cv::Point> findLineinQImage(const QImage& inputImg){
    std::vector<cv::Point> locations;
    cv::Mat maskcv = cvert::QImageToCvMat(inputImg);
    if(maskcv.channels()!=1){
        cv::cvtColor(maskcv, maskcv, cv::COLOR_RGB2GRAY);
    }
    cv::findNonZero(maskcv, locations);
    return locations;
}
void MainWindow::extractDataFromLine(const QImage& inputMask){

    locations = findLineinQImage(inputMask);
    int x_minl, y_minl, x_maxl;
    qDebug()<<"Size bf:"<<locations.size()<<"\n";
    if (getNewStartEnd){
        int index;
        int x_min = x_mincut;
        int x_max = x_maxcut;
        std::vector<cv::Point>::iterator itm;
        itm = std::find_if(locations.begin(), locations.end(), [x_min](const cv::Point p){return p.x==x_min;});
        if (itm == locations.end()){
            auto mmx = std::minmax_element(locations.begin(), locations.end(), point_smaller_x);
            x_minl = mmx.first->x;
            y_minl = mmx.first->y;
            x_maxl = mmx.second->x;
        }
        else{
            index = itm - locations.begin();
            x_minl = locations[index].x;
            y_minl = locations[index].y;
            itm = std::find_if(locations.begin(), locations.end(), [x_max](const cv::Point p){return p.x==x_max;});
            index = itm - locations.begin();
            x_maxl = locations[index].x;

        }

//        locations.erase(std::remove_if(locations.begin(), locations.end(),
//                                       [x_min, x_max](const cv::Point& p){return x_min<p.x&&p.x<x_max;}),
//                                       locations.end());
//        qDebug()<<"Size at:"<<locations.size()<<"\n";
    }
    else{
        auto mmx = std::minmax_element(locations.begin(), locations.end(), point_smaller_x);
        x_minl = mmx.first->x;
        y_minl = mmx.first->y;
        x_maxl = mmx.second->x;
    }
    int xLineWidth = qAbs(x_maxl - x_minl);
    int blockWidthPx = xLineWidth/numCols;
    int blockHeightPx = gridHeight/numRows;


    std::vector<int> extractedPointAtX;
    std::vector<int> extractedPointAtY;
    std::vector<int> sortedPointAtX;
    std::vector<int> sortedPointAtY;
    std::vector<size_t> sortedIndexes;
    std::vector<int> copiedExtractedX;
    int j = 0;
    int value = 0;
    std::vector<int>::iterator it;
    std::vector<int> indexFound;
    std::vector<int> missingIndexes;
    if(chartType == 4 || chartType == 2){
        std::vector<int> locationsX;
        for (cv::Point p: locations) {
            locationsX.push_back(p.x);
        }

        while(value<x_maxl){
            value = x_minl + blockWidthPx * j;
            qDebug()<<value<<"\n";
            it = std::find(locationsX.begin(), locationsX.end(), value);
            if (it != locationsX.end()){
                indexFound.push_back(it - locationsX.begin());
            }
            j++;
        }
        for (int i:indexFound) {
            extractedPointAtX.push_back(locations[i].x);
            extractedPointAtY.push_back(locations[i].y);
        }

//        qDebug()<<extractedPointAtX<<extractedPointAtY<<"\n";
        sortedIndexes = sort_indexes(extractedPointAtX);
        for(int i:sortedIndexes){
            sortedPointAtX.push_back(extractedPointAtX[i]);
            sortedPointAtY.push_back(extractedPointAtY[i]);
        }
//        qDebug()<<sortedPointAtX<<sortedPointAtY<<"\n";
        copiedExtractedX = sortedPointAtX;
        sortedPointAtX.erase(std::unique(sortedPointAtX.begin(), sortedPointAtX.end()), sortedPointAtX.end());
        sortedPointAtY = removeDuplicate(sortedPointAtX, copiedExtractedX, sortedPointAtY);
//        qDebug()<<sortedPointAtX<<sortedPointAtY<<"\n";
        image = drawPointDebug(image, sortedPointAtX, sortedPointAtY, Qt::green, 50);
//        std::vector<int> vec_ymin(sortedPointAtX.size(), y_min);
//        image = drawRectDebug(image, sortedPointAtX, vec_ymin, Qt::red, blockHeightPx*12);
        showImage(image);

        missingIndexes = getMissingIndex(sortedPointAtX, blockWidthPx);
        //!Converting to time and level
        for (int i = 0; i < sortedPointAtX.size(); i++) {
            sortedPointAtX[i] = (sortedPointAtX[i]-x_minl)*timeExtract*60/blockWidthPx;
            sortedPointAtY[i] = (gridHeight - (sortedPointAtY[i]-y_min))*levelExtract/blockHeightPx;
        }
    }
    else{
        // Converting time element
        std::vector<int> parabolX;
        std::vector<int> parabolXN;
        std::vector<int> parabolXSort;
        double c;
        for (int i = 0; i<locations.size(); i++) {
            c = locations[i].x-aPara*qPow(locations[i].y, 2)-bPara*locations[i].y;
            parabolX.push_back(aPara*qPow(y_min, 2)+bPara*y_min+c);
        }
        c = x_minl-aPara*qPow(y_minl, 2)-bPara*y_minl;
        int cmin = aPara*qPow(y_min, 2)+bPara*y_min+c;

        while(value<x_maxl){
            value = cmin + blockWidthPx * j;
            it = std::find(parabolX.begin(), parabolX.end(), value);
            if (it != parabolX.end()){
                indexFound.push_back(it - parabolX.begin());
            }
            j++;
        }
        for (int i : indexFound) {
            parabolXN.push_back(parabolX[i]);
            extractedPointAtX.push_back(locations[i].x);
            extractedPointAtY.push_back(locations[i].y);
        }


        sortedIndexes = sort_indexes(parabolXN);

        for(int i:sortedIndexes){
            parabolXSort.push_back(parabolXN[i]);
            sortedPointAtX.push_back(extractedPointAtX[i]);
            sortedPointAtY.push_back(extractedPointAtY[i]);
        }

        std::vector<int> parabolXSortRaw = parabolXSort;
        parabolXSort.erase(std::unique(parabolXSort.begin(), parabolXSort.end()), parabolXSort.end());
        sortedPointAtX = removeDuplicate(parabolXSort, parabolXSortRaw, sortedPointAtX);
        sortedPointAtY = removeDuplicate(parabolXSort, parabolXSortRaw, sortedPointAtY);


        std::vector<int> val(parabolXSort.size(), y_min);
        image = drawPointDebug(image, sortedPointAtX, sortedPointAtY, Qt::green, 50);
//        image = drawPointDebug(image, parabolXSort, val, Qt::black, gridHeight, 50);

//        parabolXSort.erase(parabolXSort.begin()+4);
//        sortedPointAtY.erase(sortedPointAtY.begin()+4);
//        sortedPointAtX.erase(sortedPointAtX.begin()+4);

        showImage(image);
        missingIndexes = getMissingIndex(parabolXSort, blockWidthPx);

        for (int i = 0; i < parabolXSort.size(); i++) {
            sortedPointAtX[i] = ((parabolXSort[i]-x_minl)*timeExtract*60)/blockWidthPx;
            sortedPointAtY[i] = (gridHeight - (sortedPointAtY[i] - y_min))*levelExtract/blockHeightPx;
        }

    }

    QTime rptime;
    //! Writing those data to the table
    ui->dataView->clearContents();
    ui->dataView->setRowCount(0);
    if(chartType != 2){
        for (int i = 0; i < sortedPointAtX.size(); i++) {
            rptime = startTime.addSecs(sortedPointAtX[i]);
            QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(rptime.toString("HH:mm")));
            QTableWidgetItem *item2 = new QTableWidgetItem(QString("%1").arg(QString::number(sortedPointAtY[i]+startLevel)));
            ui->dataView->insertRow(ui->dataView->rowCount());
            ui->dataView->setItem(ui->dataView->rowCount() - 1, 0, item);
            ui->dataView->setItem(ui->dataView->rowCount() - 1, 1, item2);
        }
    }
    else {
        int prevPoint;
        int currPoint;
        int diff;
        int overflow;
        for (int i = 1; i < sortedPointAtX.size(); i++) {
            rptime = startTime.addSecs(sortedPointAtX[i]);
            currPoint = sortedPointAtY[i];
            prevPoint = sortedPointAtY[i - 1];
            diff = currPoint - prevPoint;
            //! convert back to detect
            overflow = detectRainOver((sortedPointAtX[i-1]*blockWidthPx/(timeExtract*60))+x_minl,
                                       y_min,
                                       blockWidthPx,
                                       blockHeightPx*12);
            diff = diff + overflow;
            diff = qMax(diff, 0);
            QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(rptime.toString("HH:mm")));
            QTableWidgetItem *item2 = new QTableWidgetItem(QString("%1").arg(QString::number(diff)));
            ui->dataView->insertRow(ui->dataView->rowCount());
            ui->dataView->setItem(ui->dataView->rowCount() - 1, 0, item);
            ui->dataView->setItem(ui->dataView->rowCount() - 1, 1, item2);
        }
    }
    //! insert missing index
    for(int i:missingIndexes){
        ui->dataView->insertRow(i);
        QTableWidgetItem *itembf = ui->dataView->item(i-1, 0);
        QTime t = QTime::fromString(itembf->text(), "hh:mm");
        t = t.addSecs(timeExtract*60);
        QTableWidgetItem *newitem = new QTableWidgetItem(t.toString("hh:mm"));

        ui->dataView->setItem(i, 0, newitem);
    }
}



void MainWindow::showImage(const QImage &inputImage){
    scene->clear();
//    scene->installEventFilter(this);
//    QGraphicsPixmapItem *it = new QGraphicsPixmapItem(QPixmap::fromImage(inputImage));
    scene->addPixmap(QPixmap::fromImage(inputImage));
    scene->setSceneRect(0, 0, inputImage.width(), inputImage.height());
    ui->Mask->setScene(scene);
    ui->Mask->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
//    ui->Mask->centerOn(it);
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

//    if(doc.isNull()){
//        qDebug()<<"Parse failed"<<endl;
//    }
    QJsonObject jsonObj = doc.object();
//    if(jsonObj.isEmpty()){
//        qDebug()<<"Json object is empty"<<endl;
//    }
    QVariantMap jsonMap = jsonObj.toVariantMap();
    angle = jsonMap["angle"].toDouble();
    if(angle<0){
        angle = -angle;
    }
    x_minc = jsonMap["x_min"].toInt();
    y_min = jsonMap["y_min"].toInt();
    x_maxc = jsonMap["x_max"].toInt();
    y_max = jsonMap["y_max"].toInt();
    column = jsonMap["column"].toInt();
    cos = qCos(angle);
    sin = qSin(angle);
}
bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
//    if (event->type() ==  QEvent::GraphicsSceneMouseMove ) {
//       QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
//       QPointF img_coord_pt = mouseEvent->scenePos();
//       double x = img_coord_pt.x();
//       double y = img_coord_pt.y();
//       pointToValue(x, y);
//       ui->Mask->toolTip();
//       ui->Mask->setToolTip(QString("%1 %2\n%3 %4").arg(bubble[1]).arg(pixelLitter).arg(bubble[0]).arg(time.toString("HH:mm")));
//       return true;
//     }
    if(event->type() == QEvent::KeyPress){
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
    dayCount++;
    ui->daychart->setText(QString::number(dayCount));
    ui->dataView->clearContents();
    ui->dataView->setRowCount(0);
    QString maskPath;
    maskPath = itemPath.replace(jsonFolder, lineFolder);
    maskPath.insert(maskPath.size() - 4, QString("_%1").arg(QString::number(dayCount)));
    maskPath.replace(".jpg", ".png");
    mask.load(maskPath);
    if(!mask.isNull()){
        mask = rotating(mask, totalAngle);
        if(autoCropped){
            mask = cropping(mask, x_minc, y_min, x_maxc-x_minc, y_max-y_min, false);
        }
        QImage maskDilate = performDilation(mask);
        QImage resultImg = createImageWithOverlay(image, maskDilate);
        scene->clear();
        showImage(resultImg);
        ui->statusBar->showMessage("Ngày thứ "+QString::number(dayCount)+" của đồ thị.");
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Đã hết ngày trên đồ thị.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
        dayCount--;
    }

}
void MainWindow::prevDay(){
    dayCount--;
    ui->daychart->setText(QString::number(dayCount));
    ui->dataView->clearContents();
    ui->dataView->setRowCount(0);
    QString maskPath;
    maskPath = itemPath.replace(jsonFolder, lineFolder);
    maskPath.insert(maskPath.size() - 4, QString("_%1").arg(QString::number(dayCount)));
    maskPath.replace(".jpg", ".png");
    mask.load(maskPath);
    if(!mask.isNull()){
        mask = rotating(mask, totalAngle);
        if(autoCropped){
            mask = cropping(mask, x_minc, y_min, x_maxc-x_minc, y_max-y_min, false);
        }
        QImage maskDilate = performDilation(mask);
        QImage resultImg = createImageWithOverlay(image, maskDilate);
        showImage(resultImg);
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Đã hết ngày trên đồ thị.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
        dayCount++;
    }

}
void MainWindow::switchMode(int index){
    opened = 0;
    iconSize = QSize(250, 70);
    gridSize = QSize(250, 100);
    ui->showFolder->setGridSize(gridSize);
    ui->showFolder->setIconSize(iconSize);
    ui->stationBox->clear();
    ui->stationID->clear();
    ui->stationBox->addItems(stationsName);
    ui->stationID->addItems(stationsID);    
    switch (index) {
    case 0:
        colNames = {"Giờ phút", "Độ ẩm"};
        bubble= {"Giờ phút:", "Độ ẩm:", "ml"};
        
        

        days = 1;
        startLevel = 0;
        levelExtract = 2;
        endLevel = 100;
        break;
    case 1:
        
        colNames = {"Giờ phút", "Áp suất"};
        bubble = {"Giờ phút:", "Áp suất:", "mb"};
        

        days = 1;
        startLevel = 946;
        levelExtract = 1;
        endLevel = 1052;
        break;
    case 2:
        
        colNames = {"Giờ phút", "Chênh lệch mưa"};
        bubble = {"Giờ phút:", "Lượng mưa:", "ml"};
    

        
        days = 1;
        startLevel = -5;
        levelExtract = 1;
        endLevel = 105;
        break;
    case 3:
        
        colNames = {"Giờ phút", "Nhiệt độ"};
        bubble = {"Giờ phút:", "Nhiệt độ:", "°C"};
     

        days = 1;
        startLevel = -150;
        levelExtract = 10;
        endLevel = 650;
        break;
    case 4:

        iconSize = QSize(250, 350);
        gridSize = QSize(250, 380);
        colNames = {"Giờ phút", "Mức nước"};
        bubble = {"Giờ phút:", "Mức nước:", "ml"};
        ui->showFolder->setIconSize(iconSize);
        ui->showFolder->setGridSize(gridSize);
        ui->stationBox->clear();
        ui->stationID->clear();
        ui->stationBox->addItems(stationsNameW);
        ui->stationID->addItems(stationsIDW);

        days = 1;
        startLevel = 47190;
        levelExtract = 0.5;
        endLevel = 47390;
        break;
    }
    timeExtract = 60;
    ui->dataView->setHorizontalHeaderLabels(colNames);
    startTime.setHMS(7, 0, 0);
    endTime.setHMS(7, 0, 0);
    numCols = timeToCols(startTime, timeExtract, endTime, days);
    numRows = levelToRows(startLevel, levelExtract, endLevel);
    chartType = index;
    opened = 0;
    timeLabel->setText(QString("%1: %2->%3+%9h %10 phút(%4) || %5: %6->%7 %11 %12(%8)").
                       arg("Thời gian").
                       arg(startTime.toString("HH:mm")).
                       arg(endTime.toString("HH:mm")).
                       arg(QString::number(numCols)).
                       arg(colNames[1]).
                       arg(QString::number(startLevel)).
                       arg(QString::number(endLevel)).
                       arg(QString::number(numRows)).
                       arg(days*24).
                       arg(timeExtract).
                       arg(levelExtract).
//                       arg(addUp).
                       arg(bubble[2]));
//                       arg(bias));
    ui->statusBar->showMessage("Đang chọn tham số tính toán của "+colNames[1]+", điều chỉnh trước khi chọn thư mục");
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
        ui->statusBar->showMessage("Đã chọn xong thư mục, nhấn vào 1 ảnh để thao tác.");
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
    Input *dialog = new Input(this, chartType, opened);
    opened = 1;
    connect(dialog, &Input::passParams, this, &MainWindow::changeParams);
    dialog->exec();
}


void MainWindow::quitApp(){
    int ret = QMessageBox::question(this, "Thoát", "Bạn có muốn thoát hay không?",
                          QMessageBox::Yes|QMessageBox::No);
    if(ret == QMessageBox::Yes){
        QCoreApplication::quit();
    }
}
QImage MainWindow::cropping(QImage input, int x1, int y1, int w, int h, bool draw){
    if(chartType == 4){
        QRect crop(x1, y1, w, h);
        input = input.copy(crop);
    }
    else{
        QRect crop(x1, 0, w, input.height());
        input = input.copy(crop);
        if(draw){
            QPainter painter(&input);
            painter.setPen(QPen(QBrush(Qt::blue), 5));
            painter.drawLine(0, y1, input.width(), y1);
            painter.drawLine(0, y1+h, input.width(), y1+h);
        }
    }
    return input;
}
QImage MainWindow::rotating(QImage input, double angleinp){
    totalAngle += angleinp;
    QTransform rotation;
    rotation.rotate(angleinp);
    input = input.transformed(rotation,Qt::SmoothTransformation);
    return input;
}

void MainWindow::itemClicked(QListWidgetItem *item){
    itemPath = chosenDir + "\\" + item->text();
    dayCount = 0;
    totalAngle = 0;
    ui->IDchart->setText(item->text());
    ui->daychart->setText(QString::number(dayCount));
    ui->dataView->clearContents();
    ui->dataView->setRowCount(0);
    if(image.load(itemPath)){
        mask = QImage();
        QString json = itemPath.replace("Anh goc", "json");
        json = json.replace(".jpg", ".json");
        readJson(json);
        ratio = 1;

        sizeWidth = image.width();
        sizeHeight = image.height();
        gridHeight = sizeHeight;

        autoCropped = false;
        autoRotated = false;
        getNewStartEnd = false;
        showImage(image);
    }
}
void MainWindow::removeTableRows(){
    for (QTableWidgetItem *x: ui->dataView->selectedItems()) {
        ui->dataView->removeRow(x->row());
    }
}
void MainWindow::addStringToFile(const QString &name, const QString &id){
    bool isPresent;
    QStringList stations, ids;
    QString stationsPath, idsPath;
    if(chartType == 4){
        stations = stationsNameW;
        ids = stationsIDW;
        stationsPath = sNPathW;
        idsPath = sIPathW;

    }
    else{
        stations = stationsName;
        ids = stationsID;
        stationsPath = sNPath;
        idsPath = sIPath;
    }

    isPresent = stations.contains(name)&&ids.contains(id);

    if(!isPresent){
        QMessageBox msgBox;
        msgBox.setText(QString("Bạn có muốn thêm trạm tên %1 với mã %2 không").arg(name).arg(id));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Ok){
            QFile txtFile(stationsPath);
            QFile idFile(idsPath);
            if(txtFile.open(QIODevice::Append|QIODevice::WriteOnly)&&idFile.open(QIODevice::Append|QIODevice::WriteOnly)){
                QTextStream stream(&txtFile);
                QTextStream streami(&idFile);
                stream<<"\n"<<name;
                streami<<"\n"<<id;
                txtFile.close();
                idFile.close();
                stations = loadTxtToStringList(stationsPath);
                ids = loadTxtToStringList(idsPath);
                ui->stationBox->clear();
                ui->stationID->clear();
                ui->stationBox->addItems(stations);
                ui->stationBox->setCurrentIndex(ui->stationBox->count()-1);
                ui->stationID->addItems(ids);
                ui->stationID->setCurrentIndex(ui->stationID->count()-1);

            }

        }
    }
}
void MainWindow::rotForward(){
    image = rotating(image, angle);
    showImage(image);
}

void MainWindow::rotBackward(){
    image = rotating(image, -angle);
    showImage(image);
}



