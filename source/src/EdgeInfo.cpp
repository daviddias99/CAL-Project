#include "EdgeInfo.h"

EdgeInfo::EdgeInfo(unsigned int ID, unsigned int vMax, double distance, unsigned int fTransito, float timeFunc(unsigned int, double, unsigned int))
{
	this->ID = ID;
	this->vMax = vMax;
	this->distance = distance;
	this->fTransito = fTransito;

	tempo = timeFunc(vMax, distance, fTransito);
}

int EdgeInfo::getTempo() const
{
	return tempo;
}

unsigned int EdgeInfo::getID()
{
	return ID;
}
