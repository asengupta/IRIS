#include "SOM_Trainer.h"

Comrade::Osiris::SOM_Trainer::SOM_Trainer()
{
    time_step=0;
}

void Comrade::Osiris::SOM_Trainer::assign_map(NeuronMap* nmap)
{
	trainee=nmap;
}

void Comrade::Osiris::SOM_Trainer::reset_time()
{
    time_step=0;	
}

void Comrade::Osiris::SOM_Trainer::train()
{
    ++time_step;
}

Comrade::Osiris::SOM_Trainer::~SOM_Trainer()
{}

