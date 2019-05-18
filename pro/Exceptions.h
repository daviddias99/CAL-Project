//
// Created by david on 16-05-2019.
//

#ifndef PRO_EXCEPTIONS_H
#define PRO_EXCEPTIONS_H


#include <string>
using namespace std;

/**
 * @brief Classe que representa uma excecao geral que apenas contem a informacao sobre a ocorrencia da excecao,
 *  usada para derivar nova excecoes
 */
class ExcecaoGeral {
protected:
    /**
     * @brief Informacao sobre a excecao
     */
    string info;
public:
    /**
     * @brief Cria uma excecao com a informacao passada por argumento
     *
     * @param i informacao sobre a excecao
     */
    ExcecaoGeral(string i) { info = i; }
    /**
     * @brief Obtem informacao sobre a excecao
     */
    string getInfo() const { return info; }
};

/**
 * @brief Excecao que ocorre quando um hora e invalida
 *
 */
class TimeInvalido : public ExcecaoGeral {
public:
    /**
     * @brief Cria uma excecao com a informacao passada por argumento
     *
     * @param i informacao sobre a excecao
     */
    TimeInvalido(string i) : ExcecaoGeral(i) {}
};

#endif //PRO_EXCEPTIONS_H
