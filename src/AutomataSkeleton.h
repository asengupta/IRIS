#ifndef AUTOMATA_SKELETON_H
#define AUTOMATA_SKELETON_H

#include "BufferConvertor.h"

namespace Comrade {
    namespace IrisXT {

using namespace Comrade::IrisFoundation;

class CA_Skeletoniser
{
protected:

public:     CA_Skeletoniser();
            void skeletonise(Buffer<RGB>* ip_buffer,
                             Buffer<RGB>* op_buffer);
            ~CA_Skeletoniser();
};

}
}

#endif

