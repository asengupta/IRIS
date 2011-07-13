#include "SpecialKernels.h"

Comrade::IrisXT::KernelGenerator::KernelGenerator()
{
    cout<<"KernelGenerator object created...\n";
}

void Comrade::IrisXT::KernelGenerator::generate_Gaussian(KernelMatrix* ker,
                                        double std_dev)
{
    int lx=ker->xsize;
    int ly=ker->ysize;

    int hx=(lx-1)/2;
    int hy=(ly-1)/2;

    for (int yy=-hy; yy<=hy; yy++)
    {
        for (int xx=-hx; xx<=hx; xx++)
        {
            ker->matrix[hy+yy][hx+xx]=exp(-(xx*xx+yy*yy)/
                                         (2*std_dev*std_dev));
        }
    }
}

void Comrade::IrisXT::KernelGenerator::generate_RobertsCross(KernelMatrix* H1,
                                            KernelMatrix* H2)
{
    double arr1[]={ 0, 0, 0,
                    0, 0, 1,
                    0,-1, 0};

    double arr2[]={ 0, 0, 0,
                    0, 1, 0,
                    0, 0,-1};

    H1->set_values(arr1);
    H2->set_values(arr2);
}

void Comrade::IrisXT::KernelGenerator::generate_Sobel(KernelMatrix* H1,
                                     KernelMatrix* H2)
{
    double arr1[]={-1, 0, 1,
                   -2, 0, 2,
                   -1, 0, 1};

    double arr2[]={ 1, 2, 1,
                    0, 0, 0,
                   -1,-2,-1};

    H1->set_values(arr1);
    H2->set_values(arr2);
}

void Comrade::IrisXT::KernelGenerator::generate_Prewitt(KernelMatrix* H1,
                                       KernelMatrix* H2)
{
    double arr1[]={-1, 0, 1,
                   -1, 0, 1,
                   -1, 0, 1};

    double arr2[]={-1,-1,-1,
                    0, 0, 0,
                    1, 1, 1};

    H1->set_values(arr1);
    H2->set_values(arr2);
}

void Comrade::IrisXT::KernelGenerator::generate_isotropic(KernelMatrix* H1,
                                         KernelMatrix* H2)
{
    double arr1[]={-1, 0, 1,
                   -1.414, 0, 1.414,
                   -1, 0, 1};

    double arr2[]={-1,-1.414,-1,
                    0, 0, 0,
                    1, 1.414, 1};

    H1->set_values(arr1);
    H2->set_values(arr2);
}

void Comrade::IrisXT::KernelGenerator::generate_Laplacian(KernelMatrix* H1,
                                         KernelMatrix* H2)
{
    double arr1[]={ 1,-2, 1,
                   -2, 4,-2,
                   -1,-2, 1};

    double arr2[]={ 0, 0, 0,
                    0, 0, 0,
                    0, 0, 0};

    H1->set_values(arr1);
    H2->set_values(arr2);
}

Comrade::IrisXT::KernelGenerator::~KernelGenerator()
{}


