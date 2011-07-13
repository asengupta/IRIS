#include "NeuronMap.h"

Comrade::Osiris::NeuronMap::NeuronMap(int rows,int cols):Buffer<FastSOM_Neuron>(cols,rows)
{}

Comrade::Osiris::FastSOM_Neuron& Comrade::Osiris::NeuronMap::at(int row,int col)
{
	return Comrade::IrisFoundation::Buffer<FastSOM_Neuron>::at(col,row);
}

Comrade::Osiris::NeuronMap::~NeuronMap()
{}

