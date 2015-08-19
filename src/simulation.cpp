#include <stdlib.h>
#include <getopt.h>
#include <string>
#include <iostream>
#include <random>


#include "swarmsettings.h"
#include "pfswarm.h"


void satelliteSetup(PFSwarm * pf, SwarmSettings * settings)
{
    pf->setupSwarm(settings->simulationSatelliteCount());
}

int main(int argc, char **argv) 
{  
    // Settings object
    SwarmSettings settings = SwarmSettings();
 
    // Parse arguments and update Settings as needed    
    int opt_c;
    
    while (1){
        int option_index = 0;
        
        static struct option long_options[] = {
            {"satellite_count",   required_argument, 0, 'c' },
            {"simulation_cycles", required_argument, 0, 's' }
        };
        
        opt_c = getopt_long(argc, argv, "c:s:", long_options, &option_index);
        if (opt_c == -1) break;
        
        switch(opt_c){
            case 'c':
                settings.simulationSatelliteCount(atoi(optarg));
                break;
            case 's': 
                settings.simulationCycleLimit(atoi(optarg));
                break;
            default: 
                break;
        }
    }
    
    // What settings are being used?
    settings.print();
            
    
    // Create the swarm
    PFSwarm pf = PFSwarm(&settings);
    pf.setupSwarm();

    pf.run();

    pf.printRangeTable();
    pf.printRepulsiveForceTable();
    //pf.print();

    exit(EXIT_SUCCESS);
}