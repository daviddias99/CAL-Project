//
// Created by david on 16-05-2019.
//

#ifndef PRO_UTIL_H
#define PRO_UTIL_H

#include <ostream>
#include <string>
#include "Exceptions.h"
#include <sstream>
#include <time.h>

using namespace std;

typedef unsigned int uint;

/**
 * @brief Classe que representa uma hora do dia (horas, minutos, segundos)
 *
 */
class Time {

protected:

    /**
    * @brief segundo associado ao presente objeto de Time
    */
    unsigned int segundo;
    /**
    * @brief minuto associado ao presente objeto de Time
    */
    unsigned int minuto;
    /**
    * @brief hora associado ao presente objeto de Time
    */
    unsigned int hora;



public:

    bool passedToNext;

    /**
    * @brief Construtor default da classe Time, constroi o objeto  com o tempo(hora, minuto
    * e segundo) atual.
    */
    Time();

    /**
    * @brief Constroi um objeto da classe Time a partir das informacoes contidas na string passada como argumento
    *
    * @return string com as horas no formato HH:MM:SS
    */
    Time(string time);


    /**
    * @brief constroi a classe Time com os valores para a hora, minuto e segundo dados
    *
    * @param hora		hora associado ao time
    * @param minuto		minuto associado ao time
    * @param segundo	segundo associado ao time
    */
    Time(unsigned int hora, unsigned int minuto, unsigned int segundo = 0);


    /**
    * @brief retorna um string com o tempo associado ao objeto no formato HH:MM:SS
    *
    * @param mostraSegundos	mostra tempo no formato HH:MM:SS se true e HH:MM se false
    * @return				string com o tempo num formato pretendido
    */
    string getTime(bool mostraSegundos = false) const;

    /**
    * @brief retorna a hora associado ao objeto tempo
    *
    * @return	hora associada ao objeto tempo
    */
    unsigned int getHora() const;

    /**
    * @brief retorna os minutos associados ao objeto tempo
    *
    * @return	minutos associados ao objeto tempo
    */
    unsigned int getMin() const;

    /**
    * @brief retorna os segundos associados ao objeto tempo
    *
    * @return	segundos associados ao objeto tempo
    */
    unsigned int getSeg() const;

    /**
    * @brief envia para a stream os a data no formato DD-MM-YYYY
    *
    * @param os	referencia para uma output stream
    * @param d	referencia para uma hora
    * @return	a output stream de argumento
    */
    friend ostream& operator<<(ostream& os, const Time& d);

	Time operator+(Time& time2);
	Time operator+(double minutes);

	bool operator<(Time &time2);

};


#endif //PRO_UTIL_H
