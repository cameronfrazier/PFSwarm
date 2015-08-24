#ifndef PF_SWARM
#define PF_SWARM

#include <stdlib.h>
#include <random>
#include <math.h>

#include "swarmsettings.h"
#include "satellite.h"
#include "state.h"

#define IS_THREE_DIMENSTIONAL
//#define IS_THREE_DIMENSTIONAL = false


class PFSwarm
{
private:
    SwarmSettings * _settings;
    std::vector<Satellite*> _satellites;
    State _gravity;

public:
    
    PFSwarm(SwarmSettings * settings);
    ~PFSwarm();

    void run(int cycles = -1, double convergence = NAN);
    void setupSwarm();
    void setupSwarm(int numSatellites);

    void addSatellites(Satellite * satellite);
    void removeSatellites(int index);
    void clearSatellites();

    void printRangeTable();
    void printRangeStats();
    void printRepulsiveForceTable();
    void print();
};

#endif
