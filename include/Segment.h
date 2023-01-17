#ifndef SEGMENT_H_
#define SEGMENT_H_

#include <cstddef>
#include <vector>
#include <utility>
#include <ngl/Vec3.h>
class Segment
{
public:
<<<<<<< HEAD
    Segment(std::pair<ngl::Vec3, ngl::Vec3> _endpoints, float _arclength );
=======
    Segment(std::pair<ngl::Vec3, ngl::Vec3> _endpoints, float _arclength, float _width, std::pair<ngl::Vec3, ngl::Vec3> normals, std::pair<ngl::Vec3, ngl::Vec3> _tangents);
>>>>>>> 147266053939b042db250a79a0f0cc6fdf47bc02
    std::pair<ngl::Vec3, ngl::Vec3> getEndpoints() const;
    void setEndpoint(ngl::Vec3 _endpoint, int _index);

    float getLen() const;
    void setLen(float _length, int _index);

    float getWidth() const;
    void setWidth(float _width);

    std::pair<ngl::Vec3, ngl::Vec3> getTan() const;
    void setTan(ngl::Vec3 _tangent, int _index);
    void setTan(ngl::Vec3 _tangent1, ngl::Vec3 _tangent2);

    std::pair<ngl::Vec3, ngl::Vec3> getNorms() const;
    void setNorm(ngl::Vec3 _normal, int _index);
    void setNorm(ngl::Vec3 _normal1, ngl::Vec3 _normal);
private:
    std::pair<ngl::Vec3, ngl::Vec3> endpoints;
    float arclength;
    float width;
    std::pair<ngl::Vec3, ngl::Vec3> normals;
    std::pair<ngl::Vec3, ngl::Vec3> tangents;
};

#endif