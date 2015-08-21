#include "satellite.h"

/*
 Constructor, accepts a satellite ID and an optionsal initial State
 */
Satellite::Satellite(int satID, 
        SwarmSettings * settings, 
        State * gravity, 
        std::vector<Satellite*> * swarm, 
        State initial_state)
{
    this->_id = satID;
    this->_settings = settings;
    this->_gravity = gravity;
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
    State delta = this->_state.deltaPosition(&target_state);
    return delta.length;
}

void Satellite::addPSP(PSP * psp)
{
	this->_psps.push_back(psp);
}

void Satellite::removePSP(int index)
{
	this->_psps.erase(this->_psps.begin() + index);
}

void Satellite::applyForce(State force)
{    
    double dt = _settings->simulationTimestep();
    double m = _settings->satelliteMass();
    force.position /= m;
//    double accelx = force.x()/m;
//    double accely = force.y()/m;
//    double accelz = force.z()/m;
    _state.velocity += force.position*dt;
//    this->_state.vx( this->_state.vx() + accelx*dt );
//    this->_state.vy( this->_state.vy() + accely*dt );
//    this->_state.vz( this->_state.vz() + accelz*dt );
}

void Satellite::step(double timestep)
{
    this->_state.step(timestep);
}

void Satellite::findNeighbours()
{
    double rangeLimit = 0;
    unsigned int neighbourCount = _settings->satelliteNeighbourhoodSize();
    bool isNeighbourhoodFull;
    
    double range;
    double rangeTmp;
    
    _neighbours.clear();
    
//    std::cout << "Finding Neighbours!!" << std::endl;
    for(auto &sat : *_swarm){
        
        // Ignore ourselves
        if(sat->getID() == getID()) continue;
        
        isNeighbourhoodFull = (_neighbours.size() >= neighbourCount);
        range = rangeToTarget(sat);
        
        if( isNeighbourhoodFull) {
            if(range > rangeLimit) continue; 
        }
        else {
            // Expand to accept considered satellites
            if (range > rangeLimit) 
                rangeLimit = range;
        }
        
        if( _neighbours.size() == 0 ){
            _neighbours.push_back(sat);
        } else {
            // Loop over current neighbours and insert where appropriate
            for( unsigned int idx = _neighbours.size(); idx > 0; idx-- ){
                rangeTmp = rangeToTarget(_neighbours[idx-1]);
                if(range > rangeTmp ){            
                    _neighbours.insert(_neighbours.begin()+idx, sat);
                    break;              
                } else if (idx == 1) {            
                    _neighbours.insert(_neighbours.begin(), sat);
                    break; 
                } 
            }
        }
//        std::cout << "Checking Neighbours size!!" << std::endl;
        if (_neighbours.size() > neighbourCount){
            rangeLimit = rangeToTarget((_neighbours[neighbourCount-1]));
            _neighbours.resize(neighbourCount);
        }
    }
}

void Satellite::calculateForces()
{
    fObs = forceRepulsive();
    fAtt = forceAttractive();
    fDrg = forceDrag();
    fGrv = forceGravity(_gravity);
    
//    std::cout << "\tfObs: " << fObs.magnitude() << std::endl;
//    std::cout << "\tfAtt: " << fAtt.magnitude() << std::endl;
//    std::cout << "\tfDrg: " << fDrg.magnitude() << std::endl;
//    std::cout << "\tfGrv: " << fGrv.magnitude() << std::endl;
    
    State net = State();

    net.position = fObs.position + fAtt.position + fDrg.position + fGrv.position; 
    
//    net.x( this->fObs.x() + this->fAtt.x() + this->fDrg.x() + this->fGrv.x() );
//    net.y( this->fObs.y() + this->fAtt.y() + this->fDrg.y() + this->fGrv.y() );
//    net.z( this->fObs.z() + this->fAtt.z() + this->fDrg.z() + this->fGrv.z() );
    
//    if(net.magnitude() > this->_settings->satelliteForceLimit()){
//        net = net.unit();
//    }
//    
    this->applyForce(net);
//    std::cout << "\tNet repulsive force: " << net.magnitude() << std::endl;
}

State Satellite::forceRepulsive(Satellite * sat){
    double force;
    double tSpacing = this->_settings->simulationTargetSpacing();
    double gain = this->_settings->forceGainRepulsive();
    State stateT, delta, unit;
    State net = State();
    
    std::vector<Satellite*> list; 
    
    if (sat)
        list.push_back(sat);
    else
        this->findNeighbours();
        list = this->_neighbours;
    
    for( auto &sat : list){
        if (sat->getID() == _id) continue;
        
        stateT = sat->getState();    
        delta = this->_state.deltaPosition(&stateT);

        unit = delta.unit();
    
        force = -gain*pow(tSpacing,2)*pow(delta.magnitude(),-2);

        net.position += unit.position*force/list.size();
        
//        net.x(net.x() + unit.x()*force/list.size());
//        net.y(net.y() + unit.y()*force/list.size());
//        net.z(net.z() + unit.z()*force/list.size());
    }
    
    return net;
}


State Satellite::forceAttractive(Satellite * sat)
{ 
    double force;
    double tSpacing = this->_settings->simulationTargetSpacing();
    double gain = this->_settings->forceGainAttractive();
    State stateT, delta, unit;
    State net = State();
    
    std::vector<Satellite*> list; 
    
    if (sat)
        list.push_back(sat);
    else
        list = *this->_swarm;
    
    for( auto &sat : list){
        if (sat->getID() == _id) continue;
        
        stateT = sat->getState(); 
        delta = this->_state.deltaPosition(&stateT);

        unit = delta.unit();
    
        force = gain*pow(tSpacing,-2)*pow(delta.magnitude(),2);
        net.position += unit.position*(force/list.size());
        
//        net.x(net.x() + unit.x()*force/list.size());
//        net.y(net.y() + unit.y()*force/list.size());
//        net.z(net.z() + unit.z()*force/list.size());
    }
    
    return net; 
}

State Satellite::forceDrag()
{ 
    double gain = this->_settings->forceGainDrag();
    State net = State();
    
    net.position = _state.velocity*gain;     
//    net.x( gain*this->_state.vx() );
//    net.y( gain*this->_state.vy() );
//    net.z( gain*this->_state.vz() );
    
    return net;

}

State Satellite::forceGravity(State * gravity)
{ 
    double gain = this->_settings->forceGainGravity();
    State net = State();
    
    State * grav = this->_gravity;
    State delta;
    
    if (gravity)
        grav = gravity;
    
    delta = this->_state.deltaPosition(grav);
    delta.position *= gain;
    
//    net.x( gain*delta.x() );
//    net.y( gain*delta.y() );
//    net.z( gain*delta.z() );
    
    return net;
}




void Satellite::print()
{
    std::cout << "Satellite ID:" << this->_id << " - " << this->_neighbours.size() << " neighbours " << std::endl;
//    for(auto &sat: this->_neighbours)
//        std::cout << "\t" << sat->getID() << "\t" << this->rangeToTarget(sat) << std::endl;
    this->_state.print();
    std::cout << this->fObs.magnitude() << " | ";
    std::cout << this->fAtt.magnitude() << " | ";
    std::cout << this->fDrg.magnitude() << " | ";
    std::cout << this->fGrv.magnitude() << std::endl;
}
