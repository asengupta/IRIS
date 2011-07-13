#ifndef STEREOVISION_H
#define STEREOVISION_H

#include <iostream>
#include <cmath>
#include <vector>
#include "BitmapStreamer.h"
#include "Correlator.h"

namespace Comrade {
	namespace Iris3D {

using namespace IrisFoundation;
		
class DepthmapBuilder
{
private:	int step_size;

public:		DepthmapBuilder();
		void set_stepsize(int step);
		void build_depthmap(Buffer<RGB>* left,
				    Buffer<RGB>* right,
				    Buffer<RGB>* dmap);
		
		~DepthmapBuilder();
};

}
}

#endif
