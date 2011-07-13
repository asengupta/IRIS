#ifndef COLOR_SPACES_H
#define COLOR_SPACES_H

#include <iostream>

namespace Comrade {
    namespace IrisFoundation {

enum Channel {RED,GREEN,BLUE};

inline double max(double m1,double m2);
inline double min(double m1,double m2);

struct RGBstruct
{
    double red;
    double green;
    double blue;
};

struct RGB
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

struct HSLstruct
{
    double hue;
    double saturation;
    double luminance;
//    bool marked; // This should be removed in the final version.
};

class ColorSpaceConvertor
{
protected:

public:     ColorSpaceConvertor();
            static HSLstruct RGB_to_HSL(RGBstruct& arg);
            static RGBstruct HSL_to_RGB(HSLstruct& arg);
            static HSLstruct uRGB_to_HSL(RGB& arg);
            static RGB HSL_to_uRGB(HSLstruct& arg);
            ~ColorSpaceConvertor();
};

}
}

#endif

