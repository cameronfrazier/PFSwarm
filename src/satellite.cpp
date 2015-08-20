#include "satellite.h"

/*
 Constructor, accepts a satellite ID and an optionsal initial State
 */
Satellite::Satellite(int satID, SwarmSettings * settings)
{
    this->_id = satID;
    this->_settings = settings;
}

Satellite::Satellite(int satID, SwarmSettings * settings, State initial_state)
{
    this->_id = satID;
    this->_settings = settings;
    this->_state = initial_state;
}

int Satellite::getID()
{ 
    return this->_id;
}

State Satellite::getState(){
    return this->_state;
}


/*
 Add a neighbouring satellite to be considered during force calculation
 */
void Satellite::addNeighbour(Satellite * satellite)
{
	this->_neighbours.push_back(satellite);
}

void Satellite::removeNeighbour(int index)
{
	this->_neighbours.erase(this->_neighbours.begin() + index);
}

void Satellite::clearNeighbours()
{
	this->_neighbours.clear();
}


double Satellite::rangeToTarget(Satellite * target){
    State target_state = target->getState();
    State delta = this->_state.lengthFrom(&target_state);
    return delta.magnitude();
}

void Satellite::addPSP(PSP * psp)
{
	this->_psps.push_back(psp);
}

void Satellite::removePSP(int index)
{
	this->_psps.erase(this->_psps.begin() + index);
}

void Satellite::applyForce(State force){
    double dt = this->_settings->simulationTimestep();
    double m = this->_settings->satelliteMass();
    double accelx = force.x()/m;
    double accely = force.y()/m;
    double accelz = force.z()/m;
    this->_state.vx( this->_state.vx() + accelx*dt );
    this->_state.vy( this->_state.vy() + accely*dt );
    this->_state.vz( this->_state.vz() + accelz*dt );
}

void Satellite::step(){this->step(1.0);}
void Satellite::step(double timestep){
    this->_state.step(timestep);
}
 

State Satellite::forceRepulsive(Satellite * target){
    State stateT = target->getState();    
    State delta = this->_state.lengthFrom(&stateT);

    State unit = delta.unit();

    double tSpacing = this->_settings->simulationTargetSpacing();    
    double force = pow(tSpacing,2)*pow(delta.magnitude(),-2);

    unit.x(unit.x()*force);
    unit.y(unit.y()*force);
    unit.z(unit.z()*force);
    
    return unit;
}


State Satellite::forceAttractive(Satellite * target){ return State(); };
State Satellite::forceDrag(){ return State(); };
State Satellite::forceGravity(State * gravity){ return State(); };




void Satellite::print()
{
    std::cout << "Satellite ID:" << this->_id << std::endl;
    this->_state.print();
}
