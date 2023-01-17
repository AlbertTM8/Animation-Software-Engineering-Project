#include <Segment.h>

<<<<<<< HEAD
Segment::Segment(std::pair<ngl::Vec3, ngl::Vec3> _endpoints, float _arclength){
    endpoints = _endpoints;
    arclength = _arclength;
=======
Segment::Segment(std::pair<ngl::Vec3, ngl::Vec3> _endpoints, float _arclength, float _width, std::pair<ngl::Vec3, ngl::Vec3> _normals, std::pair<ngl::Vec3, ngl::Vec3> _tangents){
    endpoints = _endpoints;
    arclength = _arclength;
    width = _width;
    normals = _normals;
    tangents = _tangents;
>>>>>>> 147266053939b042db250a79a0f0cc6fdf47bc02
}
