#include "Correlator.h"

double Comrade::Iris3D::correlate(Buffer<RGB>* buffer1,
                                  Buffer<RGB>* buffer2,
                                  int x1,int y1,int x2,int y2,
                                  int bx,int by)
{
    double sum=0;
    double total=0;

    for (int yy=y1; yy<=y2; yy++)
    {
        for (int xx=x1; xx<=x2; xx++)
        {
            if (xx>=buffer1->maxx-1 ||
                yy>=buffer1->maxy-1 ||
                bx+xx-x1>=buffer2->maxx-1 ||
                by+yy-y1>=buffer2->maxy-1)
            {
                continue;
            }

            double val1=buffer1->at(xx,yy).green/255.0;
            double val2=buffer2->at(bx+xx-x1,by+yy-y1).green/255.0;

            sum+=(val1-val2)*(val1-val2);
            total++;
        }
    }

    sum/=total;

    return sum;
}


