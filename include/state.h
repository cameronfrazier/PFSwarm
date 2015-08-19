#ifndef PF_STATE
#define PF_STATE

#include <iostream>
#include <iomanip>
#include <math.h>

class State
{
private:
    bool	THREE_DIMENSION;

    // State values
    //  position and orienation
    double 	 _x,  _y,  _z,  _roll,  _pitch,  _yaw;
    //  translation and rotation motion
    double	_vx, _vy, _vz, _wroll, _wpitch, _wyaw;

    void initialize();

public:
    // deltas when calculated
    double	length, angle, speed, rate;

    State();
    explicit State(bool threeD);
    State(const State &initial_state);
    ~State() {};

    State lengthTo(State * toState);
    State lengthFrom(State * fromState);

    State speedTo(State * toState);
    State speedFrom(State * fromState);

    State rateTo(State * toState);
    State rateFrom(State * fromState);

    void step(double timestep = 1.0);

    State unit();
    double magnitude();

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

    void print();
        
};

#endif