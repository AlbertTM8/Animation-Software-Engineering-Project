#ifndef SPLINE_H_
#define SPLINE_H_
#include <ngl/BezierCurve.h>
<<<<<<< HEAD
#include "Segments.h"
=======
>>>>>>> 147266053939b042db250a79a0f0cc6fdf47bc02

class Spline{
public:
Spline();
<<<<<<< HEAD
Spline(std::shared_ptr<ngl::BezierCurve> _spline);
void generate_Segments(int _div);
std::shared_ptr<Segment> setIntersection(ngl::Vec3 _intersection);
void addControlPoints(std::vector<ngl::Vec3> _controlPoints);
void addControlPoints(ngl::Vec3 _controlPoints);
std::shared_ptr<Segment> getSeg(ngl::Vec3 _position);
// std::unique_ptr<Segment> getSeg(int _ind);
private:
std::shared_ptr<ngl::BezierCurve> m_spline;
std::vector<Segment> m_segments;
std::vector<ngl::Vec3> m_controlPoints;
std::vector<ngl::Vec3> m_intersections;
float calcLength(float _one, float _two);
void calcNorms();
void calcWidths();
void calcTangents(int _div);
=======
Spline(std::unique_ptr<ngl::BezierCurve> _spline);
private:
std::shared_ptr<ngl::BezierCurve> m_spline;
>>>>>>> 147266053939b042db250a79a0f0cc6fdf47bc02
};

#endif