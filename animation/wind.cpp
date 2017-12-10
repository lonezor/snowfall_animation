/*
 *  Snowfall Animation
 *  Copyright (C) 2017 Johan Norberg <lonezor@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>
 */

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

                // Change wind direction.
                if (drand48() < 0.5) this->direction *= -1;

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
                if (this->yDiff < 0) this->yDiff *= -1;
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
                if (this->yDiff < 0) this->yDiff *= -1;
            }
            break;
        default:
            break;
    }
}

