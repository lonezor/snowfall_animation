#include <stdio.h>
#include <math.h>

#include "image_surface.h"
#include "drawing_context.h"

const double PI = 3.14159265359;

int main(int argc, char* argv[])
{
    ImageSurface*   imageSurface   = new ImageSurface(640,480);
    DrawingContext* dc             = new DrawingContext((Surface*)imageSurface, ANTI_ALIAS_BEST);

    dc->setSourceRgb(0.1,0,0.1);
    dc->paint();

    

    dc->setSourceRgb(1,1,1);
    dc->setLineWidth(1);
    dc->moveTo(300,100);
    dc->lineTo(300,150);
    dc->lineTo(600,300);
    dc->closePath();
    dc->stroke();

    dc->setSourceRgba(1,0,0, 0.5);
    dc->rectangle(300,100,100,50);
    dc->fill();

    dc->setSourceRgb(1,1,1);
    dc->arc(200, 200, 100, 0, 2 * PI);
    dc->stroke();


    imageSurface->writePngFile("/tmp/out.png");

    delete imageSurface;
    delete dc;

    return 0;
}