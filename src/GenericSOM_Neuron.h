#ifndef GENERIC_SOM_NEURON_H
#define GENERIC_SOM_NEURON_H

#include <vector>
#include "ActivationFunctions.h"

namespace Comrade {
	namespace Osiris {
		
class FastSOM_Neuron
{
protected:	int num_inputs;
			
			int posx,posy;
			std::vector<double> input_vector;
			std::vector<double> weight_vector;
			
			double output;
			double (*activation_fn)(double inner_product,double LAMBDA,double THRESHOLD);

public:		FastSOM_Neuron(int num_ip=100);
			
			inline void set_x(int x);
			inline void set_y(int y);
			inline int get_x();
			inline int get_y();
			
			void set_weight_vector(const std::vector<double>& wt_vector);
			void set_input_vector(const std::vector<double>& ip_vector);
			void set_activation_function(double (*fn)(double inner_product,double LAMBDA,double THRESHOLD));
			double calculate_inner_product();
			void calculate_output();
			void calculate_output(const std::vector<double>& ip_vector);
			double get_last_output();
			
			~FastSOM_Neuron();
};

}
}

#endif

