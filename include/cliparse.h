/* 
 * File:   cliparse.h
 * Author: c_frazier
 *
 * Created on August 24, 2015, 1:57 PM
 */

#ifndef CLIPARSE_H
#define	CLIPARSE_H

#include <getopt.h>

#include "swarmsettings.h"

class CLIParse
{
public:
    void parse(int argc, char **argv, SwarmSettings * settings);
};

#endif	/* CLIPARSE_H */

