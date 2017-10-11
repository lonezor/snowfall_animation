#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "drawing_context.h"

class Object
{
public:
virtual ~Object();
double getX(void);
double getY(void);
double getWidth(void);
double getHeight(void);
void   setRgb(double r, double g, double b);
void   setRgba(double r, double g, double b, double a);
void randomCoordinates(double width, double height);
void randomColor(void);
void randomTransparency(void);

virtual bool collision(Object& other); // This class checks using bounding box
                                       // Derived classes may check more precisely

virtual void randomSize(double start, double end);

virtual void draw(DrawingContext* dc);

protected:
    double r;
    double g;
    double b;
    double a;

    double x;
    double y;

    // Bounding Box sizes for rough collision detection.
    // Must be updated in case of rotation or similar.
    double width;
    double height;
};


// Four properties that contain the whole object in the coordinate system
// double x
// double y
// width
// height

// provide virtual method for collision detection. Two objects
// should polymorhically compare if they collide with each other
// based on their coordinate and their internal structure.
// base class implementation will test collision based on rectangle
// information. For precision the polymorphic implementation can
// be used (important for complex objects when another object is close
// to rectangle)

#endif /* _OBJECT_H_ */