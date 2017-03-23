#include "saver.h"

saver::saver()
{

}

void saver::savevideo(string& date, vector<Mat>& frame)
{

    VideoWriter vidwrit;
    vidwrit.open(date+".MP4",CV_FOURCC('X','2','6','4'),25,Size(320,240),true);
    for(size_t i = 0;i <frame.size();++i)
    {
        vidwrit.write(frame[i]);

    }
    vidwrit.release();
    frame.clear();
}

void saver::savepicture(string &date,Mat frame)
{
    imwrite(date+".jpg",frame);
}
