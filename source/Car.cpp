#include "Vertex.h"
#include "Car.h"


Car::Car(uint carID, uint driverID, uint maxSeats)
{
	this->carID = carID;
	this->driverID = driverID;
	this->maxSeats = maxSeats;
	this->currentTakenSeats = 0;
}

uint Car::getCarID()
{
	return this->carID;
}

uint Car::getDriverID()
{
	return this->driverID;
}

uint Car::getMaxSeats()
{
	return this->maxSeats;
}

uint Car::getCurrentTakenSeats()
{
	return currentTakenSeats;
}
