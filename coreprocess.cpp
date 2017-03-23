#include "coreprocess.h"


coreprocess::coreprocess(std::string index)
{

    capVec.clear();
    cv::VideoCapture vc;

    cv::VideoCapture cap;
    vc.open(index);

    capVec.push_back(vc);
    capVec.push_back(cap);


}

coreprocess::coreprocess(int index, int index2)
{
    capVec.clear();
    cv::VideoCapture vc;

    cv::VideoCapture cap;
    vc.open(index);
    vc.set(CV_CAP_PROP_FRAME_WIDTH,320);
    vc.set(CV_CAP_PROP_FRAME_HEIGHT,240);
    cap.open(index2);
    cap.set(CV_CAP_PROP_FRAME_WIDTH,320);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,240);

    capVec.push_back(vc);
    capVec.push_back(cap);
}

void coreprocess::EntryPoint()
{
    //might doo some basic check here.
    aftermain();

}
void inline coreprocess::aftermain()
{

    cv::Mat imgFrame1;
    cv::Mat imgFrame2;

    cv::Mat imgFrame3;
    cv::Point detectionline[2];
    int line =  0;
    saver sv;
    static int count = 0;
    vector<cv::Mat> MATRIX;


    detectionline[0].x = 0;
    detectionline[0].y = imgFrame1.size().height/2;
    detectionline[1].x = imgFrame1.size().width;
    detectionline[1].y = imgFrame1.size().height/2;

    static int record;
    int rec = 0;
    int frameCount = 2;

    int  i = 0;
    while(true){

        if(i % 2 == 0)
        {
            capVec[1] >> imgFrame1;
            capVec[1] >> imgFrame2;
        }
        else{
            capVec[0] >> imgFrame1;
            capVec[0] >> imgFrame2;

        }
        if(MainWindow::instance()->breakloop())
        {
            break;
        }
        line = imgFrame1.size().height/2;
        imgFrame3 = imgFrame1.clone();


        std::vector<Blob> blobs;
        std::vector<Blob> currentFrameBlobs;
        cv::Mat imgDifference;
        cv::Mat imgThresh;




        cv::Mat imgFrame1Copy = imgFrame1.clone();
        cv::Mat imgFrame2Copy = imgFrame2.clone();

        cv::cvtColor(imgFrame1Copy, imgFrame1Copy, CV_BGR2GRAY);
        cv::cvtColor(imgFrame2Copy, imgFrame2Copy, CV_BGR2GRAY);

        cv::GaussianBlur(imgFrame1Copy, imgFrame1Copy, cv::Size(5, 5), 0);
        cv::GaussianBlur(imgFrame2Copy, imgFrame2Copy, cv::Size(5, 5), 0);

        cv::absdiff(imgFrame1Copy, imgFrame2Copy, imgDifference);

        cv::threshold(imgDifference, imgThresh, 30, 255.0, CV_THRESH_BINARY);



        cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5,5));


        cv::dilate(imgThresh, imgThresh, structuringElement5x5);
        cv::dilate(imgThresh, imgThresh, structuringElement5x5);
        cv::erode(imgThresh, imgThresh, structuringElement5x5);


        cv::Mat imgThreshCopy = imgThresh.clone();

        std::vector<std::vector<cv::Point> > contours;

        cv::findContours(imgThreshCopy, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        DrawContours(imgThresh.size(), contours);//image Contours

        std::vector<std::vector<cv::Point> > convexHulls(contours.size());

        for (unsigned int i = 0; i < contours.size(); i++) {
            cv::convexHull(contours[i], convexHulls[i]);
        }

        DrawContours(imgThresh.size(), convexHulls);//image ConvexHulls

        for (auto &convexHull : convexHulls) {
            Blob possibleBlob(convexHull);
            //  counting ;
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

        if (blnFirstFrame == true) {
            for (auto &currentFrameBlob : currentFrameBlobs) {
                blobs.push_back(currentFrameBlob);
            }
        }
        else {
            MatchCurrentFrameBlobsToExistingBlobsVector(blobs, currentFrameBlobs);
        }

        DrawContours(imgThresh.size(), blobs);//image Blobs

        imgFrame2Copy = imgFrame2.clone();          // get another copy of frame 2 since we changed the previous frame 2 copy in the processing above

        DrawBlobInfoOnFrame(blobs, imgFrame2Copy);
        bool blnAtLeastOneBlobCrossedTheLine = hasblobcrossed(blobs, line, count);
        if(i % 2 == 0)
        {

            if (blnAtLeastOneBlobCrossedTheLine == true) {
                // cv::line(imgFrame2Copy, detectionline[0], detectionline[1], SCALAR_GREEN, 7);
                cv::line(imgFrame2Copy, cv::Point(0,imgFrame1.size().height/2),cv::Point(imgFrame1.size().width,imgFrame1.size().height/2), SCALAR_GREEN, 2);
                time_t now = time(0);
                char* dt = ctime(&now);
                string time = string(dt).c_str();
                sv.savepicture( time,imgFrame2Copy);


            }
            else {
                //cv::line(imgFrame2Copy, detectionline[0], detectionline[1], SCALAR_RED, 7);
                cv::line(imgFrame2Copy, cv::Point(0,imgFrame1.size().height/2),cv::Point(imgFrame1.size().width,imgFrame1.size().height/2), SCALAR_RED, 2);
                //  cv::line(imgFrame2Copy, cv::Point(imgFrame1.size().height,imgFrame1.size().width/2),cv::Point(imgFrame1.size().width/2,0), SCALAR_GREEN, 2);

            }

        }
        else
        {
            if (blnAtLeastOneBlobCrossedTheLine == true) {
                // cv::line(imgFrame2Copy, detectionline[0], detectionline[1], SCALAR_GREEN, 7);
                //  cv::line(imgFrame2Copy, cv::Point(0,imgFrame1.size().height/2),cv::Point(imgFrame1.size().width,imgFrame1.size().height/2), SCALAR_GREEN, 2);
                time_t now = time(0);
                char* dt = ctime(&now);
                string time = string(dt).c_str();
                sv.savepicture( time,imgFrame2Copy);

            }

        }
        if(blnAtLeastOneBlobCrossedTheLine == true)
        {
            record = 1;

        }
        if(record == 1)
        {
            if(rec == 50)
            {
                notify nt;
                vector<string> ips;
                ips.push_back(MainWindow::instance()->getTextIP());
                ips.push_back(MainWindow::instance()->getTextIP2());
                ips.push_back(MainWindow::instance()->getTextIP3());
                std::thread t([&]{nt.notifyselected(ips);});
                t.join();
            }

        }
        if(i % 2 != 0)
        {
            if(record == 1)
            {

                MATRIX.push_back(imgFrame3);
                rec++;
                if(rec == 500)
                {

                    time_t now = time(0);
                    char* dt = ctime(&now);
                    string time = string(dt).c_str();
                    saver sv;
                    std::thread t([&]{sv.savevideo(time,MATRIX);});
                    t.join();
                    rec = 0;
                    record = 0;

                }
            }
        }

        cv::cvtColor(imgFrame2Copy,imgFrame2Copy,CV_BGR2RGB);
        QImage img = QImage((const unsigned char*)(imgFrame2Copy.data),
                            imgFrame2Copy.cols,imgFrame2Copy.rows,QImage::Format_RGB888);

        if(i % 2 == 0)
        {
            MainWindow::instance()->updater1(img);
            qApp->processEvents();
        }
        else
        {
            MainWindow::instance()->updater2(img);
            qApp->processEvents();

        }


        currentFrameBlobs.clear();

        imgFrame1 = imgFrame2.clone();           // move frame 1 up to where frame 2 is

        if(imgFrame1.empty())
        {
            //break;
        }
        frameCount++;
        i++;

    }
}


void inline coreprocess::MatchCurrentFrameBlobsToExistingBlobsVector(std::vector<Blob> &existingBlobs, std::vector<Blob> &currentFrameBlobs) {

    for (auto &existingBlob : existingBlobs) {

        existingBlob.blnCurrentMatchFoundOrNewBlob = false;

        existingBlob.predictNextPosition();
    }

    for (auto &currentFrameBlob : currentFrameBlobs) {

        int intIndexOfLeastDistance = 0;
        double dblLeastDistance = 100000.0;

        for (unsigned int i = 0; i < existingBlobs.size(); i++) {
            if (existingBlobs[i].blnStillBeingTracked == true) {
                double dblDistance = CalcDistanceBetweenPoints(currentFrameBlob.centerPositions.back(), existingBlobs[i].predictedNextPosition);

                if (dblDistance < dblLeastDistance) {
                    dblLeastDistance = dblDistance;
                    intIndexOfLeastDistance = i;
                }
            }
        }

        if (dblLeastDistance < currentFrameBlob.dblCurrentDiagonalSize * 1.15) {
            InsertBlobToExistingBlobVector(currentFrameBlob, existingBlobs, intIndexOfLeastDistance);
        }
        else {
            InsertNewBlobIntoVector(currentFrameBlob, existingBlobs);
        }

    }

    for (auto &existingBlob : existingBlobs) {

        if (existingBlob.blnCurrentMatchFoundOrNewBlob == false) {
            existingBlob.intNumOfConsecutiveFramesWithoutAMatch++;
        }

        if (existingBlob.intNumOfConsecutiveFramesWithoutAMatch >= 5) {
            existingBlob.blnStillBeingTracked = false;
        }

    }

}


void inline coreprocess::InsertBlobToExistingBlobVector(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs, int &intIndex) {

    existingBlobs[intIndex].currentContour = currentFrameBlob.currentContour;
    existingBlobs[intIndex].currentBoundingRect = currentFrameBlob.currentBoundingRect;

    existingBlobs[intIndex].centerPositions.push_back(currentFrameBlob.centerPositions.back());

    existingBlobs[intIndex].dblCurrentDiagonalSize = currentFrameBlob.dblCurrentDiagonalSize;
    existingBlobs[intIndex].dblCurrentAspectRatio = currentFrameBlob.dblCurrentAspectRatio;

    existingBlobs[intIndex].blnStillBeingTracked = true;
    existingBlobs[intIndex].blnCurrentMatchFoundOrNewBlob = true;
}


void inline coreprocess::InsertNewBlobIntoVector(Blob &currentFrameBlob, std::vector<Blob> &existingBlobs) {

    currentFrameBlob.blnCurrentMatchFoundOrNewBlob = true;

    existingBlobs.push_back(currentFrameBlob);
}


double inline coreprocess::CalcDistanceBetweenPoints(cv::Point point1, cv::Point point2) {

    int intX = abs(point1.x - point2.x);
    int intY = abs(point1.y - point2.y);

    return(sqrt(pow(intX, 2) + pow(intY, 2)));
}


void inline coreprocess::DrawContours(cv::Size MatSize, std::vector<std::vector<cv::Point> > contours) {
    cv::Mat image(MatSize, CV_8UC3, SCALAR_BLACK);

    cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);


}


void inline coreprocess::DrawContours(cv::Size MatSize, std::vector<Blob> blobs) {

    cv::Mat image(MatSize, CV_8UC3, SCALAR_BLACK);

    std::vector<std::vector<cv::Point> > contours;

    for (auto &blob : blobs) {
        if (blob.blnStillBeingTracked == true) {
            contours.push_back(blob.currentContour);
        }
    }

    cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);


}


void inline coreprocess::DrawBlobInfoOnFrame(std::vector<Blob> &blobs, cv::Mat &imgFrame2Copy) {

    for (unsigned int i = 0; i < blobs.size(); i++) {

        if (blobs[i].blnStillBeingTracked == true) {
            cv::rectangle(imgFrame2Copy, blobs[i].currentBoundingRect, SCALAR_RED, 2);

            //            int intFontFace = CV_FONT_HERSHEY_SIMPLEX;
            //            double dblFontScale = blobs[i].dblCurrentDiagonalSize / 60.0;
            //            int intFontThickness = (int)std::round(dblFontScale * 1.0);

            //  cv::putText(imgFrame2Copy, std::to_string(i), blobs[i].centerPositions.back(), intFontFace, dblFontScale, SCALAR_GREEN, intFontThickness);
        }
    }
}
bool inline coreprocess::hasblobcrossed(std::vector<Blob>&blob,int& theline,int& count)
{
    bool crossed = false;
    for(auto obj : blob)
    {
        if(obj.blnStillBeingTracked == true)// && obj.centerPositions.size() > 2)
        {
            //int prev = obj.centerPositions.size() - 2;
            int curr = obj.centerPositions.size() - 1;
            if(obj.centerPositions[0].y > theline && obj.centerPositions[curr].y > theline)
            {

                crossed = true;
            }

        }
    }
    if(crossed)
    {
        count++;
    }
    return crossed;
}



