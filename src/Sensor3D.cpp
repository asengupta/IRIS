#include "Sensor3D.h"

Comrade::Iris3D::Sensor::Sensor()
{
    x_up=y_up=0;
    z_up=1;
}

void Comrade::Iris3D::Sensor::set(Comrade::Iris3D::Coordinate opc,Comrade::Iris3D::Coordinate foc,double apx,double apy)
{
    optical_center=opc;
    focal_center=foc;

    viewline.A=focal_center.get_x()-
               optical_center.get_x();

    viewline.B=focal_center.get_y()-
               optical_center.get_y();

    viewline.C=focal_center.get_z()-
               optical_center.get_z();

    focal_length=sqrt(viewline.A*viewline.A+
                      viewline.B*viewline.B+
                      viewline.C*viewline.C);

    viewline.x1=focal_center.get_x();
    viewline.y1=focal_center.get_y();
    viewline.z1=focal_center.get_z();

    phy_aperture_x=apx;
    phy_aperture_y=apy;
}

Comrade::Iris3D::Sensor::~Sensor()
{}

