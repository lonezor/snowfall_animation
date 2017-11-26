#include "drawing_context.h"
#include <assert.h>

DrawingContext::DrawingContext(Surface* surface, anti_alias_t antiAlias)
{
    this->cr = cairo_create (surface->getCairoSurface());   
    assert(this->cr);

    this->width  = surface->getWidth();
    this->height = surface->getHeight();

    switch(antiAlias)
    {
        case ANTI_ALIAS_NONE:
            cairo_set_antialias(this->cr, CAIRO_ANTIALIAS_NONE);
            break;
        case ANTI_ALIAS_FAST:
            cairo_set_antialias(this->cr, CAIRO_ANTIALIAS_FAST);
            break;
        case ANTI_ALIAS_BEST:
        default:
            cairo_set_antialias(this->cr, CAIRO_ANTIALIAS_BEST);
            break;
    }

    this->refWidth  = 1920;
    this->refHeight = 1080;
    this->scalingMode = SCALING_WITH_REFERENCE;
}

void DrawingContext::setReferenceResolution(int width, int height)
{
    this->refWidth  = (double)width;
    this->refHeight = (double)height;
}

void DrawingContext::setScalingMode(scaling_t scalingMode)
{
    this->scalingMode = scalingMode;
}

double DrawingContext::scale(double value)
{
    if (this->scalingMode == SCALING_NONE) return value;
    
    // When scaling between resolutions with the same aspect ratio
    // width and height have the same proportions against the
    // reference. Width used for the calculation.
    double multiplier = this->width / this->refWidth;
    return value * multiplier;
}

void DrawingContext::setLineWidth(double lineWidth)
{
    cairo_set_line_width (this->cr, scale(lineWidth));
}

void DrawingContext::setSourceRgb(double r, double g, double b)
{
    cairo_set_source_rgb(this->cr, r, g, b);
}

void DrawingContext::setSourceRgba(double r, double g, double b, double a)
{
    cairo_set_source_rgba(this->cr, r, g, b, a);
}

void DrawingContext::paint(void)
{
    cairo_paint(this->cr);
}

void DrawingContext::clear(void)
{
    cairo_set_source_rgb(this->cr, 0, 0, 0);
    cairo_paint(this->cr);
}

void DrawingContext::moveTo(double x, double y)
{
    cairo_move_to(this->cr, scale(x), scale(y));
}

void DrawingContext::lineTo(double x, double y)
{
    cairo_line_to(this->cr, scale(x), scale(y));
}

void DrawingContext::closePath()
{
    cairo_close_path(this->cr);
}

void DrawingContext::arc(double xc, double yc, double radius, double angle1, double angle2)
{
    cairo_arc(this->cr, scale(xc), scale(yc), scale(radius), angle1, angle2);
}

void DrawingContext::stroke()
{
    cairo_stroke(this->cr);
}

void DrawingContext::fill()
{
    cairo_fill(this->cr);
}


void DrawingContext::rectangle(double x, double y, double width, double height)
{
    cairo_rectangle(this->cr, scale(x), scale(y), scale(width), scale(height));
}

