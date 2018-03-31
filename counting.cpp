#include "counting.h"

counting::counting()
{

}

std::vector<int> counting::crossedline( std::vector<cv::Point> _contour)
{
    cv::Rect BoundingRect = cv::boundingRect(_contour);

    cv::Point Center;

    Center.x = (BoundingRect.x + BoundingRect.x + BoundingRect.width) / 2;
    Center.y = (BoundingRect.y + BoundingRect.y + BoundingRect.height) / 2;

    return std::vector<int>(Center.x,Center.y);
}
