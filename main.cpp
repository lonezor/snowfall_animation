#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "image_surface.h"
#include "drawing_context.h"
#include "snowflake.h"
#include "wind.h"
#include "config.h"

#define NR_FRAMES         (FRAME_RATE*60*3)
#define MAX_NR_SNOWFLAKES (10000)
#define IMAGE_WIDTH_2K    (1920)
#define IMAGE_HEIGHT_2K   (1080)
#define IMAGE_WIDTH_4K    (3840)
#define IMAGE_HEIGHT_4K   (2160)
#define IMAGE_WIDTH_8K    (7680)
#define IMAGE_HEIGHT_8K   (4320)

static Snowflake* snowflakes[MAX_NR_SNOWFLAKES] = {0};

// Video encoding command: ffmpeg -r 60 -f image2 -s 1920x1080 -i out_%06d.png -vcodec libx264 -crf 25  -pix_fmt yuv420p test.mp4

int main(int argc, char* argv[])
{
    int i,j;
    int frameIdx;
    int frameNr = 0;

    // The graphics backend automatically scale for any resolution,
    // although the same aspect ratio should be used.
    ImageSurface*   imageSurface   = new ImageSurface(IMAGE_WIDTH_2K,IMAGE_HEIGHT_2K);
    //ImageSurface*   imageSurface   = new ImageSurface(IMAGE_WIDTH_4K,IMAGE_HEIGHT_4K);
    //ImageSurface*   imageSurface   = new ImageSurface(IMAGE_WIDTH_8K,IMAGE_HEIGHT_8K);
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

    memset(snowflakes, 0, sizeof(snowflakes));
 
    for(frameIdx=0; frameIdx < NR_FRAMES; frameIdx++)
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

      snprintf(fileName, sizeof(fileName), "/home/samba/git/png/out_%06d.png", frameNr++);
      printf("Writing file %s\n", fileName);
      imageSurface->writePngFile(fileName);
    }

    delete imageSurface;
    delete dc;
    delete wind;
    return 0;
}
