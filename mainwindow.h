#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QSettings>
#include <QListWidgetItem>
#include <QImageReader>
#include <QSize>
#include <QScrollBar>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QLabel>
#include <QVector>
#include <QDebug>
#include <QMessageBox>
#include <QJsonDocument>
#include <QDateTime>
#include <QComboBox>
#include <QLineEdit>
#include <QProcess>
#include <QRadioButton>
#include <QTextEdit>
#include <QGraphicsPixmapItem>
#include <QProgressDialog>
#include <QVector>
#include "input.h"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void addStringToFile(const QString &name, const QString &id);
    QStringList loadTxtToStringList(const QString &txtpath);
    void removeTableRows();
    void moveDay(bool isNext);
    int timeToCols(QTime startTime, double timeSpace, QTime endTime, int days);
    int levelToRows(int startLevel, double levelExtract, int endLevel);
    int totalTimeofLineinSecs(QTime startTime, QTime endtime, int days);
    void showImage(const QImage &inputImage);

    void detectDays();
    void changeParabol();

    bool isWithin(cv::Point p);
    QString getLitters(double, double);

    void extractDataFromLine(const QImage& inputMask);

    void readJson(QString);
    QImage createImageWithOverlay(const QImage& baseImage, const QImage& overlayImage);
    void pointToValue(double x, double y);
    QImage cropping(QImage, int, int, int, int, bool);
    QImage rotating(const QImage&, double);
    QImage performDilation(const QImage& input);


    int detectRainOver(int x, int y, int w, int h);


    int parabolGrid(int mousePos, double parabolPos, int nx);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    bool eventFilter(QObject *object, QEvent *event);

public slots:

    void rotateClick(bool forward);


    void receivePoint(QPointF);
    void addingRpPoint(QPointF);
    void addingRectPoint(QPointF);
    void changeStartEndPoint(QPointF);

    void NameToID(int);
    void IDToName(int);
    void changeParams(QTime, int, QTime, double, double, double, int, bool, bool);
    void saveToTxt();

    void switchMode(int);
    void statusMessage(bool, const QString& message);
    void exportNow();
    void changeTable();


    void test_rain_reader();
    void addToMask(const QVector<QPoint>& pointsVec);
    void createMask(bool);

    void calculateParabolafrom3points(QPointF x1, QPointF x2, QPointF x3);
    void getNewCutRect(int xmin, int ymin, int xmax, int ymax);

    void quitApp();
    void openFolder();
    void itemClicked(QListWidgetItem *item);
    void inputDialog();
    void dialogCloseOk(bool);


private:
    std::vector<cv::Point> locations;
    QSize gridSize;
    QSize iconSize;
    QVector<QPointF> neededPoints;
    QVector<QPointF> rectPoints;
    QVector<QPointF> limitPoints;
    QWidget *spacer = new QWidget;
    QStringList errorImages;

    bool manualCropped = false;
    bool autoCropped = false;
    bool autoRotated = false;
    bool pickingPoints = false;
    bool getNewStartEnd = false;

    bool keepPara = true;
    bool keepStartEnd = false;

    bool opened;
    QTime startTime;
    QTime endTime;
    int days;
    double startLevel;
    double endLevel;
    int timeExtract;
    double levelExtract;
    QPixmap pixmap;

    QLabel *modeLabel = new QLabel;
    QLabel *timeLabel = new QLabel;
    QLabel *colNum = new QLabel;
    QLabel *rowNum = new QLabel;

    QComboBox *modeBox = new QComboBox;

    QString boxName = "Chọn loại biểu đồ: ";
    //! Mode list for choosing in the combobox
    QStringList modeList = {"Độ Ẩm", "Áp Suất", "Lượng Mưa", "Nhiệt Độ", "Mức Nước"};

    QString sNPath = "./stations/station_name.txt";
    QString sIPath = "./stations/station_id.txt";
    QString sNPathW = "./stations/station_namew.txt";
    QString sIPathW = "./stations/station_idw.txt";

    QStringList stationsName;
    QStringList stationsID;
    QStringList stationsNameW;
    QStringList stationsIDW;
    //! 3 python files with 3 missions

    QString argChart;
    QString lineFolder = "line";
    QString jsonFolder = "json";
    QString itemPath;
    QString exportImgs;
    QString chosenDir;
    QString exportDir;


    QLabel *icon1 = new QLabel;
    QLabel *icon2 = new QLabel;
    // Image properties
    int sizeHeight;
    int sizeWidth;
    int numCols;
    int numRows;
    

    
    int maskCount = 0;
    // Mask for detecting
    QImage cropMaskRain;
    cv::Mat cropRain;
    // contours for storing
    std::vector<std::vector<cv::Point>> contours;
    int timeX;
    int gridnX;
    int gridnY;
    int nX;
    double parabolPos;

    int pixelLitter;
    int lit;
    int litp;
    int difL = 0;
    QTime time;
    double pointSize = 0.002;
    QImage image;
    QImage imagePr;
    QImage mask;

    int dayCount = 0;
    int chartType = 0;
    QGraphicsScene *scene = new QGraphicsScene;
    QList<QString> colNames;
    QList<QString> bubble;

    double totalAngle = 0;
    double angle = 1;
    double cos;
    double sin;

    int decimalDigit = 0;

    int x_mincut, x_maxcut;

    int x_minc;
    int x_maxc;
    int y_min;
    int y_max;
    int column;

    double ratio;
    double aPara = 0;
    double bPara = 0;
    int gridHeight;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
