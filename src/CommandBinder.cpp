#include "CommandBinder.h"

Comrade::IrisRuntime::CommandObject::CommandObject()
{
    argument_format[0]='\0';
    fn_handle=NULL;
}

void Comrade::IrisRuntime::CommandObject::set_parameters(std::string format,function_handle fn)
{
    argument_format=format;
    fn_handle=fn;
}

Comrade::IrisRuntime::CommandBinder::CommandBinder()
{
    is_valid=false;
    std::cout<<"CommandBinder object created...\n";

}

void Comrade::IrisRuntime::CommandBinder::add(std::string command_string,std::string form,function_handle fn)
{
    CommandObject c_o;
    c_o.set_parameters(form,fn);
    command_array[command_string]=c_o;

    //cout<<"Added a command..."<<command_string<<endl;
}

Comrade::IrisRuntime::CommandObject&
Comrade::IrisRuntime::CommandBinder::return_command_object_for
(std::string cmd_string)
{
    if (check_for_existence(cmd_string)==true)
    {
        is_valid=true;
        return command_array[cmd_string];
    }

    is_valid=false;
    return dummy;
}

void Comrade::IrisRuntime::CommandBinder::erase(std::string cmd_string)
{
    if (check_for_existence(cmd_string)==true)
    {
        is_valid=true;
        command_array.erase(cmd_string);
    }

    else
    {
        is_valid=false;
    }
}

bool Comrade::IrisRuntime::CommandBinder::check_for_existence
(std::string cmd_string)
{
    Comrade::IrisRuntime::comm_itor search=command_array.find(cmd_string);

    if (search==command_array.end())
    {
        return false;
    }

    return true;

    /*for (comm_itor i=command_array.begin(); i!=command_array.end(); i++)
    {
        if (i->first==cmd_string)
        {
            return true;
        }
    }

    return false;*/
}

Comrade::IrisRuntime::CommandBinder::~CommandBinder()
{}

