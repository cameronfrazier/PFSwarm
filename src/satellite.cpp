#include "satellite.h"

/*
 Constructor, accepts a satellite ID and an optionsal initial State
 */
Satellite::Satellite(int satID, SwarmSettings * settings, std::vector<Satellite*> * swarm)
{
    this->_id = satID;
    this->_settings = settings;
    this->_swarm = swarm;
}

Satellite::Satellite(int satID, SwarmSettings * settings, std::vector<Satellite*> * swarm, State initial_state)
{
    this->_id = satID;
    this->_settings = settings;
    this->_swarm = swarm;
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

void Satellite::step(double timestep){
    this->_state.step(timestep);
}

void Satellite::findNeighbours(){
    double rangeLimit = 0;
    unsigned int neighbourCount = this->_settings->satelliteNeighbourhoodSize();
    bool isNeighbourhoodFull;
    
    double range;
    double rangeTmp;
    
    this->_neighbours.clear();
    
    std::cout << "Finding Neighbours!!" << std::endl;
    for(auto &sat : *this->_swarm){
        
        // Ignore ourselves
        if(sat->getID() == this->getID()) continue;
        
        isNeighbourhoodFull = (this->_neighbours.size() >= neighbourCount);
        range = this->rangeToTarget(sat);
        
        if( isNeighbourhoodFull) {
            if(range > rangeLimit) continue; 
        }
        else {
            // Expand to accept considered satellites
            if (range > rangeLimit) 
                rangeLimit = range;
        }
        
        if( this->_neighbours.size() == 0 ){
            this->_neighbours.push_back(sat);
        } else {
            // Loop over current neighbours and insert where appropriate
            for( unsigned int idx = this->_neighbours.size(); idx > 0; idx-- ){
                rangeTmp = this->rangeToTarget(this->_neighbours[idx-1]);
                if(range > rangeTmp ){            
                    this->_neighbours.insert(this->_neighbours.begin()+idx, sat);
                    break;              
                } else if (idx == 1) {            
                    this->_neighbours.insert(this->_neighbours.begin(), sat);
                    break; 
                } 
            }
        }
        
        if (this->_neighbours.size() > neighbourCount){
            rangeLimit = this->rangeToTarget((this->_neighbours[neighbourCount-1]));
        }
    }
    this->_neighbours.resize(neighbourCount);
}

void Satellite::calculateForces(){
    this->findNeighbours();
    this->print();
    State fObs = this->forceRepulsive();
    std::cout << "\tNet repulsive force: " << fObs.magnitude() << std::endl;
}

State Satellite::forceRepulsive(Satellite * sat){
    double force;
    double tSpacing = this->_settings->simulationTargetSpacing();
    State stateT, delta, unit;   
    
        stateT = sat->getState();    
        delta = this->_state.lengthFrom(&stateT);

        unit = delta.unit();
    
        force = pow(tSpacing,2)*pow(delta.magnitude(),-2);

        unit.x(unit.x()*force);
        unit.y(unit.y()*force);
        unit.z(unit.z()*force);
    
    return unit;
}
State Satellite::forceRepulsive(){
    double force;
    double tSpacing = this->_settings->simulationTargetSpacing();
    State stateT, delta, unit;
    State net = State();
    
    for( auto &sat : this->_neighbours){
        stateT = sat->getState();    
        delta = this->_state.lengthFrom(&stateT);

        unit = delta.unit();
    
        force = pow(tSpacing,2)*pow(delta.magnitude(),-2);

        net.x(net.x() + unit.x()*force);
        net.y(net.y() + unit.y()*force);
        net.z(net.z() + unit.z()*force);
    }
    
    return net;
}


State Satellite::forceAttractive(){ return State(); };
State Satellite::forceDrag(){ return State(); };
State Satellite::forceGravity(State * gravity){ return State(); };




void Satellite::print()
{
    std::cout << "Satellite ID:" << this->_id << " - " << this->_neighbours.size() << " neighbours " << std::endl;
    for(auto &sat: this->_neighbours)
        std::cout << "\t" << sat->getID() << "\t" << this->rangeToTarget(sat) << std::endl;
//    this->_state.print();
}
