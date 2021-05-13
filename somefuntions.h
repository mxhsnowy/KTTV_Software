#ifndef SOMEFUNTIONS_H
#define SOMEFUNTIONS_H
#include <iostream>
#include <vector>
#include <numeric>      // std::iota
#include <algorithm>    // std::sort, std::stable_sort
#include <opencv2/opencv.hpp>
#include <QImage>
#include <QPainter>
#include <QPen>
using namespace std;

template <typename T>
vector<size_t> sort_indexes(const vector<T> &v) {

  // initialize original index locations
  vector<size_t> idx(v.size());
  iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  // using std::stable_sort instead of std::sort
  // to avoid unnecessary index re-orderings
  // when v contains elements of equal values
  stable_sort(idx.begin(), idx.end(),
       [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

  return idx;
}

template<typename T> int first(const std::vector<T> &input, int n, int x)
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
template<typename T> int last(const std::vector<T> &input, int n, int x)
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

QImage drawALine(const QImage& image, int x, const QColor& color, int penWidth){
    QImage outputImg = image.copy();
    QPainter painter(&outputImg);
    QPen pen;
    pen.setWidth(penWidth);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(color);
    painter.setPen(pen);
    painter.drawLine(x, 0, x, image.height());
    painter.end();
    return outputImg;
}
template <typename T1, typename T2> QImage drawPointDebug(const QImage& image, const std::vector<T1>& xP, const std::vector<T2>& yP,
                                                          const QColor &color, int penWidth = 10){
    QImage outputImg = image.copy();
    QPainter painter(&outputImg);
    QPen pen;
    pen.setWidth(penWidth);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(color);
    painter.setPen(pen);
    for (int i = 0; i < xP.size(); i++) {
        painter.drawPoint(int(xP.at(i)), int(yP.at(i)));

    }
    painter.end();
    return outputImg;
}
QImage drawPointDebug(const QImage& image, const std::vector<cv::Point2d>& points, const QColor &color, int penWidth = 10){
    QImage outputImg = image.copy();
    QPainter painter(&outputImg);
    QPen pen;
    pen.setWidth(penWidth);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(color);
    painter.setPen(pen);
    for (cv::Point2d p: points) {
        painter.drawPoint(p.x, p.y);
    }
    painter.end();
    return outputImg;
}
template <typename T1, typename T2> QImage drawRectDebug(QImage image, std::vector<T1> xP, std::vector<T2> yP,
                                                          const QColor &color, double height, int penWidth = 20){
    QPainter painter(&image);
    QPen pen;
    pen.setWidth(penWidth);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(color);
    painter.setPen(pen);
    for (int i = 0; i < xP.size()-1; i++) {
        painter.drawRect(int(xP[i]), int(yP[i]), int(xP[i+1]-xP[i]), height);
    }
    painter.end();
    return image;
}
template <typename T1, typename T2> std::vector<T2> removeDuplicate(const std::vector<T1> &uniqueVector, const std::vector<T1> &rawVector, const std::vector<T2> &findVector){
    int index;

    std::vector<T1> forward;
    std::vector<T2> output;
    for (int x:uniqueVector) {

        index = first(rawVector, rawVector.size(), x);
        forward.push_back(index);

    }

    for(const int& x:forward){
        output.push_back(findVector.at(x));
    }
    return output;
}

template<typename T> std::vector<int> getMissingIndex(std::vector<T> inputTimeVector, double threshold){
    // Make diff and index vector
//    qDebug()<<"Input vector"<<inputTimeVector<<"\n";
//    qDebug()<<"difference"<<threshold<<"\n";
    std::vector<int> diff;
    std::vector<int> indexes;
    for (int i = 1; i<inputTimeVector.size(); ++i) {
//        qDebug()<<"Pair"<<"\n";
//        qDebug()<<inputTimeVector[i]<<"\n";
//        qDebug()<<inputTimeVector[i-1]<<"\n";
        diff.push_back(inputTimeVector[i]-inputTimeVector[i-1]);
    }
    for (int i = 0; i<diff.size(); ++i) {
        if(diff[i]!=threshold){
            indexes.push_back(i+1);
        }
    }
    return indexes;
}


#endif // SOMEFUNTIONS_H
