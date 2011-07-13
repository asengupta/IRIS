#ifndef MODEL_BUILDER_H
#define MODEL_BUILDER_H

#include <cassert>
#include <vector>
#include "BufferConvertor.h"
#include "WorldSpace.h"

namespace Comrade {
    namespace Iris3D {

using namespace Comrade::IrisFoundation;

//#define DEBUG

bool x_space_carve_dec(std::vector<Sensor>& senarr,
                       WorldSpace& space);

bool x_space_carve_inc(std::vector<Sensor>& senarr,
                       WorldSpace& space);

bool y_space_carve_dec(std::vector<Sensor>& senarr,
                       WorldSpace& space);

bool y_space_carve_inc(std::vector<Sensor>& senarr,
                       WorldSpace& space);

bool z_space_carve_dec(std::vector<Sensor>& senarr,
                       WorldSpace& space);

bool z_space_carve_inc(std::vector<Sensor>& senarr,
                       WorldSpace& space);

void common_code(Voxel& vox,std::vector<Sensor*> active);
/* WorldSpace& space --> Put in as last argument if needed.
See ModelBuilder.cpp */

}
}

#endif


