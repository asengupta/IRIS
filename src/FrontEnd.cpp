#include "FrontEnd.h"

Comrade::IrisRuntime::FrontEnd*
Comrade::IrisRuntime::FrontEnd::front_handle=NULL;

Comrade::IrisRuntime::FrontEnd::FrontEnd()
{
    system("clear");
    
    std::cout<<"\nScorpioCLI v2.01 for Linux/Windows\n";
    std::cout<<"--------------------------------------\n";
    std::cout<<"(c) 2003 Avishek Sen Gupta\n";
    std::cout<<"\nHave a nice day :-)\n\n";
    std::cout<<"Currently loaded environment is IRIS Runtime for Linux/Windows.\n";
}

void Comrade::IrisRuntime::FrontEnd::set_prompt(std::string p)
{
    prompt=p;
}

void Comrade::IrisRuntime::FrontEnd::add
(std::string command_string,std::string form,function_handle fn)
{
    interpreter.add(command_string,form,fn);
}

void Comrade::IrisRuntime::FrontEnd::erase(std::string cmd_string)
{
    interpreter.erase(cmd_string);
}

void Comrade::IrisRuntime::FrontEnd::interpret(char* cmd)
{
    front_handle=this;
    interpreter.interpret(cmd);
}

void Comrade::IrisRuntime::FrontEnd::ext_interpret(char* cmd)
{
    interpreter.store_current();
    interpret(cmd);
    interpreter.restore_current();
}

void Comrade::IrisRuntime::FrontEnd::activate()
{
    while (true)
    {
        std::cout<<prompt;
        std::cin.getline(command,79);

        interpret(command);
    }
}

Comrade::IrisRuntime::FrontEnd::~FrontEnd()
{}

