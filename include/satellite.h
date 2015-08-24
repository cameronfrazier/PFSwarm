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
    // Satellite ID
    int _id;

    // pointer to settings object
    SwarmSettings * _settings;

    // pointer to gravity object
    State * _gravity;
    
    // List of neighbouring satellites
    std::vector<Satellite*> _neighbours;

    // List of active psp points
    std::vector<PSP*> _psps;

    // Current satellite state.
    State _state;
        
    // pointer to global satellite list
    std::vector<Satellite*> * _swarm;
    
    // Current Forces
    State fObs, fAtt, fDrg, fGrv;

public:    
    Satellite(int satID, 
            SwarmSettings * settings, 
            State * gravity, 
            std::vector<Satellite*> * swarm, 
            State initial_statee = State());
    
    ~Satellite() {};

    struct RangeStats {
        Vector3<double> minp = Vector3<double>(9999.,9999.,9999.); 
        Vector3<double> maxp = Vector3<double>(-9999.,-9999.,-9999.); 
        double total = 0;
        double min = 9999;
        double max = 0;
        double std = 0;
        double avg = 0;
        std::vector<double> ranges;
    };
    
    

    struct ForceStats {
        double total = 0;
        double min = 9999;
        double max = 0;
        double std = 0;
        double avg = 0;
        std::vector<double> ranges;
    };
    
    
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

    State forceRepulsive(Satellite * sat = nullptr);
    State forceAttractive(Satellite * sat = nullptr);
    State forceDrag();
    State forceGravity(State * gravity = nullptr);
   
    RangeStats getRangeStats(); 
    
    void print();
};

#endif