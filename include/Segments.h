#ifndef SEGMENT_H_
#define SEGMENT_H_

#include <cstddef>
#include <utility>
#include <ngl/Vec3.h>
struct Segment
{
    std::pair<ngl::Vec3, ngl::Vec3> endpoints;
    float arclength;
    float width;
    std::pair<ngl::Vec3, ngl::Vec3> LRnormals;
    std::pair<ngl::Vec3, ngl::Vec3> tangents;
    bool interB = false;
};

#endif