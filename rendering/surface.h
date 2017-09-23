#ifndef _SURFACE_H_
#define _SURFACE_H_

#include <stdint.h>
#include <cairo.h>

class Surface
{
public:
    virtual ~Surface();

    virtual cairo_surface_t* getCairoSurface(void) = 0;
    
    int getWidth(void);
    int getHeight(void);

protected:
    int              width;
    int              height;
    cairo_surface_t* cairoSurface;
};

#endif /* _SURFACE_H_ */