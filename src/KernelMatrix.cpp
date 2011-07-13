#include "KernelMatrix.h"

Comrade::IrisXT::KernelMatrix::KernelMatrix(int r,int c)
{
    matrix=new double*[r];

    for (int i=0; i<=c-1; i++)
    {
        matrix[i]=new double[c];
    }

    xsize=c;
    ysize=r;

    half_xsize=(xsize-1)/2;
    half_ysize=(ysize-1)/2;
}

void Comrade::IrisXT::KernelMatrix::set_values(double* arr)
{
    int u=0;

    for (int y=0; y<=ysize-1; y++)
    {
        for (int x=0; x<=xsize-1; x++)
        {
            matrix[y][x]=arr[u];
            u++;
        }
    }
}

Comrade::IrisXT::KernelMatrix::~KernelMatrix()
{
       for (int y=0; y<=ysize-1; y++)
       {
            delete[] matrix[y];
       }

       delete[] matrix;
}

Comrade::IrisXT::KernelOperator::KernelOperator()
{
    factor=1;
    cout<<"KernelOperator object created...\n";
}

// Deprecated, do NOT use this function. You can get by without it.
// ****************************************************************
//void KernelOperator::set_bounds(int x, int y)
//{
//    xsz=x;
//    ysz=y;
//}
// ****************************************************************

void Comrade::IrisXT::KernelOperator::set_bounds(BitmapStreamer* bmp_reader)
{
    reader=bmp_reader;

    xsz=reader->byte_reader.read_field(BMP_WIDTH,SZ_BMP_WIDTH);
    ysz=reader->byte_reader.read_field(BMP_HEIGHT,SZ_BMP_HEIGHT);
}

void Comrade::IrisXT::KernelOperator::convolve()
{
    convolve(1,1,xsz-2,ysz-2);
}

void Comrade::IrisXT::KernelOperator::convolve(int x1,int y1,int x2,int y2)
{
    //Gollum thief("IRIS-profile.txt");

    //clock_t start=clock();
    //cout<<"Start:"<<start<<endl<<"CLOCKS_PER_SEC is "<<CLOCKS_PER_SEC<<endl<<endl;

    //RGB val;
    HSLstruct cur_HSLtemp;
    RGBstruct cur_RGBtemp;

    //thief.log_now("\n1) Creating temporary HSL buffer...");

    /* Create temporary HSL buffer */
    Buffer<HSLstruct> hsl_ip(ip_buffer->maxx,ip_buffer->maxy);
    BufferConvertor::RGB_to_HSL_buffer(&hsl_ip,ip_buffer);

    /* Copy the image into the RGB buffer and initialise HSL ip buffer */
    //thief.log_now("2) Constructing HSL version of image...");

    //reader->goto_start();

    //thief.log_now("3) Convolving...");

    for (int y=y1; y<=y2; y++)
    {
        for (int x=x1; x<=x2; x++)
        {
            cur_HSLtemp=hsl_ip.at(x,y);
            double sum_luminance=unit_convolve(x,y,&hsl_ip);

            sum_luminance/=factor;

            sum_luminance=(sum_luminance>1)?1:sum_luminance;
            sum_luminance=(sum_luminance<0)?0:sum_luminance;

            cur_HSLtemp.luminance=sum_luminance;
            cur_RGBtemp=ColorSpaceConvertor::HSL_to_RGB(cur_HSLtemp);

            op_buffer->at(x,y).red=static_cast<unsigned char>(cur_RGBtemp.red*255);
            op_buffer->at(x,y).green=static_cast<unsigned char>(cur_RGBtemp.green*255);
            op_buffer->at(x,y).blue=static_cast<unsigned char>(cur_RGBtemp.blue*255);
        }
    }

    //thief.log_now("6) Convolution complete.");
}

double Comrade::IrisXT::KernelOperator::unit_convolve(int x,int y,Buffer<HSLstruct>* hsl_ip)
{
    double sum_luminance=0;

    int cand_x=x-rgb_kernel->half_xsize;
    int cand_y=y-rgb_kernel->half_ysize;

    int kernel_x=rgb_kernel->xsize;
    int kernel_y=rgb_kernel->ysize;

    for (int yy=0; yy<=rgb_kernel->ysize-1; yy++)
    {
        for (int xx=0; xx<=rgb_kernel->xsize-1; xx++)
        {
            int fx=cand_x+xx;
            int fy=cand_y+yy;

            if (fx>=0 && fx<=xsz-1 && fy>=0 && fy<=ysz-1)
            {
                double current_luminance=hsl_ip->at(fx,fy).luminance;
                double current_coefficient=rgb_kernel->matrix[(kernel_y-1)-yy][(kernel_x-1)-xx];
                sum_luminance+=(current_luminance*current_coefficient);
            }
        }
    }

    return sum_luminance;
}

double Comrade::IrisXT::KernelOperator::greyscale_unit_convolve(int x,int y,Buffer<RGB>* rgb_ip)
{
    double sum_luminance=0;

    int cand_x=x-rgb_kernel->half_xsize;
    int cand_y=y-rgb_kernel->half_ysize;

    int kernel_x=rgb_kernel->xsize;
    int kernel_y=rgb_kernel->ysize;

    for (int yy=0; yy<=rgb_kernel->ysize-1; yy++)
    {
        for (int xx=0; xx<=rgb_kernel->xsize-1; xx++)
        {
            int fx=cand_x+xx;
            int fy=cand_y+yy;

            if (fx>=0 && fx<=xsz-1 && fy>=0 && fy<=ysz-1)
            {
                unsigned char current_luminance=rgb_ip->at(fx,fy).green;
                double current_coefficient=rgb_kernel->matrix[(kernel_y-1)-yy][(kernel_x-1)-xx];
                sum_luminance+=(current_luminance*current_coefficient);
            }
        }
    }

    return sum_luminance;
}

Comrade::IrisXT::KernelOperator::~KernelOperator()
{}


