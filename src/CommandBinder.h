#ifndef COMMAND_BINDER_H
#define COMMAND_BINDER_H

#include <iostream>
#include <map>
#include <string>
#include "ArgDecs.h"

namespace Comrade {
    namespace IrisRuntime {

#define MAX_ARGUMENTS 20
#define AS_STRING 0
#define AS_NUMBER 1

typedef void (*function_handle)(std::vector <Argument> arr);

struct CommandObject
{
    std::string argument_format;
    function_handle fn_handle;

    CommandObject();
    void set_parameters(std::string format,function_handle fn);
};

typedef std::map<std::string,Comrade::IrisRuntime::CommandObject>::const_iterator comm_itor;

class CommandBinder
{
protected:      std::map<std::string,CommandObject> command_array;
                CommandObject dummy;

public:         bool is_valid;

                CommandBinder();
                void add(std::string command_string,std::string form,function_handle fn);
                void erase(std::string cmd_string);
                CommandObject& return_command_object_for(std::string cmd_string);
                bool check_for_existence(std::string cmd_string);
                ~CommandBinder();
};

}
}

#endif

