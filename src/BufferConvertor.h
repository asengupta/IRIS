#ifndef BUFFER_CONVERTOR_H
#define BUFFER_CONVERTOR_H

#include "Buffer.h"

namespace Comrade {
    namespace IrisFoundation {

class BufferConvertor
{
protected:

public:     BufferConvertor();
            static void RGB_to_HSL_buffer(Buffer<HSLstruct>* dest, Buffer<RGBstruct>* src);
            static void RGB_to_HSL_buffer(Buffer<HSLstruct>* dest, Buffer<RGB>* src);
            static void HSL_to_RGB_buffer(Buffer<RGBstruct>* dest, Buffer<HSLstruct>* src);
            static void HSL_to_RGB_buffer(Buffer<RGB>* dest, Buffer<HSLstruct>*src);
            ~BufferConvertor();
};

}
}

#endif

