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
    bool doRangeTable = false;
    bool doForceTable = false;
    
    while (1){
        int option_index = 0;
        
        static struct option long_options[] = {
            {"satellite-count",   required_argument, 0, 'c' },
            {"simulation-cycles", required_argument, 0, 's' },
            {"print-range-table", no_argument, 0, 'r' },
            {"print-force-table", no_argument, 0, 'f' }
        };
        
        opt_c = getopt_long(argc, argv, "c:s:rf", long_options, &option_index);
        if (opt_c == -1) break;
        
        switch(opt_c){
            case 'c':
                settings.simulationSatelliteCount(atoi(optarg));
                break;
            case 's': 
                settings.simulationCycleLimit(atoi(optarg));
                break;
            case 'r': 
                doRangeTable = true;
                break;
            case 'f': 
                doForceTable = true;
                break;
            default: 
                break;
        }
    }
    
    // What settings are being used?
    settings.print();
            
    
    // Create the swarm
    MSG("Creating PFSwarm")
    PFSwarm pf = PFSwarm(&settings);
    
    MSG("Setup PFSwarm")
    pf.setupSwarm();
            
    MSG("Running PFSwarm")
    pf.run();

    if(doRangeTable)
        pf.printRangeTable();

    if(doForceTable)
        pf.printRepulsiveForceTable();

    exit(EXIT_SUCCESS);
}