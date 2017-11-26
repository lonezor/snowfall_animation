#ifndef _ANIMATED_OBJECT_H_
#define _ANIMATED_OBJECT_H_

#include "drawing_context.h"

class AnimatedObject // Defines how a object is animated in time
{
public:
    virtual ~AnimatedObject() {};

    virtual void drawNextFrame(DrawingContext* dc) = 0;

};

#endif /* _ANIMATED_OBJECT_H_ */