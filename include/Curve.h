#ifndef CURVE_H_
#define CURVE_H_

#include "Spline.h"
#include <memory>
#include <ngl/Mat4.h>
#include <ngl/Vec4.h>
#include <iostream>

class Curve{
public:
Curve();
Curve(std::vector<std::shared_ptr<ngl::BezierCurve>> _splines);
void addCurve(std::shared_ptr<ngl::BezierCurve> &_spline);
void addPoint(ngl::Vec3 _point, int _index);
void setup(float _lod);
void resetup(float _LOD);
void draw();
void calculateIntersections();
void rotate(float _degrees, int _axis);
void translate(float _x, float _y, float _z);
void scale(float _x, float _y, float _z);
void calcLength();
void transformSquare();
void straightenSides();
void setHullVisibility();
private:
std::vector<std::shared_ptr<ngl::BezierCurve>> m_splines;
std::vector<std::vector<std::pair<int, int>>> m_intersections;
std::vector<Spline> splines;
std::vector<float> m_lengths; 
bool hullVisibility = false;
void updateIntersections(int _spline);
void centerMiddlePoints(int _index);
void followMiddlePoints(int _index);
bool checkShorter(int _index);
void bulgeLines(int _index);

};


#endif