#ifndef SOM_TRAINER_H
#define SOM_TRAINER_H

#include "NeuronMap.h"

namespace Comrade {
    namespace Osiris {
    
class SOM_Trainer
{
protected:	NeuronMap* trainee;
			int time;

public:		double sigma_0;
			double tau_1;
			double learn_rate;
            long int time_step;
            
			SOM_Trainer();

			void assign_map(NeuronMap* nmap);
			void reset_time();
			void train();
			
			~SOM_Trainer();
};

}
}

#endif


