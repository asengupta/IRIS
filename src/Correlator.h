#ifndef CORRELATOR_H
#define CORRELATOR_H

#include "Buffer.h"

namespace Comrade {
    namespace Iris3D {

using namespace Comrade::IrisFoundation;

double correlate(Buffer<RGB>* buffer1,Buffer<RGB>* buffer2,
                 int x1,int y1,int x2,int y2,
                 int bx,int by);

}
}

#endif


