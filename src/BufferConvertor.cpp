#include "BufferConvertor.h"

Comrade::IrisFoundation::BufferConvertor::BufferConvertor()
{}

void Comrade::IrisFoundation::BufferConvertor::RGB_to_HSL_buffer(Buffer<HSLstruct>* dest, Buffer<RGBstruct>* src)
{
    if ((dest->maxx!=src->maxx) || (dest->maxy!=src->maxy))
    {
        cout<<"Unequal sizes. Cannot convert.\n";
    }

    else
    {
        for (int y=0; y<=(dest->maxy)-1; y++)
        {
            for (int x=0; x<=(dest->maxx)-1; x++)
            {
                dest->buffer_ptr[y][x]=ColorSpaceConvertor::RGB_to_HSL(src->buffer_ptr[y][x]);
            }
        }
    }
}

void Comrade::IrisFoundation::BufferConvertor::RGB_to_HSL_buffer(Buffer<HSLstruct>* dest, Buffer<RGB>* src)
{
    if ((dest->maxx!=src->maxx) || (dest->maxy!=src->maxy))
    {
        cout<<"Unequal sizes. Cannot convert.\n";
    }

    else
    {
        for (int y=0; y<=(dest->maxy)-1; y++)
        {
            for (int x=0; x<=(dest->maxx)-1; x++)
            {
                RGB& tmp=src->buffer_ptr[y][x];
                RGBstruct temporary={tmp.red/255.0,tmp.green/255.0,tmp.blue/255.0};

                dest->buffer_ptr[y][x]=ColorSpaceConvertor::RGB_to_HSL(temporary);
            }
        }
    }
}

void Comrade::IrisFoundation::BufferConvertor::HSL_to_RGB_buffer(Buffer<RGBstruct>* dest, Buffer<HSLstruct>*src)
{
    if ((dest->maxx!=src->maxx) || (dest->maxy!=src->maxy))
    {
        cout<<"Unequal sizes. Cannot convert.\n";
    }

    else
    {
        for (int y=0; y<=(dest->maxy)-1; y++)
        {
            for (int x=0; x<=(dest->maxx)-1; x++)
            {
                dest->buffer_ptr[y][x]=ColorSpaceConvertor::HSL_to_RGB(src->buffer_ptr[y][x]);
            }
        }
    }
}

void Comrade::IrisFoundation::BufferConvertor::HSL_to_RGB_buffer(Buffer<RGB>* dest, Buffer<HSLstruct>* src)
{
    if ((dest->maxx!=src->maxx) || (dest->maxy!=src->maxy))
    {
        cout<<"Unequal sizes. Cannot convert.\n";
    }

    else
    {
        for (int y=0; y<=(dest->maxy)-1; y++)
        {
            for (int x=0; x<=(dest->maxx)-1; x++)
            {
                RGBstruct tmp=ColorSpaceConvertor::HSL_to_RGB(src->buffer_ptr[y][x]);
                RGB temporary;

                temporary.red=static_cast<unsigned char>(tmp.red*255);
                temporary.green=static_cast<unsigned char>(tmp.green*255);
                temporary.blue=static_cast<unsigned char>(tmp.blue*255);

                dest->buffer_ptr[y][x]=temporary;
            }
        }
    }
}

Comrade::IrisFoundation::BufferConvertor::~BufferConvertor()
{}

