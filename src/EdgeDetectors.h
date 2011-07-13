#ifndef EDGE_DETECTORS_H
#define EDGE_DETECTORS_H

#include <cmath>
#include "newmath.h"
#include "BufferConvertor.h"
#include "SpecialKernels.h"

// Not implemented properly yet. Use CA_EdgeDetector instead.
// May not be useful unless they perform better than my system.

namespace Comrade {
    namespace IrisXT {

using namespace Comrade::IrisFoundation;

class EdgeDetectorManager
{
protected:  Buffer<RGB>* ip;
            Buffer<RGB>* op;

            double greyscale_correlate(Buffer<RGB>* buffer,
                                       int x,int y,
                                       KernelMatrix* ker);

            void call_operator(KernelMatrix* H1,
                               KernelMatrix* H2,
                               int threshold);

public:     EdgeDetectorManager();

            // Note that the fns are separate for now.
            // May need refactoring later on.

            void RobertsCross(Buffer<RGB>* ip_buffer,
                              Buffer<RGB>* op_buffer,int threshold);

            void Prewitt(Buffer<RGB>* ip_buffer,
                         Buffer<RGB>* op_buffer,int threshold);

            void Sobel(Buffer<RGB>* ip_buffer,
                       Buffer<RGB>* op_buffer,int threshold);

            void isotropic(Buffer<RGB>* ip_buffer,
                           Buffer<RGB>* op_buffer,int threshold);

            void Laplacian(Buffer<RGB>* ip_buffer,
                           Buffer<RGB>* op_buffer,int threshold);

            void Canny(Buffer<RGB>*ip_buffer,
                       Buffer<RGB>* op_buffer,double sigma);

            ~EdgeDetectorManager();
};

}
}

#endif

