#ifndef SETUPFACES_H
#define SETUPFACES_H
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>



using namespace std;
using namespace cv;


class setupfaces
{
   const string cascade = "cascades/haarcascade_frontalface_default.xml";
public:
    setupfaces();
    vector<Mat> preparefortraining();
};

#endif // SETUPFACES_H

