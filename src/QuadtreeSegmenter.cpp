#include "QuadtreeSegmenter.h"

Comrade::IrisFoundation::QuadtreeSegmenter::QuadtreeSegmenter()
{}

void Comrade::IrisFoundation::QuadtreeSegmenter::build_quadtree
(Comrade::IrisFoundation::Tree<Rectangle,Comrade::Iris3D::Coordinate>* quad,
 Comrade::IrisFoundation::Buffer<RGB>* buf)
{
    TreeNode<Rectangle>* start=quad->get_root();

    recursive_segment(start,buf);
}

void Comrade::IrisFoundation::QuadtreeSegmenter::recursive_segment
(Comrade::IrisFoundation::TreeNode<Comrade::IrisFoundation::Rectangle>* current,
 Comrade::IrisFoundation::Buffer<RGB>* buf)
{
    RGB black={0,0,0};

    int x1=current->data.x1;
    int y1=current->data.y1;
    int x2=current->data.x2;
    int y2=current->data.y2;

    //cout<<"Now checking "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;

    if (x2-x1<=minx || y2-y1<=miny)
    {
        //cout<<"Bad1";
        current->data.color=buf->at((x1+x2)/2,(y1+y2)/2);
        return;
    }

    if (is_consistent(current->data,buf)==false)
    {
        Rectangle r1={x1,y1,(x1+x2)/2,(y1+y2)/2,black};
        Rectangle r2={(x1+x2)/2,y1,x2,(y1+y2)/2,black};
        Rectangle r3={(x1+x2)/2,(y1+y2)/2,x2,y2,black};
        Rectangle r4={x1,(y1+y2)/2,(x1+x2)/2,y2,black};

        /*cout<<"Breaking into 4..."<<current->data.x1<<" "
                                  <<current->data.y1<<" "
                                  <<current->data.x2<<" "
                                  <<current->data.y2<<"\n";*/

        current->add_branch(r1);
        current->add_branch(r2);
        current->add_branch(r3);
        current->add_branch(r4);

        for (int i=0; i<=3; i++)
        {
            recursive_segment(current->branch_list[i],buf);
        }
    }

    else
    {
        //cout<<"Bad2";
        current->data.color=buf->at((x1+x2)/2,(y1+y2)/2);
        return;
    }
}

bool Comrade::IrisFoundation::QuadtreeSegmenter::is_consistent
(Comrade::IrisFoundation::Rectangle rect,
 Comrade::IrisFoundation::Buffer<RGB>* buf)
{
    // Write color variance testing code here
    double avgr=0,avgg=0,avgb=0,total=0;
    double varr=0,varg=0,varb=0;

    for (int yy=rect.y1; yy<=rect.y2; yy++)
    {
        for (int xx=rect.x1; xx<=rect.x2; xx++)
        {
            avgr+=buf->at(xx,yy).red;
            avgg+=buf->at(xx,yy).green;
            avgb+=buf->at(xx,yy).blue;

            total++;
        }
    }

    avgr/=total;
    avgg/=total;
    avgb/=total;

    for (int yy=rect.y1; yy<=rect.y2; yy++)
    {
        for (int xx=rect.x1; xx<=rect.x2; xx++)
        {
            varr+=(buf->at(xx,yy).red-avgr)*(buf->at(xx,yy).red-avgr);
            varg+=(buf->at(xx,yy).green-avgg)*(buf->at(xx,yy).green-avgg);
            varb+=(buf->at(xx,yy).blue-avgb)*(buf->at(xx,yy).blue-avgb);
        }
    }

    varr/=total*3;
    varg/=total*3;
    varb/=total*3;

    double final=varr+varg+varb;
    cout<<varr+varg+varb<<" "<<total<<endl;

    /*if (final>=min && final<=max)
    {
        return true;
    }

    else
    {
        return false;
    }*/

    if (final<=threshold)
    {
        return true;  // to create a quadtree, return true here.
    }

    else
    {
        return false; // to create a quadtree, return false here.
    }
}

void Comrade::IrisFoundation::QuadtreeSegmenter::draw_quadtree
(Comrade::IrisFoundation::Tree<Rectangle,Comrade::Iris3D::Coordinate>* quad,
 Comrade::IrisFoundation::Buffer<RGB>* buf)
{
    TreeNode<Rectangle>* start=quad->get_root();

    recursive_draw(start,buf);
}

void Comrade::IrisFoundation::QuadtreeSegmenter::recursive_draw
(Comrade::IrisFoundation::TreeNode<Comrade::IrisFoundation::Rectangle>* current,
 Comrade::IrisFoundation::Buffer<RGB>* buf)
{
    if (current->is_terminal()==false)
    {
        for (unsigned int i=0; i<=current->branch_list.size()-1; i++)
        {
            recursive_draw(current->branch_list[i],buf);
        }
    }

    else
    {
        for (int yy=current->data.y1; yy<=current->data.y2; yy++)
        {
            for (int xx=current->data.x1; xx<=current->data.x2; xx++)
            {
                buf->at(xx,yy)=current->data.color;
            }
        }

        #ifdef DRAW_QUADTREE_BORDERS
        RGB black={0,0,0};
        for (int yy=current->data.y1; yy<=current->data.y2; yy++)
        {
            buf->at(current->data.x1,yy)=black;
            buf->at(current->data.x2,yy)=black;
        }

        for (int xx=current->data.x1; xx<=current->data.x2; xx++)
        {
            buf->at(xx,current->data.y1)=black;
            buf->at(xx,current->data.y2)=black;
        }
        #endif
    }
}

Comrade::IrisFoundation::QuadtreeSegmenter::~QuadtreeSegmenter()
{}


