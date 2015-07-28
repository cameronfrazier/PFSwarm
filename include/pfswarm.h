#ifndef PF_SWARM
#define PF_SWARM

#include "satellite.h"
#include "state.h"

#define IS_THREE_DIMENSTIONAL
//#define IS_THREE_DIMENSTIONAL = false


class PFSwarm
{
private:
	std::vector<Satellite*> satellites;

public:
	State gravity;
        
	PFSwarm();
	~PFSwarm();
	
	void run();
	void setupSwarm();
	void setupSwarm(int numSatellites);

        void addSatellites(Satellite * satellite);
        void removeSatellites(int index);
        
        void print();
};

#endif
