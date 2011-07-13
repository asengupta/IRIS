#include "ModelBuilder.h"

Comrade::IrisFoundation::Buffer<Comrade::IrisFoundation::RGB>* bufptr;
bool complete=true;
long carved=0;
double THRESHOLD=0.78;

bool Comrade::Iris3D::x_space_carve_dec(std::vector<Comrade::Iris3D::Sensor>& senarr,
                                        Comrade::Iris3D::WorldSpace& space)
{
    //int num=0;
    bool answer=false;
    // Sweep in x-dir front
    double ctr=0;
    std::vector< std::vector<Sensor*> > active_array;

    for (int xsweep=WORLD_X-1; xsweep>=0; xsweep--)
    {
        std::vector<Sensor*> active;

        for (unsigned int i=0; i<=senarr.size()-1; i++)
        {
            if (senarr[i].focal_center.get_x()>space.world[0][0][xsweep].x)
            {
                 active.push_back(&senarr[i]);
            }
        }

        active_array.push_back(active);
    }

    for (int x0=WORLD_X-1; x0>=0; x0--)
    {
        std::vector<Sensor*>& active=active_array[WORLD_X-1-x0];
        //int num_views=active.size();

        for (int z=WORLD_Z-1; z>=0; z--)
        {
            for (int y=WORLD_Y-1; y>=0; y--)
            {
                cout<<"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
                    <<ctr*100/(WORLD_X*WORLD_Y*WORLD_Z)<<"%  ";

                Voxel& vox=space.world[z][y][x0];

                #ifdef DEBUG
                cout<<"Now checking voxel ("<<vox.z<<","
                    <<vox.y<<","<<vox.x<<")\n";
                #endif

                common_code(vox,active);//,space);
                ctr++;
            }
        }
    }

    return answer;
}

bool Comrade::Iris3D::x_space_carve_inc(std::vector<Comrade::Iris3D::Sensor>& senarr,
                                        Comrade::Iris3D::WorldSpace& space)
{
    //int num=0;
    bool answer=false;
    // Sweep in x-dir front
    double ctr=0;
    std::vector< std::vector<Sensor*> > active_array;

    for (int xsweep=0; xsweep<=WORLD_X-1; xsweep++)
    {
        std::vector<Sensor*> active;

        for (unsigned int i=0; i<=senarr.size()-1; i++)
        {
            if (senarr[i].focal_center.get_x()<space.world[0][0][xsweep].x)
            {
                 active.push_back(&senarr[i]);
                 //cout<<"Pushing camera "<<i<<endl;
            }
        }

        //cin.get();

        active_array.push_back(active);
    }

    //cin.get();

    for (int x0=0; x0<=WORLD_X-1; x0++)
    {
        std::vector<Sensor*>& active=active_array[x0];

        //int num_views=active.size();

        for (int z=WORLD_Z-1; z>=0; z--)
        {
            for (int y=WORLD_Y-1; y>=0; y--)
            {
                cout<<"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
                    <<"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
                    <<ctr*100/(WORLD_X*WORLD_Y*WORLD_Z)<<"%  ";
                //cout<<"("<<x0<<","<<y<<","<<z<<")\n";

                Voxel& vox=space.world[z][y][x0];

                #ifdef DEBUG
                cout<<"Now checking voxel ("<<vox.z<<","
                    <<vox.y<<","<<vox.x<<")\n";
                #endif

                //cout<<"Calling common code...\n";
                common_code(vox,active);//,space);
                ctr++;
            }
        }
    }

    return answer;
}

bool Comrade::Iris3D::y_space_carve_dec(std::vector<Comrade::Iris3D::Sensor>& senarr,
                                        Comrade::Iris3D::WorldSpace& space)
{
    //int num=0;
    bool answer=false;
    // Sweep in x-dir front
    double ctr=0;
    std::vector< std::vector<Sensor*> > active_array;

    for (int ysweep=WORLD_Y-1; ysweep>=0; ysweep--)
    {
        std::vector<Sensor*> active;

        for (unsigned int i=0; i<=senarr.size()-1; i++)
        {
            if (senarr[i].focal_center.get_y()>space.world[0][ysweep][0].y)
            {
                 active.push_back(&senarr[i]);
            }
        }

        active_array.push_back(active);
    }

    for (int y0=WORLD_Y-1; y0>=0; y0--)
    {
        std::vector<Sensor*>& active=active_array[y0];

        //int num_views=active.size();

        for (int z=WORLD_Z-1; z>=0; z--)
        {
            for (int x=WORLD_X-1; x>=0; x--)
            {
                cout<<"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
                    <<ctr*100/(WORLD_X*WORLD_Y*WORLD_Z)<<"%  ";
                //cout<<"("<<x0<<","<<y<<","<<z<<")\n";

                Voxel& vox=space.world[z][y0][x];
                common_code(vox,active);//,space);
                ctr++;
            }
        }
    }

    return answer;
}

bool Comrade::Iris3D::y_space_carve_inc(std::vector<Comrade::Iris3D::Sensor>& senarr,
                                        Comrade::Iris3D::WorldSpace& space)
{
    //int num=0;
    bool answer=false;
    // Sweep in x-dir front
    double ctr=0;
    std::vector< std::vector<Sensor*> > active_array;

    for (int ysweep=0; ysweep<=WORLD_Y-1; ysweep++)
    {
        std::vector<Sensor*> active;

        for (unsigned int i=0; i<=senarr.size()-1; i++)
        {
            if (senarr[i].focal_center.get_y()<space.world[0][ysweep][0].y)
            {
                 active.push_back(&senarr[i]);
            }
        }

        active_array.push_back(active);
    }

    for (int y0=0; y0<=WORLD_Y-1; y0++)
    {
        std::vector<Sensor*>& active=active_array[y0];

        //int num_views=active.size();

        for (int z=WORLD_Z-1; z>=0; z--)
        {
            for (int x=WORLD_X-1; x>=0; x--)
            {
                cout<<"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
                    <<ctr*100/(WORLD_X*WORLD_Y*WORLD_Z)<<"%  ";
                //cout<<"("<<x0<<","<<y<<","<<z<<")\n";

                Voxel& vox=space.world[z][y0][x];
                #ifdef DEBUG
                cout<<"Now checking voxel ("<<vox.z<<","
                    <<vox.y<<","<<vox.x<<")\n";
                #endif
                common_code(vox,active);//,space);
                ctr++;
            }
        }
    }

    return answer;
}

bool Comrade::Iris3D::z_space_carve_dec(std::vector<Comrade::Iris3D::Sensor>& senarr,
                                        Comrade::Iris3D::WorldSpace& space)
{
    //int num=0;
    bool answer=false;
    // Sweep in x-dir front
    double ctr=0;
    std::vector< std::vector<Sensor*> > active_array;

    for (int zsweep=WORLD_Z-1; zsweep>=0; zsweep--)
    {
        std::vector<Sensor*> active;

        for (unsigned int i=0; i<=senarr.size()-1; i++)
        {
            if (senarr[i].focal_center.get_z()>space.world[zsweep][0][0].z)
            {
                 active.push_back(&senarr[i]);
            }
        }

        active_array.push_back(active);
    }

    for (int z0=WORLD_Z-1; z0>=0; z0--)
    {
        std::vector<Sensor*>& active=active_array[WORLD_Z-1-z0];
        //int num_views=active.size();

        for (int x=WORLD_X-1; x>=0; x--)
        {
            for (int y=WORLD_Y-1; y>=0; y--)
            {
                cout<<"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
                    <<ctr*100/(WORLD_X*WORLD_Y*WORLD_Z)<<"%  ";

                Voxel& vox=space.world[z0][y][x];

                #ifdef DEBUG
                cout<<"Now checking voxel ("<<vox.z<<","
                    <<vox.y<<","<<vox.x<<")\n";
                #endif

                common_code(vox,active);//,space);
                ctr++;
            }
        }
    }

    return answer;
}

bool Comrade::Iris3D::z_space_carve_inc(std::vector<Comrade::Iris3D::Sensor>& senarr,
                                        Comrade::Iris3D::WorldSpace& space)
{
    //int num=0;
    bool answer=false;
    // Sweep in x-dir front
    double ctr=0;
    std::vector< std::vector<Sensor*> > active_array;

    for (int zsweep=0; zsweep<=WORLD_Z-1; zsweep++)
    {
        std::vector<Sensor*> active;

        for (unsigned int i=0; i<=senarr.size()-1; i++)
        {
            if (senarr[i].focal_center.get_z()<space.world[zsweep][0][0].z)
            {
                 active.push_back(&senarr[i]);
            }
        }

        active_array.push_back(active);
    }

    for (int z0=0; z0<=WORLD_Z-1; z0++)
    {
        std::vector<Sensor*>& active=active_array[z0];

        //int num_views=active.size();

        for (int y=WORLD_Y-1; y>=0; y--)
        {
            for (int x=WORLD_X-1; x>=0; x--)
            {
                cout<<"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
                    <<ctr*100/(WORLD_X*WORLD_Y*WORLD_Z)<<"%  ";
                //cout<<"("<<x0<<","<<y<<","<<z<<")\n";

                Voxel& vox=space.world[z0][y][x];
                #ifdef DEBUG
                cout<<"Now checking voxel ("<<vox.z<<","
                    <<vox.y<<","<<vox.x<<")\n";
                #endif
                common_code(vox,active);//,space);
                ctr++;
            }
        }
    }

    return answer;
}

void Comrade::Iris3D::common_code(Comrade::Iris3D::Voxel& vox,
                                  std::vector<Comrade::Iris3D::Sensor*> active)
/* Comrade::Iris3D::WorldSpace& space --> This argument
was there in the initial version. Not required now, but
might use it if a better algorithm requires it. */

{
    HSLstruct black={0,0,0};
        
    int num_views=active.size();
    #ifdef DEBUG
    cout<<"This voxel is watched by: "<<num_views<<" cameras.\n";
    #endif

    //cout<<"Active candidates="<<num_views<<" ";

    bool carve=false;
    Coordinate arr[8];
    //Coordinate rect[2][2];

    if (vox.carved==true || num_views<=1)
    {
        //cout<<"Already done, no?\n";
        return;
    }

    //double hue=0;
    double tot=0;
    std::vector<double> hue_arr;

    //cout<<"Before loop. "<<senarr.size()<<"\n";

    std::vector<Sensor*> flagged;
    // Narrowing down active
    for (int i=0; i<=num_views-1; i++)
    {
        VoxelWorker::bounded_intersection_of
                    (vox,*active[i],arr);

        VoxelWorker::find_rectangle(active[i]->proj_rect,arr);
        //cout<<"Before...";
        int imgx1=GARGOYLE_X/2+(active[i]->proj_rect[0][0]);
        int imgy1=GARGOYLE_Y/2+(active[i]->proj_rect[0][1]);
        int imgx2=GARGOYLE_X/2+(active[i]->proj_rect[1][0]);
        int imgy2=GARGOYLE_Y/2+(active[i]->proj_rect[1][1]);

        #ifdef DEBUG
        cout<<"For camera "<<active[i]->id<<", defined rectangle is : ";
        cout<<"("<<imgx1<<","<<imgy1<<")-("<<imgx2<<","<<imgy2<<")";
        #endif

        if ((imgy1>GARGOYLE_Y-1 || imgy1<0) ||
            (imgy2>GARGOYLE_Y-1 || imgy2<0) ||
            (imgx1>GARGOYLE_X-1 || imgx1<0) ||
            (imgx2>GARGOYLE_X-1 || imgx2<0))
        {
            #ifdef DEBUG
            cout<<"Rectangle out of image. Rejecting this camera and carving the voxel...";
            cin.get();
            #endif

            vox.carved=true;
            vox.color=black;
            return;
            //continue;
        }

        active[i]->isect_color=active[i]->img_buffer_ptr
                                          ->at
                                          ((imgx1+imgx2)/2,
                                           (imgy1+imgy2)/2);

        double num=0;
        int total=0;

        for (int y=imgy1; y<=imgy2; y++)
        {
            for (int x=imgx1; x<=imgx2; x++)
            {
                if (active[i]->
                    flag_buffer_ptr->
                    at(x,y)==false)
                {
                    num++;
                }

                total++;
            }
        }

        //cout<<"Ending time in loop 1\n";
                    
        /*if (active[i]->flag_buffer_ptr->at((imgx1+imgx2)/2,
                                           (imgy1+imgy2)/2)==true)*/
        if (num/total<=0.9)
        {
            #ifdef DEBUG
            cout<<"But the voxel is occluded, so no calculations will be done...\n";
            #endif

            return;
        }

        else
        {
            #ifdef DEBUG
            cout<<"Voxel is exposed, so camera "<<active[i]->id<<" is to be used.\n";
            #endif

            flagged.push_back(active[i]);

            double huesum=0;
            for (int yy=imgy1; yy<=imgy2; yy++)
            {
                for (int xx=imgx1; xx<=imgx2; xx++)
                {
                    huesum+=active[i]->img_buffer_ptr
                                     ->at(xx,yy).luminance;
                }
            }

            if (imgx1!=imgx2 && imgy1!=imgy2)
            {
                huesum/=((imgy2-imgy1)*(imgx2-imgx1));
            }

            #ifdef DEBUG
            cout<<"Hue average for camera "<<active[i]->id<<" is "<<huesum;
            #endif

            hue_arr.push_back(huesum);
            tot+=huesum;
        }
    }

    //cout<<"Checking for consistencies...\n";
    //int valid_views=flagged.size();
    int used_views=hue_arr.size();

    //if (used_views>0)
    //{
        //cout<<"Used views="<<used_views<<" ";
    //}

    if (used_views<=1)
    {
        #ifdef DEBUG
        cout<<"No usable views...carving out voxel.\n";
        #endif

        vox.carved=true;
        vox.color=black;

        return;
    }

    tot/=used_views;
    double var=0;

    for (int i=0; i<=used_views-1; i++)
    {
        double sqdiff=hue_arr[i]-tot;
        sqdiff=sqdiff*sqdiff;
        var+=sqdiff;
    }

    //cout<<var<<" "<<used_views<<endl;
                
    if (tot==0 && used_views>0)
    {
        carve=false;
        return;
    }

    else
    {
        var=sqrt(var/tot);
        #ifdef DEBUG
        cout<<"Variance from all cameras is "<<var;
        #endif

        carve=(var<THRESHOLD)?false:true;
    }

    if (carve==true)
    {
        #ifdef DEBUG
        cout<<"Voxel is inconsistent, will be carved.\n";
        #endif

        complete=false;
        carved++;
        //num++;
        //cout<<" Carving...\n";
        vox.color=black;
        vox.carved=true;
    }

    else
    {
        #ifdef DEBUG
        cout<<"Voxel is consistent, will not be carved.\n";
        #endif

        vox.carved=false;
        //cout<<" Not carving...\n";
        vox.color=flagged[0]->img_buffer_ptr->at
                  (GARGOYLE_X/2+
                   (flagged[0]->proj_rect[0][0]+
                    flagged[0]->proj_rect[1][0])/2,
                   GARGOYLE_Y/2+
                   (flagged[0]->proj_rect[0][1]+
                    flagged[0]->proj_rect[1][1])/2);

        //RGB color=ColorSpaceConvertor::HSL_to_uRGB(vox.color);

        /*cout<<static_cast<int>(color.red)
            <<static_cast<int>(color.green)
            <<static_cast<int>(color.blue)<<endl;
        */

        #ifdef DEBUG
        cin.get();
        #endif

        for (int i=0; i<=used_views-1; i++)
        {
            #ifdef DEBUG

            cout<<"Marking ("
            <<GARGOYLE_X/2+flagged[i]->proj_rect[0][0]
            <<","<<GARGOYLE_Y/2+flagged[i]->proj_rect[0][1]<<") to ("
            <<GARGOYLE_X/2+flagged[i]->proj_rect[1][0]<<","
            <<GARGOYLE_Y/2+flagged[i]->proj_rect[1][1]
            <<") in image associated with camera "<<flagged[i]->id<<".\n";
            #endif

            for (int yy=GARGOYLE_Y/2+flagged[i]->proj_rect[0][1]; yy<=GARGOYLE_Y/2+flagged[i]->proj_rect[1][1]; yy++)
            {
                for (int xx=GARGOYLE_X/2+flagged[i]->proj_rect[0][0]; xx<=GARGOYLE_X/2+flagged[i]->proj_rect[1][0]; xx++)
                {
                    flagged[i]->flag_buffer_ptr->at(xx,yy)=true;
                }
            }
        }
    }

    #ifdef DEBUG
    cin.get();
    #endif
}


