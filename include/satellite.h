#ifndef PF_SATELLITE
#define PF_SATELLITE

#include <vector>

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
        

public:
	Satellite(int satID, SwarmSettings * settings);
	Satellite(int satID, SwarmSettings * settings, State initial_state);
	~Satellite() {};
    
        int getID();
        State getState();
        
	void addNeighbour(Satellite * satellite);
	void removeNeighbour(int index);
        void clearNeighbours();
        
        double rangeToTarget(Satellite * target);

	void addPSP(PSP * psp);
	void removePSP(int index);
        
        void applyForce(State force);
        
        void step();
        void step(double timestep);
        
        void print();
};

#endif