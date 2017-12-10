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

#include "snowflake.h"

#include <stdio.h>
#include <stdlib.h>

Snowflake::Snowflake(DrawingContext* dc, Wind* wind)
{
    this->dc = dc;
    this->wind = wind;
    this->object = new Circle(200,200, 100);
    this->object->setFilled(true);
    //this->object->randomAlpha(0.7,1.0);

    // Random coordinate above the screen
    this->object->randomCoordinates(1920,1080);
    this->object->decY(1080+100);

    // Randomize size. Smaller flakes are more common
    double r = drand48();
    if (r < 0.7) // smaller flakes
    {
        this->object->randomSize(0.5,3.5);
    }
    else // larger flakes
    {
        this->object->randomSize(3.5,5);
    }
    this->size = this->object->getWidth() * 2; // Diameter

    // Randomize horizontal speed. The majority of flakes towards the right.
    // Also, add randomization during animation with xDiff which may also change direction
    this->xVelocity = drand48() * 1.0;
    if (drand48() < 0.1) this->xVelocity *= -1;
    this->xDiff = drand48() / 1024; // make horizontal animation look random instead of contant value.
                                  // the direction is later changed randomy as well.

    // Randomize vertical speed. A larger flake have lower velocity due to increased air resistance
    this->yVelocity = 10.5 - this->size;
    this->yVelocity /= 4; // scaling factor
    
}

bool Snowflake::onScreen()
{
    double y = this->object->getY();
    return ( y > -2 * 1080 && y < 1080 * 2);
}

void Snowflake::drawNextFrame()
{
    // Snowflake specific horizontal velocity
    double r = drand48();
    if (r < 0.001) // Has to be rare. If too frequent the animation goes back and forth
    {              // On the other hand it has to occur during screen time
        this->xDiff *= -1; // change direction
    } // TODO: the xVelocity may change much more for all flakes to take into account for strong side wind
    this->xVelocity += this->xDiff;

    // Wind affecting all snowflakes
    this->xVelocity += this->wind->getXDiff();
    this->yVelocity += this->wind->getYDiff();

    this->object->incX(this->xVelocity);
    this->object->incY(this->yVelocity);
    this->object->draw(dc);
}