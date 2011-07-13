#include "AutomataEdge.h"

Comrade::IrisXT::CA_EdgeDetector::CA_EdgeDetector()
{
    lim_x=lim_y=5;
    threshold=0.165;
    quorum=16;
}

void Comrade::IrisXT::CA_EdgeDetector::set_check_limits(int ly,int lx)
{
    lim_x=lx;
    lim_y=ly;
}

void Comrade::IrisXT::CA_EdgeDetector::set_threshold(double th)
{
    threshold=th;
}

void Comrade::IrisXT::CA_EdgeDetector::set_quorum(int qu)
{
    quorum=qu;
}

void Comrade::IrisXT::CA_EdgeDetector::detect_edge(Buffer<RGB>* ip_buffer,
                                  Buffer<RGB>* op_buffer)
{
    detect_edge(ip_buffer,op_buffer,0,0,
                ip_buffer->maxx-1,
                ip_buffer->maxy-1);
}

void Comrade::IrisXT::CA_EdgeDetector::detect_edge(Buffer<RGB>* ip_buffer,
                                  Buffer<RGB>* op_buffer,
                                  int x1,int y1,int x2,int y2)
{
    int hx=(lim_x-1)/2;
    int hy=(lim_y-1)/2;

    int mx=ip_buffer->maxx;
    int my=ip_buffer->maxy;

    Buffer<HSLstruct> temp(ip_buffer->maxx,ip_buffer->maxy);
    BufferConvertor::RGB_to_HSL_buffer(&temp,ip_buffer);

    for (int y=y1; y<=y2; y++)
    {
        for (int x=x1; x<=x2; x++)
        {
            int total=0;
            double& luminance=temp.at(x,y).luminance;

            for (int yy=y-hy; yy<=y+hy; yy++)
            {
                for (int xx=x-hx; xx<=x+hx; xx++)
                {
                    if ((xx<0 || xx>mx-1 || yy<0 || yy>my-1) ||
                        (xx==x && yy==y))
                    {
                        continue;
                    }

                    double check=temp.at(xx,yy).luminance;

                    if (fabs(luminance-check)>=threshold)
                    {
                        total++;
                    }
                }
            }

            if (total>=quorum)
            {
                temp.at(x,y).hue=0;
                temp.at(x,y).saturation=0;
                luminance=1;
            }

            else
            {
                luminance=0;
            }
        }
    }

    BufferConvertor::HSL_to_RGB_buffer(op_buffer,&temp);
}

void Comrade::IrisXT::CA_EdgeDetector::clean(Buffer<RGB>* ip_buffer,
                            Buffer<RGB>* op_buffer)
{
    clean(ip_buffer,op_buffer,0,0,
          ip_buffer->maxx-1,ip_buffer->maxy-1);
}

void Comrade::IrisXT::CA_EdgeDetector::clean(Buffer<RGB>* ip_buffer,
                            Buffer<RGB>* op_buffer,
                            int x1,int y1,int x2,int y2)
{
    Buffer<HSLstruct> temp(ip_buffer->maxx,ip_buffer->maxy);

    BufferConvertor::RGB_to_HSL_buffer(&temp,ip_buffer);

    for (int y=y1; y<=y2; y++)
    {
        for (int x=x1; x<=x2; x++)
        {
            int total=0;

            for (int yy=y-1; yy<=y+1; yy++)
            {
                for (int xx=x-1; xx<=x+1; xx++)
                {
                    if (xx==x && yy==y)
                    {
                        continue;
                    }

                    if (xx>=0 && xx<=ip_buffer->maxx-1 &&
                        yy>=0 && yy<=ip_buffer->maxy-1)
                    {
                        HSLstruct check=temp.at(xx,yy);

                        if (check.luminance>0)
                        {
                            total++;
                        }
                    }
                }
            }

            if (total==0)
            {
                temp.at(x,y).luminance=0;
                temp.at(x,y).saturation=0;
                temp.at(x,y).hue=0;
            }
        }
    }

    BufferConvertor::HSL_to_RGB_buffer(op_buffer,&temp);
}

Comrade::IrisXT::CA_EdgeDetector::~CA_EdgeDetector()
{}


