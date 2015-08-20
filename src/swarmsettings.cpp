#include "swarmsettings.h"

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

SwarmSettings::SwarmSettings(){
    // Satellite Settings
    this->satelliteNeighbourhoodSize(6);
    this->satelliteMass(1);
    this->satelliteMomentOfInertia(1);
    
    // Simulation Settings
    this->simulationSatelliteCount(7);
    this->simulationCycleLimit(5);
    this->simulationConvergenceLimit(0.0);
    this->simulationTargetSpacing(50);
    this->simulationTimestep(1.0);
    
    // Force Settings
//    this->force_gain_repulsive(10);
//    this->force_gain_attractive(10);
//    this->force_gain_drag(10);
//    this->force_gain_gravity(10);
}
SwarmSettings::~SwarmSettings(){}

SETTING_ABS_INT(satelliteNeighbourhoodSize, satellite_neighbourhood_size)
SETTING_ABS_DOUBLE(satelliteMass,satellite_mass)
SETTING_ABS_DOUBLE(satelliteMomentOfInertia,satellite_moment_of_inertia)

SETTING_ABS_INT(simulationSatelliteCount, simulation_satellite_count)
SETTING_ABS_INT(simulationCycleLimit, simulation_cycle_limit)
SETTING_ABS_DOUBLE(simulationConvergenceLimit,simulation_convergence_limit)
SETTING_ABS_DOUBLE(simulationTargetSpacing,simulation_target_spacing)
SETTING_ABS_DOUBLE(simulationTimestep,simulation_timestep)



//int SwarmSettings::satelliteNeighbourhoodSize(double _val){
//    if( ! isnan( _val ) ) { this->satellite_neighbourhood_size = (int) abs(_val); }
//    return this->satellite_neighbourhood_size;
//}
//double SwarmSettings::satelliteMass(double _val){
//    if( ! isnan( _val ) ) this->satellite_mass = abs(_val);
//    return this->satellite_mass;
//}
//double SwarmSettings::satelliteMomentOfInertia(double _val){
//    if( ! isnan( _val ) ) this->satellite_moment_of_inertia = abs(_val);
//    return this->satellite_moment_of_inertia;
//}
//
//int SwarmSettings::simulationSatelliteCount(double _val){
//    if( ! isnan( _val ) ) this->simulation_satellite_count = (int) abs(_val);
//    return this->simulation_satellite_count;
//}
//
//int SwarmSettings::simulationCycleLimit(double _val){
//    if( ! isnan( _val ) ) this->simulation_cycle_limit = (int) abs(_val);
//    return this->simulation_cycle_limit;
//}
//
//double SwarmSettings::simulationConvergenceLimit(double _val){
//    if( ! isnan( _val ) ) this->simulation_convergence_limit = abs(_val);
//    return this->simulation_convergence_limit;
//}
//
//double SwarmSettings::simulationTargetSpacing(double _val){
//    if( ! isnan( _val ) ) this->simulation_target_spacing = abs(_val);
//    return this->simulation_target_spacing;
//}
//
//double SwarmSettings::simulationTimestep(double _val){
//    if( ! isnan( _val ) ) this->simulation_timestep = abs(_val);
//    return this->simulation_timestep;
//}

void SwarmSettings::print(){
    std::cout << "Current Settings:" << std::endl;
    std::cout << "    Satellite Settings" << std::endl;
    std::cout << "        Neighbourhood Size:  " << this->satelliteNeighbourhoodSize() << std::endl;
    std::cout << "        Mass:                " << this->satelliteMass() << std::endl;
    std::cout << "        Moment of Inertia:   " << this->satelliteMomentOfInertia() << std::endl;
    std::cout << "    Simulation Settings" << std::endl;
    std::cout << "        Satellite Count:     " << this->simulationSatelliteCount() << std::endl;
    std::cout << "        Cycle Limit:         " << this->simulationCycleLimit() << std::endl;
    std::cout << "        Convergence Limit:   " << this->simulationConvergenceLimit() << std::endl;
    std::cout << "        Satellite Spacing:   " << this->simulationTargetSpacing() << std::endl;
    std::cout << "        Simulation Timestep: " << this->simulationTimestep() << std::endl;
    std::cout << std::endl;
}