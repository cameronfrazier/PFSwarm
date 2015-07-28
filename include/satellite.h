#ifndef PF_SATELLITE
#define PF_SATELLITE

#include <vector>

#include "psp.h"
#include "state.h"

class Satellite
{
private:
	// List of neighbouring satellites
	std::vector<Satellite*> neighbours;

	// List of active psp points
	std::vector<PSP*> psps;

	// Current satellite state.
	State state;
        
        // Satellite ID
        int _id;

public:
	Satellite(int satID);
	Satellite(int satID, State initial_state);
	~Satellite() {};

        int getID();
        
	void addNeighbour(Satellite * satellite);
	void removeNeighbour(int index);

	void addPSP(PSP * psp);
	void removePSP(int index);
        
        void print();
};

#endif