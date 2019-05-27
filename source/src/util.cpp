//
// Created by david on 16-05-2019.
//

#include "util.h"


Time::Time(uint hora, uint minuto, uint segundo) : hora(hora), minuto(minuto), segundo(segundo) {

    if (hora > 23)
        throw TimeInvalido("Hora invalida.");
    if (minuto > 59)
        throw TimeInvalido("Minuto invalido.");
    if (segundo > 59)
        throw TimeInvalido("Segundo invalido.");

}

Time::Time(string time) {

    stringstream ss(time);

    ss >> hora;
    if (ss.fail())
        TimeInvalido("Formato invalido.");
    if (hora > 23) {
        throw TimeInvalido("Hora invalida.");
    }
    if (ss.peek() != ':')
        throw TimeInvalido("Formato invalido.");
    ss.ignore();

    ss >> minuto;
    if (ss.fail())
        TimeInvalido("Formato invalido.");
    if (minuto > 59)
        throw TimeInvalido("Minuto invalido.");
    if (ss.peek() != ':')
        throw TimeInvalido("Formato invalido.");
    ss.ignore();

    ss >> segundo;
    if (ss.fail())
        TimeInvalido("Formato invalido.");
    if (segundo > 59)
        throw TimeInvalido("Segundo invalido.");
}


string Time::getTime(bool mostraSegundos) const
{
    string result;

    result = to_string(this->getHora()) + ':' + to_string(this->getMin());

    if (mostraSegundos)
        result += ':' + to_string(this->getSeg());

    return result;
}

unsigned int Time::getHora() const
{
    return this->hora;
}

unsigned int Time::getMin() const
{
    return this->minuto;
}

unsigned int Time::getSeg() const
{
    return this->segundo;
}

Time Time::operator+(Time & time2)
{
	uint second = this->segundo + time2.segundo;
	uint minute = this->minuto + time2.minuto + (second / 60);
	uint hour  = this->hora + time2.hora + (minute / 60);
	minute = minute % 60;
	second = second % 60;

	return Time(hour, minute);
}

bool Time::operator<(Time &time2) {

	if (this->hora < time2.hora)
		return true;
	else if (this->hora == time2.hora) {

		if (this->minuto < time2.minuto)
			return true;
		else if (this->minuto == time2.minuto) {

			if (this->segundo < time2.segundo)
				return true;
			else
				return false;
		}
		else
			return false;

	}
	else
		return false;
}

Time::Time() {

    time_t tempoAtual = time(NULL);

    tm* tempAtualStruct = new tm;
    //localtime(tempAtualStruct, &tempoAtual);

    this->hora = tempAtualStruct->tm_hour;
    this->minuto = tempAtualStruct->tm_min;
    this->segundo = tempAtualStruct->tm_sec;


}

Time Time::operator+(double minutes) {

        Time final;
        unsigned h= this->hora;
        unsigned m= this->minuto;
        unsigned s= this->segundo;
        h+=minutes/60;
        m+= (int)minutes%60;
        final=Time(h,m,s);
        return final;

}
