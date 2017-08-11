#ifndef SAVER_H
#define SAVER_H
#include <string>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <vector>


using namespace std;
using namespace cv;

class saver
{
public:

    saver();
    void savevideo(const string& date,vector<Mat>& frame);
    void savepicture(const string& date,Mat& frame);
};

#endif // SAVER_H
