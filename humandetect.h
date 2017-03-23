#ifndef HUMANDETECT_H
#define HUMANDETECT_H
#include <iostream>
#include <opencv2/opencv.hpp>  //include from header main file instead.
#include <string>
#include <mainwindow.h>
#include "coreprocess.h"


using namespace std;
using namespace cv;
class humansdetect
{
private:
    //surely something will come here
public:
     void detectthem(MainWindow* w);
     void detectthem(cv::Mat& frame,MainWindow* w);


};
#endif //HUMANDETECT_H
