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

#include "circle.h"

#include <stdlib.h>

const double PI = 3.14159265359;

Circle::Circle(double x, double y, double radius)
{
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->width  = radius;
    this->height = radius;
    this->r = 1;
    this->g = 1;
    this->b = 1;
    this->rAlphaRequested = false;
    this->rAlphaValue = 0;
}

void Circle::setFilled(bool flag)
{
    this->filled = flag;
}

void Circle::randomSize(double start, double end) // Implements Object::randomSize()
{
    double r     = drand48();
    double range = end - start;

    r = start + (r*range);

    this->radius = r;
    this->width  = r;
    this->height = r;
}

void Circle::randomAlpha(double start, double end)
{
    double r     = drand48();
    double range = end - start;

    this->rAlphaRequested = true;
    this->rAlphaValue     = start + (r*range);
}

void Circle::draw(DrawingContext* dc) // Implements Object::draw()
{
    if (this->rAlphaRequested)
    {
        dc->setSourceRgba(this->r, this->g, this->b, rAlphaValue);
    }
    else
    {
        dc->setSourceRgb(this->r, this->g, this->b);
    }
    dc->arc(this->x, this->y, this->radius, 0, 2 * PI);
    if (this->filled) dc->fill();
    else              dc->stroke();
}


