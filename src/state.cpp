#include "state.h"

/*
private intialization function
*/
void State::initialize()
{
    position = Vector3<double>();
    velocity = Vector3<double>();
    orientation = Vector3<double>();
    rate = Vector3<double>();
    
    this->_x = this->_y = this->_z = 0;
    this->_roll = this->_pitch = this->_yaw = 0;
    this->_vx = this->_vy = this->_vz = 0;
    this->_wroll = this->_wpitch = this->_wyaw = 0;
}

State::State(bool threeD)
{
    initialize();
    THREE_DIMENSION = threeD;
}

State::State(const State &initial_state)
{
    this->initialize();
    this->THREE_DIMENSION = initial_state.THREE_DIMENSION;
    position        = initial_state.position;
    velocity        = initial_state.position;
    orientation     = initial_state.orientation;
    rate            = initial_state.rate;
    
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

State State::deltaPosition(State * other)
{
    State delta = State(this->THREE_DIMENSION);
    delta.position = other->position - position;
    delta.length = delta.position.mag();

    return delta;
}

State State::deltaSpeed(State * other)
{
    State delta = State(this->THREE_DIMENSION);
    delta.velocity = other->velocity - velocity;
    delta.velocity = delta.velocity.mag();

    return delta;
}

State State::deltaOrientation(State * other)
{
    return State();
}

State State::deltaRate(State * other)
{
    State delta = State(this->THREE_DIMENSION);
    delta.rate = other->rate - rate;
    delta.rate = delta.rate.mag();

    return delta;
}

/*
step

performs one motion step of size timestep
*/
void State::step(double timestep)
{
    position += velocity * timestep;
//    this->_x += this->_vx * timestep;
//    this->_y += this->_vy * timestep;
//    this->_z += this->_vz * timestep;

    orientation += rate * timestep;
//    this->_roll  += this->_wroll * timestep;
//    this->_pitch += this->_wpitch * timestep;
//    this->_yaw   += this->_wyaw * timestep;
    
    // TODO 
    // Add orientation updates
}

//double State::x( double val )
//{ 
//    if (!isnan(val)){ this->_x = val ; }
//    return this->_x; 
//}
//
//
//double State::y( double val )
//{ 
//    if (!isnan(val)){ this->_y = val; }
//    return this->_y; 
//}
//
//
//double State::z( double val )
//{ 
//    if (!isnan(val)){ this->_z = val; }
//    return this->_z; 
//}
//
//
//double State::roll( double val )
//{ 
//    if (!isnan(val)){ this->_roll = val; }
//    return this->_roll; 
//}
//
//
//double State::pitch( double val )
//{ 
//    if (!isnan(val)){ this->_pitch = val; }
//    return this->_pitch; 
//}
//
//
//double State::yaw( double val )
//{ 
//    if (!isnan(val)){ this->_yaw = val; }
//    return this->_yaw; 
//}
//
//
//
//double State::vx( double val )
//{ 
//    if (!isnan(val)){ this->_vx = val; }
//    return this->_vx; 
//}
//
//
//double State::vy( double val )
//{ 
//    if (!isnan(val)){ this->_vy = val; }
//    return this->_vy; 
//}
//
//
//double State::vz( double val )
//{ 
//    if (!isnan(val)){ this->_vz = val; }
//    return this->_vz; 
//}
//
//
//double State::wroll( double val )
//{ 
//    if (!isnan(val)){ this->_wroll = val; }
//    return this->_wroll; 
//}
//
//
//double State::wpitch( double val )
//{ 
//    if (!isnan(val)){ this->_wpitch = val; }
//    return this->_wpitch; 
//}
//
//
//double State::wyaw( double val )
//{ 
//    if (!isnan(val)){ this->_wyaw = val; }
//    return this->_wyaw; 
//}
double State::magnitude(){
    return position.mag();
}

State State::unit()
{
    State u = State(*this);
    u.normalize();
    return u;
}

void State::normalize()
{
    position.scale(1/this->magnitude());
}

void State::scale(double factor)
{
    position.scale(factor);
    velocity.scale(factor);
    orientation.scale(factor);
    rate.scale(factor);
}

void State::print()
{
	std::cout << "Current state" << std::endl;
	std::cout << "---------------" << std::endl;
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Position      | [" 
				<< position.x << ", " 
				<< position.y << ", " 
				<< position.z << "] " << std::endl;
//        State unit = this->unit();
//	std::cout << "Unit          | [" 
//				<< unit._x << ", " 
//				<< unit._y << ", " 
//				<< unit._z << "] " << std::endl;
	std::cout << "Orientation   | ["
		<< orientation.x << ", "
		<< orientation.y << ", "
		<< orientation.z << "] " << std::endl;
	std::cout << "Velocity      | [" 
				<< rate.x << ", " 
				<< rate.y << ", " 
				<< rate.z << "] " << std::endl;
	std::cout << "---------------" << std::endl;
}


