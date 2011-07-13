#ifndef WORLD_SPACE_H
#define WORLD_SPACE_H

#include "Voxel.h"

namespace Comrade {
    namespace Iris3D {

using namespace Comrade::IrisFoundation;

class WorldSpace
{
public:     Voxel world[WORLD_Z][WORLD_Y][WORLD_X]; //Should be private

public:     WorldSpace();

            void fill_coordinates(int rcz,int rcy,int rcx);

            ~WorldSpace();
};

}
}

#endif

