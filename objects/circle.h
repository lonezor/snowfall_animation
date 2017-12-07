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

#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "object.h"

class Circle : public Object
{
public:
    Circle(double x, double y, double radius);

    void setFilled(bool flag);

    void randomSize(double start, double end);

    void randomAlpha(double start, double end);

    void draw(DrawingContext* dc);

private:
    double radius;
    bool   filled;
    bool   rAlphaRequested;
    double rAlphaValue;

};

#endif /* _CIRCLE_H_ */