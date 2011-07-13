#ifndef COMMAND_FN_LIST
#define COMMAND_FN_LIST

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <vector>
#include "IrisEnv.h"
#include "FrontEnd.h"

namespace Comrade {
  namespace IrisRuntime {
    
using namespace IrisFoundation;
using namespace IrisXT;
using namespace Iris3D;

void fn1(std::vector <Comrade::IrisRuntime::Argument> arr);
void fn2(std::vector <Comrade::IrisRuntime::Argument> arr);
void quit(std::vector <Comrade::IrisRuntime::Argument> arr);
void exec(std::vector <Comrade::IrisRuntime::Argument> arr);
void set_p(std::vector <Comrade::IrisRuntime::Argument> arr);
void multi_args(std::vector <Comrade::IrisRuntime::Argument> arr);
void cls(std::vector <Comrade::IrisRuntime::Argument> arr);

}
}

#endif

