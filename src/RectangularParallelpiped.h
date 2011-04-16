#include <string>
#include <sstream>
#include <iostream>
#include "MeshRegion.h"

using namespace std;

class RectangularParallelpiped: public MeshRegion {
  double xMinimum, xMaximum, yMinimum, yMaximum, elevation, height;
  
  int xLocation, yLocation;
  
  // string PART_NAME = "Scint";;
  string PART_NAME;
  // string PART_TYPE = "ag_rpp10";;
  string PART_TYPE;
  
  public:
  
  //This section defines each member of the class
  void setXLocation(int x) {this->xLocation = x;}
  void setYLocation(int y) {this->yLocation = y;}
  void setXMinimum(double xMn) {this->xMinimum = xMn;}
  void setXMaximum(double xMx) {this->xMaximum = xMx;} 
  void setYMinimum(double yMn) {this->yMinimum = yMn;}
  void setYMaximum(double yMx) {this->yMaximum = yMx;}
  void setHeight(double h) {this->height = h;}
  void setElevation(double e) {this->elevation = e;}
    
  
  //This section calls each member of the class for use
  int getXLocation(void) {return this->xLocation;}
  int getYLocation(void) {return this->yLocation;}
  double getXMinimum(void) {return this->xMinimum;}
  double getXMaximum(void) {return this->xMaximum;}
  double getYMinimum(void) {return this->yMinimum;}
  double getYMaximum(void) {return this->yMaximum;}
  double getHeight(void) {return this->height;}
  double getElevation(void) {return this->elevation;}

  RectangularParallelpiped::RectangularParallelpiped(int xLocation, int yLocation, double xMinimum, double xMaximum, double yMinimum, double yMaximum) {
    this->xLocation = xLocation;
    this->yLocation = yLocation;
    this->xMinimum = xMinimum;
    this->xMaximum = xMaximum;
    this->yMinimum = yMinimum;
    this->yMaximum = yMaximum;
  }
    
  RectangularParallelpiped::RectangularParallelpiped(int xLocation, int yLocation, double xMinimum, double xMaximum, double yMinimum, double yMaximum, double height, double elevation) {
    this->xLocation = xLocation;
    this->yLocation = yLocation;
    this->xMinimum = xMinimum;
    this->xMaximum = xMaximum;
    this->yMinimum = yMinimum;
    this->yMaximum = yMaximum;
    this->height = height;
    this->elevation = elevation;
  }


  string toGeo(void) {
    ostringstream strs;
    strs << "'" << PART_NAME << "_" << xLocation << yLocation << "'  '" << PART_TYPE << "' /" << endl;
    strs << xMinimum << ", " << xMaximum << ", " << yMinimum << ", " << yMaximum<< ", " << elevation << ", " << height<<" /" << endl;
    strs << "'NULL' /" << endl;
    return strs.str();
  }
};