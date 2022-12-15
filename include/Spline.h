#ifndef SPLINE_H_
#define SPLINE_H_
#include <ngl/BezierCurve.h>

class Spline{
public:
Spline();
Spline(std::unique_ptr<ngl::BezierCurve> _spline);
private:
std::shared_ptr<ngl::BezierCurve> m_spline;
};

#endif