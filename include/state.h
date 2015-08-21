#ifndef PF_STATE
#define PF_STATE

#include <iostream>
#include <iomanip>
#include <math.h>

#include "vector3.h"

class State
{
    bool	THREE_DIMENSION;

    
    double 	 _x,  _y,  _z,  _roll,  _pitch,  _yaw;
    //  translation and rotation motion
    double	_vx, _vy, _vz, _wroll, _wpitch, _wyaw;

    void initialize();

public:
    
    // State values
    //  position and orienation
    Vector3<double> position;
    Vector3<double> velocity;
    Vector3<double> orientation;
    Vector3<double> rate;
    
    // deltas when calculated
    double	length, angle, speed;
    State(bool threeD = true);
    State(const State &initial_state);
    ~State() {};

    State deltaPosition(State * other);
    State deltaSpeed(State * other);
    State deltaOrientation(State * other);
    State deltaRate(State * other);

    void step(double timestep = 1.0);


    double x(double _x = NAN);
    double y(double _y = NAN);
    double z(double _z = NAN);
    double roll(double _roll = NAN);
    double pitch(double _pitch = NAN);
    double yaw(double _yaw = NAN);

    double vx(double _vx = NAN);
    double vy(double _vy = NAN);
    double vz(double _vz = NAN);
    double wroll(double _wroll = NAN);
    double wpitch(double _wpitch = NAN);
    double wyaw(double _wyaw = NAN);

    State unit();
    double magnitude();
    
    void normalize();
    
    void scale(double factor);
    void scalePosition(double factor);
    void scaleVelocity(double factor);
    void scaleRate(double factor);
    
    void print();
        
};

#endif