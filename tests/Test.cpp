#include <gtest/gtest.h>

#include "Intersection.h"

TEST(Intersection, ctor)
{   
    //input/test values
    std::vector<ngl::Vec3> test_tangents = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};
    std::vector<float> test_lengths = {1.0, 0.2, 1.1};
    ngl::Vec3 test_location = {0.0f, 0.0f, 0.0f};
    //constructor test
    Intersection a(test_tangents, test_lengths, test_location);
    ASSERT_EQ(test_tangents, a.getTan());
    ASSERT_EQ(test_lengths, a.getLen());
    ASSERT_EQ(test_location, a.getLoc());
}


TEST(Intersection, CornerCtor)
{   //input/test values
    std::vector<float> dummy_lengths = {1.0, 0.2, 1.1};
    ngl::Vec3 test_location = {1.0f, 2.0f, 3.0f};
    std::vector<ngl::Vec3> test_tangents = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};
    std::vector<Corner> corners_ans = {{{0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}, {{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}, {{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}};
    
    //test for corner values with simple numbers
    Intersection a(test_tangents, dummy_lengths, test_location);
    std::vector<Corner> aCorn= a.getCorn();
    for(int i = 0; i<3; ++i){
    ASSERT_EQ(corners_ans[i].CornerVec, aCorn[i].CornerVec);
    ASSERT_EQ(corners_ans[i].CornerNorm, aCorn[i].CornerNorm);
    }

    //more specific values
    test_tangents = {{1.2f, 1.0f, 0.0f}, {0.8f, 1.0f, 0.5f}, {0.6f, 0.1f, 1.8f}};
    corners_ans = {{{0.5f, -0.6f, 0.4f}, {0.569802882, -0.68376345, 0.45584230}}, {{1.75f, -1.14f, -0.52f}, {0.81307448f, -0.52965995f, -0.24159927f}}, {{-1.8f, 2.16f, 0.48f}, {-0.63105474f, 0.75726569f, 0.16828136f}}};
    //Test for Corner Values with more specific numbers
    Intersection b(test_tangents, dummy_lengths, test_location);
    std::vector<Corner> bCorn= b.getCorn();
    for(int i = 0; i<3; ++i){
    ASSERT_EQ(corners_ans[i].CornerVec, bCorn[i].CornerVec);
    ASSERT_EQ(corners_ans[i].CornerNorm, bCorn[i].CornerNorm);
    }
}

// TEST(Intersection, CornerNorms)
// {   //input values
//     std::vector<float> dummy_lengths = {1.0, 0.2, 1.1};
//     ngl::Vec3 test_location = {1.0f, 2.0f, 3.0f};
//     std::vector<ngl::Vec3> test_tangents = {{1.2f, 1.0f, 0.0f}, {0.8f, 1.0f, 0.5f}, {0.6f, 0.1f, 1.8f}};
//     std::vector<std::pair<ngl::Vec3, ngl::Vec3>> normals_ans = {{{0.569802882, -0.68376345, 0.45584230}, {-0.63105474f, 0.75726569f, 0.16828136f}}, {{0.81307448f, -0.52965995f, -0.24159927f}, {0.569802882, -0.68376345, 0.45584230}}, {{-0.63105474f, 0.75726569f, 0.16828136f}, {0.81307448f, -0.52965995f, -0.24159927f}}};
//     //Test for Normal Values 
//     Intersection a(test_tangents, dummy_lengths, test_location);
//     std::vector<std::pair<ngl::Vec3, ngl::Vec3>> anormals= a.getNorms();
//     ASSERT_EQ(anormals, normals_ans);

// }


