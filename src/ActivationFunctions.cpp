#include "ActivationFunctions.h"

double Comrade::Osiris::bipolar_softlimiting(double sum,double LAMBDA,double THRESHOLD)
{
	return (2./(1.+exp(-LAMBDA*sum))-1);
}

double Comrade::Osiris::unipolar_softlimiting(double sum,double LAMBDA,double THRESHOLD)
{
	return (1./(1.+exp(-LAMBDA*sum)));
}

double Comrade::Osiris::bipolar_hardlimiting(double sum,double LAMBDA,double THRESHOLD)
{
	if (sum>=THRESHOLD)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

double Comrade::Osiris::unipolar_hardlimiting(double sum,double LAMBDA,double THRESHOLD)
{
	if (sum>=THRESHOLD)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

double Comrade::Osiris::unipolar_hardlimiting1(double sum,double LAMBDA,double THRESHOLD)
{
	if (sum>=1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

