#ifndef QUADTREE_SEGMENTER_H
#define QUADTREE_SEGMENTER_H

#include "QuadtreeCore.h"
#include "BufferConvertor.h"
#include "BitmapStreamer.h"
#include "Vert3D.h"

namespace Comrade {
    namespace IrisFoundation {

#define DRAW_QUADTREE_BORDERS

struct Rectangle
{
    int x1,y1,x2,y2;
    RGB color;
};

class QuadtreeSegmenter
{
protected:

public:     int threshold;
            int minx,miny;
            int min,max;

            QuadtreeSegmenter();

            void build_quadtree(Tree<Rectangle,
                                Comrade::Iris3D::Coordinate>* quad,
                                Buffer<RGB>* buf);

            void recursive_segment(TreeNode<Rectangle>* current,
                                   Buffer<RGB>* buf);

            bool is_consistent(Rectangle rect,Buffer<RGB>* buf);

            void draw_quadtree(Tree<Rectangle,
                               Comrade::Iris3D::Coordinate>* quad,
                               Buffer<RGB>* buf);

            void recursive_draw(TreeNode<Rectangle>* current,
                                Buffer<RGB>* buf);

            ~QuadtreeSegmenter();
};

}
}

#endif


