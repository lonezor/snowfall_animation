/*
 *  Snowfall Animation
 *  Copyright (C) 2017 Johan Norberg <lonezor@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "image_surface.h"
#include "drawing_context.h"
#include "snowflake.h"
#include "wind.h"
#include "config.h"

//#define NR_FRAMES         (FRAME_RATE * 60 * 4)
#define NR_FRAMES (9300)
#define MAX_NR_SNOWFLAKES (10000)
#define IMAGE_WIDTH_1K    (720)
#define IMAGE_HEIGHT_1K   (405)
#define IMAGE_WIDTH_2K    (1920)
#define IMAGE_HEIGHT_2K   (1080)
#define IMAGE_WIDTH_4K    (3840)
#define IMAGE_HEIGHT_4K   (2160)
#define IMAGE_WIDTH_8K    (7680)
#define IMAGE_HEIGHT_8K   (4320)

static Snowflake* snowflakes[MAX_NR_SNOWFLAKES] = {0};

// Video encoding commands:
// ffmpeg -r 60 -f image2 -i out_%06d.png -crf 23 output.mp4
// ffmpeg -i output.mp4 -i audio_155s.m4a -c:v copy -c:a copy snowfall.mp4 

int main(int argc, char* argv[])
{
    int i,j;
    int frameIdx;
    int frameNr = 0;
    char fileName[100];

    ImageSurface*   imageSurface   = new ImageSurface(IMAGE_WIDTH_4K, IMAGE_HEIGHT_4K);
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
        dc->setSourceRgb(0,0,0);
        dc->paint();

        wind->nextFrame();

        // Snow flake emitter
        double r = drand48();
        r *= (double)40;
        for(i=0; i<(int)r; i++)
        {
            for(j=0; j<MAX_NR_SNOWFLAKES; j++) // TODO: improve storage of snowflakes and handle their life cycle
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
