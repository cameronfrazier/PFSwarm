#include "satellite.h"


Satellite::Satellite(int satID)
{
    this->_id = satID;
}

Satellite::Satellite(int satID, State initial_state)
{
    this->_id = satID;
    this->state = initial_state;
}

int Satellite::getID()
{ 
    return this->_id;
}

void Satellite::addNeighbour(Satellite * satellite)
{
	this->neighbours.push_back(satellite);
}

void Satellite::removeNeighbour(int index)
{
	this->neighbours.erase(this->neighbours.begin() + index);
}

void Satellite::addPSP(PSP * psp)
{
	this->psps.push_back(psp);
}

void Satellite::removePSP(int index)
{
	this->psps.erase(this->psps.begin() + index);
}

void Satellite::print()
{
    std::cout << "Satellite ID:" << this->_id << std::endl;
}
