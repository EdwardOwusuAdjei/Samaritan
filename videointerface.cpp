#include "videointerface.h"

videointerface::videointerface()
{

}

vector<string> videointerface::getavailablecams()
{
  //  cv::VideoCapture tempdetails;
    int max = 10;

    for(int i=0;i<max;i++)
    {
       cv::VideoCapture tempdetails(i);
       bool couldopen = (!tempdetails.isOpened());
       tempdetails.release();
       if(couldopen)
       {
          // return i;
       }

    }
  //  return
}
