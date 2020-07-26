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
    void changeTable();
    void lineDetection();
    void removeTableRows();
    int timeToCols();
    int levelToRows();
    void drawPointDebug(std::vector<int> xP, std::vector<double> yP, const QColor &color);
    void drawPointDebug(std::vector<double> xP, std::vector<double> yP, const QColor &color);
    void drawPointDebug(std::vector<int> xP, std::vector<int> yP, const QColor &color);
    void detectDays();
    void changeParabol();
    int first(std::vector<int>, int n, int x);
    int last(std::vector<int>, int n, int x);
    QString getLitters(double, double);
    void extractData();
    void unique();
    void readJson(QString);
    QImage createImageWithOverlay(const QImage& baseImage, const QImage& overlayImage);
    void pointToValue(double x, double y);

    std::vector<int> removeDuplicate(std::vector<int> uniqueVector, std::vector<int> rawVector, std::vector<int> findVector);
    std::vector<double> removeDuplicate(std::vector<int> uniqueVector, std::vector<int> rawVector, std::vector<double> findVector);
    std::vector<int> vectorThreshold(std::vector<int> input, QTime threshTime, int day);
    void detectRainOver(int x, int y, int w, int h);

    int parabolGrid(int mousePos, double parabolPos, int nx);
    void cropImage();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:

    bool eventFilter(QObject *object, QEvent *event);

public slots:
    void NameToID(int);
    void IDToName(int);
    void changeSetup();
    void saveToTxt();
    void switchMode(int);
    void exportNow();
    void nextDay();
    void prevDay();
    void enableRotateandCrop();
    QImage RotateAndCrop(QImage);
    QImage cropOnly(QImage);
    void mouseDrawLineToMask(const QVector<QPointF> &input);
    void getNewVariables(int xmin, int ymin, int xmax, int ymax);
    void cropGridToggled(bool enabled);
    void zoomToggled(bool enabled);
    void drawToggled(bool enabled);
    void quitApp();
    void openFolder();
    void itemClicked(QListWidgetItem *item);
    void inputDialog();

private:
    QWidget *spacer = new QWidget;
    bool cropped = false;
    bool opened;
    QTime startTime;
    QTime endTime;
    int days;
    double startLevel;
    double endLevel;
    int timeSpace;
    double levelSpace;
    Input *dialog;
    QPixmap pixmap;
    QLabel *modeLabel = new QLabel;
    QLabel *timeLabel = new QLabel;
    QLabel *colNum = new QLabel;
    QLabel *rowNum = new QLabel;

    QLineEdit *inputBox = new QLineEdit;
    QLineEdit *timeBox = new QLineEdit;
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
    double gridWidth;
    double gridHeight;

    QSize iconSize;
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

    QImage image;
    QImage imagePr;
    QImage mask;

    int dayCount = 0;

    int overFlow=0;
    int total;
    QString chartType = "am";
    bool ev;

    QGraphicsScene *scene = new QGraphicsScene;
    QList<QString> colNames;
    QList<QString> bubble;

    double angle;
    double cos;
    double sin;
    int x_min;
    int y_min;
    int x_max;
    int y_max;
    int column;
    double ratio;
    int bias = 0;
    double addUp = 0;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
