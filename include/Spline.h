#ifndef SPLINE_H_
#define SPLINE_H_
#include <ngl/BezierCurve.h>
#include "Segments.h"

class Spline{
public:
Spline();
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
};

#endif