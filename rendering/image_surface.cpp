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

#include "image_surface.h"

#include <assert.h>
#include <stdio.h>


ImageSurface::ImageSurface(int width, int height)
{
    this->width = width;
    this->height = height;

    this->cairoSurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    assert(this->cairoSurface);
}

cairo_surface_t* ImageSurface::getCairoSurface(void)
{
    return this->cairoSurface;
}

void ImageSurface::writePngFile(const char* path)
{
    cairo_surface_write_to_png(this->cairoSurface, path);
}

