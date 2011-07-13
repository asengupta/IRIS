#include "WorldSpace.h"

Comrade::Iris3D::WorldSpace::WorldSpace()
{}

void Comrade::Iris3D::WorldSpace::fill_coordinates(int rcz,int rcy,int rcx)
{
    int startz=-rcz*VOXEL_Z;

    RGB rgbwhite={255,255,255};
    HSLstruct hslwhite=ColorSpaceConvertor::uRGB_to_HSL(rgbwhite);
                
    for (int z=0; z<=WORLD_Z-1; z++)
    {
        int starty=-rcy*VOXEL_Y;

        for (int y=0; y<=WORLD_Y-1; y++)
        {
            int startx=-rcx*VOXEL_X;

            for (int x=0; x<=WORLD_X-1; x++)
            {
                world[z][y][x].x=startx;
                world[z][y][x].y=starty;
                world[z][y][x].z=startz;
                world[z][y][x].carved=false;

                world[z][y][x].color=hslwhite;

                //cout<<"Coordinates\("<<startz<<" "<<starty<<" "<<startx<<")\n";

                startx+=VOXEL_X;
            }

            starty+=VOXEL_Y;
        }

        startz+=VOXEL_Z;
    }
}

Comrade::Iris3D::WorldSpace::~WorldSpace()
{}


