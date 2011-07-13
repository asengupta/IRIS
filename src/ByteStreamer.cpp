#include "ByteStreamer.h"

Comrade::IrisFoundation::ByteStreamer::ByteStreamer()
{
    cout<<"ByteStreamer object created...\n";

    check_type_sizes();
}

void Comrade::IrisFoundation::ByteStreamer::check_type_sizes()
{
    cout<<"Checking type sizes...\n";

    cout<<"sizeof(unsigned char)="<<sizeof(unsigned char)<<endl;
    cout<<"sizeof(int)="<<sizeof(int)<<endl;
    cout<<"sizeof(short int)="<<sizeof(short int)<<endl;

    if (sizeof(unsigned char)!=1)
    {
        cout<<"unsigned char is not 1 byte: code will malfunction.\n";
    }

    else
    {
        cout<<"unsigned char passed test.\n";
    }

    if (sizeof(int)!=4)
    {
        cout<<"int is not 4 bytes: code will malfunction.\n";
    }

    else
    {
        cout<<"int passed test.\n";
    }

    if (sizeof(short int)!=2)
    {
        cout<<"short int is not 2 bytes: code will malfunction.\n";
    }

    else
    {
        cout<<"short int passed test.\n";
    }
}

void Comrade::IrisFoundation::ByteStreamer::read(short& val)
{
    if (reader.eof()==false)
    {
        reader.read(reinterpret_cast<char*>(&val),sizeof(short));
    }
}

void Comrade::IrisFoundation::ByteStreamer::read(int& val)
{
    if (reader.eof()==false)
    {
        reader.read(reinterpret_cast<char*>(&val),sizeof(int));

    }
}

/*void Comrade::IrisFoundation::ByteStreamer::read(char& val)
{
    if (reader.eof()==false)
    {
        reader.read(reinterpret_cast<char*>(&val),sizeof(char));
    }
}*/

void Comrade::IrisFoundation::ByteStreamer::read(unsigned char& val)
{
    if (reader.eof()==false)
    {
        reader.read(reinterpret_cast<char*>(&val),sizeof(char));
    }
}

int Comrade::IrisFoundation::ByteStreamer::read_field(int field_offset,int field_size)
{
    short sx;
    int ix;
    int ans=-1;

/*    if (reader.is_open())
    {
        cout<<"File is open...\n";
    }

    else
    {
        cout<<"File is not open...\n";
    }*/

    reader.seekg(field_offset,ios::beg);

    if (field_size==4)
    {
        read(ix);
        ans=ix;
    }

    if (field_size==2)
    {
        read(sx);
        ans=sx;
    }

    return ans;
}

Comrade::IrisFoundation::ByteStreamer::~ByteStreamer()
{
    if (reader.is_open()==true)
    {
        reader.close();
    }
}

