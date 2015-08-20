/* 
 * File:   swarmsettigs.h
 * Author: c_frazier
 *
 * Created on August 18, 2015, 4:41 PM
 */

#ifndef SWARMSETTIGS_H
#define	SWARMSETTIGS_H

#include <stdlib.h>
#include <math.h>
#include <iostream>

class SwarmSettings
{
private:
    // Satellite Settings
    int satellite_neighbourhood_size;
    double satellite_mass;
    double satellite_moment_of_inertia;
    
    // Simulation Settings
    int simulation_satellite_count;
    int simulation_cycle_limit;
    double simulation_convergence_limit;
    double simulation_target_spacing;
    double simulation_timestep;
    
public:
    SwarmSettings();
    ~SwarmSettings();
    
    int satelliteNeighbourhoodSize(double _val = NAN);
    double satelliteMass(double _val = NAN);
    double satelliteMomentOfInertia(double _val = NAN);
    
    int simulationSatelliteCount(double _val = NAN);
    int simulationCycleLimit(double _val = NAN);
    double simulationConvergenceLimit(double _val = NAN);
    double simulationTargetSpacing(double _val = NAN);
    double simulationTimestep(double _val = NAN);
    
    void print();
};

#endif	/* SWARMSETTIGS_H */

