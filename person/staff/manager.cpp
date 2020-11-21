#include "staff.h"
#include <iostream>
#include <iomanip>

Manager::Manager(const std::string& name, const unsigned int & NIF, const float& wage, const std::string & password, const unsigned int & evaluation): Staff(name,NIF,wage){
    this->evaluation = evaluation;
    this->password = password;
};


unsigned int Manager :: getEvaluation() const{
    return this->evaluation;
}

std::string Manager::getType() {
    return "Manager";
}

std::string Manager::getPassword() {
    return this->password;
}

void Manager::printConsole() {
    std::cout << std::left << std::setw(13) << "Manager" <<  std::setw(22) << std::setfill(' ') << this->getName() <<
              std::setw(10) << this->getNIF() << std::setw(7) << this->getWage() << std::setw(16) << this->getYearsOfService()
              << std::setw(16) << "  " << std::setw(8) << "     " << std::setw(12) << this->getEvaluation();
}


void Manager::managerModify(const std::string& name, const std::string& NIF, const std::string& wage,const std::string & password, const std::string& evaluation){
    if (name != "."){
        this->name = name;
    }
    if(NIF != "."){
        this->NIF =stoi(NIF);
    }
    if(password != "."){
        this->password = password;
    }
    if(wage != "."){
        this->wage = stof(wage);
    }
    if(evaluation != "."){
        this->evaluation = stoi(evaluation);
    }
}