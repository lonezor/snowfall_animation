#ifndef _WIND_H_
#define _WIND_H_

typedef enum
{
    WIND_STATE_UNKNOWN,
    WIND_STATE_IDLE,
    WIND_STATE_ACCELERATION,
    WIND_STATE_FULL_STRENGTH,
    WIND_STATE_DEACCELERATION,
} windState_t;

#define DEFAULT_MIN_IDLE_TIME           (5)
#define DEFAULT_MAX_IDLE_TIME           (10.0)
#define DEFAULT_MIN_ACCELERATION_TIME   (0.2)
#define DEFAULT_MAX_ACCELERATION_TIME   (0.7)
#define DEFAULT_MIN_STRENGTH            (0.020)
#define DEFAULT_MAX_STRENGTH            (0.070)
#define DEFAULT_MIN_DURATION_TIME       (0.1)
#define DEFAULT_MAX_DURATION_TIME       (0.5)
#define DEFAULT_MIN_DEACCELERATION_TIME (0.2)
#define DEFAULT_MAX_DEACCELERATION_TIME (0.7)

class Wind
{
public:
    Wind(double minIdleTime,         double maxIdleTime,     double minAccelerationTime,
         double maxAccelerationTime, double minStrength,     double maxStrength, 
         double minDurationTime,     double maxDurationTime, double minDeaccelerationTime,
         double maxDeAccelerationTime);

    // Query functions used by animated objects
    double getXDiff(void); // Horizontal diff
    double getYDiff(void); // Vertical diff (mostly downwards but possible with upward direction with strong wind)

    // Tick function
    void nextFrame(void); // Starts with idle period

private:
    // Value domains
    double minIdleTime;
    double maxIdleTime;
    double minAccelerationTime;
    double maxAccelerationTime;
    double minStrength;
    double maxStrength;
    double minDurationTime;
    double maxDurationTime;
    double minDeaccelerationTime;
    double maxDeaccelerationTime;

    // Config
    double      idleTime;
    double      accelerationTime;
    double      duration;
    double      deaccelerationTime;
    double      strength;
    
    // State
    windState_t state;
    double      elapsedIdleTime;
    double      elapsedAccelerationTime;
    double      elapsedDeaccelerationTime;
    double      elapsedDuration;
    double      xDiff;
    double      yDiff;
    double      direction;
};

#endif /* _WIND_H_ */