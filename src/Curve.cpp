#include "Curve.h"
#include <ngl/ShaderLib.h>

Curve::Curve(){
    m_splines.push_back(std::make_unique<ngl::BezierCurve>());
    m_splines.push_back(std::make_unique<ngl::BezierCurve>());
    m_splines.push_back(std::make_unique<ngl::BezierCurve>());
    m_splines.push_back(std::make_unique<ngl::BezierCurve>());
    splines.push_back(Spline());
    splines.push_back(Spline());
    splines.push_back(Spline());
    splines.push_back(Spline());
 }

Curve::Curve(std::vector<std::unique_ptr<ngl::BezierCurve>> _splines){
    m_splines = std::move(_splines);
    for(int i = 0; i< _splines.size(); ++i){
        splines[0]= Spline(std::move(m_splines[0]));
    }
    
}


void Curve::addCurve(std::unique_ptr<ngl::BezierCurve> &_spline){
    std::shared_ptr<ngl::BezierCurve> spline = std::make_unique<ngl::BezierCurve>();
    spline = std::move(_spline);
    m_splines.push_back(std::move(_spline));
    splines.push_back(Spline(std::move(_spline)));
}
void Curve::addPoint(ngl::Vec3 _point, int _index){
    m_splines[_index]->addPoint(_point);
}

void Curve::setup(float _LOD){
    for(int i = 0; i<4; ++i){
        m_splines[i]->setLOD(_LOD);
        m_splines[i]->createKnots();
        m_splines[i]->createVAO();
 }
}
void Curve::draw(){
    for(int i = 0; i<4; ++i){
        ngl::ShaderLib::use("nglColourShader");
        ngl::ShaderLib::setUniform("Colour", 1.0f, 1.0f, 1.0f, 1.0f);
        m_splines[i]->draw();

        glPointSize(4);
        ngl::ShaderLib::setUniform("Colour", 0.0f, 1.0f, 0.0f, 1.0f);
        m_splines[i]->drawControlPoints();

        glPointSize(1);
        ngl::ShaderLib::setUniform("Colour", 1.0f, 0.0f, 0.0f, 1.0f);
        m_splines[i]->drawHull();
    }
}



