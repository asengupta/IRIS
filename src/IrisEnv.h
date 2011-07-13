#ifndef IRIS_ENV_H
#define IRIS_ENV_H

#include <iostream>
#include "RuntimePool.h"
#include "FrontEnd.h"

namespace Comrade {
    namespace IrisRuntime {

using namespace IrisFoundation;
using namespace IrisXT;
using namespace Iris3D;

class IrisEnvironment
{
public:   IrisObjectPool obj_pool;
          FrontEnd cli;

public:   IrisEnvironment();

          void activate();

          ~IrisEnvironment();
};

void fn1(std::vector <Argument> arr);
void fn2(std::vector <Argument> arr);
void quit(std::vector <Argument> arr);
void exec(std::vector <Argument> arr);
void set_p(std::vector <Argument> arr);
void multi_args(std::vector <Argument> arr);
void cls(std::vector <Argument> arr);
void load_bmp(std::vector <Argument> arr);

}
}

#endif

