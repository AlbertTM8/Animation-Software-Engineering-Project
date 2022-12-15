#include <Segment.h>

Segment::Segment(std::pair<ngl::Vec3, ngl::Vec3> _endpoints, float _arclength, float _width, std::pair<ngl::Vec3, ngl::Vec3> _normals, std::pair<ngl::Vec3, ngl::Vec3> _tangents){
    endpoints = _endpoints;
    arclength = _arclength;
    width = _width;
    normals = _normals;
    tangents = _tangents;
}
