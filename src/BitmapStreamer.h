#ifndef BITMAP_STREAMER_H
#define BITMAP_STREAMER_H

#include "ByteStreamer.h"
#include "ColorSpaces.h"

namespace Comrade {
    namespace IrisFoundation {

#define FILE_TYPE 0
#define FILE_SIZE 2
#define RESERVED 6
#define OFFSET 10
#define STRUCT_SIZE 14
#define BMP_WIDTH 18
#define BMP_HEIGHT 22
#define COLOR_PLANES 26
#define BPP 28
#define COMPRESSION 30
#define IMAGE_SIZE 34
#define HOR_RES 38
#define VER_RES 42
#define COLS_USED 46
#define COLS_IMP 50

#define SZ_FILE_TYPE 2
#define SZ_FILE_SIZE 4
#define SZ_RESERVED 4
#define SZ_OFFSET 4
#define SZ_STRUCT_SIZE 4
#define SZ_BMP_WIDTH 4
#define SZ_BMP_HEIGHT 4
#define SZ_COLOR_PLANES 2
#define SZ_BPP 2
#define SZ_COMPRESSION 4
#define SZ_IMAGE_SIZE 4
#define SZ_HOR_RES 4
#define SZ_VER_RES 4
#define SZ_COLS_USED 4
#define SZ_COLS_IMP 4

//struct HSL
//{
//    int hue;
//    long saturation;
//    long luminance;
//};

class BitmapStreamer
{
protected:

public:     ByteStreamer byte_reader;

            BitmapStreamer();
            int seq_read();
            void seq_write(int value);
            void goto_start();
            void read_RGB(RGB& value);
            void read_RGB(int x,int y,RGB& value);
            void write_RGB(int x,int y,RGB value);
            void write_RGB(RGB& value);
            int read_raw_image(int index);
            void write_raw_image(int index,int value);
            ~BitmapStreamer();
};

}
}

#endif

