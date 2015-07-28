#include "pfswarm.h"

void satelliteSetup(PFSwarm * pf)
{
    pf->setupSwarm(5);
}

int main() 
{
	PFSwarm pf = PFSwarm();
        satelliteSetup(&pf);
        
        pf.print();

	return 0;
}