#include "cliparse.h"
#include "swarmsettings.h"

void CLIParse::parse(int argc, char **argv, SwarmSettings * settings)
{
    int opt_c;
    while (1){
        int option_index = 0;
        
        static struct option long_options[] = {
            {"satellite-count",   required_argument, 0, 'c' },
            {"simulation-cycles", required_argument, 0, 's' },
            {"simulation-target-spacing", required_argument, 0, 'x' },
            {"print-range-table", no_argument, 0, 'r' },
            {"print-force-table", no_argument, 0, 'f' }
        };
        
        opt_c = getopt_long(argc, argv, "c:s:rfx:", long_options, &option_index);
        if (opt_c == -1) break;
        
        switch(opt_c){
            case 'c':
                settings->simulationSatelliteCount(atoi(optarg));
                break;
            case 's': 
                settings->simulationCycleLimit(atoi(optarg));
                break;
            case 'x': 
                settings->simulationTargetSpacing(atof(optarg));
                break;
            case 'r': 
                settings->displayTableRange(true);
                break;
            case 'f': 
                settings->displayTableForce(true);
                break;
            default: 
                break;
        }
    }
}
