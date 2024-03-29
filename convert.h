#ifndef CONVERT_H
#define CONVERT_H
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
namespace cvert
{
inline QImage MatToQImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS=1
    if(mat.type()==CV_8UC1)
    {
        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }
    // 8-bits unsigned, NO. OF CHANNELS=3
    if(mat.type()==CV_8UC3)
    {
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    return QImage();
}
    inline QImage  cvMatToQImage(const cv::Mat &inMat)
    {
        cv::cvtColor(inMat, inMat, cv::COLOR_BGR2RGB);
        switch (inMat.type())
        {
            // 8-bit, 4 channel
        case CV_8UC4:
        {
            QImage image(inMat.data,
                inMat.cols, inMat.rows,
                static_cast<int>(inMat.step),
                QImage::Format_ARGB32);

            return image;
        }

        // 8-bit, 3 channel
        case CV_8UC3:
        {
            QImage image(inMat.data,
                inMat.cols, inMat.rows,
                static_cast<int>(inMat.step),
                QImage::Format_RGB888);

            return image.rgbSwapped();
        }

        // 8-bit, 1 channel
        case CV_8UC1:
        {
//            QImage image(inMat.data,
//                inMat.cols, inMat.rows,
//                static_cast<int>(inMat.step),
//                QImage::Format_Grayscale8);

//            return image;
//#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
            QImage image( inMat.data,
                          inMat.cols, inMat.rows,
                          static_cast<int>(inMat.step),
                          QImage::Format_Grayscale8 );
//#else
//            static QVector<QRgb>  sColorTable;

//            // only create our color table the first time
//            if ( sColorTable.isEmpty() )
//            {
//               sColorTable.resize( 256 );

//               for ( int i = 0; i < 256; ++i )
//               {
//                  sColorTable[i] = qRgb( i, i, i );
//               }
//            }

//            QImage image( inMat.data,
//                          inMat.cols, inMat.rows,
//                          static_cast<int>(inMat.step),
//                          QImage::Format_Indexed8 );

//            image.setColorTable( sColorTable );
//#endif
            return image;
        }

        default:
            qWarning() << "CVS::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
            break;
        }

        return QImage();
    }
    inline QPixmap cvMatToQPixmap(const cv::Mat &inMat)
    {
        return QPixmap::fromImage(cvMatToQImage(inMat));
    }
    inline cv::Mat QImageToCvMat(const QImage &inImage, bool inCloneImageData = true)
    {
        switch (inImage.format())
        {
            // 8-bit, 4 channel
        case QImage::Format_ARGB32:
        case QImage::Format_ARGB32_Premultiplied:
        {
            cv::Mat  mat(inImage.height(), inImage.width(),
                CV_8UC4,
                const_cast<uchar*>(inImage.bits()),
                static_cast<size_t>(inImage.bytesPerLine())
            );

            return (inCloneImageData ? mat.clone() : mat);
        }

        // 8-bit, 3 channel
        case QImage::Format_RGB32:
        case QImage::Format_RGB888:
        {
            if (!inCloneImageData)
            {
                qWarning() << "CVS::QImageToCvMat() - Conversion requires cloning because we use a temporary QImage";
            }

            QImage   swapped = inImage;

            if (inImage.format() == QImage::Format_RGB32)
            {
                swapped = swapped.convertToFormat(QImage::Format_RGB888);
            }

            swapped = swapped.rgbSwapped();

            return cv::Mat(swapped.height(), swapped.width(),
                CV_8UC3,
                const_cast<uchar*>(swapped.bits()),
                static_cast<size_t>(swapped.bytesPerLine())
            ).clone();
        }

        // 8-bit, 1 channel
        case QImage::Format_Indexed8:
        {
            cv::Mat  mat(inImage.height(), inImage.width(),
                CV_8UC1,
                const_cast<uchar*>(inImage.bits()),
                static_cast<size_t>(inImage.bytesPerLine())
            );

            return (inCloneImageData ? mat.clone() : mat);
        }
        case QImage::Format_Grayscale8:
        {
            cv::Mat  mat(inImage.height(), inImage.width(),
                CV_8UC1,
                const_cast<uchar*>(inImage.bits()),
                static_cast<size_t>(inImage.bytesPerLine())
            );

            return (inCloneImageData ? mat.clone() : mat);
        }
        default:
            qWarning() << "CVS::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
            break;
        }

        return cv::Mat();
    }

    inline cv::Mat QPixmapToCvMat(const QPixmap &inPixmap, bool inCloneImageData = true)
    {
        return QImageToCvMat(inPixmap.toImage(), inCloneImageData);
    }
}
#endif // CONVERT_H
