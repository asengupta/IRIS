#ifndef ARG_DECS_H
#define ARG_DECS_H

#include <vector>

namespace Comrade {
    namespace IrisRuntime {

union ArgumentCell
{
    int number_part;
    char string_part[20];
};

struct Argument
{
public:     ArgumentCell argument_cell;
            bool is_valid;

            Argument();
    //{
    //    is_valid=false;
    //}
};

}
}

#endif

