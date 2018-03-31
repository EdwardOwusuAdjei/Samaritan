#include "videointerface.h"

videointerface::videointerface()
{

}

vector<int> videointerface::getavailablecams()
{
    int max = 10;
    vector<int> interfaces;
    for(int i=0 ;i < max; i++)
    {
        cv::VideoCapture tempdetails;
        bool couldopen = tempdetails.open(i);
        if(couldopen)
        {
            interfaces.push_back(i);
        }
    }

    return interfaces;
}
