#include "CommandFunctionList.h"

void fn1(std::vector <Comrade::IrisRuntime::Argument> arr)
{
    std::cout<<"Called fn1()";
    std::cout<<"Validity="<<arr[0].is_valid<<" and "<<arr[1].is_valid<<std::endl;
    std::cout<<arr[0].argument_cell.number_part<<" "<<arr[1].argument_cell.string_part<<std::endl;
}

void fn2(std::vector <Comrade::IrisRuntime::Argument> arr)
{
    if (arr[0].is_valid==arr[1].is_valid==arr[2].is_valid==true)
    {
        for (int i=1; i<=arr[2].argument_cell.number_part; i++)
        {
            std::cout<<arr[0].argument_cell.string_part<<" likes to eat "<<arr[1].argument_cell.string_part<<std::endl;
        }
    }

    std::cout<<"Called fn2()\n";
}

void quit(std::vector <Comrade::IrisRuntime::Argument> arr)
{
    std::cout<<arr.size()<<std::endl;
    std::cout<<"Exiting...press a key.";

    std::cin.get();
    exit(0);
}

void exec(std::vector <Comrade::IrisRuntime::Argument> arr)
{
    std::cout<<arr.size()<<std::endl;
    
    Comrade::IrisRuntime::FrontEnd* handle=
    Comrade::IrisRuntime::FrontEnd::front_handle;

    char ch[80];
    std::ifstream media(arr[0].argument_cell.string_part);

    if (media.is_open())
    {
        while (media.eof()==false)
        {
            media.getline(ch,79);
            //cout<<ch;
            handle->ext_interpret(ch);
        }

        media.clear();
        media.close();
    }


    //cout<<"I am invincible...\n";
}

void multi_args(std::vector <Comrade::IrisRuntime::Argument> arr)
{
    //assert(arr.size()!=0);
    //Remove the comments above for debug versions

    if (arr.size()!=0)
    {
        for (unsigned int i=0; i<=arr.size()-1; i++)
        {
            if (arr[i].is_valid==true)
            {
                //cout<<"At least one is there...\n";
                std::cout<<arr[i].argument_cell.string_part<<" ";
            }
        }

        std::cout<<std::endl;
    }

    else
    {
        std::cout<<"No arguments passed.\n";
    }
}

void set_p(std::vector <Comrade::IrisRuntime::Argument> arr)
{
    Comrade::IrisRuntime::FrontEnd* h=
    Comrade::IrisRuntime::FrontEnd::front_handle;

    h->add("do","WWN",fn2);

    if (arr[0].is_valid==true)
    {
        h->set_prompt(arr[0].argument_cell.string_part);
    }
}

void cls(std::vector <Comrade::IrisRuntime::Argument> arr)
{
    std::cout<<arr.size();
    system("clear");  
}

