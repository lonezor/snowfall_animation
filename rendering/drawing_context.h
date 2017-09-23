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

class DrawingContext
{
public:
    DrawingContext(Surface* surface, anti_alias_t antiAlias);

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

private:
    int width;
    int height;

    cairo_t* cr;
};

#endif /* _DRAWING_CONTEXT_H_ */