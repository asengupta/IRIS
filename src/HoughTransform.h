#ifndef HOUGH_TRANSFORM_H
#define HOUGH_TRANSFORM_H

#include "newmath.h"
#include "BufferConvertor.h"

namespace Comrade {
    namespace IrisXT {

using namespace Comrade::IrisFoundation;

class HoughTransformObject
{
private:

public:     HoughTransformObject();
            virtual void transform(Buffer<RGB>* ip)=0;
            virtual ~HoughTransformObject();
};

class StraightLineDetector:public HoughTransformObject
{
private:    int rows,cols;
            int** param_array;

			void allocate(int r,int c);
            void deallocate();

public:     StraightLineDetector(int perp_levels,int theta_levels);

            int** return_array();
			void set_param(int perp_levels,int theta_levels);
            void transform(Buffer<RGB>* ip);

            ~StraightLineDetector();
};

}
}

#endif


