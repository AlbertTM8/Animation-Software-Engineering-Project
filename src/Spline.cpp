#include "Spline.h"
<<<<<<< HEAD
#include <iostream>
Spline::Spline(std::shared_ptr<ngl::BezierCurve> _spline){
    m_spline =  _spline;
}
//NEEDS WORK
void Spline::generate_Segments(int _div){
    m_segments.resize(_div);
    for(float i =  0; i<_div; i += 1.0f){
        float seg_index = i/_div;   
        m_segments[i].endpoints = std::make_pair<ngl::Vec3, ngl::Vec3>(m_spline->getPointOnCurve(seg_index), m_spline->getPointOnCurve(seg_index+(1.0f/_div)));
        m_segments[i].arclength = calcLength(seg_index, seg_index+(1/_div));
    }
    // for(int i = 0; i<m_segments.size(); ++i){
    //     std::cout << "segment first" << m_segments[i].endpoints.first.m_x << ", " << m_segments[i].endpoints.first.m_y << ", " << m_segments[i].endpoints.first.m_z << '\n';
    //     std::cout << "segment second" << m_segments[i].endpoints.second.m_x << ", " << m_segments[i].endpoints.second.m_y << ", " << m_segments[i].endpoints.second.m_z << '\n';
    // }
    calcTangents(_div);
    // // calcNormals();
    // // calcWidth();
}
float Spline::calcLength(float _one, float _two){
    float length = 0.0f;
    for(float i = _one; i<_two; i+0.001){
        ngl::Vec3 first = m_spline->getPointOnCurve(i);
        ngl::Vec3 second = m_spline->getPointOnCurve(i+0.001);
        length += sqrt(((first.m_x-second.m_x)*(first.m_x-second.m_x))+ ((first.m_y-second.m_y)*(first.m_x-second.m_x)) + ((first.m_z-second.m_z)
        *(first.m_x-second.m_x)));
    }
    return length;
}

std::shared_ptr<Segment> Spline::setIntersection(ngl::Vec3 _intersection){
    ngl::Vec3 cornerVec;
    ngl::Vec3 cornerNorm;
    std::pair<ngl::Vec3, ngl::Vec3> LRnorms;
    int counter = 0;
    int numofloops = 0;
    const int ind = m_segments.size();
    for(float i = 0; i<=1.0f; i += 0.01f){
        numofloops++;
        if(numofloops >= 100.0f/ind){
            numofloops = 0;
            counter++;
            if(counter == ind){
                counter--;
            }
         }
         if(std::abs(m_spline->getPointOnCurve(i).m_x-_intersection.m_x) <=0.001f &&
         std::abs(m_spline->getPointOnCurve(i).m_y-_intersection.m_y) <=0.001f &&
         std::abs(m_spline->getPointOnCurve(i).m_z-_intersection.m_z) <=0.001f){
            // m_segments[counter].interB = true;
            // return std::make_shared<Segment>(m_segments[counter]);
         }
    }
}

void Spline::addControlPoints(std::vector<ngl::Vec3> _controlPoints){
    m_controlPoints.insert(m_controlPoints.end(), _controlPoints.begin(), _controlPoints.end());

}
void Spline::addControlPoints(ngl::Vec3 _controlPoint){
    m_controlPoints.push_back(_controlPoint);
}

 void Spline::calcTangents(int _div){
    if(m_controlPoints.size() == 4){
        m_segments[0].tangents.first = m_controlPoints[1]- m_controlPoints[0];
        m_segments[0].tangents.second = m_spline->getPointOnCurve((1.0f/_div)+0.001)- m_spline->getPointOnCurve((1.0f/_div)-0.001);
        m_segments[m_segments.size()-1].tangents.first = m_spline->getPointOnCurve((1-(1.0f/_div))+0.001)- m_spline->getPointOnCurve((1-(1.0f/_div))-0.001);
        m_segments[m_segments.size()-1].tangents.second = m_controlPoints[2]- m_controlPoints[3];
    }
    for(int i = 1; i < m_segments.size()-1; ++i){
        m_segments[i].tangents.first = m_spline->getPointOnCurve((i*(1.0f/_div))+0.001)- m_spline->getPointOnCurve((i*(1.0f/_div))-0.001);
        m_segments[i].tangents.second = m_spline->getPointOnCurve((i*(1.0f/_div))+0.001)- m_spline->getPointOnCurve((i*(1.0f/_div))-0.001);
    }
 }

// void Spline::calcNorms(){
//     std::vector<ngl::Vec3> cornerVec;
//     std::vector<ngl::Vec3> cornerNorm;
//     cornerVec.resize(m_segments.size());
//     cornerNorms.resize(m_segments.size());
//     for(int i = 0; i< m_segments.size(); ++i){
//     if(i!=m_corners.size()-1){
//     CornerVec[i] = m_segments[i].tangent.cross(m_segments[i+1].tangent);
//     }
//     else
//     {
//     CornerVec[i] =  m_segments[i].tangent.cross(m_segments[0].tangent);
//     }
//     CornerNorm = m_corners[i].CornerVec;
//     CornerNorm.normalize();
//     }
    
//     for(int i = 0; i< m_corners.size(); ++i){
//     if(i==0){
//         m_normals[i].first=m_corners[i].CornerNorm; 
//         m_normals[i].second=m_corners.back().CornerNorm; 
//     }

//     else
//     {     
//         m_normals[i].first=m_corners[i].CornerNorm;
//         m_normals[i].second=m_corners[i-1].CornerNorm; 
//     }
//     }

// }
// void Spline::calcWidths(){



// }

std::shared_ptr<Segment> Spline::getSeg(ngl::Vec3 _position){
    int counter = 0;
    int numofloops = 0;
    int ind = m_segments.size();
    for(float i = 0; i<1.0f; i=i+0.01f){
        numofloops++;
        if(numofloops == ind){
            numofloops = 0;
            counter++;
        }
        if(std::abs(m_spline->getPointOnCurve(i).m_x-_position.m_x) <=0.001
        && (m_spline->getPointOnCurve(i).m_y-_position.m_y <=0.001)
        && (m_spline->getPointOnCurve(i).m_z-_position.m_z <=0.001)){
            return std::make_shared<Segment>(m_segments[counter]);
        }
    }
=======

Spline::Spline(){
}
Spline::Spline(std::unique_ptr<ngl::BezierCurve> _spline){
    m_spline =  std::move(_spline);
>>>>>>> 147266053939b042db250a79a0f0cc6fdf47bc02
}