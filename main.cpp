#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "image_surface.h"
#include "drawing_context.h"
#include "snowflake.h"
#include "wind.h"
#include "config.h"

#define NR_FRAMES (FRAME_RATE*60*3)
#define NR_DRY_RUN_FRAMES (FRAME_RATE*60)

#define MAX_NR_SNOWFLAKES (10000)

static Snowflake* snowflakes[MAX_NR_SNOWFLAKES] = {0};

int main(int argc, char* argv[])
{
    int i,j;
    int frameIdx;
    int frameNr = 0;
    ImageSurface*   imageSurface   = new ImageSurface(1920,1080);
    //ImageSurface*   imageSurface   = new ImageSurface(3840,2160);
    //ImageSurface*   imageSurface   = new ImageSurface(7680,4320);
    char fileName[100];
  

    DrawingContext* dc = new DrawingContext((Surface*)imageSurface, ANTI_ALIAS_BEST);
    Wind* wind = new Wind(DEFAULT_MIN_IDLE_TIME,
                          DEFAULT_MAX_IDLE_TIME,
                          DEFAULT_MIN_ACCELERATION_TIME,
                          DEFAULT_MAX_ACCELERATION_TIME,
                          DEFAULT_MIN_STRENGTH,
                          DEFAULT_MAX_STRENGTH,
                          DEFAULT_MIN_DURATION_TIME,
                          DEFAULT_MAX_DURATION_TIME,
                          DEFAULT_MIN_DEACCELERATION_TIME,
                          DEFAULT_MAX_DEACCELERATION_TIME);
    

    // to long wind duration!!!
    
    memset(snowflakes, 0, sizeof(snowflakes));
 
    // 600 frames
    for(frameIdx=0; frameIdx < NR_DRY_RUN_FRAMES + NR_FRAMES; frameIdx++)
    {
        dc->clear();
        dc->setSourceRgb(0.1,0,0.1);
        dc->paint();

        wind->nextFrame();

        // Snow flake emitter
        double r = drand48();
        r *= 40;
        for(i=0; i<(int)r; i++)
        {
            for(j=0; j<MAX_NR_SNOWFLAKES; j++) // Major TODO: storage of new objects and life cycle of objects
            {
                if (!snowflakes[j])
                {
                    snowflakes[j] = new Snowflake(dc, wind);
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
              snowflakes[i]->drawNextFrame();
            }
            else
            {
                delete snowflakes[i];
                snowflakes[i] = NULL;
                printf("Deleting snowflake %d\n", i);
            }
          }
        }

      //if (frameIdx >= NR_DRY_RUN_FRAMES)
        if (1)
      {
        snprintf(fileName, sizeof(fileName), "/home/samba/git/png/out_%06d.png", frameNr++);
        printf("Writing file %s\n", fileName);
        imageSurface->writePngFile(fileName);
      }
      else
      {
        printf("Dry run frame %d\n", i);
      }
      
    }

    delete imageSurface;
    delete dc;
    delete wind;
    return 0;
}