#ifndef FACEREC_H
#define FACEREC_H


#include <vector>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/face/facerec.hpp>
#include <opencv2/objdetect/objdetect.hpp>
using namespace cv;
using namespace std;
class FaceRecog
{
    Ptr<cv::face::FaceRecognizer> _model;
    Size _faceSize;
public:
    FaceRecog();
    //readtraining -> train -> DetectFaces -> Recognize
    int DetectFacesForCut(const string& cascadepath,const cv::Mat &img,vector<Rect> &resol,int& i);
    int DetectFaces(const string& cascadepath,const cv::Mat &img,vector<cv::Rect> &resol,double scale = 1.01 ,unsigned int minneighbors = 40,double minsizeratio=0.06,double maxsizeratio=0.18);
    int FaceRecognize(const cv::Mat &face, double &confidence);
    int train(const vector<Mat> &imgs, int radius, int neighbors,int grid_x, int grid_y, double threshold);
    void readtraining(const string &path, vector<Mat> &images);
};

#endif // FACEREC_H
