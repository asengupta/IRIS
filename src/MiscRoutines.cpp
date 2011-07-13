#include "MiscRoutines.h"

double Comrade::IrisXT::regression(Buffer<RGB>* buffer)
{
    double ans;

    long double A[2][2]={{0,0},{0,0}};
    long double b[2][1]={{0},{0}};

    int lim_x=buffer->maxx;
    int lim_y=buffer->maxy;

    for (int y=0; y<=lim_y-1; y++)
    {
        for (int x=0; x<=lim_x-1; x++)
        {
            RGB val=buffer->at(x,(lim_y-1)-y);

            if (val.red>=200)// && val.green<=10 && val.blue<=10)
            {
                //cout<<"Selected:x="<<x<<",y="<<y<<endl;

                A[0][0]++;
                A[0][1]+=x;
                A[1][1]+=(x*x);

                b[0][0]+=y;
                b[1][0]+=(x*y);
            }
        }
    }

    A[1][0]=A[0][1]; // Important step

    long double det=fabs(A[0][0]*A[1][1]-A[0][1]*A[1][0]);

    if (det==0)
    {
        return 90;
    }

    long double AX[2][2]={{-A[1][1]/det, A[0][1]/det},
                     { A[1][0]/det,-A[0][0]/det}};

    long double a0=AX[0][0]*b[0][0]+AX[0][1]*b[1][0];
    long double a1=AX[1][0]*b[0][0]+AX[1][1]*b[1][0];

    if (a1<0 && a0<0)
    {
        a1=fabs(a1);
        a0=fabs(a0);
    }

    if (a1>=0 && a0<0)
    {
        a1=-a1;
        a0=-a0;
    }

    cout<<"Equation is: y="<<a1<<"x+("<<a0<<")";
    int sign=(a0>=0)?1:-1;
    ans=atan2(a1,sign)*180./3.1415926;

    return ans;
}

