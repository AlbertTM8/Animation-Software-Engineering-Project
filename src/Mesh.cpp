#include "Mesh.h"
#include <ngl/ShaderLib.h>
#include <iostream>
//Constructor for Mesh Class. Initialises 12 empty shared_pointers for the points to be assigned to.
//I used shared pointers because initially I wanted a parallel class (Spline) that also referred to the same Curve and that could alter it as well. 
Mesh::Mesh()
{
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
//Another contructor that allows users to directly input a vector of curves, although this was not used in NGLScene
Mesh::Mesh(std::vector<std::shared_ptr<ngl::BezierCurve>> _splines)
{
    m_splines = _splines;
    for(int i = 0; i< _splines.size(); ++i)
    {
        splines[0]= Spline(m_splines[0]);
    }
    calculateIntersections();
}

//addPoint function to add a control point onto the end of curve number _index.
void Mesh::addPoint(ngl::Vec3 _point, int _index)
{
    m_splines[_index]->addPoint(_point);
    splines[_index].addControlPoints(_point);
}


//setting up LOD, knots and vertex array object forthe curves. 
void Mesh::setup(float _LOD)
{
    for(int i = 0; i<m_splines.size(); ++i)
    {
        m_splines[i]->setLOD(_LOD);
        m_splines[i]->createKnots();
        m_splines[i]->createVAO();
 }

}
//setting up only the top 8 for when those curves are translated
void Mesh::resetup(float _LOD)
{
    for(int i = 0; i<8; ++i)
    {
        m_splines[i]->setLOD(_LOD);
        m_splines[i]->createKnots();
        m_splines[i]->createVAO();
 }

}
//toggle convex hull visibility
void Mesh::setHullVisibility()
{
    if(m_hullVisibility == false)
    {
        m_hullVisibility = true;
    }
    else{
        m_hullVisibility = false;
    }
}
//draw 
void Mesh::draw()
{
    for(int i = 0; i<m_splines.size(); ++i)
    {
        ngl::ShaderLib::use("nglColourShader");
        ngl::ShaderLib::setUniform("Colour", 1.0f, 1.0f, 1.0f, 1.0f);
        m_splines[i]->draw();
        if(m_hullVisibility == true)
        {
            glPointSize(4);
            ngl::ShaderLib::setUniform("Colour", 0.0f, 1.0f, 0.0f, 1.0f);
            m_splines[i]->drawControlPoints();
            glPointSize(1);
            ngl::ShaderLib::setUniform("Colour", 1.0f, 0.0f, 0.0f, 1.0f);
            m_splines[i]->drawHull();
        }
    }
}
//rotate fubction defined constant x, y and z rotational matrices, and based on the input of degrees(actually radians) and axis rotates them that amount on that axis
//since ngl::BezierCurve doesn't have a function for altering control points, a new "placeholder" curve had all the transformations applied, and then the original curve was assigned to the placeholder curve
//this method is used repeatedly for all the transformations and deformations of the curves
void Mesh::rotate(float _degrees, int _axis)
{
    const ngl::Mat4 rotational_matrix_x = ngl::Mat4(1, 0, 0, 0, 0 , cos(_degrees), -sin(_degrees), 0, 0, sin(_degrees), cos(_degrees), 0, 0, 0, 0, 1);
    const ngl::Mat4 rotational_matrix_y = ngl::Mat4(cos(_degrees), 0, sin(_degrees), 0,0, 1, 0, 0, -sin(_degrees), 0, cos(_degrees), 0, 0, 0, 0, 1);
    const ngl::Mat4 rotational_matrix_z = ngl::Mat4(cos(_degrees), sin(_degrees), 0, 0,-sin(_degrees), cos(_degrees), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    //X Axis
    if( _axis == 0)
    {
        std::vector<ngl::Vec3> controlPoints;
        for(int i  = 0; i < 4; ++i)
        {
            controlPoints = m_splines[i]->getControlPoints();
            std::shared_ptr<ngl::BezierCurve> placeholder = std::make_shared<ngl::BezierCurve>(); 
            for(int j = 0; j<4; ++j)
            {
                ngl::Vec4 Vector4 = {{controlPoints[j]}, 1};
                Vector4 = rotational_matrix_x * Vector4;
                placeholder->addPoint(Vector4.toVec3());
            }
            m_splines[i] = placeholder;
        }
        for(int i = 0; i < 4; ++i)
        {
            updateIntersections(i);
        }
        for(int i = 4; i<8; ++i)
        {
            followMiddlePoints(i);
            bulgeLines(i);
        }

    }
    //Y-Axis
    else if(_axis == 1)
    {
        std::vector<ngl::Vec3> controlPoints;
        for(int i  = 0; i < 4; ++i)
        {
            controlPoints = m_splines[i]->getControlPoints();
            std::shared_ptr<ngl::BezierCurve> placeholder = std::make_shared<ngl::BezierCurve>(); 
            for(int j = 0; j<4; ++j)
            {
                ngl::Vec4 Vector4 = {{controlPoints[j]}, 1};
                Vector4 = rotational_matrix_y * Vector4; 
                placeholder->addPoint(Vector4.toVec3());
            }
            m_splines[i] = placeholder;
        }
        for(int i = 0; i < 4; ++i)
        {
            updateIntersections(i);
        }
        for(int i = 4; i<8; ++i)
        {
            followMiddlePoints(i);
            bulgeLines(i);
        }
    }
    //Z-Axis
    else{
        std::vector<ngl::Vec3> controlPoints;
        for(int i  = 0; i < 4; ++i)
        {
            controlPoints = m_splines[i]->getControlPoints();
            std::shared_ptr<ngl::BezierCurve> placeholder = std::make_shared<ngl::BezierCurve>(); 
            for(int j = 0; j<4; ++j)
            {
                ngl::Vec4 Vector4 = {{controlPoints[j]}, 1};
                Vector4 = rotational_matrix_z * Vector4;
                placeholder->addPoint(Vector4.toVec3());
            }
            m_splines[i] = placeholder;

        }
        for(int i = 0; i < 4; ++i)
        {
            updateIntersections(i);
        }
        for(int i = 4; i<8; ++i)
        {
            followMiddlePoints(i);
            bulgeLines(i);
        }
    }

}
//translate by _x, _y and _z
void Mesh::translate(float _x, float _y, float _z)
{
    const ngl::Mat4 translation_matrix = ngl::Mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, _x, _y, _z, 1);
    std::vector<ngl::Vec3> controlPoints;
        for(int i  = 0; i < 4; ++i)
        {
            controlPoints = m_splines[i]->getControlPoints();
            std::shared_ptr<ngl::BezierCurve> placeholder = std::make_shared<ngl::BezierCurve>(); 
            for(int j = 0; j < 4; ++j)
            {
                ngl::Vec4 Vector4 = {{controlPoints[j]}, 1};
                Vector4 = translation_matrix * Vector4;
                placeholder->addPoint(Vector4.toVec3());
            }
            m_splines[i] = placeholder;
            
        }
        for(int i = 0; i < 4; ++i)
        {
            updateIntersections(i);
        }
        for(int i = 4; i<8; ++i)
        {
            followMiddlePoints(i);
            bulgeLines(i);
        }
}
//scale by _x, _y and _z
void Mesh::scale(float _x, float _y, float _z)
{
    if(_x == 0)
    {
        _x = 1;
    }
    if(_y == 0)
    {
        _y = 1;
    }
    if(_z == 0)
    {
        _z = 1;
    }
    const ngl::Mat4 translation_matrix = ngl::Mat4(_x, 0, 0, 0, 0, _y, 0, 0, 0, 0, _z, 0, 0, 0, 0, 1);
        std::vector<ngl::Vec3> controlPoints;
        for(int i  = 0; i < 4; ++i)
        {
            controlPoints = m_splines[i]->getControlPoints();
            std::shared_ptr<ngl::BezierCurve> placeholder = std::make_shared<ngl::BezierCurve>(); 
            for(int j = 0; j < 4; ++j)
            {
                ngl::Vec4 Vector4 = {{controlPoints[j]}, 1};
                Vector4 = translation_matrix * Vector4;
                placeholder->addPoint(Vector4.toVec3());
            }
            m_splines[i] = placeholder;
            
        }
        for(int i = 0; i < 4; ++i)
        {
            updateIntersections(i);
        }
        for(int i = 4; i<8; ++i)
        {
            followMiddlePoints(i);
            bulgeLines(i);
        }
}

//calculated intersections as outlined in CGI techniques report
//uses std::vector of std::vector to create a rows and column table
//first column of each row a pair with each spline number, and then either 0 or 3 to refer to the first and last anchor points
//next columns of each row are all points intersecting with that point. They are in the same format as the first pair
void Mesh::calculateIntersections()
{
    m_intersections.resize(m_splines.size()*2);
    for(int a = 0;a < m_splines.size(); ++a)
    {
        m_intersections[(a*2)].push_back(std::make_pair(a, 0));
        m_intersections[(a*2)+1].push_back(std::make_pair(a, 3));
        for(int b = 0;b < m_splines.size();++b)
        {
            if(a != b)
            {
            for(float i = 0; i<=1.0f; i += 0.01f)
            {
                for(float j = 0; j<=1.0f; j += 0.01f)
                {
                    if(std::abs(m_splines[a]->getPointOnCurve(i).m_x-m_splines[b]->getPointOnCurve(j).m_x)<=0.001f &&
                    std::abs(m_splines[a]->getPointOnCurve(i).m_y-m_splines[b]->getPointOnCurve(j).m_y)<=0.001f &&
                    std::abs(m_splines[a]->getPointOnCurve(i).m_z-m_splines[b]->getPointOnCurve(j).m_z)<=0.001f)
                    {
                        if(i >= 0.9f)
                        {
                            if(j>=0.9f)
                            {
                                if(!(std::find(m_intersections[(a*2)+1].begin(), m_intersections[(a*2)+1].end(), std::pair<int, int>(b, 3)) != m_intersections[(a*2)+1].end())) {
                                    m_intersections[(a*2)+1].push_back({b, 3});
                                    int end = m_intersections[a*2+1].size()-1;

                                }  
                        }
                            else if(j<=0.1f)
                            {
                                if(!(std::find(m_intersections[(a*2)+1].begin(), m_intersections[(a*2)+1].end(), std::pair<int, int>(b, 0)) != m_intersections[(a*2)+1].end())) {
                                    m_intersections[(a*2)+1].push_back({b, 0}); 
                                    int end = m_intersections[a*2+1].size()-1;

                                }
                            }
                        }
                        else if(i <= 0.1f)
                        {
                            if(j>=0.9f)
                            {
                                if(!(std::find(m_intersections[(a*2)].begin(), m_intersections[(a*2)].end(), std::pair<int, int>(b, 3)) != m_intersections[(a*2)].end())) {
                                    m_intersections[(a*2)].push_back({b, 3});
                                    int end = m_intersections[a*2].size()-1;
                        
                                }  
                            }
                            else if(j<=0.1f)
                            {
                                if(!(std::find(m_intersections[(a*2)].begin(), m_intersections[(a*2)].end(), std::pair<int, int>(b, 0)) != m_intersections[(a*2)].end())) {
                                    m_intersections[(a*2)].push_back({b, 0});
                                    int end = m_intersections[a*2].size()-1;


                                }   
                            }
                        }

                    }

                }
            }
            }
        }
    } 
}
//update intersections updates the the intersected points as the first point moves
//ex: if point 1 and 2 are intersecting, as point 1 is moved point 2 follows to the same position using the updateIntersectoins functions
void  Mesh::updateIntersections(int _spline)
{
    std::vector<ngl::Vec3> oldPoints = m_splines[m_intersections[_spline*2][0].first]->getControlPoints();
    for(int i = 1; i <= 2; ++i)
    {
        std::vector<ngl::Vec3> Points = m_splines[m_intersections[_spline*2][i].first]->getControlPoints();
       Points[m_intersections[_spline*2][i].second] = oldPoints[m_intersections[_spline*2][0].second];
        std::shared_ptr<ngl::BezierCurve> placeholder = std::make_shared<ngl::BezierCurve>(); 
            for(int j = 0; j<4; ++j)
            {
            placeholder->addPoint(Points[j]);
        }
        m_splines[m_intersections[_spline*2][i].first] = placeholder;
    }


            
    oldPoints = m_splines[m_intersections[(_spline*2)+1][0].first]->getControlPoints();
    for(int i = 1; i <= 2; ++i)
    {
        std::vector<ngl::Vec3> Points = m_splines[m_intersections[(_spline*2)+1][i].first]->getControlPoints();
        Points[m_intersections[(_spline*2)+1][i].second] = oldPoints[m_intersections[(_spline*2)+1][0].second];
        std::shared_ptr<ngl::BezierCurve> placeholder = std::make_shared<ngl::BezierCurve>(); 
        for(int j = 0; j<4; ++j)
        {
            placeholder->addPoint(Points[j]);
        }
        m_splines[m_intersections[(_spline*2)+1][i].first] = placeholder;
        }

}

//calculated the length of each curve using the LERP method
void Mesh::calcLength()
{
    m_lengths.resize(m_splines.size());
    for(int a = 0; a < m_splines.size(); ++a)
    {
        float length = 0.0f;
        for(float i = 0; i<0.999; i=i+0.01f)
        {
            ngl::Vec3 first = m_splines[a]->getPointOnCurve(i);
            ngl::Vec3 second = m_splines[a]->getPointOnCurve(i+0.01f);
            length += std::sqrt(((first.m_x-second.m_x)*(first.m_x-second.m_x))+ ((first.m_y-second.m_y)*(first.m_y-second.m_y)) + ((first.m_z-second.m_z)
            *(first.m_z-second.m_z)));
        }
    m_lengths[a] = length;
    }
}

//centers middle two control points to be 33 and 67 percent of the way between the anchor points
void Mesh::centerMiddlePoints(int _index)
{
    ngl::Vec3 endPoint;
    ngl::Vec3 startPoint;
    std::vector<ngl::Vec3>controlPoints;
    controlPoints = m_splines[_index]->getControlPoints();
    startPoint = controlPoints[0];
    endPoint = controlPoints[3];
    std::shared_ptr<ngl::BezierCurve> placeholder = std::make_shared<ngl::BezierCurve>(); 
    ngl::Vec3 secondPoint = startPoint + ((endPoint-startPoint)*0.33);
    ngl::Vec3 thirdPoint = startPoint + ((endPoint-startPoint)*0.67);
    placeholder->addPoint(startPoint);
    placeholder->addPoint(secondPoint);
    placeholder->addPoint(thirdPoint);
    placeholder->addPoint(endPoint);
    m_splines[_index] = placeholder;
}

//transforms the cylinder into a square
void Mesh::transformSquare()
{
    for(int i = 0; i<m_splines.size(); ++i)
    {
        centerMiddlePoints(i);
    }
}

//sraightens curves on the side of the cylinder
void Mesh::straightenSides()
{
    for(int i = 4; i<8; ++i)
    {
        centerMiddlePoints(i);
    }

}

//places middle two control points 25% and 75% along the curve as a way of updating the center control points
//creates curvature as the anchor points are transformed
void Mesh::followMiddlePoints(int _index)
{
    ngl::Vec3 endPoint;
    ngl::Vec3 startPoint;
    std::vector<ngl::Vec3>controlPoints;
    controlPoints = m_splines[_index]->getControlPoints();
    std::shared_ptr<ngl::BezierCurve> placeholder = std::make_shared<ngl::BezierCurve>(); 
    ngl::Vec3 secondPoint = m_splines[_index]->getPointOnCurve(0.25f);
    ngl::Vec3 thirdPoint = m_splines[_index]->getPointOnCurve(0.75f);
    placeholder->addPoint(controlPoints[0]);
    placeholder->addPoint(secondPoint);
    placeholder->addPoint(thirdPoint);
    placeholder->addPoint(controlPoints[3]);
    m_splines[_index] = placeholder;
}

//checks if the curve is shorter than when it started
bool Mesh::checkShorter(int _index)
{

    float length = 0.0f;
    for(float i = 0; i<0.999; i=i+0.01f)
    {
        ngl::Vec3 first = m_splines[_index]->getPointOnCurve(i);
        ngl::Vec3 second = m_splines[_index]->getPointOnCurve(i+0.01f);
        length += std::sqrt(((first.m_x-second.m_x)*(first.m_x-second.m_x))+ ((first.m_y-second.m_y)*(first.m_y-second.m_y)) + ((first.m_z-second.m_z)
        *(first.m_z-second.m_z)));
    }
    if(length < m_lengths[_index])
    {
        return true;
    }
    return false;

    }

//"bulges" line when checkShorter == true. i.e. they are being compressed
//middle two control points are rotated and translated according to the closer anchor point
//in order to create the bulging/"filling" effect
void Mesh::bulgeLines(int _index)
{
    float rotation = 0.0f;
    int loops = 0;
    float translation = 0.0f;
    while(checkShorter(_index))
    {
        loops++;
        std::vector<ngl::Vec3> controlPoints = m_splines[_index]->getControlPoints();
        ngl::Vec3 startPoint = controlPoints[0];
        ngl::Vec3 endPoint = controlPoints[3];
        ngl::Mat4 rotational_matrix;
        ngl::Mat4 reverse_rotational_matrix;
        float _degrees = rotation+0.2;
        rotation += 0.1;
        if(controlPoints[0].m_z > controlPoints[0].m_x && controlPoints[0].m_z >0)
        {
            rotational_matrix = ngl::Mat4(1, 0, 0, 0, 0 , cos(_degrees), -sin(_degrees), 0, 0, sin(_degrees), cos(_degrees), 0, 0, 0, 0, 1);
            reverse_rotational_matrix = ngl::Mat4(1, 0, 0, 0, 0 , cos(-_degrees), -sin(-_degrees), 0, 0, sin(-_degrees), cos(-_degrees), 0, 0, 0, 0, 1);
            translation += 0.1;
            }
        else if(controlPoints[0].m_z < controlPoints[0].m_x && controlPoints[0].m_z < 0)
        {
            rotational_matrix = ngl::Mat4(1, 0, 0, 0, 0 , cos(-_degrees), -sin(-_degrees), 0, 0, sin(-_degrees), cos(-_degrees), 0, 0, 0, 0, 1);
            reverse_rotational_matrix = ngl::Mat4(1, 0, 0, 0, 0 , cos(_degrees), -sin(_degrees), 0, 0, sin(_degrees), cos(_degrees), 0, 0, 0, 0, 1);
            translation += 0.1;
            }
        else if(controlPoints[0].m_x>controlPoints[0].m_z && controlPoints[0].m_x > 0)
        {
            rotational_matrix = ngl::Mat4(cos(_degrees), sin(_degrees), 0, 0,-sin(_degrees), cos(_degrees), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); 
            reverse_rotational_matrix = ngl::Mat4(cos(_degrees), sin(-_degrees), 0, 0,-sin(-_degrees), cos(-_degrees), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);      
            translation += 0.1;     
            }
        else if(controlPoints[0].m_x<controlPoints[0].m_z && controlPoints[0].m_x < 0)
        {
            rotational_matrix = ngl::Mat4(cos(_degrees), sin(-_degrees), 0, 0,-sin(-_degrees), cos(-_degrees), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);   
            reverse_rotational_matrix = ngl::Mat4(cos(_degrees), sin(_degrees), 0, 0,-sin(_degrees), cos(_degrees), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); 
            translation += 0.1; 
            }
        std::shared_ptr<ngl::BezierCurve> placeholder = std::make_shared<ngl::BezierCurve>();
        placeholder->addPoint(controlPoints[0]);

        std::shared_ptr<ngl::BezierCurve> shifted_points = std::make_shared<ngl::BezierCurve>(); 
        ngl::Mat4 translation_matrix_start = ngl::Mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -startPoint.m_x, -startPoint.m_y-translation, -startPoint.m_z, 1);
        ngl::Mat4 reverse_translation_matrix_start = ngl::Mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, startPoint.m_x, startPoint.m_y+translation, startPoint.m_z, 1);

        ngl::Vec4 secondPoint= {{controlPoints[1]}, 1};
        secondPoint = translation_matrix_start * secondPoint;
        secondPoint = rotational_matrix * secondPoint;
        secondPoint = reverse_translation_matrix_start * secondPoint;
        placeholder->addPoint(secondPoint.toVec3());

        ngl::Mat4 translation_matrix_end = ngl::Mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -endPoint.m_x, -endPoint.m_y+translation, -endPoint.m_z, 1);
        ngl::Mat4 reverse_translation_matrix_end = ngl::Mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, endPoint.m_x, endPoint.m_y-translation, endPoint.m_z, 1);

        ngl::Vec4 thirdPoint = {{controlPoints[2]}, 1};
        thirdPoint = translation_matrix_end * thirdPoint;
        thirdPoint = reverse_rotational_matrix * thirdPoint;
        thirdPoint = reverse_translation_matrix_end * thirdPoint;
        placeholder->addPoint(thirdPoint.toVec3());

        placeholder->addPoint(controlPoints[3]);


        m_splines[_index] = placeholder;
}
}


//get function for splines
std::vector<ngl::Vec3> Mesh::getSpline(int i)
{
    return m_splines[i]->getControlPoints();
}

//get function for intersections
std::vector<std::pair<int, int>> Mesh::getIntersections(int i)
{
    return m_intersections[i];
}
//get function for lengths
float Mesh::getLength(int i)
{
    return m_lengths[i];
}