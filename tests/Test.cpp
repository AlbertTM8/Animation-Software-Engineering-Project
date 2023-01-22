#include <gtest/gtest.h>
#include "Mesh.h"


TEST(Mesh, ctor)
{   
    //input/test values
   std::vector<ngl::Vec3> test_curves = {{1.0f, 1.0f, 0.0f}, {1.0f, 0.75f, 0.0f}, {1.0f, 0.25f, 0.0f}, {1.0f, 0.0f, 0.0f}};
   Mesh a;
   a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.0f), 0);
   a.addPoint(ngl::Vec3(1.0f, 0.75f, 0.0f), 0);
   a.addPoint(ngl::Vec3(1.0f, 0.25f, 0.0f), 0);
   a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.0f), 0);
   a.addPoint(ngl::Vec3(0.0f, 0.0f, 1.0f), 1);
   a.addPoint(ngl::Vec3(0.0f, 0.25f, 1.0f), 1);
   a.addPoint(ngl::Vec3(0.0f, 0.75f, 1.0f), 1);
   a.addPoint(ngl::Vec3(0.0f, 1.0f, 1.0f), 1);

    ASSERT_EQ(test_curves, a.getSpline(0));
    test_curves = {{0.0f, 0.0f, 1.0f}, {0.0f, 0.25f, 1.0f}, {0.0f, 0.75f, 1.0f}, {0.0f, 1.0f, 1.0f}};
    ASSERT_EQ(test_curves, a.getSpline(1));
}

TEST(Mesh, intersections)
{   
    //input/test values
   std::vector<std::pair<int, int>> test_curves = {std::make_pair<int, int>(0, 0), std::make_pair<int, int>(1, 0), std::make_pair<int, int>(2, 3)};
   Mesh a;
   a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.0f), 0);
   a.addPoint(ngl::Vec3(1.0f, 0.75f, 0.0f), 0);
   a.addPoint(ngl::Vec3(1.0f, 0.25f, 0.0f), 0);
   a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.0f), 0);
   a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.0f), 1);
   a.addPoint(ngl::Vec3(0.0f, 0.25f, 1.0f), 1);
   a.addPoint(ngl::Vec3(0.0f, 0.75f, 1.0f), 1);
   a.addPoint(ngl::Vec3(0.0f, 1.0f, 1.0f), 1);
   a.addPoint(ngl::Vec3(0.0f, 1.0f, 0.0f), 2);
   a.addPoint(ngl::Vec3(0.25f, 1.0f, 0.0f), 2);
   a.addPoint(ngl::Vec3(0.75f, 1.0f, 0.0f), 2);
   a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.0f), 2);
    a.calculateIntersections();
    ASSERT_EQ(test_curves, a.getIntersections(0));

}

TEST(Mesh, lengths)
{   

   float testLength = 1.0f;
   Mesh a;
   a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.0f), 0);
   a.addPoint(ngl::Vec3(1.0f, 0.75f, 0.0f), 0);
   a.addPoint(ngl::Vec3(1.0f, 0.25f, 0.0f), 0);
   a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.0f), 0);
    a.calcLength();
    EXPECT_NEAR(testLength, 1.0f, 0.01);

}

TEST(Mesh, translation)
{   

   std::vector<ngl::Vec3> testPoints = {{1.1f, 1.0f, 0.0f}, {0.85f, 1.0f, 0.0f}, {0.35f, 1.0f, 0.0f} ,{0.1f, 1.0f, 0.0f}};

   Mesh a;
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.0f), 0);
    a.addPoint(ngl::Vec3(0.75f, 1.0f, 0.0f), 0);
    a.addPoint(ngl::Vec3(0.25f, 1.0f, 0.0f), 0);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 0.0f), 0);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 1.0f), 1);
    a.addPoint(ngl::Vec3(0.75f, 1.0f, 1.0f), 1);
    a.addPoint(ngl::Vec3(0.25f, 1.0f, 1.0f), 1);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 1.0f), 1);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 1.0f),2);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 0.75f), 2);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 0.25f), 2);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 0.0f), 2);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 1.0f), 3);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.75f), 3);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.25f), 3);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.0f), 3);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.0f), 4);
    a.addPoint(ngl::Vec3(1.0f, 0.75f, 0.0f), 4);
    a.addPoint(ngl::Vec3(1.0f, 0.25f, 0.0f), 4);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.0f), 4);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 1.0f), 5);
    a.addPoint(ngl::Vec3(1.0f, 0.75f, 1.0f), 5);
    a.addPoint(ngl::Vec3(1.0f, 0.25f, 1.0f), 5);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 1.0f), 5);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 1.0f), 6);
    a.addPoint(ngl::Vec3(0.0f, 0.75f, 1.0f), 6);
    a.addPoint(ngl::Vec3(0.0f, 0.25f, 1.0f), 6);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 1.0f), 6);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 0.0f), 7);
    a.addPoint(ngl::Vec3(0.0f, 0.75f, 0.0f), 7);
    a.addPoint(ngl::Vec3(0.0f, 0.25f, 0.0f), 7);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 0.0f), 7);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.0f), 8);
    a.addPoint(ngl::Vec3(0.75f, 0.0f, 0.0f), 8);
    a.addPoint(ngl::Vec3(0.25f, 0.0f, 0.0f), 8);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 0.0f), 8);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 1.0f), 9);
    a.addPoint(ngl::Vec3(0.75f, 0.0f, 1.0f), 9);
    a.addPoint(ngl::Vec3(0.25f, 0.0f, 1.0f), 9);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 1.0f), 9);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 1.0f),10);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 0.75f), 10);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 0.25f), 10);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 0.0f), 10);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 1.0f), 11);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.75f), 11);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.25f), 11);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.0f), 11);
    a.calculateIntersections();
    a.calcLength();
    a.translate(0.1f, 0.0f, 0.0f);
    ASSERT_EQ(testPoints, a.getSpline(0));
    a.translate(0.0f, 0.1f, 0.0f);
    testPoints = {{1.1f, 1.1f, 1.0f}, {1.1f, 1.1f, 0.75f}, {1.1f, 1.1f, 0.25f} ,{1.1f, 1.1f, 0.0f}};
    ASSERT_EQ(testPoints, a.getSpline(3));
    a.translate(0.0f, 0.1f, 0.1f);
    testPoints = {{1.1f, 1.2f, 1.1f}, {1.1f, 1.2f, 0.85f}, {1.1f, 1.2f, 0.35f} ,{1.1f, 1.2f, 0.1f}};
    ASSERT_EQ(testPoints, a.getSpline(3));
}
TEST(Mesh, rotation)
{   

   std::vector<ngl::Vec3> testPoints = {{1.0f, 0.0f, 1.0f}, {0.75f, 0.0f, 1.0f}, {0.25f, 0.0f, 1.0f} ,{0.0f, 0.0f, 1.0f}};

   Mesh a;
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.0f), 0);
    a.addPoint(ngl::Vec3(0.75f, 1.0f, 0.0f), 0);
    a.addPoint(ngl::Vec3(0.25f, 1.0f, 0.0f), 0);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 0.0f), 0);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 1.0f), 1);
    a.addPoint(ngl::Vec3(0.75f, 1.0f, 1.0f), 1);
    a.addPoint(ngl::Vec3(0.25f, 1.0f, 1.0f), 1);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 1.0f), 1);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 1.0f),2);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 0.75f), 2);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 0.25f), 2);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 0.0f), 2);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 1.0f), 3);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.75f), 3);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.25f), 3);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.0f), 3);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.0f), 4);
    a.addPoint(ngl::Vec3(1.0f, 0.75f, 0.0f), 4);
    a.addPoint(ngl::Vec3(1.0f, 0.25f, 0.0f), 4);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.0f), 4);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 1.0f), 5);
    a.addPoint(ngl::Vec3(1.0f, 0.75f, 1.0f), 5);
    a.addPoint(ngl::Vec3(1.0f, 0.25f, 1.0f), 5);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 1.0f), 5);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 1.0f), 6);
    a.addPoint(ngl::Vec3(0.0f, 0.75f, 1.0f), 6);
    a.addPoint(ngl::Vec3(0.0f, 0.25f, 1.0f), 6);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 1.0f), 6);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 0.0f), 7);
    a.addPoint(ngl::Vec3(0.0f, 0.75f, 0.0f), 7);
    a.addPoint(ngl::Vec3(0.0f, 0.25f, 0.0f), 7);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 0.0f), 7);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.0f), 8);
    a.addPoint(ngl::Vec3(0.75f, 0.0f, 0.0f), 8);
    a.addPoint(ngl::Vec3(0.25f, 0.0f, 0.0f), 8);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 0.0f), 8);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 1.0f), 9);
    a.addPoint(ngl::Vec3(0.75f, 0.0f, 1.0f), 9);
    a.addPoint(ngl::Vec3(0.25f, 0.0f, 1.0f), 9);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 1.0f), 9);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 1.0f),10);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 0.75f), 10);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 0.25f), 10);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 0.0f), 10);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 1.0f), 11);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.75f), 11);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.25f), 11);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.0f), 11);
    a.calculateIntersections();
    a.calcLength();
    a.rotate(-1.5708f, 0);
    ASSERT_EQ(testPoints, a.getSpline(0));
    a.rotate(3.14159f, 0);
    testPoints = {{1.0f, 0.0f, -1.0f}, {0.75f, 0.0f, -1.0f}, {0.25f, 0.0f, -1.0f} ,{0.0f, 0.0f, -1.0f}};
    ASSERT_EQ(testPoints, a.getSpline(0));
}

TEST(Mesh, scaling)
{   

   std::vector<ngl::Vec3> testPoints = {{1.0f, 1.0f, 1.1f}, {0.75f, 1.0f, 1.1f}, {0.25f, 1.0f, 1.1f} ,{0.0f, 1.0f, 1.1f}};


   Mesh a;
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.0f), 0);
    a.addPoint(ngl::Vec3(0.75f, 1.0f, 0.0f), 0);
    a.addPoint(ngl::Vec3(0.25f, 1.0f, 0.0f), 0);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 0.0f), 0);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 1.0f), 1);
    a.addPoint(ngl::Vec3(0.75f, 1.0f, 1.0f), 1);
    a.addPoint(ngl::Vec3(0.25f, 1.0f, 1.0f), 1);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 1.0f), 1);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 1.0f),2);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 0.75f), 2);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 0.25f), 2);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 0.0f), 2);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 1.0f), 3);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.75f), 3);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.25f), 3);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.0f), 3);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 0.0f), 4);
    a.addPoint(ngl::Vec3(1.0f, 0.75f, 0.0f), 4);
    a.addPoint(ngl::Vec3(1.0f, 0.25f, 0.0f), 4);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.0f), 4);
    a.addPoint(ngl::Vec3(1.0f, 1.0f, 1.0f), 5);
    a.addPoint(ngl::Vec3(1.0f, 0.75f, 1.0f), 5);
    a.addPoint(ngl::Vec3(1.0f, 0.25f, 1.0f), 5);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 1.0f), 5);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 1.0f), 6);
    a.addPoint(ngl::Vec3(0.0f, 0.75f, 1.0f), 6);
    a.addPoint(ngl::Vec3(0.0f, 0.25f, 1.0f), 6);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 1.0f), 6);
    a.addPoint(ngl::Vec3(0.0f, 1.0f, 0.0f), 7);
    a.addPoint(ngl::Vec3(0.0f, 0.75f, 0.0f), 7);
    a.addPoint(ngl::Vec3(0.0f, 0.25f, 0.0f), 7);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 0.0f), 7);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.0f), 8);
    a.addPoint(ngl::Vec3(0.75f, 0.0f, 0.0f), 8);
    a.addPoint(ngl::Vec3(0.25f, 0.0f, 0.0f), 8);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 0.0f), 8);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 1.0f), 9);
    a.addPoint(ngl::Vec3(0.75f, 0.0f, 1.0f), 9);
    a.addPoint(ngl::Vec3(0.25f, 0.0f, 1.0f), 9);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 1.0f), 9);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 1.0f),10);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 0.75f), 10);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 0.25f), 10);
    a.addPoint(ngl::Vec3(0.0f, 0.0f, 0.0f), 10);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 1.0f), 11);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.75f), 11);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.25f), 11);
    a.addPoint(ngl::Vec3(1.0f, 0.0f, 0.0f), 11);
    a.calculateIntersections();
    a.calcLength();
    a.scale(0.0f, 0.0f, 1.1f);
    ASSERT_EQ(testPoints, a.getSpline(1));

}


//   mesh.scale(0.9f, 0.0f, 0.0f);