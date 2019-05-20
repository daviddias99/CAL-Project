//
// Created by david on 16-05-2019.
//

#include "Person.h"

unsigned int Person::getID() {
    return this->ID;
}

Person::Person(unsigned int ID, string name) {

    this->ID = ID;
    this->name = name;

}

