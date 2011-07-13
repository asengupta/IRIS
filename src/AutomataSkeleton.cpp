#include "AutomataSkeleton.h"

Comrade::IrisXT::CA_Skeletoniser::CA_Skeletoniser()
{
    cout<<"CA_Skeletoniser object created...\n";
}

void Comrade::IrisXT::CA_Skeletoniser::skeletonise(Buffer<RGB>* ip_buffer,
                                  Buffer<RGB>* op_buffer)
{
    RGB white={255,255,255};
    RGB black={0,0,0};

    for (int y=0; y<=ip_buffer->maxy-1; y++)
    {
        for (int x=0; x<=ip_buffer->maxx-1; x++)
        {
            int total=0;

            for (int yy=y-1; yy<=y+1; yy++)
            {
                for (int xx=x-1; xx<=x+1; xx++)
                {
                    if (xx>=0 && xx<=ip_buffer->maxx-1 &&
                        yy>=0 && yy<=ip_buffer->maxy-1)
                    {
                        RGB c=ip_buffer->at(xx,yy);

                        if (c.red==255 && c.green==255 &&
                            c.blue==255)
                        {
                            total++;
                        }
                    }
                }
            }

            if (total<8)
            {
                op_buffer->at(x,y)=black;
            }

            else
            {
                op_buffer->at(x,y)=white;
            }
        }
    }
}

Comrade::IrisXT::CA_Skeletoniser::~CA_Skeletoniser()
{}

