#ifndef _SNOWFLAKE_H_
#define _SNOWFLAKE_H_

#include "animated_object.h"
#include "circle.h"

class Snowflake : AnimatedObject // At the moment, a snowflake is an animated circle
{
public:
    Snowflake(DrawingContext* dc);

    bool onScreen();
    void drawNextFrame();

private:
    double xVelocity; // Wind and air turbulence
    double yVelocity; // Gravity and air resistance
    double size;      // Diameter
    double xDiff;     // Horizontal randomness
    Circle* object;
    DrawingContext* dc;
};




#endif /* _SNOWFLAKE_H_ */