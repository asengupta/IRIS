#ifndef RUNTIME_POOL_H
#define RUNTIME_POOL_H

#include <iostream>
#include "ModelBuilder.h"
#include "BitmapStreamer.h"
#include "KernelMatrix.h"
#include "NonkernelAlgorithms.h"
#include "MiscRoutines.h"
#include "HoughTransform.h"
#include "AutomataEdge.h"
#include "AutomataSkeleton.h"
#include "EdgeDetectors.h"
#include "SpecialKernels.h"
#include "StereoVision.h"
#include "QuadtreeSegmenter.h"

namespace Comrade {
	namespace IrisRuntime {
		
using namespace Comrade::IrisFoundation;
using namespace Comrade::IrisXT;
using namespace Comrade::Iris3D;

class IrisObjectPool
{
public:   RGB_BufferManager man1,man2,man3;
          BitmapStreamer bmp1,bmp2,bmp3;
          Tree<Rectangle,Coordinate>* pooltree;
          QuadtreeSegmenter seger;
          DepthmapBuilder stereomapper;
          AlgorithmManager algoman;
          StraightLineDetector* linedet;
          EdgeDetectorManager edgeman;
          KernelOperator kernelop;          

public:		IrisObjectPool();
		      ~IrisObjectPool();	
};

}
}

#endif
