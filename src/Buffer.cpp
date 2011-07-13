#include "Buffer.h"

Comrade::IrisFoundation::BufferManager::BufferManager()
{}

Comrade::IrisFoundation::BufferManager::~BufferManager()
{}

Comrade::IrisFoundation::RGB_BufferManager::RGB_BufferManager()
{}

void Comrade::IrisFoundation::RGB_BufferManager::assign_buffer(Buffer<RGB>* buf)
{
    maxx=buf->maxx;
    maxy=buf->maxy;
    buffer_ptr=buf->buffer_ptr;
}

void Comrade::IrisFoundation::RGB_BufferManager::copy_from_image(BitmapStreamer* bmp_reader)
{
    bmp_reader->goto_start();

    for (int y=0; y<=maxy-1; y++)
    {
        for (int x=0; x<=maxx-1; x++)
        {
            bmp_reader->read_RGB(buffer_ptr[(maxy-1)-y][x]);// maxyminus -1
        }
    }
}

void Comrade::IrisFoundation::RGB_BufferManager::copy_to_image(BitmapStreamer* bmp_reader)
{
    bmp_reader->goto_start();

    for (int y=0; y<=maxy-1; y++)
    {
        for (int x=0; x<=maxx-1; x++)
        {
            bmp_reader->write_RGB(buffer_ptr[(maxy-1)-y][x]);// maxy-1
        }
    }
}

void Comrade::IrisFoundation::RGB_BufferManager::block_copy_from_image(BitmapStreamer* bmp_reader,
                             int x1,int y1,int x2,int y2,
                             int destx,int desty)
{
    bmp_reader->goto_start();

	int stx,sty=desty;
	

	for(int sy=y1; sy<=y2; sy++)
	{
		stx=destx;
        // Add assertion or mugtraps...
		bmp_reader->read_RGB(x1,sy,buffer_ptr[sty][stx]);
		stx++;
		
		for (int sx=x1+1; sx<=x2; sx++)
		{
			bmp_reader->read_RGB(buffer_ptr[sty][stx]);
			stx++;
		}
	
		sty++;
	}
}

void Comrade::IrisFoundation::RGB_BufferManager::block_copy_to_image(BitmapStreamer* bmp_reader,
                           int x1,int y1,int x2,int y2,
                           int destx,int desty)
{
    bmp_reader->goto_start();
	int stx=destx,sty=desty;
	
    // Add assertion or mugtraps...
	for(int sy=y1; sy<=y2; sy++)
	{
        bmp_reader->write_RGB(stx,sty,buffer_ptr[sy][x1]);

		for (int sx=x1+1; sx<=x2; sx++)
		{
			bmp_reader->write_RGB(buffer_ptr[sy][sx]);
		}
	
		sty++;
	}
}

Comrade::IrisFoundation::RGB_BufferManager::~RGB_BufferManager()
{}

