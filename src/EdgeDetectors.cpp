#include "EdgeDetectors.h"

Comrade::IrisXT::EdgeDetectorManager::EdgeDetectorManager()
{
    cout<<"EdgeDetectorManager object created...\n";
}

double Comrade::IrisXT::EdgeDetectorManager::greyscale_correlate(Buffer<RGB>* buffer,
                                                int x,int y,
                                                KernelMatrix* ker)
{
    double sum=0;
    int yhalf=(ker->ysize-1)/2;
    int xhalf=(ker->xsize-1)/2;

    for (int yy=-yhalf; yy<=yhalf; yy++)
    {
        for (int xx=-xhalf; xx<=xhalf; xx++)
        {
            if (xx+x>=0 && xx+x<=buffer->maxx-1 &&
                yy+y>=0 && yy+y<=buffer->maxy-1)
            {
                sum+=buffer->at(xx+x,yy+y).green*
                    (ker->matrix[yy+yhalf][xx+xhalf]);
            }
        }
    }

    return sum;
}

void Comrade::IrisXT::EdgeDetectorManager::call_operator(KernelMatrix* H1,
                                        KernelMatrix* H2,
                                        int threshold)
{
    for (int y=0; y<=ip->maxy-1; y++)
    {
        for (int x=0; x<=ip->maxx-1; x++)
        {
            double value1=greyscale_correlate(ip,x,y,H1);
            double value2=greyscale_correlate(ip,x,y,H2);

            double final=fabs(value1)+fabs(value2);
            final/=2;

            final=(final>255)?255:final;
            final=(final<0)?0:final;

            //op->at(x,y).red=static_cast<unsigned char>(final);
            //op->at(x,y).green=static_cast<unsigned char>(final);
            //op->at(x,y).blue=static_cast<unsigned char>(final);

            if (final>=threshold)
            {
                op->at(x,y).red=255;
                op->at(x,y).green=255;
                op->at(x,y).blue=255;
            }

            else
            {
                op->at(x,y).red=0;
                op->at(x,y).green=0;
                op->at(x,y).blue=0;
            }
        }
    }
}

void Comrade::IrisXT::EdgeDetectorManager::RobertsCross(Buffer<RGB>* ip_buffer,
                                       Buffer<RGB>* op_buffer,
                                       int threshold)
{
    ip=ip_buffer;
    op=op_buffer;

    KernelMatrix H1(3,3);
    KernelMatrix H2(3,3);

    KernelGenerator::generate_RobertsCross(&H1,&H2);

    /*double arr1[]={ 0, 0, 0,
                    0, 0, 1,
                    0,-1, 0};

    double arr2[]={ 0, 0, 0,
                    0, 1, 0,
                    0, 0,-1};*/

    call_operator(&H1,&H2,threshold);
}

void Comrade::IrisXT::EdgeDetectorManager::Prewitt(Buffer<RGB>* ip_buffer,
                                  Buffer<RGB>* op_buffer,
                                  int threshold)
{
    ip=ip_buffer;
    op=op_buffer;

    KernelMatrix H1(3,3);
    KernelMatrix H2(3,3);

    KernelGenerator::generate_Prewitt(&H1,&H2);

    /*double arr1[]={-1, 0, 1,
                   -1, 0, 1,
                   -1, 0, 1};

    double arr2[]={-1,-1,-1,
                    0, 0, 0,
                    1, 1, 1};*/

    call_operator(&H1,&H2,threshold);
}

void Comrade::IrisXT::EdgeDetectorManager::Sobel(Buffer<RGB>* ip_buffer,
                                Buffer<RGB>* op_buffer,
                                int threshold)
{
    ip=ip_buffer;
    op=op_buffer;

    KernelMatrix H1(3,3);
    KernelMatrix H2(3,3);

    KernelGenerator::generate_Sobel(&H1,&H2);

    /*double arr1[]={-1, 0, 1,
                   -2, 0, 2,
                   -1, 0, 1};

    double arr2[]={-1,-2,-1,
                    0, 0, 0,
                    1, 2, 1};*/

    call_operator(&H1,&H2,threshold);
}

void Comrade::IrisXT::EdgeDetectorManager::isotropic(Buffer<RGB>* ip_buffer,
                                    Buffer<RGB>* op_buffer,
                                    int threshold)
{
    ip=ip_buffer;
    op=op_buffer;

    KernelMatrix H1(3,3);
    KernelMatrix H2(3,3);

    KernelGenerator::generate_isotropic(&H1,&H2);

    /*double arr1[]={-1, 0, 1,
                   -1.414, 0, 1.414,
                   -1, 0, 1};

    double arr2[]={-1,-1.414,-1,
                    0, 0, 0,
                    1, 1.414, 1};*/

    call_operator(&H1,&H2,threshold);
}

void Comrade::IrisXT::EdgeDetectorManager::Laplacian(Buffer<RGB>* ip_buffer,
                                    Buffer<RGB>* op_buffer,
                                    int threshold)
{
    ip=ip_buffer;
    op=op_buffer;

    KernelMatrix H1(3,3);
    KernelMatrix H2(3,3);

    KernelGenerator::generate_Laplacian(&H1,&H2);

    /*double arr1[]={ 1,-2, 1,
                   -2, 4,-2,
                   -1,-2, 1};

    double arr2[]={ 0, 0, 0,
                    0, 0, 0,
                    0, 0, 0};*/

    call_operator(&H1,&H2,threshold);
}

void Comrade::IrisXT::EdgeDetectorManager::Canny(Buffer<RGB>*ip_buffer,
                                                 Buffer<RGB>* op_buffer,
                                                 double sigma)
{
    int edge_direction=0;

    KernelMatrix vec(5,5);
    KernelGenerator::generate_Gaussian(&vec,sigma);
    
    KernelOperator op;
    op.assign_kernel(&vec);
    op.set_factor(sqrt(2*PI)*sigma);

    op.assign_buffer_ptrs(ip_buffer,op_buffer);
    op.convolve();

    ip_buffer->copy_from(op_buffer);

    op.set_factor(1);

    double orient,edgeDirection;
    double leftPixel,rightPixel;

    KernelMatrix h1(3,3), h2(3,3);
    KernelGenerator::generate_Sobel(&h1,&h2);

    for (int yy=1; yy<=ip_buffer->maxy-2; yy++)
    {
        for (int xx=1; xx<=ip_buffer->maxx-2; xx++)
        {
            op.assign_kernel(&h1);
            double sumX=op.greyscale_unit_convolve(xx,yy,op_buffer);

            op.assign_kernel(&h2);
            double sumY=op.greyscale_unit_convolve(xx,yy,op_buffer);

            double sum=fabs(sumX)+fabs(sumY);

            sum=(sum>255)?255:sum;
            sum=(sum<0)?0:sum;

            /*if(sumX==0)
            {
                if(sumY==0)
                {
                    orient=0.0;
                }

                else if (sumY<0)
                {
                    sumY=-sumY;
                    orient = 90.0;
                }

                else
                {
                    orient = 90.0;
                }
            }

            else if(sumX<0 && sumY>0)
            {
                sumX = -sumX;
                orient = 180 - atan(sumY/sumX) * (180/PI);
            }

            else if(sumX>0 && sumY<0)
            {
                sumY = -sumY;
                orient = 180 - ((atan((float)(sumY)/(float)(sumX))) * (180/PI));
            }

	        else
            {
                orient = (atan((float)(sumY)/(float)(sumX))) * (180/PI);
            }*/

            orient=rad_to_deg(atan2(sumY,sumX));

            if(orient<22.5)
            {
                edgeDirection=0;
            }

            else if(orient<67.5)
            {
                edge_direction=45;
            }

            else if(orient<112.5)
            {
                edge_direction=90;
            }

            else if(orient<157.5)
            {
                edge_direction=135;
            }

            else
            {
                edge_direction=0;
            }

            if(edge_direction==0)
            {
                leftPixel=op_buffer->at(xx,yy-1).green;
                rightPixel=op_buffer->at(xx,yy+1).green;
            }

            else if(edge_direction==45)
            {
                leftPixel=op_buffer->at(xx-1,yy-1).green;
                rightPixel=op_buffer->at(xx+1,yy+1).green;
            }

            else if(edge_direction==90)
            {
                leftPixel=op_buffer->at(xx+1,yy).green;
                rightPixel=op_buffer->at(xx-1,yy).green;
            }

            else
            {
                leftPixel=op_buffer->at(xx+1,yy-1).green;
                rightPixel=op_buffer->at(xx-1,yy+1).green;
            }

            if(sum<leftPixel || sum<rightPixel)
            {
                sum=0;
            }

            else
            {
                double highThreshold=180.;
                double lowThreshold=20.;

                if(sum>=highThreshold)
                {
                    sum=255;
                }

                else if(sum<lowThreshold)
                {
                    //cout<<"Self threshold failed...\n";
                    sum=0;
                }

                else
                {
                    double l1=op_buffer->at(xx-1,yy-1).green;
                    double l2=op_buffer->at(xx,yy-1).green;
                    double l3=op_buffer->at(xx+1,yy-1).green;
                    double l4=op_buffer->at(xx+1,yy).green;
                    double l5=op_buffer->at(xx+1,yy+1).green;
                    double l6=op_buffer->at(xx,yy+1).green;
                    double l7=op_buffer->at(xx-1,yy+1).green;
                    double l8=op_buffer->at(xx-1,yy).green;

                    if(l1>highThreshold ||
                       l2>highThreshold ||
                       l3>highThreshold ||
                       l4>highThreshold ||
                       l5>highThreshold ||
                       l6>highThreshold ||
                       l7>highThreshold ||
                       l8>highThreshold)
                    {
                        sum=255;
                    }

                    else
                    {
                        //cout<<"Neighbourhood threshold failed...\n";
                        sum=0;
                    }
                }
            }

            ip_buffer->at(xx,yy).red=
            ip_buffer->at(xx,yy).green=
            ip_buffer->at(xx,yy).blue=static_cast<unsigned char>(sum);
        }
    }

}

Comrade::IrisXT::EdgeDetectorManager::~EdgeDetectorManager()
{}


