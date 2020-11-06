#include "person.h"
#include <iostream>
#include <iomanip>
#include "../GUI/utils.h"

Person::Person(const std::string& name, const unsigned int & NIF){
    this->name = name;
    this->NIF = NIF;
}

std::string Person::getName() const {
    return this->name;
}

unsigned int Person::getNIF() const {
    return this->NIF;
}

void Person::print() {
    std::cout << std::setw(20) << std::setfill(' ') << this->getName() << std::setw(10) << this->getNIF();
}

void Person::setName(const std::string &name){
    this->name = name;
}

void Person::setNIF(const unsigned int &NIF){
    this->NIF = NIF;
}
/*
void Person::edit() {
    std::string edit;
    std::cout << "Edit the client's information as follows: " << std::endl;
    std::cout << "Note: If you do not wish to edit the current camp, type '.' \n" << std::endl;
    std::cout << "Name: " << std::endl;
    getStringInput(edit, 6, 3);
    if (edit != ".") this->setName(edit);
    gotoxy(0, 5);
    edit = "";
    std::cout << "NIF: " << std::endl;
    edit = GetNumberInput(5,5,CheckIfInteger);
    if(edit != ".") this->setNIF(std::stoi(edit));
}*/