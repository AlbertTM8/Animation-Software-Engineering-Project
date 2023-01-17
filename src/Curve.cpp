#include "Curve.h"
#include <ngl/ShaderLib.h>
#include <iostream>

Curve::Curve(){
    m_splines.push_back(std::make_shared<ngl::BezierCurve>());
    m_splines.push_back(std::make_shared<ngl::BezierCurve>());
    m_splines.push_back(std::make_shared<ngl::BezierCurve>());
    m_splines.push_back(std::make_shared<ngl::BezierCurve>());
    m_splines.push_back(std::make_shared<ngl::BezierCurve>());
    m_splines.push_back(std::make_shared<ngl::BezierCurve>());
    m_splines.push_back(std::make_shared<ngl::BezierCurve>());
    m_splines.push_back(std::make_shared<ngl::BezierCurve>());
    m_splines.push_back(std::make_shared<ngl::BezierCurve>());
    m_splines.push_back(std::make_shared<ngl::BezierCurve>());
    m_splines.push_back(std::make_shared<ngl::BezierCurve>());
    m_splines.push_back(std::make_shared<ngl::BezierCurve>());
    splines.push_back(Spline(m_splines[0]));
    splines.push_back(Spline(m_splines[1]));
    splines.push_back(Spline(m_splines[2]));
    splines.push_back(Spline(m_splines[3]));
    splines.push_back(Spline(m_splines[4]));
    splines.push_back(Spline(m_splines[5]));
    splines.push_back(Spline(m_splines[6]));
    splines.push_back(Spline(m_splines[7]));
    splines.push_back(Spline(m_splines[8]));
    splines.push_back(Spline(m_splines[9]));
    splines.push_back(Spline(m_splines[10]));
    splines.push_back(Spline(m_splines[11]));
 }

Curve::Curve(std::vector<std::shared_ptr<ngl::BezierCurve>> _splines){
    m_splines = _splines;
    for(int i = 0; i< _splines.size(); ++i){
        splines[0]= Spline(m_splines[0]);
    }
    calculateIntersections();
    
}


// void Curve::addCurve(std::unique_ptr<ngl::BezierCurve> &_spline){
//     std::shared_ptr<ngl::BezierCurve> spline = std::make_unique<ngl::BezierCurve>();
//     spline = std::move(_spline);
//     m_splines.push_back(std::move(_spline));
//     splines.push_back(Spline(std::move(_spline)));
// }

void Curve::addPoint(ngl::Vec3 _point, int _index){
    m_splines[_index]->addPoint(_point);
    splines[_index].addControlPoints(_point);
}



void Curve::setup(float _LOD){
    for(int i = 0; i<m_splines.size(); ++i){
        m_splines[i]->setLOD(_LOD);
        m_splines[i]->createKnots();
        m_splines[i]->createVAO();
        splines[i].generate_Segments(5);
 }

}
void Curve::resetup(float _LOD){
    for(int i = 0; i<8; ++i){
        m_splines[i]->setLOD(_LOD);
        m_splines[i]->createKnots();
        m_splines[i]->createVAO();
        splines[i].generate_Segments(5);
 }

}
void Curve::draw(){
    for(int i = 0; i<m_splines.size(); ++i){
        ngl::ShaderLib::use("nglColourShader");
        ngl::ShaderLib::setUniform("Colour", 1.0f, 1.0f, 1.0f, 1.0f);
        m_splines[i]->draw();
        glPointSize(4);
        // ngl::ShaderLib::setUniform("Colour", 0.0f, 1.0f, 0.0f, 1.0f);
        // m_splines[i]->drawControlPoints();
        // glPointSize(1);
        // ngl::ShaderLib::setUniform("Colour", 1.0f, 0.0f, 0.0f, 1.0f);
        // m_splines[i]->drawHull();
    }
}

void Curve::rotate(float _degrees, int _axis){
    const ngl::Mat4 rotational_matrix_x = ngl::Mat4(1, 0, 0, 0, 0 , cos(_degrees), -sin(_degrees), 0, 0, sin(_degrees), cos(_degrees), 0, 0, 0, 0, 1);
    const ngl::Mat4 rotational_matrix_y = ngl::Mat4(cos(_degrees), 0, sin(_degrees), 0,0, 1, 0, 0, -sin(_degrees), 0, cos(_degrees), 0, 0, 0, 0, 1);
    const ngl::Mat4 rotational_matrix_z = ngl::Mat4(cos(_degrees), sin(_degrees), 0, 0,-sin(_degrees), cos(_degrees), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    //X Axis
    if( _axis == 0){
        std::vector<ngl::Vec3> controlPoints;
        for(int i  = 0; i < 4; ++i){
            controlPoints = m_splines[i]->getControlPoints();
            std::shared_ptr<ngl::BezierCurve> placeholder = std::make_shared<ngl::BezierCurve>(); 
            for(int j = 0; j<4; ++j){
                ngl::Vec4 Vector4 = {{controlPoints[j]}, 1};
                Vector4 = rotational_matrix_x * Vector4;
                placeholder->addPoint(Vector4.toVec3());
            }
            m_splines[i] = placeholder;
        }
        for(int i = 0; i < 4; ++i){
        updateIntersections(i);
        }

    }
    //Y-Axis
    else if(_axis == 1){
        std::vector<ngl::Vec3> controlPoints;
        for(int i  = 0; i < 4; ++i){
            controlPoints = m_splines[i]->getControlPoints();
            std::shared_ptr<ngl::BezierCurve> placeholder = std::make_shared<ngl::BezierCurve>(); 
            for(int j = 0; j<4; ++j){
                ngl::Vec4 Vector4 = {{controlPoints[j]}, 1};
                Vector4 = rotational_matrix_y * Vector4; 
                placeholder->addPoint(Vector4.toVec3());
            }
            m_splines[i] = placeholder;
        }
        for(int i = 0; i < 4; ++i){
        updateIntersections(i);
        }
    }
    //Z-Axis
    else{
        std::vector<ngl::Vec3> controlPoints;
        for(int i  = 0; i < 4; ++i){
            controlPoints = m_splines[i]->getControlPoints();
            std::shared_ptr<ngl::BezierCurve> placeholder = std::make_shared<ngl::BezierCurve>(); 
            for(int j = 0; j<4; ++j){
                ngl::Vec4 Vector4 = {{controlPoints[j]}, 1};
                Vector4 = rotational_matrix_z * Vector4;
                placeholder->addPoint(Vector4.toVec3());
            }
            m_splines[i] = placeholder;

        }
        for(int i = 0; i < 4; ++i){
        updateIntersections(i);
        }
    }

}

void Curve::translate(float _x, float _y, float _z){
    const ngl::Mat4 translation_matrix = ngl::Mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, _x, _y, _z, 1);
        std::vector<ngl::Vec3> controlPoints;
        for(int i  = 0; i < 4; ++i){
            controlPoints = m_splines[i]->getControlPoints();
            std::shared_ptr<ngl::BezierCurve> placeholder = std::make_shared<ngl::BezierCurve>(); 
            for(int j = 0; j < 4; ++j){
                ngl::Vec4 Vector4 = {{controlPoints[j]}, 1};
                Vector4 = translation_matrix * Vector4;
                placeholder->addPoint(Vector4.toVec3());
            }
            m_splines[i] = placeholder;
        }
        for(int i = 0; i < 4; ++i){
        updateIntersections(i);
        }
}


void Curve::calculateIntersections(){
    m_intersections.resize(m_splines.size()*2);
    for(int a = 0;a < m_splines.size(); ++a){
        m_intersections[(a*2)].push_back(std::make_pair(a, 0));
        m_intersections[(a*2)+1].push_back(std::make_pair(a, 3));
        for(int b = 0;b < m_splines.size();++b){
            if(a != b){
            for(float i = 0; i<=1.0f; i += 0.01f){
                for(float j = 0; j<=1.0f; j += 0.01f){
                if(std::abs(m_splines[a]->getPointOnCurve(i).m_x-m_splines[b]->getPointOnCurve(j).m_x)<=0.001f &&
                std::abs(m_splines[a]->getPointOnCurve(i).m_y-m_splines[b]->getPointOnCurve(j).m_y)<=0.001f &&
                std::abs(m_splines[a]->getPointOnCurve(i).m_z-m_splines[b]->getPointOnCurve(j).m_z)<=0.001f){
                    //std::shared_ptr<Segment> one = splines[a].setIntersection(m_splines[a]->getPointOnCurve(i));
                    //std::shared_ptr<Segment> two = splines[b].setIntersection(m_splines[b]->getPointOnCurve(j));
                        if(i >= 0.9f){
                        if(j>=0.9f){
                            if(!(std::find(m_intersections[(a*2)+1].begin(), m_intersections[(a*2)+1].end(), std::pair<int, int>(b, 3)) != m_intersections[(a*2)+1].end())) {
                                m_intersections[(a*2)+1].push_back({b, 3});
                                int end = m_intersections[a*2+1].size()-1;

                        }  
                        }
                        else if(j<=0.1f){
                            if(!(std::find(m_intersections[(a*2)+1].begin(), m_intersections[(a*2)+1].end(), std::pair<int, int>(b, 0)) != m_intersections[(a*2)+1].end())) {
                                m_intersections[(a*2)+1].push_back({b, 0}); 
                                int end = m_intersections[a*2+1].size()-1;

                            }
                        }
                        }
                        else if(i <= 0.1f){
                        if(j>=0.9f){
                            if(!(std::find(m_intersections[(a*2)].begin(), m_intersections[(a*2)].end(), std::pair<int, int>(b, 3)) != m_intersections[(a*2)].end())) {
                                m_intersections[(a*2)].push_back({b, 3});
                                int end = m_intersections[a*2].size()-1;
                        
                        }  
                         }
                        else if(j<=0.1f){
                            if(!(std::find(m_intersections[(a*2)].begin(), m_intersections[(a*2)].end(), std::pair<int, int>(b, 0)) != m_intersections[(a*2)].end())) {
                                m_intersections[(a*2)].push_back({b, 0});
                                int end = m_intersections[a*2].size()-1;


                        }   
                        }
                        }
                    // std::cout << "spline one " << one->endpoints.first.m_x << ", " << one->endpoints.first.m_y << ", " << one->endpoints.first.m_z << '\n';
                    // std::cout << "spline two " << two->endpoints.first.m_x << ", " << two->endpoints.first.m_y << ", " << two->endpoints.first.m_z << '\n';
                    // //TEST RETURN FUNCTIONS
                }

            }
        }
        }
    }
    } 
}
void  Curve::updateIntersections(int _spline){
            std::vector<ngl::Vec3> oldPoints = m_splines[m_intersections[_spline*2][0].first]->getControlPoints();
            for(int i = 1; i <= 2; ++i){
            std::vector<ngl::Vec3> Points = m_splines[m_intersections[_spline*2][i].first]->getControlPoints();
            Points[m_intersections[_spline*2][i].second] = oldPoints[m_intersections[_spline*2][0].second];
            std::shared_ptr<ngl::BezierCurve> placeholder = std::make_shared<ngl::BezierCurve>(); 
            for(int j = 0; j<4; ++j){
            placeholder->addPoint(Points[j]);
            }
            m_splines[m_intersections[_spline*2][i].first] = placeholder;
            }


            
        oldPoints = m_splines[m_intersections[(_spline*2)+1][0].first]->getControlPoints();
            for(int i = 1; i <= 2; ++i){
            std::vector<ngl::Vec3> Points = m_splines[m_intersections[(_spline*2)+1][i].first]->getControlPoints();
            Points[m_intersections[(_spline*2)+1][i].second] = oldPoints[m_intersections[(_spline*2)+1][0].second];
            std::shared_ptr<ngl::BezierCurve> placeholder = std::make_shared<ngl::BezierCurve>(); 
            for(int j = 0; j<4; ++j){
            placeholder->addPoint(Points[j]);
            }
            m_splines[m_intersections[(_spline*2)+1][i].first] = placeholder;
            }

}


void Curve::calcLength(){
    m_lengths.resize(m_splines.size());
    for(int a = 0; a < m_splines.size(); ++a){
    float length = 0.0f;
    for(float i = 0; i<0.999; i=i+0.01f){
        ngl::Vec3 first = m_splines[a]->getPointOnCurve(i);
        ngl::Vec3 second = m_splines[a]->getPointOnCurve(i+0.01f);
        length += std::sqrt(((first.m_x-second.m_x)*(first.m_x-second.m_x))+ ((first.m_y-second.m_y)*(first.m_y-second.m_y)) + ((first.m_z-second.m_z)
        *(first.m_z-second.m_z)));
    }
    m_lengths[a] = length;
    std::cout<< "length of " << a << " is " << m_lengths[a] << '\n';
    }

}