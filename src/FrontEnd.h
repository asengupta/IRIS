#ifndef FRONT_END_H
#define FRONT_END_H

#include <iostream>
#include <string>
#include "WordFinder.h"
#include "Interpreter.h"

namespace Comrade {
    namespace IrisRuntime {

class FrontEnd
{
protected:      std::string prompt;
                char command[80];
                Interpreter interpreter;

public:         static FrontEnd* front_handle;

                FrontEnd();
                void interpret(char* cmd);
                void erase(std::string cmd_string);
                void ext_interpret(char* cmd);
                void add(std::string command_string,std::string form,function_handle fn);
                void set_prompt(std::string p);
                void activate();
                ~FrontEnd();
};

}
}

#endif

