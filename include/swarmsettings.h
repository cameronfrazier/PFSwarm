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


#define MSG(message) std::cout << message << std::endl;

#define SETTING_ABS_INT(func,name) \
int SwarmSettings::func(double _val){\
    if( ! isnan( _val ) ) { this->name = (int) abs(_val); }\
    return this->name;\
}

#define SETTING_ABS_DOUBLE(func,name) \
double SwarmSettings::func(double _val){\
    if( ! isnan( _val ) ) this->name = abs(_val);\
    return this->name;\
}

#define SETTING_DOUBLE(func,name) \
double SwarmSettings::func(double _val){\
    if( ! isnan( _val ) ) this->name = _val;\
    return this->name;\
}

#define SETTING_BOOL(func,name) \
bool SwarmSettings::func(int _val){ \
    if ( _val >= 0 ) \
        this->name = (bool)_val; \
    return this->name; \
}

class SwarmSettings
{
private:
    // Satellite Settings
    int satellite_neighbourhood_size;
    double satellite_mass;
    double satellite_moment_of_inertia;
    double satellite_force_limit;
    
    // Simulation Settings
    int simulation_satellite_count;
    int simulation_cycle_limit;
    double simulation_convergence_limit;
    double simulation_target_spacing;
    double simulation_timestep;
    
    // Force gain values
    double force_gain_repulsive;
    double force_gain_attractive;
    double force_gain_drag;
    double force_gain_gravity;
    
    // display control
    bool display_table_force;
    bool display_table_range;
    
    
public:
    SwarmSettings();
    ~SwarmSettings();
    
    int satelliteNeighbourhoodSize(double _val = NAN);
    double satelliteMass(double _val = NAN);
    double satelliteMomentOfInertia(double _val = NAN);
    double satelliteForceLimit(double _val = NAN);
    
    int simulationSatelliteCount(double _val = NAN);
    int simulationCycleLimit(double _val = NAN);
    double simulationConvergenceLimit(double _val = NAN);
    double simulationTargetSpacing(double _val = NAN);
    double simulationTimestep(double _val = NAN);
    
    double forceGainRepulsive(double _val = NAN);
    double forceGainAttractive(double _val = NAN);
    double forceGainDrag(double _val = NAN);
    double forceGainGravity(double _val = NAN);
    
    bool displayTableForce(int _val = -1);
    bool displayTableRange(int _val = -1);
    
    void print();
};

#endif	/* SWARMSETTIGS_H */

