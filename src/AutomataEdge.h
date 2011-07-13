#ifndef AUTOMATA_EDGE_H
#define AUTOMATA_EDGE_H

#include <cmath>
#include "BufferConvertor.h"

namespace Comrade {
    namespace IrisXT {

using namespace Comrade::IrisFoundation;

class CA_EdgeDetector
{
protected:  int lim_x,lim_y;
            double threshold;
            int quorum;

public:     CA_EdgeDetector();

            void set_check_limits(int ly,int lx);
            void set_threshold(double th);
            void set_quorum(int qu);

            
            void detect_edge(Buffer<RGB>* ip_buffer,
                             Buffer<RGB>* op_buffer);

            void detect_edge(Buffer<RGB>* ip_buffer,
                             Buffer<RGB>* op_buffer,
                             int x1,int y1,int x2,int y2);

            void clean(Buffer<RGB>* ip_buffer,
                       Buffer<RGB>* op_buffer);

            void clean(Buffer<RGB>* ip_buffer,
                       Buffer<RGB>* op_buffer,
                       int x1,int y1,int x2,int y2);

            ~CA_EdgeDetector();
};

}
}

#endif

