#include "newmath.h"

double Comrade::IrisFoundation::deg_to_rad(double degrees)
{
	return (PI*degrees)/180.0;
}

double Comrade::IrisFoundation::rad_to_deg(double rad)
{
	return (PI/rad)*180.0;
}

int Comrade::IrisFoundation::sign(double val)
{
	if (val>0)
    {
		return 1;
    }

	else if (val<0)
    {
		return -1;
    }

	else
    {
		return 0;
    }
}


