#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "object.h"

class Circle : public Object
{
public:
    Circle(double x, double y, double radius);

    void setFilled(bool flag);

    void randomSize(double start, double end);

    void draw(DrawingContext* dc);

private:
    double radius;
    bool filled;

};

#endif /* _CIRCLE_H_ */