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

#include "object.h"

#include <stdlib.h>

Object::~Object()
{
    
}

double Object::getX()
{
    return this->x;
}

double Object::getY()
{
    return this->y;
}

void Object::setX(double x)
{
    this->x = x;
}

void Object::setY(double y)
{
    this->y = y;
}

void Object::incX(double amount)
{
    this->x += amount;
}

void Object::decX(double amount)
{
    this->x -= amount;
}

void Object::incY(double amount)
{
    this->y += amount;
}

void Object::decY(double amount)
{
    this->y -= amount;
}

double Object::getWidth()
{
    return this->width;
}

double Object::getHeight()
{
    return this->height;
}

void Object::setRgb(double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}
void Object::setRgba(double r, double g, double b, double a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

bool Object::collision(Object& other)
{
    return 0;
}

void Object::randomCoordinates(double width, double height)
{
    double rx = drand48();
    double ry = drand48();
    rx *= width;
    ry *= height;

    this->x = rx;
    this->y = ry;
}

void Object::randomSize(double start, double end)
{
   



}

void Object::randomColor()
{

}

void Object::randomTransparency()
{

}

void Object::draw(DrawingContext* dc)
{

}
