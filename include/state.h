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
	double 	 x,  y,  z,  roll,  pitch,  yaw;
	//  translation and rotation motion
	double	vx, vy, vz, wroll, wpitch, wyaw;

	// deltas when calculated
	double	length, angle, speed, rate;

	void initialize();

public:
	State();
	explicit State(bool threeD);
	State(const State &initial_state);
	~State() {};

	State lengthTo(State toState);
	State lengthFrom(State fromState);

	State speedTo(State toState);
	State speedFrom(State fromState);

	State rateTo(State toState);
	State rateFrom(State fromState);

	void step(double timestep);

	void print();
};

#endif