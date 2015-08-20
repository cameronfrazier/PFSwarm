#ifndef PF_SATELLITE
#define PF_SATELLITE

#include <vector>
#include <limits>       // std::numeric_limit
#include <algorithm>    // std::sort

#include "psp.h"
#include "state.h"
#include "swarmsettings.h"

class Satellite
{
private:
    // List of neighbouring satellites
    std::vector<Satellite*> _neighbours;

    // List of active psp points
    std::vector<PSP*> _psps;

    // Current satellite state.
    State _state;

    // Satellite ID
    int _id;

    // pointer to settings object
    SwarmSettings * _settings;
    
    std::vector<Satellite*> * _swarm;
        

public:
    Satellite(int satID, SwarmSettings * settings, std::vector<Satellite*> * swarm);
    Satellite(int satID, SwarmSettings * settings, std::vector<Satellite*> * swarm, State initial_state);
    ~Satellite() {};

    int getID();
    State getState();

    void addNeighbour(Satellite * satellite);
    void removeNeighbour(int index);
    void clearNeighbours();

    double rangeToTarget(Satellite * target);

    void addPSP(PSP * psp);
    void removePSP(int index);
    
    void findNeighbours();
    void applyForce(State force);

    void step(double timestep = 1.0);
    
    void calculateForces();

    State forceRepulsive(Satellite * sat);
    State forceRepulsive();
    State forceAttractive();
    State forceDrag();
    State forceGravity(State * gravity);
   
    
    void print();
};

#endif