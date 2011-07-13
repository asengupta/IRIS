#ifndef SENSOR_3D_H
#define SENSOR_3D_H

#include "Vert3D.h"
#include "Buffer.h"

namespace Comrade {
    namespace Iris3D {

using namespace IrisFoundation;

struct Sensor
{
    int id;
    Coordinate optical_center;
    Coordinate focal_center;
    double focal_length;
    Parametric viewline;

    double phy_aperture_x;
    double phy_aperture_y;

    double x_up,y_up,z_up;

    Buffer<HSLstruct>* img_buffer_ptr;
    Buffer<bool>* flag_buffer_ptr;

    int proj_rect[2][2];
    HSLstruct isect_color;

    Sensor();
    void set(Coordinate opc,Coordinate foc,double apx,double apy);
    ~Sensor();
};

}
}

#endif


