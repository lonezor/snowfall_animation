#ifndef _IMAGE_SURFACE_H_
#define _IMAGE_SURFACE_H_

#include "surface.h"

#include <stdint.h>
#include <cairo.h>

class ImageSurface : Surface
{
public:
    ImageSurface(int width, int height);

    cairo_surface_t* getCairoSurface(void);
    void             writePngFile(const char* path);

private:
};

#endif /* _IMAGE_SURFACE_H_ */