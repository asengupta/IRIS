#ifndef VOXEL_H
#define VOXEL_H

#include "newmath.h"
#include "Vert3D.h"
#include "Sensor3D.h"

namespace Comrade {
    namespace Iris3D {

using namespace IrisFoundation;

#define GARGOYLE_X 320
#define GARGOYLE_Y 240

#define WORLD_X 61
#define WORLD_Y 61
#define WORLD_Z 61

#define ORIGIN_X (WORLD_X/2-1)
#define ORIGIN_Y (WORLD_Y/2-1)
#define ORIGIN_Z (WORLD_Z/2-1)

#define VOXELS_PER_SIDE 61
#define VOXEL_SQUARE (VOXELS_PER_SIDE*VOXELS_PER_SIDE)
#define VOXEL_VOLUME (VOXEL_SQUARE*VOXELS_PER_SIDE)

#define VOXEL_X WORLD_X/VOXELS_PER_SIDE
#define VOXEL_Y WORLD_Y/VOXELS_PER_SIDE
#define VOXEL_Z WORLD_Z/VOXELS_PER_SIDE

struct Voxel
{
    double x,y,z;
    HSLstruct color;
    bool carved;
};

class VoxelWorker
{
protected:

public:     VoxelWorker();

            static Coordinate true_intersection_of(Coordinate pt,Sensor& sense);
            static Coordinate intersection_of(Coordinate pt,Sensor& sense);
            static void bounded_intersection_of(Voxel vox,Sensor& sense,Coordinate array[8]);
            static void find_rectangle(int op[2][2],Coordinate array[8]);
            
            ~VoxelWorker();
};

}
}

#endif


