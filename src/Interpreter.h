#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <cctype>
#include <vector>
#include "WordFinder.h"
#include "CommandBinder.h"

namespace Comrade {
    namespace IrisRuntime {

struct PreserverUnit
{
    char cmd[80];
    int position;
};

class Interpreter
{
protected:      char command_string[80];
                CommandBinder binder;
                WordFinder finder;
                std::vector <Argument> arg_array;
                std::vector <PreserverUnit> cmd_stack;

public:         Interpreter();
                void add(std::string command_string,std::string form,function_handle fn);
                void erase(std::string cmd_string);
                void interpret(char* cmd);
                void match_with_command(char s[20]);
                void parse_for_arguments(CommandObject& cmd_obj);
                void store_current();
                void restore_current();
                ~Interpreter();
};

}
}

#endif

