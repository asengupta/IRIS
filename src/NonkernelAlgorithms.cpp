#include "NonkernelAlgorithms.h"

Comrade::IrisXT::AlgorithmManager::AlgorithmManager()
{
    copy_to_output=false;
}

void Comrade::IrisXT::AlgorithmManager::build_prob_vector(int* vect,
                                         double* final,
                                         int num)
{
    long sum=0;

    for (int i=0; i<=num-1; i++)
    {
        sum+=vect[i];
    }

    for (int i=0; i<=num-1; i++)
    {
        final[i]=static_cast<double>(vect[i])/static_cast<double>(sum);

    }
}

void Comrade::IrisXT::AlgorithmManager::build_cumulative_prob_vector(double* prob,
                                                    double* total,
                                                    int num)
{
    double sum=0;

    for (int i=0; i<=num-1; i++)
    {
        sum+=prob[i];
        total[i]=sum;
    }
}

// Overloaded implicit processing calls begin
//*******************************************************************

void Comrade::IrisXT::AlgorithmManager::dilate(Buffer<RGB>* ip_buffer,
                              Buffer<RGB>* op_buffer)
{
    dilate(ip_buffer,op_buffer,0,0,ip_buffer->maxx-1,ip_buffer->maxy-1);
}

void Comrade::IrisXT::AlgorithmManager::erode(Buffer<RGB>* ip_buffer,
                             Buffer<RGB>* op_buffer)
{
    erode(ip_buffer,op_buffer,0,0,ip_buffer->maxx-1,ip_buffer->maxy-1);
}

void Comrade::IrisXT::AlgorithmManager::convert_to_greyscale(Buffer<RGB>* ip_buffer,
                                            Buffer<RGB>* op_buffer)
{
    convert_to_greyscale(ip_buffer,op_buffer,0,0,
                         ip_buffer->maxx-1,
                         ip_buffer->maxy-1);
}

void Comrade::IrisXT::AlgorithmManager::convert_to_negative(Buffer<RGB>* ip_buffer,
                                           Buffer<RGB>* op_buffer)
{
    convert_to_negative(ip_buffer,op_buffer,0,0,
                        ip_buffer->maxx-1,
                        ip_buffer->maxy-1);
}

void Comrade::IrisXT::AlgorithmManager::channel_adjust(Buffer<RGB>* ip_buffer,
                                      Buffer<RGB>* op_buffer,
                                      int red,int green,int blue)
{
    channel_adjust(ip_buffer,op_buffer,
                   red,green,blue,0,0,
                   ip_buffer->maxx-1,
                   ip_buffer->maxy-1);
}

void Comrade::IrisXT::AlgorithmManager::fast_unsharp_mask(Buffer<RGB>* ip_buffer,
                                         Buffer<RGB>* op_buffer,
                                         double lambda)
{
    fast_unsharp_mask(ip_buffer,op_buffer,lambda,
                      0,0,
                      ip_buffer->maxx-1,
                      ip_buffer->maxy-1);
}

void Comrade::IrisXT::AlgorithmManager::histogram_equalise(Buffer<RGB>* ip_buffer,
                                          Buffer<RGB>* op_buffer,
                                          Channel channel)
{
    histogram_equalise(ip_buffer,op_buffer,channel,
                       0,0,
                       ip_buffer->maxx-1,
                       ip_buffer->maxy-1);
}

void Comrade::IrisXT::AlgorithmManager::range_compress(Buffer<RGB>* ip_buffer,
                                      Buffer<RGB>* op_buffer,
                                      double scale)
{
    range_compress(ip_buffer,op_buffer,scale,
                   0,0,
                   ip_buffer->maxx-1,
                   ip_buffer->maxy-1);
}

void Comrade::IrisXT::AlgorithmManager::contrast_stretch(Buffer<RGB>* ip_buffer,
                                        Buffer<RGB>* op_buffer,
                                        Channel channel,
                                        double alpha,double beta,
                                        double gamma)
{
    contrast_stretch(ip_buffer,op_buffer,channel,
                     alpha,beta,gamma,0,0,
                     ip_buffer->maxx-1,
                     ip_buffer->maxy-1);
}

// Overloaded implicit processing calls end
//******************************************************************
// Overloaded explicit processing calls begin

void Comrade::IrisXT::AlgorithmManager::dilate(Buffer<RGB>* ip_buffer,
                              Buffer<RGB>* op_buffer,
                              int x1,int y1,
                              int x2,int y2)
{
    double max_luminance;

    if (copy_to_output==true)
    {
        op_buffer->copy_from(ip_buffer);
    }

    Buffer<HSLstruct> temp_buffer(ip_buffer->maxx,ip_buffer->maxy);
    Buffer<HSLstruct> temp_buffer_final(ip_buffer->maxx,ip_buffer->maxy);

    BufferConvertor::RGB_to_HSL_buffer(&temp_buffer,ip_buffer);
    temp_buffer_final.copy_from(&temp_buffer);

    for (int y=y1; y<=y2; y++)
    {
        for (int x=x1; x<=x2; x++)
        {
            max_luminance=0;

            for (int cand_y=y-1; cand_y<=y+1; cand_y++)
            {
                for (int cand_x=x-1; cand_x<=x+1; cand_x++)
                {
                    if (cand_x>=0 && cand_x<=(temp_buffer.maxx-1) &&
                        cand_y>=0 && cand_y<=(temp_buffer.maxy-1))
                    {
                        double lum=(temp_buffer.at(cand_x,cand_y)).luminance;

                        if (lum>=max_luminance)
                        {
                            max_luminance=lum;
                        }
                    }
                }
            }

            temp_buffer_final.at(x,y).luminance=max_luminance;
        }
    }

    BufferConvertor::HSL_to_RGB_buffer(op_buffer,&temp_buffer_final);
}

// Open question: Is this optimised or is the dilate() method better?
// If tht former is true, easily replace dilate() with this,
// else replicate dilate()'s method here.

void Comrade::IrisXT::AlgorithmManager::erode(Buffer<RGB>* ip_buffer,
                             Buffer<RGB>* op_buffer,
                             int x1,int y1,
                             int x2,int y2)
{
    double min_luminance;

    if (copy_to_output==true)
    {
        op_buffer->copy_from(ip_buffer);
    }

    Buffer<HSLstruct> temp_buffer(ip_buffer->maxx,ip_buffer->maxy);
    Buffer<HSLstruct> temp_buffer_final(ip_buffer->maxx,ip_buffer->maxy);
    // Comment out line above for alternate

    BufferConvertor::RGB_to_HSL_buffer(&temp_buffer,ip_buffer);
    temp_buffer_final.copy_from(&temp_buffer);
    // Comment out line above for alternate

    for (int y=y1; y<=y2; y++)
    {
        for (int x=x1; x<=x2; x++)
        {
            min_luminance=1;

            for (int cand_y=y-1; cand_y<=y+1; cand_y++)
            {
                for (int cand_x=x-1; cand_x<=x+1; cand_x++)
                {
                    if (cand_x>=0 && cand_x<=(temp_buffer.maxx-1) &&
                        cand_y>=0 && cand_y<=(temp_buffer.maxy-1))
                    {
                        double lum=(temp_buffer.at(cand_x,cand_y)).luminance;

                        if (lum<=min_luminance)
                        {
                            min_luminance=lum;
                        }
                    }
                }
            }

            /* Comment out the lines between now and THEN below
            HSLstruct tempHSL={(temp_buffer.at(x,y)).hue,
                               (temp_buffer.at(x,y)).saturation,
                               min_luminance};

            RGBstruct tempRGB=ColorSpaceConvertor::HSL_to_RGB(tempHSL);

            RGB tmp;

            tmp.red=static_cast<unsigned char>(tempRGB.red*255);
            tmp.green=static_cast<unsigned char>(tempRGB.green*255);
            tmp.blue=static_cast<unsigned char>(tempRGB.blue*255);

            op_buffer->at(x,y)=tmp;*/
            // THEN label

            temp_buffer_final.at(x,y).luminance=min_luminance;
        }
    }

    BufferConvertor::HSL_to_RGB_buffer(op_buffer,&temp_buffer_final);
}

void Comrade::IrisXT::AlgorithmManager::convert_to_greyscale(Buffer<RGB>* ip_buffer,
                                            Buffer<RGB>* op_buffer,
                                            int x1,int y1,
                                            int x2,int y2)
{
    if (copy_to_output==true)
    {
        op_buffer->copy_from(ip_buffer);
    }

    for (int y=y1; y<=y2; y++)
    {
        for (int x=x1; x<=x2; x++)
        {
            RGB cur_color=ip_buffer->at(x,y);

            cur_color.red=cur_color.green;
            cur_color.blue=cur_color.green;

            op_buffer->at(x,y)=cur_color;
        }
    }
}

void Comrade::IrisXT::AlgorithmManager::convert_to_negative(Buffer<RGB>* ip_buffer,
                                           Buffer<RGB>* op_buffer,
                                           int x1,int y1,
                                           int x2,int y2)
{
    if (copy_to_output==true)
    {
        op_buffer->copy_from(ip_buffer);
    }

    for (int y=y1; y<=y2; y++)
    {
        for (int x=x1; x<=x2; x++)
        {
            RGB cur_color=ip_buffer->at(x,y);

            cur_color.red=255-cur_color.red;
            cur_color.green=255-cur_color.green;
            cur_color.blue=255-cur_color.blue;

            op_buffer->at(x,y)=cur_color;
        }
    }
}

void Comrade::IrisXT::AlgorithmManager::channel_adjust(Buffer<RGB>* ip_buffer,
                                      Buffer<RGB>* op_buffer,
                                      int red,int green,int blue,
                                      int x1,int y1,
                                      int x2,int y2)
{
    if (copy_to_output==true)
    {
        op_buffer->copy_from(ip_buffer);
    }

    int r,g,b;

    for (int y=y1; y<=y2; y++)
    {
        for (int x=x1; x<=x2; x++)
        {
            RGB temp=ip_buffer->at(x,y);

            r=temp.red;
            g=temp.green;
            b=temp.blue;

            r+=red;
            g+=green;
            b+=blue;

            temp.red=(r>255)?255:r;
            temp.red=(r<0)?0:r;

            temp.green=(g>255)?255:g;
            temp.green=(g<0)?0:g;

            temp.blue=(b>255)?255:b;
            temp.blue=(b<0)?0:b;

            op_buffer->at(x,y)=temp;
        }
    }
}

// Experimental line-detection algorithm in a clean environment.
void Comrade::IrisXT::AlgorithmManager::scale_to_buffer(Buffer<RGB>* ip_buffer,
                                       Buffer<RGB>* temp)
{
    //Gollum sneak("IRIS-Profile.txt");

    //RGB white={255,255,255};
    //RGB black={0,0,0};

    //sneak.log_now("Started smalling...");

    for (int y=0; y<=ip_buffer->maxy-1; y++)
    {
        for (int x=0; x<=ip_buffer->maxx-1; x++)
        {
            int ind_x=int(x/double(ip_buffer->maxx)*temp->maxx);
            int ind_y=int(y/double(ip_buffer->maxy)*temp->maxy);

            temp->buffer_ptr[ind_y][ind_x]=ip_buffer->buffer_ptr[y][x];
        }
    }

    //sneak.log_now("Done smalling...");
}

void Comrade::IrisXT::AlgorithmManager::fast_unsharp_mask(Buffer<RGB>* ip_buffer,
                                         Buffer<RGB>* op_buffer,
                                         double lambda,
                                         int x1,int y1,
                                         int x2,int y2)
{
    if (copy_to_output==true)
    {
        op_buffer->copy_from(ip_buffer);
    }

    RGB black={0,0,0};

    for (int y=y1; y<=y2; y++)
    {
        for (int x=x1; x<=x2; x++)
        {
            RGB f1=(x-1>=0)?(ip_buffer->at(x-1,y)):black;
            RGB f2=(x+1<=ip_buffer->maxx-1)?(ip_buffer->at(x+1,y)):black;
            RGB f3=(y-1>=0)?(ip_buffer->at(x,y-1)):black;
            RGB f4=(y+1<=ip_buffer->maxy-1)?(ip_buffer->at(x,y+1)):black;
            RGB& u=op_buffer->at(x,y);
            RGB cur=ip_buffer->at(x,y);

            double v_g=(1+lambda)*cur.green-(lambda/4)*(f1.green+
                                                      f2.green+
                                                      f3.green+
                                                      f4.green);

            double v_r=(1+lambda)*cur.red-(lambda/4)*(f1.red+
                                                        f2.red+
                                                        f3.red+
                                                        f4.red);

            double v_b=(1+lambda)*cur.blue-(lambda/4)*(f1.blue+
                                                       f2.blue+
                                                       f3.blue+
                                                       f4.blue);

            v_b=(v_b>255)?255:v_b;
            v_b=(v_b<0)?0:v_b;

            v_r=(v_r>255)?255:v_r;
            v_r=(v_r<0)?0:v_r;

            v_g=(v_g>255)?255:v_g;
            v_g=(v_g<0)?0:v_g;


            u.red=static_cast<unsigned char>(v_r);
            u.green=static_cast<unsigned char>(v_g);
            u.blue=static_cast<unsigned char>(v_b);
        }
    }
}

void Comrade::IrisXT::AlgorithmManager::histogram_equalise(Buffer<RGB>* ip_buffer,
                                          Buffer<RGB>* op_buffer,
                                          Channel channel,
                                          int x1,int y1,
                                          int x2,int y2)
{
    if (copy_to_output==true)
    {
        op_buffer->copy_from(ip_buffer);
    }

    //cout<<"Doing channel : "<<channel<<endl;
    //cin.get();

    int dist[256];
    calculate_histogram(ip_buffer,dist,256,channel,
                        x1,y1,
                        x2,y2);

    double prob[256],cu_prob[256];
    build_prob_vector(dist,prob,256);
    build_cumulative_prob_vector(prob,cu_prob,256);

    double vmin=cu_prob[0];

    //for (int i=1; i<=255; i++)
    //{
    //    if (cu_prob[i]<vmin)
    //    {
    //        vmin=cu_prob[i];
    //    }
    //}

    assert(vmin>=0);
    unsigned char cx;

    for (int y=y1; y<=y2; y++)
    {
        for (int x=x1; x<=x2; x++)
        {
            if (channel==RED)
            {
                cx=ip_buffer->at(x,y).red;;
            }

            else if (channel==GREEN)
            {
                cx=ip_buffer->at(x,y).green;
            }

            else if (channel==BLUE)
            {
                cx=ip_buffer->at(x,y).blue;
            }

            int convert=static_cast<int>(cx);
            double v=cu_prob[convert];

            int result=static_cast<int>(((v-vmin)*255.0/(1-vmin))+.5);

            result=(result>255)?255:(result);
            result=(result<0)?0:(result);

            cx=static_cast<unsigned char>(result);

            if (channel==RED)
            {
                op_buffer->at(x,y).red=cx;
            }

            else if (channel==GREEN)
            {
                op_buffer->at(x,y).green=cx;
            }

            else if (channel==BLUE)
            {
                op_buffer->at(x,y).blue=cx;
            }
        }
    }
}

void Comrade::IrisXT::AlgorithmManager::range_compress(Buffer<RGB>* ip_buffer,
                                      Buffer<RGB>* op_buffer,
                                      double scale,
                                      int x1,int y1,
                                      int x2,int y2)
{
    if (copy_to_output==true)
    {
        op_buffer->copy_from(ip_buffer);
    }

    for (int y=y1; y<=y2; y++)
    {
        for (int x=x1; x<=x2; x++)
        {
            RGB check=ip_buffer->at(x,y);
            RGB& final=op_buffer->at(x,y);

            double r=check.red;
            double g=check.green;
            double b=check.blue;

            r=255*scale*(log10(1+fabs(r)));
            g=255*scale*(log10(1+fabs(g)));
            b=255*scale*(log10(1+fabs(b)));

            //cout<<r<<" "<<g<<" "<<b<<endl;

            r=(r>255)?255:r;
            r=(r<0)?0:r;

            g=(g>255)?255:g;
            g=(g<0)?0:g;

            b=(b>255)?255:b;
            b=(b<0)?0:b;

            final.red=static_cast<unsigned char>(r);
            final.green=static_cast<unsigned char>(g);
            final.blue=static_cast<unsigned char>(b);
        }
    }
}

void Comrade::IrisXT::AlgorithmManager::contrast_stretch(Buffer<RGB>* ip_buffer,
                                        Buffer<RGB>* op_buffer,
                                        Channel channel,
                                        double alpha,
                                        double beta,
                                        double gamma,
                                        int x1,int y1,
                                        int x2,int y2)
{
    if (copy_to_output==true)
    {
        op_buffer->copy_from(ip_buffer);
    }

    unsigned char a=static_cast<unsigned char>(85);
    unsigned char b=static_cast<unsigned char>(170);

    unsigned char va=static_cast<unsigned char>(alpha*a);
    unsigned char vb=static_cast<unsigned char>(va+beta*(b-a));

    for (int y=y1; y<=y2; y++)
    {
        for (int x=x1; x<=x2; x++)
        {
            unsigned char *i_map,*o_map;


            unsigned char* o_red=&(op_buffer->at(x,y).red);
            unsigned char* o_green=&(op_buffer->at(x,y).green);
            unsigned char* o_blue=&(op_buffer->at(x,y).blue);

            unsigned char* i_red=&(ip_buffer->at(x,y).red);
            unsigned char* i_green=&(ip_buffer->at(x,y).green);
            unsigned char* i_blue=&(ip_buffer->at(x,y).blue);

            if (channel==RED)
            {
                i_map=i_red;
                o_map=o_red;

                op_buffer->at(x,y).blue=ip_buffer->at(x,y).blue;
                op_buffer->at(x,y).green=ip_buffer->at(x,y).green;
            }

            if (channel==GREEN)
            {
                i_map=i_green;
                o_map=o_green;

                op_buffer->at(x,y).red=ip_buffer->at(x,y).red;
                op_buffer->at(x,y).blue=ip_buffer->at(x,y).blue;
            }

            if (channel==BLUE)
            {
                i_map=i_blue;
                o_map=o_blue;

                op_buffer->at(x,y).red=ip_buffer->at(x,y).red;
                op_buffer->at(x,y).green=ip_buffer->at(x,y).green;
            }

            double final=0;

            if ((*i_map)<a)
            {
                final=alpha*(*i_map);
            }

            else if ((*i_map)>=a && (*i_map)<b)
            {
                final=beta*(*i_map-a)+va;
            }

            else
            {
                final=gamma*(*i_map-b)+vb;
            }

            final=(final>255)?255:final;
            final=(final<0)?0:final;

            *o_map=static_cast<unsigned char>(final);
        }
    }
}

// Overloaded explicit processing calls end
//*******************************************************************

void Comrade::IrisXT::AlgorithmManager::calculate_histogram(Buffer<RGB>* buffer,
                                           int* vect,int levels,
                                           Channel channel,
                                           int x1,int y1,
                                           int x2,int y2)
{
    for (int i=0; i<=levels-1; i++)
    {
        vect[i]=0;
    }

    for (int y=y1; y<=y2; y++)
    {
        for (int x=x1; x<=x2; x++)
        {
            RGB c=buffer->at(x,y);

            if (channel==RED)
            {
                int index=static_cast<int>(c.red);
                vect[index]++;
            }

            if (channel==GREEN)
            {
                int index=static_cast<int>(c.green);
                vect[index]++;
            }

            if (channel==BLUE)
            {
                int index=static_cast<int>(c.blue);
                vect[index]++;
            }
        }
    }
}

Comrade::IrisXT::AlgorithmManager::~AlgorithmManager()
{}


