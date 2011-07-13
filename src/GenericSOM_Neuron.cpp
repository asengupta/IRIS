#include "GenericSOM_Neuron.h"

Comrade::Osiris::FastSOM_Neuron::FastSOM_Neuron(int num_ip)
{
	num_inputs=num_ip;
	
	weight_vector.resize(num_inputs,0);
	input_vector.resize(num_inputs,0);
	set_activation_function(Comrade::Osiris::unipolar_hardlimiting);
}

void Comrade::Osiris::FastSOM_Neuron::set_x(int x)
{
	posx=x;	
}

void Comrade::Osiris::FastSOM_Neuron::set_y(int y)
{
	posy=y;
}

int Comrade::Osiris::FastSOM_Neuron::get_x()
{
	return posx;
}

int Comrade::Osiris::FastSOM_Neuron::get_y()
{
	return posy;
}
			
void Comrade::Osiris::FastSOM_Neuron::set_activation_function
(double (*fn)(double inner_product,double LAMBDA,double THRESHOLD))
{
	activation_fn=fn;
}

void Comrade::Osiris::FastSOM_Neuron::set_weight_vector
(const std::vector<double>& wt_vector)
{
	weight_vector=wt_vector;
}

void Comrade::Osiris::FastSOM_Neuron::set_input_vector
(const std::vector<double>& ip_vector)
{
	input_vector=ip_vector;
}

double Comrade::Osiris::FastSOM_Neuron::calculate_inner_product()
{
	double sum=0;
	
	for (int i=0; i<=weight_vector.size()-1; ++i)
	{
		sum+=input_vector[i]*weight_vector[i];
	}
	
	return sum;
}

void Comrade::Osiris::FastSOM_Neuron::calculate_output()
{
	double inprod=calculate_inner_product();
	output=activation_fn(inprod,0.5,0.5);
}

void Comrade::Osiris::FastSOM_Neuron::calculate_output
(const std::vector<double>& ip_vector)
{
	set_input_vector(ip_vector);
	calculate_output();
}

double Comrade::Osiris::FastSOM_Neuron::get_last_output()
{
	return output;
}

Comrade::Osiris::FastSOM_Neuron::~FastSOM_Neuron()
{}

			
