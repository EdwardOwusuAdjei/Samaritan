#include <humandetect.h>

void humansdetect::detectthem(MainWindow* w)
{
    int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
    double fontScale = 2;
    int thickness = 3;
    int finder = 0;
    VideoCapture cap(CV_CAP_ANY);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

    if (!cap.isOpened())
    {
        std::cout<<"Not on\n"<<std::endl;
        exit(0);
    }
    Mat img,img_blob;
    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

    Point textOrg((img.cols - 1)/2,
                  (img.rows + 100)/2);
    while (true)
    {
        cap >> img;
        if (!img.data)
            continue;

        vector<Rect> found, found_filtered;
        hog.detectMultiScale(img, found, 0, Size(8,8), Size(32,32), 1.05, 2);


        size_t i, j;
        for (i=0; i<found.size(); i++)
        {
            Rect r = found[i];
            for (j=0; j<found.size(); j++)
                if (j!=i && (r & found[j])==r)
                    break;
            if (j==found.size())
                finder++;
            found_filtered.push_back(r);
        }
        for (i=0; i<found_filtered.size(); i++)
        {
            Rect r = found_filtered[i];
            r.x += cvRound(r.width*0.1);
            r.width = cvRound(r.width*0.8);
            r.y += cvRound(r.height*0.06);
            r.height = cvRound(r.height*0.9);
            rectangle(img, r.tl(), r.br(), cv::Scalar(0,255,0), 2);

        }

        putText(img, to_string(finder), textOrg, fontFace, fontScale,
                Scalar::all(255), thickness, 8);
        // imshow("video capture", img);
        cv::cvtColor(img,img,CV_BGR2RGB);
        QImage imgg= QImage((const unsigned char*)(img.data),
                            img.cols,img.rows,QImage::Format_RGB888);
        //MainWindow ww;
        //w->updater3(imgg);

        if (waitKey(20) >= 0)
        {break;}
    }
}
void humansdetect::detectthem(cv::Mat& img,MainWindow* w)
{
    int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
    double fontScale = 2;
    int thickness = 3;
    static int finder = 0;


    Point textOrg((img.cols - 1)/2,
                  (img.rows + 100)/2);

    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

    if (img.data)
    {

        vector<Rect> found, found_filtered;
        hog.detectMultiScale(img, found, 0, Size(8,8), Size(32,32), 1.05, 2);


        size_t i, j;

        for (i=0; i<found.size(); i++)
        {
            Rect r = found[i];
            for (j=0; j<found.size(); j++)
                if (j!=i && (r & found[j])==r)
                    break;
            if (j==found.size())
                finder++;
            found_filtered.push_back(r);
        }


        for (i=0; i<found_filtered.size(); i++)
        {
            Rect r = found_filtered[i];
            r.x += cvRound(r.width*0.1);
            r.width = cvRound(r.width*0.8);
            r.y += cvRound(r.height*0.06);
            r.height = cvRound(r.height*0.9);
            rectangle(img, r.tl(), r.br(), cv::Scalar(0,255,0), 2);

        }

        putText(img, to_string(finder), textOrg, fontFace, fontScale,
                Scalar::all(255), thickness, 8);

        cv::cvtColor(img,img,CV_BGR2RGB);
        QImage imgg= QImage((const unsigned char*)(img.data),
                            img.cols,img.rows,QImage::Format_RGB888);

    }
}
