#include "coreprocess.h"
coreprocess::coreprocess()
{

}

bool coreprocess::canCapture(int source,int pos)
{
    bcanCapture = vctry.open(source);
    if(bcanCapture)
    {
        labelpos = pos;
        return true;
    }
    return false;
}

bool coreprocess::canCapture(string source,int pos)
{
    bcanCapture = vctry.open(source);
    if(bcanCapture)
    {
        labelpos = pos;
        return true;
    }
    return false;
}

thread coreprocess::aftermainthread()
{
    return std::thread([=]{coreprocess::aftermain();});
}

void  coreprocess::aftermain()
{
    vctry >> imgFrame1;
    if(imgFrame1.channels() == 1)
    {
        channelone = true;
    }
    detectionline[0].x = 0;
    detectionline[0].y = imgFrame1.size().height/2;
    detectionline[1].x = imgFrame1.size().width;
    detectionline[1].y = imgFrame1.size().height/2;
    structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5,5));//The function constructs and returns the structuring element that can be further passed to cv::erode,cv::dilate or cv::morphologyEx.

    while(true){
        if(MainWindow::instance()->breakloop())
        {
            break;
        }
        vctry >> imgFrame1;
        vctry >> imgFrame2;

        line = imgFrame1.size().height;
        imgFrame3 = imgFrame1.clone();
        
        imgFrame1Copy = imgFrame1.clone();
        imgFrame2Copy = imgFrame2.clone();
        if(!channelone)
        {
            cv::cvtColor(imgFrame1Copy, imgFrame1Copy, CV_BGR2GRAY);
            cv::cvtColor(imgFrame2Copy, imgFrame2Copy, CV_BGR2GRAY);
        }
        cv::GaussianBlur(imgFrame1Copy, imgFrame1Copy, cv::Size(5, 5), 0);//eddie used you to read reduce noise so i can find the absdiff
        cv::GaussianBlur(imgFrame2Copy, imgFrame2Copy, cv::Size(5, 5), 0);
        
        cv::absdiff(imgFrame1Copy, imgFrame2Copy, imgDifference);
        //30
        cv::threshold(imgDifference, imgThresh, MainWindow::instance()->sensitivity(), 255.0, CV_THRESH_BINARY);//now here i take out pixels above thirty to 255 who matter :) now make it black or white

        cv::dilate(imgThresh, imgThresh, structuringElement5x5);//functions to reduce noise again
        cv::dilate(imgThresh, imgThresh, structuringElement5x5);
        cv::erode(imgThresh, imgThresh, structuringElement5x5);
        

        imgThreshCopy = imgThresh.clone();

        std::vector<std::vector<cv::Point> > contours;
        cv::findContours(imgThreshCopy, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        
        DrawContours(imgThresh.size(), contours);//image Contours
        
        std::vector<std::vector<cv::Point> > convexHulls(contours.size());
        
        for (unsigned int i = 0; i < contours.size(); i++) {
            cv::convexHull(contours[i], convexHulls[i]);
        }
        
        DrawContours(imgThresh.size(), convexHulls);//image ConvexHulls

        std::vector<Blob> blobs;
        std::vector<Blob> currentFrameBlobs;
        
        for (auto &convexHull : convexHulls) {
            Blob possibleBlob(convexHull);
            //  Necessary but could forget about it later
            if (possibleBlob.currentBoundingRect.area() > 100 &&
                    possibleBlob.dblCurrentAspectRatio >= 0.2 &&
                    possibleBlob.dblCurrentAspectRatio <= 1.25 &&
                    possibleBlob.currentBoundingRect.width > 20 &&
                    possibleBlob.currentBoundingRect.height > 20 &&
                    possibleBlob.dblCurrentDiagonalSize > 30.0 &&
                    (cv::contourArea(possibleBlob.currentContour) / (double)possibleBlob.currentBoundingRect.area()) > 0.40) {
                currentFrameBlobs.push_back(possibleBlob);
            }
        }


        DrawContours(imgThresh.size(), currentFrameBlobs);//image CurrentFrameBlobs
        

        for (auto &currentFrameBlob : currentFrameBlobs) {
            blobs.push_back(currentFrameBlob);
        }

        
        DrawContours(imgThresh.size(), blobs);//image Blobs
        
        imgFrame2Copy = imgFrame2.clone();          // get another copy of frame 2 since we changed the previous frame 2 copy in the processing above
        
        DrawBlobInfoOnFrame(blobs, imgFrame2Copy);
        bool blnAtLeastOneBlobCrossedTheLine = hasblobcrossed(blobs, line);

        if (blnAtLeastOneBlobCrossedTheLine == true) {
            time_t     now = time(0);
            struct tm  tstruct;
            char       buf[80];
            tstruct = *localtime(&now);
            std::unique_ptr<saver>sv(new saver);
            strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
            sv->savepicture( string(buf).c_str(),imgFrame2Copy);
            record = 1;
        }

        if(blnAtLeastOneBlobCrossedTheLine == true)
        {
            record = 1;
        }
        if(record == 1)
        {
            if(rec == 50)
            {
                shouldsend = false;
                notify nt;
                if(!MainWindow::instance()->getTextIP().empty())
                {
                    ips.push_back(MainWindow::instance()->getTextIP());
                    shouldsend = true;
                }
                if(!MainWindow::instance()->getTextIP2().empty())
                {
                    ips.push_back(MainWindow::instance()->getTextIP2());
                    shouldsend = true;
                }
                if(!MainWindow::instance()->getTextIP3().empty())
                {
                    ips.push_back(MainWindow::instance()->getTextIP3());
                    shouldsend = true;
                }


                if(shouldsend)
                {
                    std::thread t([&]{nt.notifyselected(ips);});
                    t.detach();
                }
            }

        }
        if(record == 1)//merge with upper IF cond.
        {
            rec++;
            if(MainWindow::instance()->shouldrecord())
            {
                MATRIX.push_back(imgFrame3);

                if(rec >= 500)
                {
                    time_t     now = time(0);
                    struct tm  tstruct;
                    char       buf[80];
                    tstruct = *localtime(&now);
                    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
                    std::unique_ptr<saver>sv(new saver);
                    std::thread t([&]{sv->savevideo(string(buf).c_str(),MATRIX);});
                    t.detach();
                    rec = 0;
                    record = 0;
                }
            }
            else
            {
                if(MATRIX.size()>0)
                {
                    rec = 0;
                    MATRIX.clear();
                    MATRIX.resize(0);
                }
                if(rec > 50)
                {
                    rec = 0;
                }
            }
        }
        cv::cvtColor(imgFrame2Copy,imgFrame2Copy,CV_BGR2RGB);
        img = QImage((const unsigned char*)(imgFrame2Copy.data),
                     imgFrame2Copy.cols,imgFrame2Copy.rows,QImage::Format_RGB888);
        emit liveupdate(img,labelpos);
        if(imgFrame1.empty())
        {
            break;
        }

    }
}

void inline coreprocess::DrawContours(cv::Size MatSize, std::vector<std::vector<cv::Point> > contours) {
    cv::Mat image(MatSize, CV_8UC3, SCALAR_BLACK);
    cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);

}

//renam to find contour
void inline coreprocess::DrawContours(cv::Size MatSize, std::vector<Blob> blobs) {
    cv::Mat image(MatSize, CV_8UC3, SCALAR_BLACK);
    std::vector<std::vector<cv::Point> > contours;
    for (auto &blob : blobs) {
        if (blob.ofinterest == true) {
            contours.push_back(blob.currentContour);
        }
    }
    cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);
    
}


void inline coreprocess::DrawBlobInfoOnFrame(std::vector<Blob> &blobs, cv::Mat &imgFrame2Copy) {
    
    for (unsigned int i = 0; i < blobs.size(); i++) {
        
        if (blobs[i].ofinterest == true) {
            cv::rectangle(imgFrame2Copy, blobs[i].currentBoundingRect, SCALAR_RED, 2);
        }
    }
}
bool inline coreprocess::hasblobcrossed(std::vector<Blob>&blob,int& theline)
{
    bool crossed = false;
    for(auto obj : blob)
    {
        if(obj.ofinterest == true)// && obj.centerPositions.size() > 2)
        {
            //int prev = obj.centerPositions.size() - 2;
            int curr = obj.centerPositions.size() - 1;
            if( obj.centerPositions[curr].y < theline)
            {
                crossed = true;
            }
            
        }
    }
    if(crossed)
    {
        //  count++;
    }
    return crossed;
}



