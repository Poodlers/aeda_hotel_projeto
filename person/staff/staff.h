#ifndef STAFF_H
#define STAFF_H
#include <string>
#include <vector>
#include "../person.h"

class Staff: public Person {
public:
    Staff(const std::string& name, const unsigned int & NIF, const float& wage);
    float getWage() const;
    int getYearsOfService() const;
    virtual std::string getType();
    void setWage(const float wage);
    void setYearsOfService(const int yearsOfService);
    virtual void print() override;

protected:
    float wage;
    unsigned int yearsOfService;
};


class Receptionist : public  Staff{
public:
    Receptionist(const std::string& name, const unsigned int & NIF, const float& wage);
    std::string getType() override;
};

class Responsible : public Receptionist{
public:
    Responsible(const std::string& name, const unsigned int & NIF, const float& wage);
    void assignFloor(const unsigned int & floor);
    void clearAssignedFloors();
    int getNumberOfFloorsBringMonitored() const;
    std::vector<int> getFloorsAssigned() const;
    std::string getType() override;
    void print() override;

private:
    int numberOfFloorsBeingMonitored;
    std::vector<int> floorsAssigned;
};

class Janitor : public Staff{
public:
    Janitor(const bool & shift,const std::string& name, const unsigned int & NIF, const float& wage);
    bool getShift() const;
    void setShift(const bool& shift);
    std::string getType() override;
    void print() override;
    void janitorModify(const std::string& name, const std::string& NIF, const std::string& shift);

private:
    bool shift; //true for day, false for night
};

class Manager : public Staff{
public:
    Manager(const std::string& name, const unsigned int & NIF, const float& wage, const std::string & password);
    unsigned int getEvaluation() const;
    void setEvaluation(const unsigned int &evaluation);
    std::string getType() override;
    std::string getPassword();
    void print() override;
    void managerModify(const std::string& name, const std::string& NIF, const std::string & password);

private:
    unsigned int evaluation; //0 if manager has not been evaluated, 1 to 5 they have been evaluated
    std::string password;
};

#endif