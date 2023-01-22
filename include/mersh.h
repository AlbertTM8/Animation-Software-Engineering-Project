#ifndef CURVE_H_
#define CURVE_H_
#include "Curve.h"
class Mesh{
public:
Mesh();
Mesh(std::vector<Curve> _curves);


private:
std::vector<curve> m_curves;
};


#endif