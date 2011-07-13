#include "BitmapStreamer.h"

Comrade::IrisFoundation::BitmapStreamer::BitmapStreamer()
{
    cout<<"BitmapStreamer object created...\n";
}

int Comrade::IrisFoundation::BitmapStreamer::read_raw_image(int index)
{
    int off=byte_reader.read_field(OFFSET,SZ_OFFSET);
    byte_reader.reader.seekg(off+index,ios::beg);
    unsigned char ch;
    byte_reader.read(ch);

    return static_cast<int>(ch);
}

void Comrade::IrisFoundation::BitmapStreamer::goto_start()
{
    int off=byte_reader.read_field(OFFSET,SZ_OFFSET);
    byte_reader.reader.seekg(off,ios::beg);
    byte_reader.writer.seekp(off,ios::beg);
}

void Comrade::IrisFoundation::BitmapStreamer::read_RGB(RGB& value)
{
    //byte_reader.read(value.blue);
    //byte_reader.read(value.green);
    //byte_reader.read(value.red);

    byte_reader.reader.read(reinterpret_cast<char*>(&value),sizeof(value));

    //byte_reader.reader.seekg(-3,ios::cur);
    //byte_reader.reader.seekg(-3,ios::cur);
}

void Comrade::IrisFoundation::BitmapStreamer::read_RGB(int x,int y,RGB& val)
{
    int off=byte_reader.read_field(OFFSET,SZ_OFFSET);
    int xsz=byte_reader.read_field(BMP_WIDTH,SZ_BMP_WIDTH);
    int ysz=byte_reader.read_field(BMP_HEIGHT,SZ_BMP_HEIGHT);
    y=ysz-y-1;
    int index=(y*xsz+x)*3;

    byte_reader.reader.seekg(off+index,ios::beg);
    RGB v;
    read_RGB(v);

    val=v;
}

void Comrade::IrisFoundation::BitmapStreamer::write_RGB(RGB& val)
{
    byte_reader.writer.write(reinterpret_cast<char*>(&val),sizeof(val));
    //byte_reader.reader.write(reinterpret_cast<char*>(&val.green),sizeof(val.green));
    //byte_reader.reader.write(reinterpret_cast<char*>(&val.red),sizeof(val.red));
}

int Comrade::IrisFoundation::BitmapStreamer::seq_read()
{
    unsigned char ch;
    byte_reader.read(ch);
    byte_reader.reader.seekg(-1,ios::cur);

    return static_cast<int>(ch);
}

void Comrade::IrisFoundation::BitmapStreamer::seq_write(int value)
{
    unsigned char ch=static_cast<char>(value);
    byte_reader.writer.write(reinterpret_cast<char*>(&ch),sizeof(ch));
}

void Comrade::IrisFoundation::BitmapStreamer::write_RGB(int x,int y,RGB value)
{
     int off=byte_reader.read_field(OFFSET,SZ_OFFSET);
     int xsz=byte_reader.read_field(BMP_WIDTH,SZ_BMP_WIDTH);
     int ysz=byte_reader.read_field(BMP_HEIGHT,SZ_BMP_HEIGHT);
     y=ysz-y-1;
     int index=(y*xsz+x)*3;

     byte_reader.writer.seekp(off+index,ios::beg);
     byte_reader.writer.write(reinterpret_cast<char*>(&value),sizeof(value));

     //write_raw_image(index,value);
     //write_raw_image(index+1,value);
     //write_raw_image(index+2,value);
}

void Comrade::IrisFoundation::BitmapStreamer::write_raw_image(int index,int value)
{
     int off=byte_reader.read_field(OFFSET,SZ_OFFSET);
     byte_reader.writer.seekp(off+index,ios::beg);
     unsigned char ch=static_cast<unsigned char>(value);
     byte_reader.writer.write(reinterpret_cast<char*>(&ch),sizeof(ch));
}

Comrade::IrisFoundation::BitmapStreamer::~BitmapStreamer()
{}

