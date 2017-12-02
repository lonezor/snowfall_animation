#include "wind.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>

Wind::Wind(double minIdleTime,         double maxIdleTime,     double minAccelerationTime,
           double maxAccelerationTime, double minStrength,     double maxStrength,
           double minDurationTime,     double maxDurationTime, double minDeaccelerationTime, 
           double maxDeaccelerationTime)
{
    // Value domains
    this->minIdleTime           = minIdleTime;
    this->maxIdleTime           = maxIdleTime;
    this->minAccelerationTime   = minAccelerationTime;
    this->maxAccelerationTime   = maxAccelerationTime;
    this->minStrength           = minStrength;
    this->maxStrength           = maxStrength;
    this->minDurationTime       = minDurationTime;
    this->maxDurationTime       = maxDurationTime;
    this->minDeaccelerationTime = minDeaccelerationTime;
    this->maxDeaccelerationTime = maxDeaccelerationTime;

    // Config
    this->idleTime           = 2;
    this->accelerationTime   = 0;
    this->duration           = 0;
    this->deaccelerationTime = 0;
    this->strength           = 0;
    
    // State
    this->state = WIND_STATE_IDLE;
    this->elapsedIdleTime           = 0;
    this->elapsedAccelerationTime   = 0;
    this->elapsedDeaccelerationTime = 0;
    this->elapsedDuration           = 0;
    this->xDiff                     = 0;
    this->yDiff                     = 0;
    this->direction                 = 1;
}

double Wind::getXDiff()
{
    return this->xDiff;
}

double Wind::getYDiff()
{
    return this->yDiff;
}

void Wind::nextFrame()
{
    switch(this->state)
    {
        case WIND_STATE_IDLE:
            this->elapsedIdleTime += FRAME_TIME;

            if (this->elapsedIdleTime > this->idleTime)
            {
                // Reset state
                this->elapsedIdleTime           = 0;
                this->elapsedAccelerationTime   = 0;
                this->elapsedDeaccelerationTime = 0;
                this->elapsedDuration           = 0;
                this->xDiff                     = 0;
                this->yDiff                     = 0;
                this->direction                 = 1;

                // Change wind direction. Most comonly to the right
                if (drand48() < 0.4) this->direction *= -1;

                // Generate new config
                this->idleTime           = this->minIdleTime           + (drand48()*(this->maxIdleTime           - this->minIdleTime));
                this->accelerationTime   = this->minAccelerationTime   + (drand48()*(this->maxAccelerationTime   - this->minAccelerationTime));
                this->strength           = this->minStrength           + (drand48()*(this->maxStrength           - this->minStrength));
                this->duration           = this->minDurationTime       + (drand48()*(this->maxDurationTime       - this->minDurationTime));
                this->deaccelerationTime = this->minDeaccelerationTime + (drand48()*(this->maxDeaccelerationTime - this->minDeaccelerationTime));

                this->elapsedIdleTime = 0; // Reset for the re-entry into idle state
                this->state           = WIND_STATE_ACCELERATION;
                printf("WIND_STATE_ACCELERATION\n");
            }
            break;
        case WIND_STATE_ACCELERATION:
            this->elapsedAccelerationTime += FRAME_TIME;

            if (this->elapsedAccelerationTime > this->accelerationTime)
            {
                this->state = WIND_STATE_FULL_STRENGTH;
                printf("WIND_STATE_FULL_STRENGTH\n");
            }
            else
            {
                this->xDiff = (this->elapsedAccelerationTime / this->accelerationTime) * this->strength;
                this->xDiff *= this->direction;
                this->yDiff = this->xDiff / 2;
            }
            break;
        case WIND_STATE_FULL_STRENGTH:
            this->elapsedDuration += FRAME_TIME;

            if (this->elapsedDuration > this->duration)
            {
                this->state = WIND_STATE_DEACCELERATION;
                printf("WIND_STATE_DEACCELERATION\n");
            }
            break;
        case WIND_STATE_DEACCELERATION:
            this->elapsedDeaccelerationTime += FRAME_TIME;

            if (this->elapsedDeaccelerationTime > this->deaccelerationTime)
            {
                this->state = WIND_STATE_IDLE;
                printf("WIND_STATE_IDLE\n");
            }
            else
            {
                this->xDiff = (1-(this->elapsedDeaccelerationTime / this->deaccelerationTime)) * this->strength;
                this->xDiff *= this->direction;
                this->yDiff = this->xDiff / 2;
            }
            break;
        default:
            break;
    }
}

