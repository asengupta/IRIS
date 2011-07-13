#include "Voxel.h"

Comrade::Iris3D::VoxelWorker::VoxelWorker()
{}

Comrade::Iris3D::Coordinate Comrade::Iris3D::VoxelWorker::intersection_of(Comrade::Iris3D::Coordinate pt,Comrade::Iris3D::Sensor& sense)
{
    //Coordinate ans=true_intersection_of(pt,sense);
    //ans.world_to_sensor(sense.viewline,0,0,1);
    // To revert to the original version,
    // comment out the next 3 code statements and
    // uncomment the above two.

    Coordinate ans=pt;
    ans.world_to_sensor(sense.viewline,0,0,1);
    ans.input(sense.focal_length*ans.get_x()/ans.get_z(),
              sense.focal_length*ans.get_y()/ans.get_z(),
              sense.focal_length);

    double x=ans.get_x();
    double y=ans.get_y();

    double scx=GARGOYLE_X/sense.phy_aperture_x;
    double scy=GARGOYLE_Y/sense.phy_aperture_y;

    ans.input(x*scx,y*scy,0);

    return ans;
}

Comrade::Iris3D::Coordinate Comrade::Iris3D::VoxelWorker::true_intersection_of(Comrade::Iris3D::Coordinate pt,Comrade::Iris3D::Sensor& sense)
{
    double xv=pt.get_x();
    double yv=pt.get_y();
    double zv=pt.get_z();

    double xc=sense.optical_center.get_x();
    double yc=sense.optical_center.get_y();
    double zc=sense.optical_center.get_z();

    double xp=sense.focal_center.get_x();
    double yp=sense.focal_center.get_y();
    double zp=sense.focal_center.get_z();

    double A=xp-xc;
    double B=yp-yc;
    double C=zp-zc;

    double A1=xv-xc;
    double B1=yv-yc;
    double C1=zv-zc;

    double u=A*A+B*B+C*C;
    u/=(A*A1+B*B1+C*C1);

    Coordinate ans(xc+A1*u,yc+B1*u,zc+C1*u);

/*    if (fabs(ans.get_x())<=1e-4)
    {
        ans.input(0,ans.get_y(),ans.get_z());
    }

    if (fabs(ans.get_y())<=1e-4)
    {
        ans.input(ans.get_x(),0,ans.get_z());
    }

    if (fabs(ans.get_z())<=1e-4)
    {
        ans.input(ans.get_x(),ans.get_y(),0);
    }*/

    return ans;
}

void Comrade::Iris3D::VoxelWorker::bounded_intersection_of
                               (Comrade::Iris3D::Voxel vox,
                                Comrade::Iris3D::Sensor& sense,
                                Comrade::Iris3D::Coordinate array[8])
{
    double HALF_X=static_cast<double>(VOXEL_X)/2.;
    double HALF_Y=static_cast<double>(VOXEL_Y)/2.;
    double HALF_Z=static_cast<double>(VOXEL_Z)/2.;

    Coordinate v1(vox.x+HALF_X,vox.y+HALF_Y,vox.z+HALF_Z);
    Coordinate v2(vox.x-HALF_X,vox.y+HALF_Y,vox.z+HALF_Z);
    Coordinate v3(vox.x+HALF_X,vox.y-HALF_Y,vox.z+HALF_Z);
    Coordinate v4(vox.x-HALF_X,vox.y-HALF_Y,vox.z+HALF_Z);

    Coordinate v5(vox.x+HALF_X,vox.y+HALF_Y,vox.z-HALF_Z);
    Coordinate v6(vox.x-HALF_X,vox.y+HALF_Y,vox.z-HALF_Z);
    Coordinate v7(vox.x+HALF_X,vox.y-HALF_Y,vox.z-HALF_Z);
    Coordinate v8(vox.x-HALF_X,vox.y-HALF_Y,vox.z-HALF_Z);

    Coordinate corners[]={v1,v2,v3,v4,v5,v6,v7,v8};

    /*cout<<endl<<"Box "<<HALF_X<<" "<<HALF_Y<<" "<<HALF_Z<<endl;
    for (int i=0; i<=7; i++)
    {
        cout<<corners[i].get_x()<<" "
            <<corners[i].get_y()<<" "
            <<corners[i].get_z()<<endl;
    }

    cout<<endl;*/

    for (int i=0; i<=7; i++)
    {
        Coordinate coord=intersection_of(corners[i],sense);
        array[i]=coord;
    }

    /*cout<<endl<<"Box "<<HALF_X<<" "<<HALF_Y<<" "<<HALF_Z<<endl;
    for (int i=0; i<=7; i++)
    {
        cout<<array[i].get_x()<<" "
            <<array[i].get_y()<<" "
            <<array[i].get_z()<<endl;
    }

    cout<<endl;*/
}

void Comrade::Iris3D::VoxelWorker::find_rectangle(int op[2][2],
                                Comrade::Iris3D::Coordinate array[8])
{
	double minx,maxx,miny,maxy;
	
	minx=maxx=array[0].get_x();
	miny=maxy=array[0].get_y();

	for (int i=1; i<=7; i++)
	{
		double cx=array[i].get_x();
		double cy=array[i].get_y();
		
		if (cx<minx)
		{
			minx=cx;
		}
		
		if (cx>maxx)
		{
			maxx=cx;
		}
		
		if (cy<miny)
		{
			miny=cy;
		}
		
		if (cy>maxy)
		{
			maxy=cy;
		}
	}
	
	op[0][0]=static_cast<int>(minx);
	op[0][1]=static_cast<int>(miny);
	op[1][0]=static_cast<int>(maxx);
	op[1][1]=static_cast<int>(maxy);

    //cout<<op[0][0]<<" "<<op[0][1]<<"-"<<op[1][0]<<" "<<op[1][1]<<endl;
}
		
Comrade::Iris3D::VoxelWorker::~VoxelWorker()
{}


