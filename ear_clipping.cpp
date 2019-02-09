#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include "triangle.h"
using namespace cv;
using namespace std;


/***********************
  THE DATA
***********************/
vector<Point> points;
vector<Triangle> triangles;


/***********************
  THE GUI
***********************/
string winName = "Points template";
Mat3b canvas;
#define CANVAS_SIZE 500
Rect buttonReset;
Rect buttonUpdate;
string buttonResetText("Reset");
string buttonUpdateText("Update");
string msgYes("Yes");
string msgNo("No");
#define BUTTON_HEIGHT 30
#define BUTTON_WEIGHT 100

Scalar gray=Scalar(200, 200, 200);
Scalar red=Scalar(0, 0, 255);
#define POINT_RADIUS 3


/***********************
  DATA METHODS
***********************/

bool are_right_oriented(Point &a,Point &b,Point &c){
  // TODO
  return false;
}

bool inTriangle(Point &a,Point &b,Point &c,Point &x){
  // TODO
  return false;
}


bool isEar(vector<Point> &points, int i){
  // TODO .. i entspricht dem Punkt points[i] der untersucht wird
  return false;
}

int getEar(vector<Point> &points){
  int n=points.size();
  for(int i=0;i<n;i++)
    if(isEar(points,i))
       return i;
  // This should never be reached by Two-Ears-Theorem
  return -1;
}

Triangle getEarTriangle(vector<Point> &points,int i){
  int n=points.size();
    
  Point p0,p1,p2;
  int i0,i2;
  
  if(i==0)
    i0=n-1;
  else
    i0=i-1;

  if(i==n-1)
    i2=0;
  else
    i2=i+1;

  p1=points[i];
  p0=points[i0];
  p2=points[i2];

  return Triangle(p0,p1,p2);
}

/***********************
  INPUT
***********************/

void read_points(){
  ifstream myfile;
  points.clear();
  myfile.open ("points.txt");
  int n;
  myfile >> n;
  int x,y;
  for(int i=0;i<n;i++){
    myfile >> x >> y;
    points.push_back(Point(x,y));
  }
  myfile.close();
}

/***********************
  THE GUI METHODS
***********************/

void MyResetButton(){
  canvas(buttonReset) = Vec3b(200,200,200); //gray
  putText(canvas(buttonReset), buttonResetText, Point(buttonReset.width*0.2, buttonReset.height*0.7), FONT_HERSHEY_PLAIN, 1.2, Scalar(0,0,0));
}
void MyUpdateButton(string text,int b,int g,int r){
  canvas(buttonUpdate) = Vec3b(b,g,r);//200,200,200); //gray
  putText(canvas(buttonUpdate), text, Point(buttonUpdate.width*0.2, buttonUpdate.height*0.7), FONT_HERSHEY_PLAIN, 1.2, Scalar(0,0,0));
}

void setup(){
  // The canvas
  canvas = Mat3b(CANVAS_SIZE, CANVAS_SIZE, Vec3b(255,255,255));

  // Your buttons
  buttonReset = Rect(10,10,BUTTON_WEIGHT,BUTTON_HEIGHT);
  buttonUpdate = Rect(10,50,BUTTON_WEIGHT,BUTTON_HEIGHT);

  // Draw the buttons
  MyResetButton();
  MyUpdateButton(buttonUpdateText,200,200,200);
}

void MyPoint( Mat &img, Point &center ,int b,int g,int r)
{
 int thickness = -1;
 int lineType = 8;

 circle( img,
         center,
         POINT_RADIUS,
         Scalar( b, g, r),
         thickness,
         lineType );
}

void MyLine( Mat img, Point &start, Point &end ,int b,int g,int r)
{
  int thickness = 1;//2;
  int lineType = LINE_8;
  line( img,
    start,
    end,
    Scalar( b, g, r ),
    thickness,
    lineType );
}

void MyTriangle( Mat img, Triangle &t)
{
  MyLine(img,t.A,t.B,0,0,0);
  MyLine(img,t.B,t.C,0,0,0);
  MyLine(img,t.C,t.A,0,0,0);
}



void draw_points(){
  setup();

  int n=points.size();
  for(int i=0;i<n;i++)
    {
      if(i<n-1)
	MyLine(canvas,points[i],points[i+1],0,0,0);
    }

  if(n>2)
    MyLine(canvas,points[n-1],points[0],0,0,0);
  
  for(int i=0;i<n;i++)
    {
      MyPoint(canvas,points[i],0,0,0);
    }
}

void draw_triangles(){
  int n=triangles.size();
  for(int i=0;i<n;i++)
    MyTriangle(canvas,triangles[i]);
}

void callBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN)
      {
	Point point=Point(x, y);
	if (buttonReset.contains(point))
	  {
	    cout << "Reset button clicked!" << endl;
	    rectangle(canvas, buttonReset, red);
	    //triangles.erase(points.begin(),points.end());
	    triangles.clear();
	    read_points();
	    draw_points();
	    imshow(winName, canvas);
	  }
	else if (buttonUpdate.contains(point))
	  {
	    cout << "Update button clicked!" <<endl;
	    rectangle(canvas, buttonUpdate, red);
	    if(points.size()>2){
	      int i=getEar(points);
	      triangles.push_back(getEarTriangle(points,i));
	      points.erase(points.begin() + i);
	      draw_points();
	      draw_triangles();
	      imshow(winName, canvas);
	    }
	  }
    }
}

int main() 
{
  read_points();
  draw_points();

  // Setup callback function
  namedWindow(winName);
  setMouseCallback(winName, callBackFunc);

  imshow(winName, canvas);
  waitKey();

  return 0;
}
