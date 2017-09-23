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

