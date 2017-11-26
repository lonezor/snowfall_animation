#include "snowflake.h"

#include <stdio.h>
#include <stdlib.h>

Snowflake::Snowflake()
{
    this->object = new Circle(200,200, 100);
    this->object->setFilled(1);
    this->object->randomCoordinates(1920,1080);
    this->object->decY(1200);

    this->xVelocity = drand48() * 5;
    if (drand48() < 0.1) this->xVelocity *= -1;

    double r = drand48();
    if (r < 0.7) // smaller flakes are more common
    {
        this->object->randomSize(0.5,3.5);
    }
    else
    {
        this->object->randomSize(3.5,5);
    }
    
    this->size = this->object->getWidth() * 2; // Diameter

    

    // Vertical velocity. The speed of snowfall. A larger flake have lower velocity due to 
    this->yVelocity = 10.5 - this->size;
    this->yVelocity /= 4;
    
}

bool Snowflake::onScreen()
{
    double y = this->object->getY();
    return ( y > -3000 && y < 3000);
}

void Snowflake::drawNextFrame(DrawingContext* dc)
{
    this->object->incX(this->xVelocity);
    this->object->incY(this->yVelocity);
    this->object->draw(dc);
    
}