#include "VarianceTester.h"

void blank_variances(Buffer<HSLstruct>& buffer,double threshold,int bound)
{
    vector<InterestArea> itbl;

    int total=0;
    int xsz=buffer.maxx;
    int ysz=buffer.maxy;

/*    for (int y=0; y<=ysz-1; y+=bound)
    {
        for (int x=0; x<=xsz-1; x+=bound)
        {
            double hue_total=0;

            for (int r=y; r<=y+bound-1; r++)
            {
                for (int c=x; c<=x+bound-1; c++)
                {
                    hue_total+=buffer.at(c,r).luminance;
                }
            }

            double mean=hue_total/(bound*bound);
            double variance=0;

            for (int r=y; r<=y+bound-1; r++)
            {
                for (int c=x; c<=x+bound-1; c++)
                {
                    double tmp=buffer.at(c,r).luminance-mean;
                    variance+=(tmp*tmp);
                }
            }

            variance/=(bound*bound);
            variance=sqrt(variance);

            if (variance>threshold)
            {
                cout<<variance<<" ";

                total++;

                InterestArea area={x,y,variance};

                itbl.push_back(area);
            }
        }
    }
*/

// Directional operator

    for (int y=0; y<=ysz-1; y+=bound)
    {
        for (int x=0; x<=xsz-1; x+=bound)
        {
            double hor=0,ver=0,ltdiag=0,rtdiag=0;

            for (int yy=y; yy<=y+bound-1; yy++)
            {
                for (int xx=x; xx<=x+bound-2; xx++)
                {
                    double v=buffer.at(xx,yy).luminance-
                             buffer.at(xx+1,yy).luminance;

                    hor+=(v*v);
                }
            }

            for (int yy=y; yy<=y+bound-2; yy++)
            {
                for (int xx=x; xx<=x+bound-1; xx++)
                {
                    double v=buffer.at(xx,yy).luminance-
                             buffer.at(xx,yy+1).luminance;

                    ver+=(v*v);
                }
            }

            for (int yy=y; yy<=y+bound-2; yy++)
            {
                for (int xx=x; xx<=x+bound-2; xx++)
                {
                    double v=buffer.at(xx,yy).luminance-
                             buffer.at(xx+1,yy+1).luminance;

                    ltdiag+=(v*v);
                }
            }

            for (int yy=y+1; yy<=y+bound-1; yy++)
            {
                for (int xx=x+1; xx<=x+bound-1; xx++)
                {
                    double v=buffer.at(xx,yy).luminance-
                             buffer.at(xx-1,yy-1).luminance;

                    rtdiag+=(v*v);
                }
            }

            double min1=(hor<ver)?hor:ver;
            double min2=(ltdiag<rtdiag)?ltdiag:rtdiag;
            double min=(min1<min2)?min1:min2;

            //cout<<hor<<" "<<ver<<" "<<ltdiag<<" "<<rtdiag<<" "<<min<<"\n";

            if (min>threshold)
            {
                total++;

                InterestArea area;
                area.x=x;
                area.y=y;
                //area.variance=min;

                itbl.push_back(area);
            }
        }
    }

    for (int i=0; i<=itbl.size()-1; i++)
    {
        int x=itbl[i].x;
        int y=itbl[i].y;

        int cx=x+bound/2;
        int cy=y+bound/2;

        //cout<<"("<<cx<<","<<cy<<")\n";

        RGBstruct rgbwhite={1,1,1};
        HSLstruct white=ColorSpaceConvertor::RGB_to_HSL(rgbwhite);

        buffer.at(cx,cy)=white;
        buffer.at(cx+1,cy)=white;
        buffer.at(cx-1,cy)=white;
        buffer.at(cx,cy+1)=white;
        buffer.at(cx,cy-1)=white;

        buffer.at(cx+2,cy)=white;
        buffer.at(cx-2,cy)=white;
        buffer.at(cx,cy+2)=white;
        buffer.at(cx,cy-2)=white;

        buffer.at(cx+3,cy)=white;
        buffer.at(cx-3,cy)=white;
        buffer.at(cx,cy+3)=white;
        buffer.at(cx,cy-3)=white;
    }

    cout<<"Total number of interest areas="<<total<<endl;
}

int build_scanline_map(Buffer<HSLstruct>& buffer,double threshold,vector<InterestArea>& itbl)
{
    int total=0;
    int xsz=buffer.maxx;
    int ysz=buffer.maxy;
    int current=0;
    double change=0;

    for (int scanline=0; scanline<=ysz-1; scanline++)
    {
        int num=0;

        for (int x=0; x<=xsz-2; x++)
        {
            change+=(buffer.at(x+1,scanline).luminance-
                    buffer.at(x,scanline).luminance);

            //cout<<change<<endl;

            if (fabs(change)>threshold)
            {
                total++;

                InterestArea pt;
                //direction_op(buffer,x,scanline,8,pt.dirn);
                pt.x=x;
                pt.y=scanline;
                pt.mean=num;

                //RGBstruct rgbwhite={1,1,1};
                //HSLstruct white=ColorSpaceConvertor::RGB_to_HSL(rgbwhite);

                //buffer.at(x,scanline)=white;
    
                itbl.push_back(pt);
                change=0;
                num=0;
            }

            else
            {
                num++;
            }
        }
    }

    //for (int i=0; i<=itbl.size()-1; i++)
    //{
        //int cx=itbl[i].lx;
        //int cy=itbl[i].ly;


        //cout<<"("<<cx<<","<<cy<<")\n";

        //RGBstruct rgbwhite={1,1,1};
        //HSLstruct white=ColorSpaceConvertor::RGB_to_HSL(rgbwhite);

        //buffer.at(cx,cy)=white;
        //buffer.at(cx+1,cy)=white;
        //buffer.at(cx-1,cy)=white;
        //buffer.at(cx,cy+1)=white;
        //buffer.at(cx,cy-1)=white;

        /*buffer.at(cx+2,cy)=white;
        buffer.at(cx-2,cy)=white;
        buffer.at(cx,cy+2)=white;
        buffer.at(cx,cy-2)=white;

        buffer.at(cx+3,cy)=white;
        buffer.at(cx-3,cy)=white;
        buffer.at(cx,cy+3)=white;
        buffer.at(cx,cy-3)=white;*/
    //}

    return total;
}

void direction_op(Buffer<HSLstruct>& buffer,int x,int y,int bound,double arr[4])
{
    arr[0]=arr[1]=arr[2]=arr[3]=0;

    int xsz=buffer.maxx;
    int ysz=buffer.maxy;

    for (int yy=y-bound/2; yy<=y+bound/2; yy++)
    {
        for (int xx=x-bound/2; xx<=x+bound/2; xx++)
        {
            double v1=buffer.at(xx,yy).luminance-
                      buffer.at(xx+1,yy).luminance;

            double v2=buffer.at(xx,yy).luminance-
                      buffer.at(xx,yy+1).luminance;

            double v3=buffer.at(xx,yy).luminance-
                      buffer.at(xx+1,yy+1).luminance;

            double v4=buffer.at(xx,yy).luminance-
                      buffer.at(xx+1,yy-1).luminance;

            arr[0]+=(v1*v1);
            arr[1]+=(v2*v2);
            arr[2]+=(v3*v3);
            arr[3]+=(v4*v4);

            //cout<<arr[0]<<" "<<arr[1]<<" "<<arr[2]<<" "<<arr[3]<<endl;
        }
    }
}

void stereo_correlate(vector<InterestArea>& vecleft,
                      vector<InterestArea>& vecright)
{
    int lsz=vecleft.size();
    int rsz=vecright.size();

    double limit=.1*(lsz+rsz);
    double diff=fabs(lsz-rsz);

    if (diff>limit)
    {
        cout<<"Size discrepancy..."<<lsz<<","<<rsz<<","<<limit<<"\n";
    }

    else
    {
        cout<<"Vectors match..."<<lsz<<","<<rsz<<","<<limit<<"\n";
    }

    int i=0;

    while (i<=lsz-1 && i<=rsz-1)
    {
        if (fabs(vecleft[i].mean-vecright[i].mean)>9)
        {
            if (vecleft[i].mean<=7)
            {
                vecleft.erase(vecleft.begin()+i,
                              vecleft.begin()+i);
            }

            else if (vecright[i].mean<=7)
            {
                vecright.erase(vecright.begin()+i,
                               vecright.begin()+i);
            }
        }

        i++;
    }

    cout<<"After pruning..."<<vecleft.size()
        <<" "<<vecright.size()<<endl;

    lsz=vecleft.size();
    rsz=vecright.size();

    for (int y=0; y<=((lsz>rsz)?rsz:lsz)-1; y++)
    {
        cout<<y<<")"<<vecleft[y].x-vecright[y].x<<endl;
    }

    /*int y=rtbuffer.maxy;
    int x=rtbuffer.maxx;

    int limit=vec.size();

    for (int i=0; i<=limit-1; i++)
    {
        cout<<"Checking "<<i<<endl;

        int curx=vec[i].x;
        int cury=vec[i].y;

        // Check rectangle around area...

        int total=0;

        for (int yy=cury-10; yy<=cury+10; yy++)
        {
            for (int xx=curx-10; xx<=curx+10; xx++)
            {
                InterestArea pt;

                direction_op(rtbuffer,xx,yy,8,pt.dirn);

                if (fabs(pt.dirn[0]-vec[i].dirn[0])<.03 &&
                    fabs(pt.dirn[1]-vec[i].dirn[1])<.03 &&
                    fabs(pt.dirn[2]-vec[i].dirn[2])<.03 &&
                    fabs(pt.dirn[3]-vec[i].dirn[3])<.03)
                {
                    total++;
                }
            }
        }

        if (total==1)
        {
            cout<<"Match...\n";
        }

        else if (total>1)
        {
            cout<<"Multiple matches...\n";
        }

        else
        {
            cout<<"No match...\n";
        }
    }*/
}


