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

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "drawing_context.h"

class Object
{
public:
virtual ~Object();
double getX(void);
double getY(void);
double getWidth(void);
double getHeight(void);
void   setRgb(double r, double g, double b);
void   setRgba(double r, double g, double b, double a);
void   setX(double x);
void   setY(double y);
void   incX(double amount);
void   incY(double amount);
void   decX(double amount);
void   decY(double amount);
void randomCoordinates(double width, double height);
void randomColor(void);
void randomTransparency(void);

virtual bool collision(Object& other); // This class checks using bounding box
                                       // Derived classes may check more precisely

virtual void randomSize(double start, double end);

virtual void draw(DrawingContext* dc) = 0;

protected:
    double r;
    double g;
    double b;
    double a;

    double x;
    double y;

    // Bounding Box sizes for rough collision detection.
    // Must be updated in case of rotation or similar.
    double width;
    double height;
};


// Four properties that contain the whole object in the coordinate system
// double x
// double y
// width
// height

// provide virtual method for collision detection. Two objects
// should polymorhically compare if they collide with each other
// based on their coordinate and their internal structure.
// base class implementation will test collision based on rectangle
// information. For precision the polymorphic implementation can
// be used (important for complex objects when another object is close
// to rectangle)

#endif /* _OBJECT_H_ */