#ifndef MAIN_H
#define MAIN_H
#include "mainwindow.h"
#include <QApplication>
#include <memory>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <humandetect.h>
#include <stdlib.h>
#include <embedpython.h>
#include<iostream>
//#include <future>
#include <thread>
#include <counting.h>
#include <setupfaces.h>
#include <facerecog.h>


#include "blob.h"

#define SHOW_STEPS

// un-comment or comment this line to show steps or not

// global variables ///////////////////////////////////////////////////////////////////////////////
const cv::Scalar SCALAR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar SCALAR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
const cv::Scalar SCALAR_YELLOW = cv::Scalar(0.0, 255.0, 255.0);
const cv::Scalar SCALAR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
const cv::Scalar SCALAR_RED = cv::Scalar(0.0, 0.0, 255.0);
static int changefocus = 1;
static bool blnFirstFrame = true;

// function prototypes ////////////////////////////////////////////////////////////////////////////
void matchCurrentFrameBlobsToExistingBlobs(std::vector<Blob> &existingBlobs, std::vector<Blob> &currentFrameBlobs);
void addBlobToExistingBlobs(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex);
void addNewBlob(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs);
double distanceBetweenPoints(cv::Point point1, cv::Point point2);
void drawAndShowContours(cv::Size imageSize, std::vector<std::vector<cv::Point> > contours, std::string strImageName,MainWindow& w);
void drawAndShowContours(cv::Size imageSize, std::vector<Blob> blobs, std::string strImageName,MainWindow& w);
void drawBlobInfoOnImage(std::vector<Blob> &blobs, cv::Mat &imgFrame2Copy);
bool blobcrossed(std::vector<Blob>&blob,int& theline,int& count);
void drawCarCountOnImage(int &carCount, cv::Mat &imgFrame2Copy);
void aftermain(MainWindow& w,VideoCapture& cap);
//Function Prototypes
void EntryPoint( MainWindow& w,unsigned int i,unsigned int cameraindx);
//void aftermain(cv::Mat imgFrame1,cv::Mat imgFrame2,MainWindow& w);
void aftermain(cv::Mat imgFrame1,cv::Mat imgFrame2,MainWindow& w,cv::VideoCapture& capVideo);
#endif // MAIN_H
