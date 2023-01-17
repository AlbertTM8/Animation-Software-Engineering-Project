#include <Segment.h>

Segment::Segment(std::pair<ngl::Vec3, ngl::Vec3> _endpoints, float _arclength){
    endpoints = _endpoints;
    arclength = _arclength;
}
