#include "Spline.h"

Spline::Spline(){
}
Spline::Spline(std::unique_ptr<ngl::BezierCurve> _spline){
    m_spline =  std::move(_spline);
}