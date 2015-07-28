#include "state.h"

/*
private intialization function
*/
void State::initialize()
{
	this->x = this->y = this->z = 0;
	this->roll = this->pitch = this->yaw = 0;
	this->vx = this->vy = this->vz = 0;
	this->wroll = this->wpitch = this->wyaw = 0;
}

State::State()
{
	this->initialize();
	this->THREE_DIMENSION = true;
}

State::State(bool threeD)
{
	this->initialize();
	this->THREE_DIMENSION = threeD;
}

State::State(const State &initial_state)
{
	this->initialize();
	this->THREE_DIMENSION = initial_state.THREE_DIMENSION;
	this->x = initial_state.x;
	this->y = initial_state.y;
	this->z = initial_state.z;
	this->roll	= initial_state.roll;
	this->pitch = initial_state.pitch;
	this->yaw = initial_state.yaw;
	this->vx = initial_state.vx;
	this->vy = initial_state.vy;
	this->vz = initial_state.vz;
	this->wroll = initial_state.wroll;
	this->wpitch = initial_state.wpitch;
	this->wyaw = initial_state.wyaw;
}

State State::lengthTo(State toState)
{
	State delta = State(this->THREE_DIMENSION);
	delta.x = toState.x - this->x;
	delta.y = toState.y - this->y;
	delta.z = (THREE_DIMENSION) ? toState.z - this->z : 0;

	delta.length = pow(pow(delta.x, 2) + pow(delta.y, 2) + pow(delta.z, 2), 0.5);

	return delta;
}

State State::lengthFrom(State fromState)
{
	return fromState.lengthTo(*this);
}


State State::speedTo(State toState)
{
	State delta = State(this->THREE_DIMENSION);
	delta.vx = toState.vx - this->vx;
	delta.vy = toState.vy - this->vy;
	delta.vz = (THREE_DIMENSION) ? toState.vz - this->vz : 0;

	delta.speed = pow(pow(delta.vx, 2) + pow(delta.vy, 2) + pow(delta.vz, 2), 0.5);

	return delta;
}

State State::speedFrom(State fromState)
{
	return fromState.speedTo(*this);
}


State State::rateTo(State toState)
{
	State delta = State(this->THREE_DIMENSION);
	delta.wroll = toState.wroll - this->wroll;
	delta.wpitch = toState.wpitch - this->wpitch;
	delta.wyaw = (THREE_DIMENSION) ? toState.wyaw - this->wyaw : 0;

	delta.rate = 0;

	return delta;
}

State State::rateFrom(State fromState)
{
	return fromState.rateTo(*this);
}

/*
step

performs one motion step of size timestep
*/
void State::step(double timestep = 1)
{
	this->x += this->vx * timestep;
	this->y += this->vy * timestep;
	this->z += this->vz * timestep;

	this->roll	+= this->wroll * timestep;
	this->pitch += this->wpitch * timestep;
	this->yaw	+= this->wyaw * timestep;
}

void State::print()
{
	std::cout << "Current state" << std::endl;
	std::cout << "---------------" << std::endl;
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Position      | [" 
				<< this->x << ", " 
				<< this->y << ", " 
				<< this->z << "] " << std::endl;
	std::cout << "Orientation   | ["
		<< this->roll << ", "
		<< this->pitch << ", "
		<< this->yaw << "] " << std::endl;
	std::cout << "---------------" << std::endl;
}


