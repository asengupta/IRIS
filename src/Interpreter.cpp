#include "Interpreter.h"

Comrade::IrisRuntime::Interpreter::Interpreter()
{
    //cout<<"Interpreter object created...\n";
}

void Comrade::IrisRuntime::Interpreter::interpret(char* cmd)
{
    if (strlen(cmd)!=0)
    {
        strcpy(command_string,cmd);

        char single[20];
        finder.assign_string(command_string);
        finder.find_next_word(single);

        while (finder.success==true)
        {
            match_with_command(single);
            finder.find_next_word(single);
        }
     }
}

void Comrade::IrisRuntime::Interpreter::add
(std::string cmd_string,std::string form,function_handle fn)
{
    binder.add(cmd_string,form,fn);
}

void Comrade::IrisRuntime::Interpreter::erase(std::string cmd_string)
{
    binder.erase(cmd_string);
}

void Comrade::IrisRuntime::Interpreter::match_with_command(char s[20])
{
    for (unsigned int i=0; i<=strlen(s)-1; i++)
    {
        s[i]=tolower(s[i]);
    }

    //cout<<"Matching "<<s<<endl;
    std::string tok=s;
    //cout<<"Converted to "<<tok<<endl;

    CommandObject cmd_obj=binder.return_command_object_for(tok);

    if (binder.is_valid==false)
    {
        std::cout<<tok<<":Unrecognised command.\n";
    }

    else
    {
        //cout<<"Recognised a command.\n";

        parse_for_arguments(cmd_obj);

        //cout<<"About to enter fn...\n";
        cmd_obj.fn_handle(arg_array);

        // Purge Argument vector
        while (arg_array.empty()==false)
        {
            arg_array.pop_back();
        }

        //cout<<"Argument array emptied...\n";
    }
}

void Comrade::IrisRuntime::Interpreter::parse_for_arguments
(Comrade::IrisRuntime::CommandObject& cmd_obj)
{
    //cout<<"In parse...nothing so far..."<<cmd_obj.argument_format<<endl;

    char* form=new char[cmd_obj.argument_format.size()+1];
    strcpy(form,cmd_obj.argument_format.c_str());
    form[strlen(form)]='\0';

    char* arg;

    arg=&form[0];
    int ptr=0;
    bool var_args=false;

    int num;
    char str[20];
    //cout<<"Printing again..."<<arg;
    // First check if the command takes variable arguments

    char* c=strstr(arg,"V");
    var_args=(c==NULL)?false:true;

    Argument dummy;

    if (var_args==true)
    {
        std::cout<<"Specified variable argument list - skipping all other argument fields...\n";
        //finder.find_next_word(str);
        //cout<<"After..."<<finder.success;
        //cin.clear();
        //cout<<"clear?";

       char c=finder.find_next_nonspace();

       while (c!=';' && c!='\0')
       {
            //cout<<"In the finder.success loop.\n";
            finder.find_next_word(str);

            if (finder.success==true)
            {
                arg_array.push_back(dummy);
                arg_array[ptr].is_valid=true;
                strcpy(arg_array[ptr].argument_cell.string_part,str);

                //cout<<"Found one...\n";

                ptr++;
                //finder.find_next_word(str);

                //cout<<"Looping around. success!=true for some reason.\n";
            }

            c=finder.find_next_nonspace();
       }
    }

    if (var_args==false)
    {
        bool is_semicolon=false;

        while (*arg!='\0')
        {
            char y=finder.find_next_nonspace();
            if (y==';')
            {
                is_semicolon=true; // Ban all further processing for the current command
                //cout<<"Found a semicolon while parsing for arguments...\n";
            }


            if (*arg=='W' || *arg=='w')
            {
                if (is_semicolon==false)
                {
                    finder.find_next_word(str);
                }

                if (finder.success==true && is_semicolon==false)
                {
                    arg_array.push_back(dummy);
                    arg_array[ptr].is_valid=true;
                    strcpy(arg_array[ptr].argument_cell.string_part,str);
                }

                else
                {
                    arg_array.push_back(dummy);
                    arg_array[ptr].is_valid=false;
                    arg_array[ptr].argument_cell.string_part[0]='\0';
                }

                ptr++;
                arg++;
            }

            if (*arg=='N' || *arg=='n')
            {
                if (is_semicolon==false)
                {
                    finder.find_next_word(num);
                }

                if (finder.success==true && is_semicolon==false)
                {
                    arg_array.push_back(dummy);
                    arg_array[ptr].is_valid=true;
                    arg_array[ptr].argument_cell.number_part=num;
                }

                else
                {
                    arg_array.push_back(dummy);
                    arg_array[ptr].is_valid=false;
                    arg_array[ptr].argument_cell.number_part=-1;
                }

                ptr++;
                arg++;
            }
        }
    }

    delete[] form;
}

void Comrade::IrisRuntime::Interpreter::store_current()
{
    //cout<<"Problem start...\n";

    PreserverUnit temp;
    //cout<<"N1"<<command_string<<"Waiting"<<endl;
    //cin.get();
    strcpy(temp.cmd,command_string);
    temp.position=finder.return_ptr();

    cmd_stack.push_back(temp);
    finder.reset();
}

void Comrade::IrisRuntime::Interpreter::restore_current()
{
    if (cmd_stack.size()>0)
    {
        int x=cmd_stack[cmd_stack.size()-1].position;
        strcpy(command_string,cmd_stack[cmd_stack.size()-1].cmd);

        finder.assign_string(command_string);
        finder.set_ptr(x);

        //cout<<"Popped "<<command_string<<endl;
        cmd_stack.pop_back();
    }
}

Comrade::IrisRuntime::Interpreter::~Interpreter()
{}


