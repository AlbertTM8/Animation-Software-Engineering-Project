#ifndef Intersection_H_
#define Intersection_H_

#include <cstddef>
#include <iostream>
#include <vector>
#include <utility>
#include <ngl/Vec3.h>
#include <ngl/Mat3.h>
#include <CornerStruct.h>
class Intersection
{
public:
    Intersection(std::vector<ngl::Vec3> _tangents, std::vector<float> _lengths, ngl::Vec3 _location);
    std::vector<ngl::Vec3> getTan() const;
    void setTan(ngl::Vec3 _tangent, int _index);

    std::vector<float> getLen() const;
    void setLen(float _length, int _index);

    ngl::Vec3 getLoc() const;
    void setLoc(ngl::Vec3 _location);

    std::vector<Corner> getCorn() const;
    void setCorn(Corner _corner, int _index);

    std::vector<std::pair<ngl::Vec3, ngl::Vec3>> getNorms() const;
    void setNorm(ngl::Vec3 _corner, int _index, bool _ind);
    void setNorm(ngl::Vec3 _corner1, ngl::Vec3 _corner2, int _index);

private:
    ngl::Vec3 location;
    std::vector<ngl::Vec3> m_tangents;
    std::vector<float> m_lengths;
    std::vector<Corner> m_corners;
    std::vector<std::pair<ngl::Vec3, ngl::Vec3>> m_normals;
};

#endif