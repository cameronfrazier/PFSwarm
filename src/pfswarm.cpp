#include "pfswarm.h"


PFSwarm::PFSwarm(){}
PFSwarm::~PFSwarm(){}

void PFSwarm::run(){}

void PFSwarm::setupSwarm()
{
    gravity = State(IS_THREE_DIMENSTIONAL);    
}

void PFSwarm::setupSwarm(int cntSatellite)
{
    this->setupSwarm();
    
    for (int idx = 0; idx < cntSatellite; idx++) {
        this->addSatellites(new Satellite(idx));
    }

        
}

void PFSwarm::addSatellites(Satellite * satellite)
{
    this->satellites.push_back(satellite);
}

void PFSwarm::removeSatellites(int index)
{
    this->satellites.erase(this->satellites.begin() + index);
}

void PFSwarm::print()
{
    
    std::cout << "Current Gravity State " << std::endl;
    this->gravity.print();   
    
    std::cout << "Current Swarm size: " << this->satellites.size() << std::endl;
    for (std::vector<Satellite*>::iterator it = this->satellites.begin() ; it != this->satellites.end(); ++it)
        std::cout << "    Satellite ID: " << (*it)->getID() << std::endl << std::endl;
}