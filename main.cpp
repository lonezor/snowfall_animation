#include <stdio.h>
#include <math.h>

#include "image_surface.h"
#include "drawing_context.h"
#include "circle.h"



int main(int argc, char* argv[])
{
    int i;
    ImageSurface*   imageSurface   = new ImageSurface(1920,1080);
    //ImageSurface*   imageSurface   = new ImageSurface(7680,4320);

    DrawingContext* dc             = new DrawingContext((Surface*)imageSurface, ANTI_ALIAS_BEST);

    dc->setSourceRgb(0.1,0,0.1);
    dc->paint();

    

    dc->setSourceRgb(1,1,1);
    dc->setLineWidth(1);
    dc->moveTo(300,100);
    dc->lineTo(300,150);
    dc->lineTo(800,300);
    dc->closePath();
    dc->stroke();

    dc->setSourceRgba(1,0,0, 0.5);
    dc->rectangle(300,100,100,50);
    dc->fill();

    for(i=0; i<500; i++)
    {
        Circle* circle = new Circle(200,200, 100);
        circle->setFilled(1);
        circle->randomCoordinates(1920,1080);
        circle->randomSize(0.5,4);
        circle->draw(dc);
        delete circle;
    }

    //dc->setSourceRgb(1,1,1);
    //dc->arc(200, 200, 100, 0, 2 * PI);
    //dc->stroke();


    imageSurface->writePngFile("/tmp/out.png");

    delete imageSurface;
    delete dc;

    return 0;
}