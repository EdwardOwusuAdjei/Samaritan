#include "saver.h"

saver::saver()
{

}

void saver::savevideo(const string& date, vector<Mat>& frame)
{
    VideoWriter vidwrit;
  //  vidwrit.open(date+".mp4",CV_FOURCC('X','2','6','4'),17,Size(320,240),true);//17-23

    vidwrit.open(date+".avi",CV_FOURCC('M', 'J', 'P', 'G'),15,Size(frame[0].size().width,frame[0].size().height),true);//17-23
    for(size_t i = 0;i <frame.size();++i)
    {
        vidwrit.write(frame[i]);
    }
    vidwrit.release();
    frame.clear();
    frame.resize(0);
}

void saver::savepicture(const string& date,Mat& frame)
{

    imwrite(date+".jpg",frame);
}
