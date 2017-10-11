#include "object.h"

#include <stdlib.h>

Object::~Object()
{
    
}

double Object::getX()
{
    return this->x;
}

double Object::getY()
{
    return this->y;
}

double Object::getWidth()
{
    return this->width;
}

double Object::getHeight()
{
    return this->height;
}

void Object::setRgb(double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}
void Object::setRgba(double r, double g, double b, double a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

bool Object::collision(Object& other)
{
    return 0;
}

void Object::randomCoordinates(double width, double height)
{
    double rx = drand48();
    double ry = drand48();
    rx *= width;
    ry *= height;

    this->x = rx;
    this->y = ry;
}

void Object::randomSize(double start, double end)
{
   



}

void Object::randomColor()
{

}

void Object::randomTransparency()
{

}

void Object::draw(DrawingContext* dc)
{

}
