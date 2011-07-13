#ifndef BYTE_READER_H
#define BYTE_READER_H

#include <fstream>
#include <iostream>

namespace Comrade {
    namespace IrisFoundation {

using std::cout;
using std::cin;
using std::fstream;
using std::ios;
using std::endl;

class ByteStreamer
{
protected:      //char filename[20];

public:         std::fstream reader;
                std::fstream writer;


                ByteStreamer();
                void check_type_sizes();
                void read(short& val);
                void read(int& val);
                //void read(char& val);
                void read(unsigned char& val);
                int read_field(int field_offset,int field_size);
                ~ByteStreamer();
};

}
}

#endif

