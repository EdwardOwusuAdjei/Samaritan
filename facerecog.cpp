#include "facerecog.h"

FaceRecog::FaceRecog()
{

}
int FaceRecog::DetectFacesForCut(const string& cascadepath,const cv::Mat &img,vector<Rect> &resol,int& i)//a lil overloading for that face cutting stuff
{

    //    double scale = 1.01 ;
    //    unsigned int minneighbors = 40;
    //    double minsizeratio=0.06;
    //    double maxsizeratio=0.18;
    double scale = 1.1 ;
    unsigned int minneighbors = 5;
    double minsizeratio=0.06;
    double maxsizeratio=0.18;
    CascadeClassifier cascade;
    cascade.load(cascadepath);
    vector<Mat>  training_set;
    double matchconfidence = 0;
    Mat m;
    // vector<Rect> faces;
    //cascade work over here
    Mat tmp;
    int width  = img.size().width,
            height = img.size().height;
    Size minScaleSize = Size(minsizeratio  * width, minsizeratio  * height),
            maxScaleSize = Size(maxsizeratio   * width, maxsizeratio  * height);

    //convert the image to grayscale and normalize histogram:
    if(img.channels() > 1)
    {
        cvtColor(img, tmp, CV_BGR2GRAY);
    }
    else
    {
        tmp = img.clone();
    }
    equalizeHist(tmp, tmp);

    //clear the vector:
    resol.clear();

    //detect faces:1.1
    // cascade.detectMultiScale(tmp, resol, scale,minneighbors, 0, minScaleSize, maxScaleSize);
    cascade.detectMultiScale(tmp, resol, 1.1,3);
}
int FaceRecog::DetectFaces(const string& cascadepath,const cv::Mat &img,vector<cv::Rect> &resol,double scale ,unsigned int minneighbors,double minsizeratio,double maxsizeratio)
{
    CascadeClassifier cascade;
    cascade.load(cascadepath);
    // vector<Mat>  training_set;
    double matchconfidence = 0;
    Mat m;
    // vector<Rect> faces;
    //cascade work over here
    Mat tmp;
    int width  = img.size().width,
            height = img.size().height;
    Size minScaleSize = Size(minsizeratio  * width, minsizeratio  * height),
            maxScaleSize = Size(maxsizeratio   * width, maxsizeratio  * height);

    //convert the image to grayscale and normalize histogram:
    if(img.channels() > 1)
    {
        cvtColor(img, tmp, CV_BGR2GRAY);
    }
    else
    {
        tmp = img.clone();
    }
    equalizeHist(tmp, tmp);

    //clear the vector:
    resol.clear();

    //detect faces:
    // cascade.detectMultiScale(tmp, resol, scale,minneighbors, 0, minScaleSize, maxScaleSize);
    cascade.detectMultiScale(tmp, resol, 1.1,3);
    //fills up resol vector for me :)
    //cascade ends here
    for (vector<Rect>::const_iterator face = resol.begin() ; face != resol.end() ; face++){
        Scalar colour = Scalar(0,0,255);
        int edge_size = max(face->width, face->height);
        Rect square(face->x, face->y, edge_size, edge_size);
        Mat face_img = Mat(tmp,square);
        //  Mat face_img = Mat(*face,tmp);
        //Mat face_imgg = ;
        double confidence = 0;
        bool face_match = false;
        bool has_match  = false;
        //try to recognize the face:
        //  int b = FaceRecognize(face_img, confidence);
        if (FaceRecognize(face_img, confidence)){
            colour = Scalar(0,255,0);
            has_match = true;
            face_match = true;
            matchconfidence = confidence;
        }

        Point center(face->x + face->width * 0.5, face->y + face->height * 0.5);
        //face radius  0.75 is chosen
        //circle thickness after detection  2.5
        if(confidence < 20)
        {
            circle(img, center, 0.75 * face->width, Scalar(255,255,255), 2.5, CV_AA, 0);
        }
        else
        {
            circle(img, center, 0.75 * face->width, colour, 2.5, CV_AA, 0);
        }
        //m;

    }

}

int FaceRecog::FaceRecognize(const cv::Mat &face, double &confidence)
{
    //add exception  handling to all models
    //Size _faceSize;

    Mat gray;
    int label;
    if(face.channels()>1)
    {
        cvtColor(face, gray, CV_BGR2GRAY);
    }
    else
    {
        gray = face;
    }
    resize(gray, gray, _faceSize);
    _model->predict(gray, label, confidence);
    return label ;
}

int FaceRecog::train(const vector<Mat> &imgs, int radius, int neighbors,int grid_x, int grid_y, double threshold) {
    //all images are faces of the same person, so initialize the same label for all.
    vector<int> labels(imgs.size());
    for (vector<int>::iterator it = labels.begin() ; it != labels.end() ; *(it++) = 10);
    _faceSize =  Size(imgs[0].size().width, imgs[0].size().height);

    // build recognizer model:
    //  _model = cv::face::createLBPHFaceRecognizer(radius, neighbors, grid_x, grid_y);
    _model = cv::face::createLBPHFaceRecognizer();
    vector<Mat> test;

    readtraining("/home/edward/build-ComputerVision-CVision-Debug/original/paths.txt",test);
    // _model->train(imgs, labels);
    _model->train(test,labels);
//    _model->train(test,labels);
//    _model->train(test,labels);
//    _model->train(test,labels);
//    _model->train(test,labels);

}

void FaceRecog::readtraining(const string &path, vector<Mat> &images) {
    ifstream file(path.c_str());
    string paths;
    // string path;
    while (getline(file, paths)) {
        images.push_back(imread(paths, CV_LOAD_IMAGE_GRAYSCALE));
    }
}
