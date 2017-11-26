#include "circle.h"

#include <stdlib.h>

const double PI = 3.14159265359;

Circle::Circle(double x, double y, double radius)
{
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->width  = radius;
    this->height = radius;
    this->r = 1;
    this->g = 1;
    this->b = 1;
}

void Circle::setFilled(bool flag)
{
    this->filled = flag;
}

void Circle::randomSize(double start, double end) // Implements Object::randomSize()
{
    double r     = drand48();
    double range = end - start;

    r = start + (r*range);

    this->radius = r;
    this->width  = r;
    this->height = r;
}

void Circle::draw(DrawingContext* dc) // Implements Object::draw()
{
    dc->setSourceRgb(this->r, this->g, this->b);
    dc->arc(this->x, this->y, this->radius, 0, 2 * PI);
    if (this->filled) dc->fill();
    else              dc->stroke();
}