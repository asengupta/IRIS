#include "IrisEnv.h"

Comrade::IrisRuntime::IrisEnvironment* iris_vm=NULL;

Comrade::IrisRuntime::IrisEnvironment::IrisEnvironment()
{
    cli.set_prompt("IRIS >>");

    cli.add("load","w",load_bmp);
    cli.add("do1","nw",fn1);
    cli.add("do2","WWN",fn2);
    cli.add("quit","",quit);
    cli.add("exit","",quit);
    cli.add("q","",quit);
    cli.add("x","",quit);
    cli.add("exec","w",exec);
    cli.add("mul","wnV",multi_args);
    cli.add("prompt","W",set_p);
    cli.add("cls","",cls);
    //cli.interpret(" exec cmd.mac ");

    std::cout<<"IrisEnvironment created...\n";
}

void Comrade::IrisRuntime::IrisEnvironment::activate()
{
    cli.activate();
}

Comrade::IrisRuntime::IrisEnvironment::~IrisEnvironment()
{
    std::cout<<"IrisEnvironment destroyed...\n";
}

void Comrade::IrisRuntime::fn1(std::vector <Comrade::IrisRuntime::Argument> arr)
{
    std::cout<<"Called fn1()";
    std::cout<<"Validity="<<arr[0].is_valid<<" and "<<arr[1].is_valid<<std::endl;
    std::cout<<arr[0].argument_cell.number_part<<" "<<arr[1].argument_cell.string_part<<std::endl;
}

void Comrade::IrisRuntime::fn2(std::vector <Comrade::IrisRuntime::Argument> arr)
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

void Comrade::IrisRuntime::quit(std::vector <Comrade::IrisRuntime::Argument> arr)
{
    std::cout<<arr.size()<<std::endl;
    std::cout<<"Exiting...press a key.";

    std::cin.get();
    exit(0);
}

void Comrade::IrisRuntime::exec(std::vector <Comrade::IrisRuntime::Argument> arr)
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

void Comrade::IrisRuntime::multi_args(std::vector <Comrade::IrisRuntime::Argument> arr)
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


void Comrade::IrisRuntime::set_p(std::vector <Comrade::IrisRuntime::Argument> arr)
{
    Comrade::IrisRuntime::FrontEnd* h=
    Comrade::IrisRuntime::FrontEnd::front_handle;

    h->add("do","WWN",Comrade::IrisRuntime::fn2);

    if (arr[0].is_valid==true)
    {
        h->set_prompt(arr[0].argument_cell.string_part);
    }
}

void Comrade::IrisRuntime::cls(std::vector <Comrade::IrisRuntime::Argument> arr)
{
    std::cout<<arr.size();
    system("clear");
}

void Comrade::IrisRuntime::load_bmp(std::vector <Comrade::IrisRuntime::Argument> arr)
{
    //std::cout<<"Called fn1()";
    //std::cout<<"Validity="<<arr[0].is_valid<<" and "<<arr[1].is_valid<<std::endl;
    if (arr[0].is_valid==true)
    {
      //std::cout<<"Cool.\n";
      const char* name=arr[0].argument_cell.string_part;
      std::cout<<name<<std::endl;
      
      BitmapStreamer& c=iris_vm->obj_pool.bmp1;
      RGB_BufferManager& man =iris_vm->obj_pool.man1;
      c.byte_reader.writer.open(name,std::ios::in|std::ios::out|std::ios::binary);
      // Replace std::ios::in with std::ios_base::in for Linux
      // but shouldn't make a difference.

      Buffer<RGB> buf(&c);
      std::cout<<"Well?\n";

      man.assign_buffer(&buf);
      man.copy_from_image(&c);

      //iris_vm->obj_pool.algoman.convert_to_negative(&buf,&buf);
      man.copy_to_image(&c);
      c.byte_reader.writer.close();
      std::cout<<"Opened and closed...\n";
    }
}


