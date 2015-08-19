#include "forcefunctions.h"

namespace RAVE {  
State forceRepulsive(Satellite * satA, Satellite * satB, SwarmSettings * settings){
    State stateA = satA->getState();
    State stateB = satB->getState();

//    std::cout << "Satellite A" << std::endl; 
//    stateA.print();
     
//    std::cout << "Satellite B" << std::endl;
//    stateB.print();
    
    State delta = stateA.lengthFrom(&stateB);
//    std::cout << "Delta" << std::endl;
//    delta.print();

    State unit = delta.unit();
//    std::cout << "unit Delta" << std::endl;
//    unit.print();

    double tSpacing = settings->simulationTargetSpacing();
//    std::cout << "Target Spacing: " << tSpacing << std::endl; 

//    std::cout << "Target Range: " << delta.magnitude() << std::endl; 

    
    double force = pow(tSpacing,2)*pow(delta.magnitude(),-2);
    
//    std::cout << "Developed force: " << force << std::endl; 

    unit.x(unit.x()*force);
    unit.y(unit.y()*force);
    unit.z(unit.z()*force);

//    std::cout << "Force Vector" << std::endl;
//    unit.print();    
    return unit;
}


//State forceAttractive(Satellite * satA, Satellite * satB, SwarmSettings * settings){};
//State forceDrag(Satellite * satA, SwarmSettings * settings){};
//State forceGravity(Satellite * satA, State * gravity, SwarmSettings * settings){};
}