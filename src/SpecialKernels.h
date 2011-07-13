#ifndef SPECIAL_KERNELS_H
#define SPECIAL_KERNELS_H

#include <cmath>
#include "KernelMatrix.h"

namespace Comrade {
    namespace IrisXT {

using namespace Comrade::IrisFoundation;

class KernelGenerator
{
protected:

public:     KernelGenerator();
            static void generate_Gaussian(KernelMatrix* ker, double std_dev);

            static void generate_RobertsCross(KernelMatrix* H1,
                                              KernelMatrix* H2);

            static void generate_Sobel(KernelMatrix* H1,
                                       KernelMatrix* H2);

            static void generate_Prewitt(KernelMatrix* H1,
                                         KernelMatrix* H2);

            static void generate_isotropic(KernelMatrix* H1,
                                           KernelMatrix* H2);

            static void generate_Laplacian(KernelMatrix* H1,
                                           KernelMatrix* H2);

            ~KernelGenerator();
};

}
}

#endif

