// Vic McGowen and Dan Goldberg Ray Tracer
// Point class

#ifndef POINT_H_
#define POINT_H_

// Included Dependencies
#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include "../aux/vector.h"

class Point{

public:
	Point(); //public default constructor
	Point(double x, double y, double z); 
  Point(Vector v);
	virtual ~Point();
	double distance(const Point& other);
	void transform(const Eigen::Matrix4d mat){point_.transform(mat);};

	double getX()const{ return point_.getX();};
	double getY()const{ return point_.getY();};
	double getZ()const{ return point_.getZ();};

	Vector operator-(const Point& b) const;
  	double& operator()(const int index);

private:
	Vector point_;
};

#endif
