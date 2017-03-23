#ifndef VIDEOINTERFACE_H
#define VIDEOINTERFACE_H
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <string>
using namespace std;
class videointerface
{
public:
    videointerface();
    vector<string> getavailablecams();
};

#endif // VIDEOINTERFACE_H
