#ifndef COREPROCESS_H
#define COREPROCESS_H
#include "mainwindow.h"
#include "saver.h"
#include "notify.h"
#include <ctime>
#include <QApplication>
#include <memory>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/video/background_segm.hpp>
#include <stdlib.h>
#include<iostream>
#include <thread>
#include <string>
#include <counting.h>
#include <vector>
#include "blob.h"






class coreprocess:public QObject
{
    Q_OBJECT
public:
    int labelpos = 0;
    bool bcanCapture = false;
    const cv::Scalar SCALAR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
    const cv::Scalar SCALAR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
    const cv::Scalar SCALAR_YELLOW = cv::Scalar(0.0, 255.0, 255.0);
    const cv::Scalar SCALAR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
    const cv::Scalar SCALAR_RED = cv::Scalar(0.0, 0.0, 255.0);
    bool shouldsend = false;
    bool channelone = false;
    Point detectionline[2];
    int line =  0;
    Mat imgFrame1;
    Mat imgFrame2;
    Mat imgFrame1Copy ;
    Mat imgFrame2Copy ;
    Mat imgFrame3;
    Mat imgThreshCopy ;
    QImage img;
    Mat imgDifference;
    Mat imgThresh;
    int record;
    int rec = 0;
    vector<string> ips;
    vector<cv::Mat> MATRIX;
    cv::Mat structuringElement5x5;

public:
    VideoCapture vctry;
    coreprocess();
    void aftermain();
    bool canCapture(int source,int pos);
    bool canCapture(string source, int pos);
    std::thread aftermainthread();
private:

    void inline DrawContours(cv::Size MatSize, std::vector<std::vector<cv::Point> > contours);
    void inline DrawContours(cv::Size MatSize, std::vector<Blob> blobs);
    void inline DrawBlobInfoOnFrame(std::vector<Blob> &blobs, cv::Mat &imgFrame2Copy);
    bool inline hasblobcrossed(std::vector<Blob>&blob,int& theline);

signals:
    void liveupdate(QImage img,int QTlabel);

};

#endif //COREPROCESS_H
