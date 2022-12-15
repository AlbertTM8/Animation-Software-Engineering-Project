#ifndef CURVE_H_
#define CURVE_H_

#include "Spline.h"
#include <ngl/BezierCurve.h>
#include <memory>

class Curve{
public:
Curve();
Curve(std::vector<std::unique_ptr<ngl::BezierCurve>> _splines);
void addCurve(std::unique_ptr<ngl::BezierCurve> &_spline);
void addPoint(ngl::Vec3 _point, int _index);
void setup(float _lod);
void draw();

private:
std::vector<std::unique_ptr<ngl::BezierCurve>> m_splines;
std::vector<Spline> splines;
};



#endif