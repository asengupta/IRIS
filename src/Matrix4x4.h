/* MATRIX.H
   Matrix implementation & definition header file
   (c) 2001 Avishek Sen Gupta

   ---created for automaton simulation visualisation---
*/

#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <iostream>
#include <cmath>

namespace Comrade {
    namespace Iris3D {

#define MATRIX_X 4
#define MATRIX_Y 4

struct Point
{
		double array[1][4];
    void input(double a,double b,double c,double d);

    void show();
};

class Matrix4x4
{

public:    double matrix[4][4];

public:		
            Matrix4x4();

            void init();
            void input(double arr[MATRIX_Y][MATRIX_X]);
            void show();

            ~Matrix4x4();
};

Point multiply(Point coord, Matrix4x4 transform);

}
}

#endif


