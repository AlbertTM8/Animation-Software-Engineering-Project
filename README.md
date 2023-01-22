# Albert Jian Sheng Tan-Mulligan Assigment

## How To Use The Program
Once the program runs, a unit cylinder shape will be drawn through Bezier Curves. In the top left hand corner are the controls. The W/A/S/D/O/P buttons will translate the top circle of the cylinder in increments of 0.1. E/R are used to rotate these the top, and by pressing x y and z you change the axis in which it is being rotated. 1/2/3/4 will scale the circle in the x and the z. All of these controls are defined in world space and not local to the unit circle. 

F will straigthen the lines and Y will turn the cylinder into a cube. C turns the convex hull of each curve on and off.

Left mouse controls the camera rotation. Alt+Scroll controls the zoom. Right click controls the camera pan.

## Important Note
Segments and Spline classes were originally created in order to generate scaled frames following the CurveNet paper. They were not finished due to misjudgement about how much content is written to create a good curve-mesh motion and control system. However, they are kept in the folder since certin design choices for the Curve class were made with the Spline and Segments classes in mind. 

## Project Topic/Proposal - Curvenets
This Project's goal is to implement the "Curvenet" rigging representation, described in the paper in Section 3 (De Geos, 2022). This project will not attempt the mesh transformation or any of the Curvenet propagation. The initial goal is to define a curvenet representing a simple cylinder, box and sphere, which can then be transformed and deformed. The representation should include interesection handles or sliders, which are then used to control the deformation gradient. As an extension to the project if time permits, I  would like to extend the project to create a flexible solver that computes the curvenet information based on input splines. 

##Used Libraries
I should not reqiure any addition libraries other than the provided libraries i.e. the NGL library, C++ Standard Library, FMT, QT and GTest.

## Class Design (Subject To Change)
![](./ASE%20Class%20Diagram%20-%20Albert%20Tan-Mulligan.png)
## References
De Goes, F., Sheffler, W. and Fleischer, K. (2022). Character articulation through profile curves. ACM Transactions on Graphics, [online] 41(4), pp.1–14. doi:10.1145/3528223.3530060. (Video Demonstration: https://www.youtube.com/watch?v=gUJ4RxMdVn8) (PDF: https://graphics.pixar.com/library/ProfileMover/paper.pdf)
