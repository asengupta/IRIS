/* VERT3D.H
   3-D Vertex definition header file
   (c) 2001 Avishek Sen Gupta

   ---created for automaton simulation visualisation---
*/

/* Note: This is a patch and the problem for robot visualisation is being
				 investigated. It makes use of a trick variable to take different
				 cos1 values at different times.*/

/* Note: This version has been updated specifically
         for the IRIS-3D platform. It is not backward-compatible
         with Turbo C++ 3.0*/

#ifndef VERT3D_H
#define VERT3D_H

#include <cmath>
#include "Matrix4x4.h"
#include "newmath.h"

namespace Comrade {
    namespace Iris3D {

using namespace Comrade::IrisFoundation;

struct Parametric
{
	double A,x1;
	double B,y1;
	double C,z1;
};

class Coordinate
{
private:    Point pt;
            Matrix4x4 mat;

public:     Coordinate();
            Coordinate(double x, double y, double z);

            Point return_data();

            double get_x();
            double get_y();
            double get_z();

            void input(Point para);
            void input(double x, double y, double z);

            void translate(int tx, int ty, int tz);
            void scale(double sx, double sy, double sz);
            void rotate_about_z(double theta);
            void rotate_about_x(double theta);
            void rotate_about_y(double theta);
            void rotate_about_parametric(Parametric line, double theta);
            void world_to_sensor(Parametric line,
                                 double x_up,
                                 double y_up,
                                 double z_up);

            Point parallel_project(Parametric vector, int color);
            Point show_arbitrary(Point pt1, Point pt2, int color);

            void draw(Point coord, int color);
            void show();
};

}
}

/*int main()
{
	clrscr();
	Coordinate coord(0,5,0);
	coord.show();
	cout<<endl;
	Parametric axis={1,0,0,0,0,0};
	coord.rotate_about_Parametric(axis,180);
	coord.show();
	getch();
	return 0;
}*/

#endif

