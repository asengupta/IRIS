#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H

#include <cmath>

namespace Comrade {
	namespace Osiris {

double bipolar_softlimiting(double sum,double LAMBDA,double THRESHOLD);
double unipolar_softlimiting(double sum,double LAMBDA,double THRESHOLD);
double bipolar_hardlimiting(double sum,double LAMBDA,double THRESHOLD);
double unipolar_hardlimiting(double sum,double LAMBDA,double THRESHOLD);
double unipolar_hardlimiting1(double sum,double LAMBDA,double THRESHOLD);

}
}

#endif

