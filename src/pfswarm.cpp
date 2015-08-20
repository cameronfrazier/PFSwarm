#include "pfswarm.h"


PFSwarm::PFSwarm(SwarmSettings * settings){
    this->_settings = settings;
}

PFSwarm::~PFSwarm(){
    std::cout << "Cleaning up!!" << std::endl;
    this->clearSatellites();
}


void PFSwarm::run(int cycles, double convergence_limit){
    int count = 0;
    double convergence_error = 1;
    
    if (-1 == cycles)
        cycles = this->_settings->simulationCycleLimit();
    
    if (std::isnan(convergence_limit))
        convergence_limit = this->_settings->simulationConvergenceLimit();
    
    this->_settings->print();
    
    // Run simulation iterations
    for(int idx = cycles; idx > 0; idx--){
        count++;

        this->_gravity.step();
        
        for (auto &sat: this->_satellites){ 
            sat->calculateForces();
            sat->step();
        }
        
        if (count % 100 == 0)
            std::cout << count << std::endl;
        else if (count % 10 == 0)
            std::cout << '|';
        else
            std::cout << '.';
        //this->print();
        
        if ( abs(convergence_error) < convergence_limit ) break;
    }
    
    std::cout << std::endl << std::endl;
}

void PFSwarm::setupSwarm()
{
    this->setupSwarm(this->_settings->simulationSatelliteCount());
}

void PFSwarm::setupSwarm(int cntSatellite)
{
    this->_gravity = State(IS_THREE_DIMENSTIONAL);
    this->_gravity.x(100);
    this->_gravity.y(200);
    this->_gravity.z(300);
    this->_gravity.vx(3);
    
    std::default_random_engine generator( (unsigned int)time(0) );
    std::uniform_int_distribution<int> uniform_dist(-50, 50);
    
    for (int idx = 0; idx < cntSatellite; idx++) {
        State init_state = State();
        init_state.x(uniform_dist(generator));
        init_state.y(uniform_dist(generator));
        init_state.z(uniform_dist(generator));
        this->addSatellites(new Satellite(idx, this->_settings, &this->_satellites, init_state));
    }
}

void PFSwarm::addSatellites(Satellite * satellite)
{
    this->_satellites.push_back(satellite);
}

/*
 Removes a satellite from the global list 
 */
void PFSwarm::removeSatellites(int index)
{
    delete this->_satellites[index];
    this->_satellites.erase(this->_satellites.begin() + index);
}


/*
 Removes all satellites from global list 
 */
void PFSwarm::clearSatellites()
{
    std::vector<Satellite*>::iterator it;
    for (auto &sat: this->_satellites){
        std::cout << "    Removing Satellite: ";
        std::cout << sat->getID() << std::endl;
        delete sat;
    }
    
    this->_satellites.clear();
}


/*
 Print range table
 */
void PFSwarm::printRangeTable(){
    
    std::cout << std::fixed << std::setprecision(2);
    
    for (auto &sat: this->_satellites) 
        std::cout << "\t" << sat->getID();
    std::cout << std::endl;
    
    for (auto &saty: this->_satellites){
        std::cout << saty->getID();
        for (auto &satx: this->_satellites)
            std::cout << "\t" << satx->rangeToTarget(saty);
        std::cout << std::endl;
    }
}

/*
 Print repulsive force table
 */
void PFSwarm::printRepulsiveForceTable(){    
    std::cout << std::fixed << std::setprecision(2);
    for(auto &sat : this->_satellites) 
        std::cout << "\t" << sat->getID();
    std::cout << std::endl;
    
    for(auto &saty: this->_satellites){
        std::cout << saty->getID();
        for (auto &satx: this->_satellites){
            State force = satx->forceRepulsive(saty);
            std::cout << "\t" << force.magnitude();
        }
        std::cout << std::endl;
    }
}

/*
 Print debug and status information
 */
void PFSwarm::print()
{
    std::cout << "Current Gravity State " << std::endl;
    this->_gravity.print();
    
    std::cout << "Current Swarm size: " << this->_satellites.size() << std::endl;
        
    for (auto &sat : this->_satellites) sat->print();
}