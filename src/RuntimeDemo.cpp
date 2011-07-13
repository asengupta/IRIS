#include <iostream>
#include "RuntimePool.h"
#include "FrontEnd.h"
#include "CommandFunctionList.h"
#include "IrisEnv.h"
#include "SOM_Trainer.h"

extern Comrade::IrisRuntime::IrisEnvironment* iris_vm;

using namespace std;
using namespace Comrade::IrisFoundation;
using namespace Comrade::IrisXT;
using namespace Comrade::Iris3D;
using namespace Comrade::IrisRuntime;
using namespace Comrade::Osiris;

int main()
{
   cout<<"Starting now...";
   
   BitmapStreamer left,right,dmap;
   left.byte_reader.reader.open("Left.bmp",ios::in|ios::binary);
   left.byte_reader.writer.open("Left.bmp",ios::out|ios::binary);

   //right.byte_reader.reader.open("Right.bmp",ios::in|ios::binary|ios::nocreate);
   //right.byte_reader.writer.open("Right.bmp",ios::out|ios::binary|ios::nocreate);

   //dmap.byte_reader.reader.open("Blank.bmp",ios::in|ios::binary|ios::nocreate);
   //dmap.byte_reader.writer.open("Blank.bmp",ios::out|ios::binary|ios::nocreate);

   /*if (left.byte_reader.reader.is_open()==false ||
       right.byte_reader.reader.is_open()==false ||
       dmap.byte_reader.reader.is_open()==false)
   {
        cout<<"Files could not be opened...\n";

        cin.get();
        return 0;
   }*/

   Buffer<RGB> l(&left),r(&right),d(&dmap);

   RGB_BufferManager manl,manr,mand;
   manl.assign_buffer(&l);
   //manr.assign_buffer(&r);
   //mand.assign_buffer(&d);

   manl.copy_from_image(&left);
   //manr.copy_from_image(&right);

   cout<<"Finished copying to buffer...\n";
   
   cin.get();
   return 0;
   
   //iris_vm=new IrisEnvironment;
    
    //iris_vm->activate();
    
    //delete iris_vm;
    
    DepthmapBuilder bldr;
    bldr.set_stepsize(1);

    bldr.build_depthmap(&l,&r,&d);

    mand.copy_to_image(&dmap);

    left.byte_reader.reader.close();
    left.byte_reader.writer.close();

    right.byte_reader.reader.close();
    right.byte_reader.writer.close();

    dmap.byte_reader.reader.close();
    dmap.byte_reader.writer.close();

    cin.get();
    return 0;
}

