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
#include <humandetect.h>
#include <stdlib.h>
#include <embedpython.h>
#include<iostream>
#include <thread>
#include <string>
#include <counting.h>
#include <setupfaces.h>
#include <facerecog.h>
#include <vector>
#include <notify.h>
#include "threading.h"
#include "blob.h"


const cv::Scalar SCALAR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar SCALAR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
const cv::Scalar SCALAR_YELLOW = cv::Scalar(0.0, 255.0, 255.0);
const cv::Scalar SCALAR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
const cv::Scalar SCALAR_RED = cv::Scalar(0.0, 0.0, 255.0);



static bool blnFirstFrame = true;

 static std::vector<cv::VideoCapture> capVec;

class coreprocess
{


public:
    coreprocess(std::string index);
    coreprocess(int index,int index2);
    void inline MatchCurrentFrameBlobsToExistingBlobsVector(std::vector<Blob> &existingBlobs, std::vector<Blob> &currentFrameBlobs);
    void inline InsertBlobToExistingBlobVector(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex);
    void inline InsertNewBlobIntoVector(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs);
    double inline CalcDistanceBetweenPoints(cv::Point point1, cv::Point point2);
    void inline DrawContours(cv::Size MatSize, std::vector<std::vector<cv::Point> > contours);
    void inline DrawContours(cv::Size MatSize, std::vector<Blob> blobs);
    void inline DrawBlobInfoOnFrame(std::vector<Blob> &blobs, cv::Mat &imgFrame2Copy);
    bool inline hasblobcrossed(std::vector<Blob>&blob,int& theline,int& count);
    void inline aftermain();
    void EntryPoint();

};

#endif //COREPROCESS_H
