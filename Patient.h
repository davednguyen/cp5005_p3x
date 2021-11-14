/*
 * name: David Nguyen
 * file: Patient.h
 * for Patient class
 */

#ifndef P3X_PATIENT_H
#define P3X_PATIENT_H


#include <string>
#include <sstream>
#include <iostream>
using namespace std;


class Patient {
public:
    Patient();
    Patient(string, int);
    string to_string();
    string to_string() const;
    void setArrivalOrder(int);
    void setPriorityCode(int); //for extra credit
    int getPriorityCode();
    string getName();
    int getArrivalOrder();
    //overloaded operators
    Patient operator + (const Patient &); // Overloaded +
    Patient operator - (const Patient &); // Overloaded -
    Patient operator ++ ();				    // Prefix ++
    Patient operator ++ (int);			    // Postfix ++
    bool operator > (Patient);// Overloaded >
    bool operator < (Patient);// Overloaded <
    bool operator == (Patient);// Overloaded ==
    bool operator >= (Patient);// overloaded >=

private:
    //variables
    string name; //full name for patient
    //list of priority codes in string to use as represent priority code in integer
    //assigned for each patient
    string priorities[5] = {" ", "immediate", "emergency", "urgent", "minimal" };
    int priorityCode; //priority code integer
    int arrivalOrder; //keep track arrival order of patient
};

/*
 * Constructor create Patient object with full name and priority code
 */
Patient::Patient(string name, int code) {
    this->name = name;
    this->priorityCode = code;
}

/*
 * representation for patient with information like arrival number, priority code and full name
 * in format of  --- arrival # ----- Priority code ---- Patient name
 */
string Patient::to_string() {
    stringstream  ss;
    if(arrivalOrder < 10){
        if(priorityCode == 4)
            ss<< "    " << arrivalOrder << "         " << priorities[priorityCode] << "         " << name;
        else if(priorityCode == 1 || priorityCode == 2)
            ss<< "    " << arrivalOrder << "         " << priorities[priorityCode] << "       " << name;
        else
            ss<< "    " << arrivalOrder << "         " << priorities[priorityCode] << "          " << name;
    }else{
        if(priorityCode == 4)
            ss<< "    " << arrivalOrder << "        " << priorities[priorityCode] << "         " << name;
        else if(priorityCode == 1 || priorityCode == 2)
            ss<< "    " << arrivalOrder << "        " << priorities[priorityCode] << "       " << name;
        else
            ss<< "    " << arrivalOrder << "        " << priorities[priorityCode] << "          " << name;
    }
    return ss.str();
}

/*
 * get priority code for a patient
 */
int Patient::getPriorityCode() {
    return priorityCode;
}

/*
 * get arrival number for patient
 */
int Patient::getArrivalOrder() {
    return arrivalOrder;
}

/*
 * get full name of patient
 */
string Patient::getName() {
    return name;
}

/*
 * set arrival order for patient
 */
void Patient::setArrivalOrder(int order) {
    arrivalOrder = order;
}

/*
 * set Priority code
 * for EXTRA credit works
 */
void Patient::setPriorityCode(int newCode) {
    priorityCode = newCode;
}
/*
 * overloaded operator equal
 * return true if priority code is equal to other patient's priority code
 */
bool Patient::operator == (Patient patient)
{
    if(priorityCode == patient.getPriorityCode())
    {
        return true;
    }else{
        return false;
    }
}

/*
 * overloaded operator less than
 * return true if priority code is less than other patient's priority code
 */
bool Patient::operator < (Patient patient) {
    if(priorityCode < patient.getPriorityCode())
    {
        return true;
    }else{
        return false;
    }
}

/*
 * overloaded operator greater than
 * return true if priority code is greater than other patient's priority code
 */
bool Patient::operator > (Patient patient)
{
    if(priorityCode > patient.getPriorityCode())
    {
        return true;
    }else{
        return false;
    }
}

/*
 * overloaded operator greater than or equal
 * return true if priority code is greater than or equal to other patient's priority code
 */
bool Patient::operator >= (Patient patient)
{
    if(priorityCode >= patient.getPriorityCode())
    {
        return true;
    }else{
        return false;
    }
}


#endif //P3X_PATIENT_H
