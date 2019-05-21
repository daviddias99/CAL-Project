#pragma once


class EdgeInfo {

private: 

	unsigned int ID;
	unsigned int vMax;
	double distance;
	unsigned int fTransito;
	int tempo;

public:

	EdgeInfo(unsigned int ID, unsigned int vMax, double distance, unsigned int fTransito, float timeFunc(unsigned int, double, unsigned int) );
	EdgeInfo(int tempo );
	int getTempo() const;
	unsigned int getID();

};