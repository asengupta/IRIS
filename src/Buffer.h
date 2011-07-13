#ifndef BUFFER_H
#define BUFFER_H

#include <cassert>
#include "BitmapStreamer.h"

namespace Comrade {
    namespace IrisFoundation {

#define DEFAULT_X 320
#define DEFAULT_Y 240

#define NO_ERROR 0
#define OUT_OF_RANGE_ERROR 1

// NOTE: Copy constructor has not been defined (yet)
// so don't try to assign one buffer to another, use
// the member function given - copy_from()

template <typename Generic>
class Buffer
{
public:     Generic** buffer_ptr;
            int maxy,maxx;
            bool error_code;

public:     Buffer();
            Buffer(int x,int y);
            Buffer(BitmapStreamer* bmp_reader);
            Buffer(const Buffer& buf);
            Buffer& operator=(const Buffer& buf);

            /* The reallocate() functions have not been tested
               fully. So, use them with care. */

            void reallocate(int x,int y);
            void reallocate(BitmapStreamer* bmp_reader);

            void copy_from(const Buffer<Generic>* buffer,
                           int x1,int y1,
                           int x2,int y2,
                           int destx,int desty);

            void copy_from(const Buffer<Generic>* buffer);
            inline Generic& at(int posx,int posy);
            ~Buffer();
};

class BufferManager
{
protected:

public:     BufferManager();
            ~BufferManager();
};

class RGB_BufferManager:public BufferManager
{
protected:  RGB** buffer_ptr;
            int maxx,maxy; // Note: maxx, maxy are used only
                           // by the copy_from_image() and
                           // copy_to_image() functions.
                           // No other significance of them.

public:     RGB_BufferManager();

            void assign_buffer(Buffer<RGB>* buf);
            void copy_from_image(BitmapStreamer* bmp_reader);
            void copy_to_image(BitmapStreamer* bmp_reader);
            void block_copy_from_image(BitmapStreamer* bmp_reader,
                                       int x1,int y1,int x2,int y2,
                                       int destx,int desty);
            void block_copy_to_image(BitmapStreamer* bmp_reader,
                                     int x1,int y1,int x2,int y2,
                                     int destx,int desty);
            
            ~RGB_BufferManager();
};

template <typename Generic>
Buffer<Generic>::Buffer()
{
    cout<<"Buffer object created...\n";

    maxx=DEFAULT_X;
    maxy=DEFAULT_Y;

    buffer_ptr=new Generic*[maxy];

    for (int i=0; i<=maxy-1; i++)
    {
        buffer_ptr[i]=new Generic[maxx];
    }
}

template <typename Generic>
Buffer<Generic>::Buffer(int x,int y)
{
    cout<<"Buffer object created...\n";

    maxx=x;
    maxy=y;

    buffer_ptr=new Generic*[maxy];

    for (int i=0; i<=maxy-1; i++)
    {
        buffer_ptr[i]=new Generic[maxx];
    }
}

template <typename Generic>
Buffer<Generic>::Buffer(BitmapStreamer* bmp_reader)
{
    cout<<"Buffer object created...\n";

    maxx=bmp_reader->byte_reader.read_field(BMP_WIDTH,SZ_BMP_WIDTH);
    maxy=bmp_reader->byte_reader.read_field(BMP_HEIGHT,SZ_BMP_HEIGHT);

    buffer_ptr=new Generic*[maxy];

    for (int i=0; i<=maxy-1; i++)
    {
        buffer_ptr[i]=new Generic[maxx];
    }
}

template <typename Generic>
Buffer<Generic>::Buffer(const Buffer<Generic>& buf)
{
    reallocate(buf.maxx,buf.maxy);

    copy_from(&buf);
}

template <typename Generic>
Buffer<Generic>&
Buffer<Generic>::operator=(const Buffer<Generic>& buf)
{
    reallocate(buf.maxx,buf.maxy);

    copy_from(&buf);

    return (*this);
}

template <typename Generic>
void Buffer<Generic>::reallocate(int x,int y)
{
    cout<<"Freeing old memory...\n";

    for (int i=0; i<=maxy-1; i++)
    {
        delete[] buffer_ptr[i];
    }

    delete[] buffer_ptr;

    cout<<"Reallocating memory...\n";

    maxx=x;
    maxy=y;

    buffer_ptr=new Generic*[maxy];

    for (int i=0; i<=maxy-1; i++)
    {
        buffer_ptr[i]=new Generic[maxx];
    }

    error_code=NO_ERROR;
    cout<<"Done.\n";
}

template <typename Generic>
void Buffer<Generic>::reallocate(BitmapStreamer* bmp_reader)
{
    cout<<"Freeing old memory...\n";

    for (int i=0; i<=maxy-1; i++)
    {
        delete[] buffer_ptr[i];
    }

    delete[] buffer_ptr;

    cout<<"Reallocating memory...\n";

    maxx=bmp_reader->byte_reader.read_field(BMP_WIDTH,SZ_BMP_WIDTH);
    maxy=bmp_reader->byte_reader.read_field(BMP_HEIGHT,SZ_BMP_HEIGHT);

    buffer_ptr=new Generic*[maxy];

    for (int i=0; i<=maxy-1; i++)
    {
        buffer_ptr[i]=new Generic[maxx];
    }

    error_code=NO_ERROR;
    cout<<"Done.\n";
}

template <typename Generic>
void Buffer<Generic>::copy_from(const Buffer<Generic>* buffer)
{
    copy_from(buffer,0,0,maxx-1,maxy-1,0,0);
}

template <typename Generic>
void Buffer<Generic>::copy_from(const Buffer<Generic>* buffer,
                                int x1,int y1,
                                int x2,int y2,
                                int destx,int desty)
{
    int stx=destx,sty=desty;

    for (int y=y1; y<=y2; y++)
    {
        stx=destx;

        for (int x=x1; x<=x2; x++)
        {
            buffer_ptr[sty][stx]=buffer->buffer_ptr[y][x];
            stx++;
        }

        sty++;
    }

    error_code=NO_ERROR;
}

template <typename Generic>
inline Generic& Buffer<Generic>::at(int posx,int posy)
{
    if (posx>=0 && posx<=maxx-1 && posy>=0 && posy<=maxy-1)
    {
        error_code=NO_ERROR;
    }

    else
    {
        //cout<<"Warning: returning min/max posn...\n";

        posx=(posx<0)?0:posx;
        posx=(posx>maxx-1)?(maxx-1):posx;

        posy=(posy<0)?0:posy;
        posy=(posy>maxy-1)?(maxy-1):posy;

        error_code=OUT_OF_RANGE_ERROR;
        //cout<<"Index out of bounds - don't know what to return...\n";
        //assert(posx>=0 && posx<=maxx-1 && posy>=0 && posy<=maxy-1);
    }

    return buffer_ptr[posy][posx];
}

template <typename Generic>
Buffer<Generic>::~Buffer()
{
    for (int i=0; i<=maxy-1; i++)
    {
        delete[] buffer_ptr[i];
    }

    delete[] buffer_ptr;
}

}
}

#endif

