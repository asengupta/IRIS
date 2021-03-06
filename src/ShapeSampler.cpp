#include "ShapeSampler.h"
#include <cmath>

Comrade::IrisXT::ShapeSampler::ShapeSampler()
{
    build_sin_table();
    build_cos_table();
}

void Comrade::IrisXT::ShapeSampler::build_sin_table()
{
    for (int i=0; i<=359; i++)
    {
        sin_table[i]=std::sin(3.1415927*i/180.);
    }
}

void Comrade::IrisXT::ShapeSampler::build_cos_table()
{
    for (int i=0; i<=359; i++)
    {
        cos_table[i]=std::cos(3.1415927*i/180.);
    }
}

void Comrade::IrisXT::ShapeSampler::sample(Buffer<RGB>* ip_buffer,
                                           std::vector<double>* radial,
                                           int no,int cx,int cy)
{
    for (int ang=0; ang<=359; ang+=360/no)
    {
        bool flag=false;

        double sx=static_cast<double>(cx);
        double sy=static_cast<double>(cy);

        while (sx>=0 && sx<=ip_buffer->maxx-1 &&
               sy>=0 && sy<=ip_buffer->maxy-1)
        {
            int isx=static_cast<int>(sx);
            int isy=static_cast<int>(sy);

            RGB check=ip_buffer->at(isx,isy);

            if (check.red>=150 || check.green>=150 ||
                check.blue>=150)
            {
                double distance=static_cast<double>(std::sqrt((isx-cx)*(isx-cx)+(isy-cy)*(isy-cy)));
                radial->push_back(distance);
                flag=true;
                break;
            }

            sx+=cos_table[ang];
            sy-=sin_table[ang];
        }

        if (flag==false)
        {
            radial->push_back(-1);
        }
    }
}

Comrade::IrisXT::ShapeSampler::~ShapeSampler()
{}


