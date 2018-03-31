#ifndef COUNTING_H
#define COUNTING_H
#include <vector>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
class counting
{
public:
    counting();
    std::vector<int> crossedline( std::vector<cv::Point> _contour);
};

#endif // COUNTING_H
