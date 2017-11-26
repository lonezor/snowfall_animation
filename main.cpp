#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "image_surface.h"
#include "drawing_context.h"
#include "snowflake.h"

#define NR_FRAMES (5000)

#define MAX_NR_SNOWFLAKES (10000)

static Snowflake* snowflakes[MAX_NR_SNOWFLAKES] = {0};

int main(int argc, char* argv[])
{
    int i,j;
    int frameIdx;
    int frameNr = 0;
    ImageSurface*   imageSurface   = new ImageSurface(1920,1080);
    //ImageSurface*   imageSurface   = new ImageSurface(7680,4320);
    char fileName[100];
    
    DrawingContext* dc             = new DrawingContext((Surface*)imageSurface, ANTI_ALIAS_BEST);
    
    memset(snowflakes, 0, sizeof(snowflakes));
 
    // 600 frames
    for(frameIdx=0; frameIdx < NR_FRAMES; frameIdx++)
    {
        dc->clear();

        dc->setSourceRgb(0.1,0,0.1);
        dc->paint();

        // Snow flake emitter
        double r = drand48();
        r *= 10;
        for(i=0; i<(int)r; i++)
        {
            for(j=0; j<MAX_NR_SNOWFLAKES; j++) // Major TODO: storage of new objects and life cycle of objects
            {
                if (!snowflakes[j])
                {
                    snowflakes[j] = new Snowflake();
                    break;
                }
            }
        }

        for(i=0; i<MAX_NR_SNOWFLAKES; i++)
        {
          if (snowflakes[i])
          {
            if (snowflakes[i]->onScreen()) 
            {
              snowflakes[i]->drawNextFrame(dc);
            }
            else
            {
                delete snowflakes[i];
                snowflakes[i] = NULL;
                printf("Deleting snowflake %d\n", i);
            }
          }
        }

      snprintf(fileName, sizeof(fileName), "/home/samba/git/png/out_%06d.png", frameNr++);
      printf("Writing file %s\n", fileName);
      imageSurface->writePngFile(fileName);
      
    }





    

    delete imageSurface;
    delete dc;

    return 0;
}