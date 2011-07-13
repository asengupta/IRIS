#ifndef VARIANCE_DETECTOR_H
#define VARIANCE_DETETCTOR_H

#include <cmath>
#include <vector>
#include "NonkernelAlgorithms.h"

using namespace std;
using namespace Comrade::IrisFoundation;

struct InterestArea
{
    int x,y;
    //int rx,ry;
    //double variance;
    double mean;
    double dirn[4];
};

void blank_variances(Buffer<HSLstruct>& buffer,double threshold,int bound);
int build_scanline_map(Buffer<HSLstruct>& buffer,double threshold,vector<InterestArea>& itbl);
void direction_op(Buffer<HSLstruct>& buffer,int x,int y,int bound,double arr[4]);
void stereo_correlate(vector<InterestArea>& vecleft,
                      vector<InterestArea>& vecright);

#endif

