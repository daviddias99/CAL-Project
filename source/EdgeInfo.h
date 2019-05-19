#pragma once


class EdgeInfo {

private: 

	unsigned int ID;
	unsigned int vMax;
	double distance;
	unsigned int fTransito;
	int tempo;

public:

	EdgeInfo(unsigned int ID, unsigned int vMax, double distance, unsigned int fTransito, int timeFunc(unsigned int, double, unsigned int) );
	int getTempo() const;
	unsigned int getID();

};