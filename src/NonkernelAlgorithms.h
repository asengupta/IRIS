#ifndef NONKERNEL_ALGORITHMS_H
#define NONKERNEL_ALGORITHMS_H

#include <cassert>
#include <cmath>
#include "Buffer.h"
#include "ColorSpaces.h"
#include "BufferConvertor.h"
//#include "Gollum.h"

namespace Comrade {
    namespace IrisXT {

using namespace Comrade::IrisFoundation;

class AlgorithmManager
{
protected:  void build_prob_vector(int* vect,
                                   double* final,
                                   int num);

            void build_cumulative_prob_vector(double* prob,
                                              double* total,
                                              int num);

            void calculate_histogram(Buffer<RGB>* buffer,
                                     int* vect,int levels,
                                     Channel channel,
                                     int x1,int y1,
                                     int x2,int y2);

public:     bool copy_to_output;

            AlgorithmManager();

            // IMPORTANT DEVELOPER'S NOTE:
            // The parameterised functions will not
            // copy the entire input buffer to
            // the output buffer unless you set
            // copy_to_output member of the
            // AlgorithmManager object to true in
            // your application.

//*******************************************************
/* Discussion on the above point:
   ------------------------------------------------------

   IRIS-XT allows you to optimise usage of the buffer.
   Thus, instead of always copying everything from the
   input buffer, you may choose to work with only a part
   of the image, and forgo iterating through the entire
   image.
   Also, copying from a buffer can be a low-level function,
   so if you want to keep the whole image, you can either
   do what is said above, or copy the image before calling
   the function. Either way, it is not very expensive.
   ------------------------------------------------------
*/

// IMPORTANT NOTE:
// The scale_to_buffer() function works
// only for downsizing from a larger
// buffer to a smaller one. You cannot
// scale up with this function.

            void dilate(Buffer<RGB>* ip_buffer,
                        Buffer<RGB>* op_buffer);

            void dilate(Buffer<RGB>* ip_buffer,
                        Buffer<RGB>* op_buffer,
                        int x1,int y1,
                        int x2,int y2);

            void erode(Buffer<RGB>* ip_buffer,
                       Buffer<RGB>* op_buffer);

            void erode(Buffer<RGB>* ip_buffer,
                       Buffer<RGB>* op_buffer,
                       int x1,int y1,
                       int x2,int y2);

            void convert_to_greyscale(Buffer<RGB>* ip_buffer,
                                      Buffer<RGB>* op_buffer);

            void convert_to_greyscale(Buffer<RGB>* ip_buffer,
                                      Buffer<RGB>* op_buffer,
                                      int x1,int y1,
                                      int x2,int y2);

            void convert_to_negative(Buffer<RGB>* ip_buffer,
                                     Buffer<RGB>* op_buffer);

            void convert_to_negative(Buffer<RGB>* ip_buffer,
                                     Buffer<RGB>* op_buffer,
                                     int x1,int y1,
                                     int x2,int y2);

            void channel_adjust(Buffer<RGB>* ip_buffer,
                                Buffer<RGB>* op_buffer,
                                int red,int green,int blue);

            void channel_adjust(Buffer<RGB>* ip_buffer,
                                Buffer<RGB>* op_buffer,
                                int red,int green,int blue,
                                int x1,int y1,
                                int x2,int y2);

            void scale_to_buffer(Buffer<RGB>* ip_buffer,
                                 Buffer<RGB>* temp);

            void fast_unsharp_mask(Buffer<RGB>* ip_buffer,
                                   Buffer<RGB>* op_buffer,
                                   double lambda);

            void fast_unsharp_mask(Buffer<RGB>* ip_buffer,
                                   Buffer<RGB>* op_buffer,
                                   double lambda,
                                   int x1,int y1,
                                   int x2,int y2);

            void histogram_equalise(Buffer<RGB>* ip_buffer,
                                    Buffer<RGB>* op_buffer,
                                    Channel channel);

            void histogram_equalise(Buffer<RGB>* ip_buffer,
                                    Buffer<RGB>* op_buffer,
                                    Channel channel,
                                    int x1,int y1,
                                    int x2,int y2);

            void range_compress(Buffer<RGB>* ip_buffer,
                                Buffer<RGB>* op_buffer,
                                double scale);

            void range_compress(Buffer<RGB>* ip_buffer,
                                Buffer<RGB>* op_buffer,
                                double scale,
                                int x1,int y1,
                                int x2,int y2);

            void contrast_stretch(Buffer<RGB>* ip_buffer,
                                  Buffer<RGB>* op_buffer,
                                  Channel channel,
                                  double alpha,double beta,
                                  double gamma);

            void contrast_stretch(Buffer<RGB>* ip_buffer,
                                  Buffer<RGB>* op_buffer,
                                  Channel channel,
                                  double alpha,double beta,
                                  double gamma,
                                  int x1,int y1,int x2,int y2);

            ~AlgorithmManager();
};

}
}

#endif

