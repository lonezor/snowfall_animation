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

#ifndef _SNOWFLAKE_H_
#define _SNOWFLAKE_H_

#include "animated_object.h"
#include "wind.h"
#include "circle.h"

class Snowflake : AnimatedObject // At the moment, a snowflake is an animated circle
{
public:
    Snowflake(DrawingContext* dc, Wind* wind);

    bool onScreen();
    void drawNextFrame();

private:
    double xVelocity; // Wind and air turbulence
    double yVelocity; // Gravity and air resistance
    double size;      // Diameter
    double xDiff;     // Horizontal randomness
    Circle* object;
    DrawingContext* dc;
    Wind* wind;
};




#endif /* _SNOWFLAKE_H_ */