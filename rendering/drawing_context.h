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

#ifndef _DRAWING_CONTEXT_H_
#define _DRAWING_CONTEXT_H_

#include "surface.h"

#include <cairo.h>

typedef enum
{
    ANTI_ALIAS_NONE,
    ANTI_ALIAS_FAST,
    ANTI_ALIAS_BEST,
} anti_alias_t;

typedef enum
{
    SCALING_NONE,
    SCALING_WITH_REFERENCE,
} scaling_t;

class DrawingContext
{
public:
    DrawingContext(Surface* surface, anti_alias_t antiAlias);

    double getScreenWidth();
    double getScreenHeight();

    // Variable surface resolution with the same coordinates as input
    void setReferenceResolution(int width, int height);
    void setScalingMode(scaling_t scalingMode);

    // Configuration
    void setLineWidth(double lineWidth);
    void setSourceRgb(double r, double g, double b);
    void setSourceRgba(double r, double g, double b, double a);

    // Background Color
    void paint(void);
    
    // Line Drawing
    void moveTo(double x, double y);
    void lineTo(double x, double y);
    void closePath();
    void arc(double xc, double yc, double radius, double angle1, double angle2);
    void fill(void);
    void stroke(void);
    
    // Simple Shapes
    void rectangle(double x, double y, double width, double height);

    void clear(void);

private:
    double scale(double value);

    double    width;
    double    height;
    double    refWidth;
    double    refHeight;
    scaling_t scalingMode;
    cairo_t*  cr;
};

#endif /* _DRAWING_CONTEXT_H_ */