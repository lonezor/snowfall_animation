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

#ifndef _IMAGE_SURFACE_H_
#define _IMAGE_SURFACE_H_

#include "surface.h"

#include <stdint.h>
#include <cairo.h>

class ImageSurface : public Surface
{
public:
    ImageSurface(int width, int height);

    cairo_surface_t* getCairoSurface(void);
    void             writePngFile(const char* path);

private:
};

#endif /* _IMAGE_SURFACE_H_ */