#include "ColorSpaces.h"

namespace Comrade{
    namespace IrisFoundation {

inline double max(double m1,double m2)
{
    return ((m1>=m2)?m1:m2);
}

inline double min(double m1,double m2)
{
    return ((m1<=m2)?m1:m2);
}

}
}

Comrade::IrisFoundation::ColorSpaceConvertor::ColorSpaceConvertor()
{}

Comrade::IrisFoundation::HSLstruct Comrade::IrisFoundation::ColorSpaceConvertor::RGB_to_HSL(RGBstruct& arg)
{
    double H,S,L;
    HSLstruct black={0,0,0};

    double R=arg.red;
    double G=arg.green;
    double B=arg.blue;

    L=max(R,max(G,B));

    if (L==0)
    {
        return black;
    }

    double X=min(R,min(G,B));

    S=(L-X)/L;

    if (S==0)
    {
        HSLstruct stopgap={0,0,L};
        return stopgap;
    }

    double R1=(L-R)/(L-X);
    double G1=(L-G)/(L-X);
    double B1=(L-B)/(L-X);

    if (R==L)
    {
        if (G==X)
        {
            H=5+B1;
        }

        else
        {
            H=1-G1;
        }
    }

    else if (G==L)
    {
        if (B==X)
        {
            H=R1+1;
        }

        else
        {
            H=3-B1;
        }
    }

    else
    {
        if (R==X)
        {
            H=3+G1;
        }

        else
        {
            H=5-R1;
        }
    }

    H*=60;

    HSLstruct ans={H,S,L};

    return ans;
}

Comrade::IrisFoundation::RGBstruct Comrade::IrisFoundation::ColorSpaceConvertor::HSL_to_RGB(HSLstruct& arg)
{
    double H,S,L;

    H=arg.hue;
    S=arg.saturation;
    L=arg.luminance;

    double H1,A[7];
    double R,G,B;

    H1=H/60.;
    int i=static_cast<int>(H1);
    double F=H1-i;

    A[0]=L;
    A[1]=L;
    A[2]=L;
    A[3]=L*(1-(S*F));
    A[4]=L*(1-S);
    A[5]=A[3];
    A[6]=L*(1-(S*(1-F)));

    if (i>4)
    {
        i-=4;
    }

    else
    {
        i+=2;
    }

    R=A[i];

    if (i>4)
    {
        i-=4;
    }

    else
    {
        i+=2;
    }

    B=A[i];

    if (i>4)
    {
        i-=4;
    }

    else
    {
        i+=2;
    }

    G=A[i];

    RGBstruct ret={R,G,B};

    return ret;
}

Comrade::IrisFoundation::HSLstruct Comrade::IrisFoundation::ColorSpaceConvertor::uRGB_to_HSL(RGB& arg)
{
    RGBstruct xarg={arg.red/255.0,arg.green/255.0,arg.blue/255.0};

    return (RGB_to_HSL(xarg));
}

Comrade::IrisFoundation::RGB Comrade::IrisFoundation::ColorSpaceConvertor::HSL_to_uRGB(HSLstruct& arg)
{
    RGBstruct ans=HSL_to_RGB(arg);
    RGB xans;
    xans.red=static_cast<char>(ans.red*255);
    xans.green=static_cast<char>(ans.green*255);
    xans.blue=static_cast<char>(ans.blue*255);

    return xans;
}
            
Comrade::IrisFoundation::ColorSpaceConvertor::~ColorSpaceConvertor()
{}


