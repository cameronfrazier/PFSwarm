#include "state.h"

/*
private intialization function
*/
void State::initialize()
{
	this->_x = this->_y = this->_z = 0;
	this->_roll = this->_pitch = this->_yaw = 0;
	this->_vx = this->_vy = this->_vz = 0;
	this->_wroll = this->_wpitch = this->_wyaw = 0;
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
    this->_x        = initial_state._x;
    this->_y        = initial_state._y;
    this->_z        = initial_state._z;
    this->_roll     = initial_state._roll;
    this->_pitch    = initial_state._pitch;
    this->_yaw      = initial_state._yaw;
    this->_vx       = initial_state._vx;
    this->_vy       = initial_state._vy;
    this->_vz       = initial_state._vz;
    this->_wroll    = initial_state._wroll;
    this->_wpitch   = initial_state._wpitch;
    this->_wyaw     = initial_state._wyaw;
}

State State::lengthTo(State * toState)
{
	State delta = State(this->THREE_DIMENSION);
	delta._x = toState->_x - this->_x;
	delta._y = toState->_y - this->_y;
	delta._z = (THREE_DIMENSION) ? toState->_z - this->_z : 0;

	delta.length = pow(pow(delta._x, 2) + pow(delta._y, 2) + pow(delta._z, 2), 0.5);

	return delta;
}

State State::lengthFrom(State * fromState)
{
	return fromState->lengthTo(this);
}


State State::speedTo(State * toState)
{
	State delta = State(this->THREE_DIMENSION);
	delta._vx = toState->_vx - this->_vx;
	delta._vy = toState->_vy - this->_vy;
	delta._vz = (THREE_DIMENSION) ? toState->_vz - this->_vz : 0;

	delta.speed = pow(pow(delta._vx, 2) + pow(delta._vy, 2) + pow(delta._vz, 2), 0.5);

	return delta;
}

State State::speedFrom(State * fromState)
{
	return fromState->speedTo(this);
}


State State::rateTo(State * toState)
{
    State delta = State(this->THREE_DIMENSION);
    delta._wroll = toState->_wroll - this->_wroll;
    delta._wpitch = toState->_wpitch - this->_wpitch;
    delta._wyaw = (THREE_DIMENSION) ? toState->_wyaw - this->_wyaw : 0;

    delta.rate = 0;

    return delta;
}

State State::rateFrom(State * fromState)
{
    return fromState->rateTo(this);
}

/*
step

performs one motion step of size timestep
*/
void State::step(double timestep)
{
    this->_x += this->_vx * timestep;
    this->_y += this->_vy * timestep;
    this->_z += this->_vz * timestep;

    this->_roll  += this->_wroll * timestep;
    this->_pitch += this->_wpitch * timestep;
    this->_yaw   += this->_wyaw * timestep;
    
    // TODO 
    // Add orientation updates
}

double State::x( double val ){ 
    if (!isnan(val)){ this->_x = val ; }
    return this->_x; 
}


double State::y( double val ){ 
    if (!isnan(val)){ this->_y = val; }
    return this->_y; 
}


double State::z( double val ){ 
    if (!isnan(val)){ this->_z = val; }
    return this->_z; 
}


double State::roll( double val ){ 
    if (!isnan(val)){ this->_roll = val; }
    return this->_roll; 
}


double State::pitch( double val ){ 
    if (!isnan(val)){ this->_pitch = val; }
    return this->_pitch; 
}


double State::yaw( double val ){ 
    if (!isnan(val)){ this->_yaw = val; }
    return this->_yaw; 
}



double State::vx( double val ){ 
    if (!isnan(val)){ this->_vx = val; }
    return this->_vx; 
}


double State::vy( double val ){ 
    if (!isnan(val)){ this->_vy = val; }
    return this->_vy; 
}


double State::vz( double val ){ 
    if (!isnan(val)){ this->_vz = val; }
    return this->_vz; 
}


double State::wroll( double val ){ 
    if (!isnan(val)){ this->_wroll = val; }
    return this->_wroll; 
}


double State::wpitch( double val ){ 
    if (!isnan(val)){ this->_wpitch = val; }
    return this->_wpitch; 
}


double State::wyaw( double val ){ 
    if (!isnan(val)){ this->_wyaw = val; }
    return this->_wyaw; 
}
double State::magnitude(){
    return pow(pow(this->_x, 2) + pow(this->_y, 2) + pow(this->_z, 2), 0.5);
}

State State::unit(){
    State u = State(*this);
    u.x(u.x()/u.magnitude());
    u.y(u.y()/u.magnitude());
    u.z(u.z()/u.magnitude());
    return u;
}

void State::print()
{
	std::cout << "Current state" << std::endl;
	std::cout << "---------------" << std::endl;
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Position      | [" 
				<< this->_x << ", " 
				<< this->_y << ", " 
				<< this->_z << "] " << std::endl;
//        State unit = this->unit();
//	std::cout << "Unit          | [" 
//				<< unit._x << ", " 
//				<< unit._y << ", " 
//				<< unit._z << "] " << std::endl;
	std::cout << "Orientation   | ["
		<< this->_roll << ", "
		<< this->_pitch << ", "
		<< this->_yaw << "] " << std::endl;
	std::cout << "---------------" << std::endl;
}


