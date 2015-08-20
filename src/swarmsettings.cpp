#include "swarmsettings.h"

SwarmSettings::SwarmSettings(){
    // Satellite Settings
    this->satelliteNeighbourhoodSize(5);
    this->satelliteMass(1);
    this->satelliteMomentOfInertia(1);
    
    // Simulation Settings
    this->simulationSatelliteCount(15);
    this->simulationCycleLimit(5);
    this->simulationConvergenceLimit(0.0);
    this->simulationTargetSpacing(50);
    this->simulationTimestep(1.0);
    
    // Force Settings
    this->forceGainRepulsive(10);
    this->forceGainAttractive(10);
    this->forceGainDrag(10);
    this->forceGainGravity(10);
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

SETTING_DOUBLE(forceGainRepulsive,force_gain_repulsive)
SETTING_DOUBLE(forceGainAttractive,force_gain_attractive)
SETTING_DOUBLE(forceGainDrag,force_gain_drag)
SETTING_DOUBLE(forceGainGravity,force_gain_gravity)

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