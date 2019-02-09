#include <opencv2/opencv.hpp>
using namespace cv;

class Triangle{
 public:
  Point A;
  Point B;
  Point C;
  Triangle(Point X,Point Y,Point Z);
};

Triangle::Triangle(Point X,Point Y,Point Z){
  A=X;
  B=Y;
  C=Z;
}
