/* 
 * File:   forcefunctions.h
 * Author: c_frazier
 *
 * Created on August 19, 2015, 4:57 PM
 */

#ifndef FORCEFUNCTIONS_H
#define	FORCEFUNCTIONS_H

#include <iostream>

#include "state.h"
#include "satellite.h"
#include "swarmsettings.h"

namespace RAVE {
    
    State forceRepulsive(Satellite * satA, Satellite * satB, SwarmSettings * settings);
    State forceAttractive(Satellite * satA, Satellite * satB, SwarmSettings * settings);
    State forceDrag(Satellite * satA, SwarmSettings * settings);
    State forceGravity(Satellite * satA, State * gravity, SwarmSettings * settings);
    
}

#endif	/* FORCEFUNCTIONS_H */

