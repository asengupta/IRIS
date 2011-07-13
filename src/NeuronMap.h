#ifndef NEURON_MAP_H
#define NEURON_MAP_H

#include "Buffer.h"
#include "GenericSOM_Neuron.h"

namespace Comrade {
	namespace Osiris {

using namespace Comrade::IrisFoundation;
		
class NeuronMap:private Buffer<FastSOM_Neuron>
{
protected:

public:		NeuronMap(int rows,int cols);
			
			FastSOM_Neuron& at(int row,int col);
			
			~NeuronMap();
};
	
}
}

#endif

