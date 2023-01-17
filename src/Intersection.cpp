#include "Intersection.h"
 engths,  ngl::Vec3 _location) : m_tangents {_tangents}, m_lengths {_lengths}, location {_location}{
    m_corners.resize(_tangents.size());
    m_normals.resize(_tangents.size());
    for(int i = 0; i< m_corners.size(); ++i){
    if(i!=m_corners.size()-1){
    m_corners[i].CornerVec = m_tangents[i].cross(m_tangents[i+1]);
    }
    else
    {
    m_corners[i].CornerVec = m_tangents[i].cross(m_tangents[0]);
    }
    m_corners[i].CornerNorm = m_corners[i].CornerVec;
    m_corners[i].CornerNorm.normalize();
    }
    
    for(int i = 0; i< m_corners.size(); ++i){
    if(i==0){
        m_normals[i].first=m_corners[i].CornerNorm; 
        m_normals[i].second=m_corners.back().CornerNorm; 
    }

    else
    {     
        m_normals[i].first=m_corners[i].CornerNorm;
        m_normals[i].second=m_corners[i-1].CornerNorm; 
    }
    }

}
    std::vector<ngl::Vec3> Intersection::getTan() const{
        return m_tangents;
    }

    void Intersection::setTan(ngl::Vec3 _tangent, int _index){
        m_tangents[_index] = _tangent;
    }
    std::vector<float> Intersection::getLen() const{
        return m_lengths;
    }
    void Intersection::setLen(float _length, int _index){
        m_lengths[_index] = _length;
    }
    ngl::Vec3 Intersection::getLoc() const{
        return location;
    }
    void Intersection::setLoc(ngl::Vec3 _location){
        location = _location;
    }

    std::vector<Corner> Intersection::getCorn() const{
        return m_corners;
    }
    void Intersection::setCorn(Corner _corner, int _index){
        m_corners[_index] = _corner;
    }

    std::vector<std::pair<ngl::Vec3, ngl::Vec3>> Intersection::getNorms() const{
        return m_normals;
    }
    void Intersection::setNorm(ngl::Vec3 _corner, int _index, bool _ind){
        if(_ind = 0){
        m_normals[_index].first = _corner;
        }
        else {
        m_normals[_index].second = _corner;
        }
    }
    void Intersection::setNorm(ngl::Vec3 _corner1, ngl::Vec3 _corner2, int _index){

        m_normals[_index].first = _corner1;
     
        m_normals[_index].second = _corner2;
  
    }