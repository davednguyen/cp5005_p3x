/*
 * name: David Nguyen
 * file: PatientPriorityQueue.h class
 * maintain patient list with MIN HEAP
 */

#ifndef P3X_PATIENTPRIORITYQUEUE_H
#define P3X_PATIENTPRIORITYQUEUE_H
#include <vector>
#include "Patient.h"
#include <cassert>
#include <string>

using namespace std;

class PatientPriorityQueue{
public:
    PatientPriorityQueue();
    void add(Patient);
    string peek() const;
    void next();
    string remove();
    void list();
    int Size();
    string to_string();
    string getLevelTraversal();
    int getLatestInsertedPatientNumber();

private:
    int count;
    int size;
    int capacity;
    vector<Patient> patients;
    int highestPriorityCode;
    int nextPatientNumber; // to keep track the last patient inserted
    int arrivalOrder; //keep track arrival order of patient
    void siftUp(int);
    void siftDown(int );
    int getParent(int) const;
    int getLeftChild(int) const;
    int getRightChild(int) const;
    void updatePriorityCode();
};

/*
 * constructor start up patient system
 */
PatientPriorityQueue::PatientPriorityQueue() {
    size = 1;
    capacity = 0;
    highestPriorityCode = 4;
    count = 1;
    arrivalOrder = 1;
}

/*
 * display next patient in the list to see doctor
 */
string PatientPriorityQueue::peek() const {
    stringstream ss;
    for(int i = 0; i < (int) patients.size(); i++){
        Patient patient = patients[i];
        if(patient.getPriorityCode() == highestPriorityCode){
            ss  <<"Highest priority patient to be called next: " << patient.getName();
            break;
        }
    }
    return ss.str();
}

/*
 * display list of patient in a HEAP
 */
string PatientPriorityQueue::to_string() {

    stringstream ss;
    vector<Patient>::iterator it;
    for(it = patients.begin()  ; it != patients.end(); it++){
        ss << it->to_string()<< endl;
    }
    return ss.str();


}

/*
 * Special function to display list of patient with order of priority codes
 * when using this function, system will display list of patients following
 *  1 immediate
 *  2 emergency
 *  3 urgent
 *  4 minimal
 */
string PatientPriorityQueue::getLevelTraversal() {
    stringstream ss;
    for(int j = 1; j <= 4; j++){
        for(int i = 0; i < (int) patients.size(); i++){
            Patient patient = patients[i];
            if(patient.getPriorityCode() == j){
                ss  << patient.to_string() << endl;
            }
        }
    }
    return ss.str();
}

/*
 * function to add patient to system
 */
void PatientPriorityQueue::add(Patient newPatient) {

    newPatient.setArrivalOrder(arrivalOrder);
    patients.push_back(newPatient);
    count++;
    arrivalOrder++;
    size++;
    nextPatientNumber = newPatient.getArrivalOrder();
    updatePriorityCode();
    siftUp(patients.size() - 1);
}

/*
 * function to remove a patient from the system after
 * the patient met the doctor
 */
string PatientPriorityQueue::remove() {

    stringstream ss;
    if(patients.size() > 0)
        for(int i = 0; i < (int) patients.size(); i++){
            if (patients[i].getPriorityCode() == highestPriorityCode){
                vector<Patient>::iterator it;
                it = patients.begin() + i;
                ss << "This patient will now be seen: " << it->getName();
                patients.erase(it);
                highestPriorityCode = 4;
                updatePriorityCode();
                size--;
                break;
            }
        }else{
        ss << "There are no patients in the waiting area.";
        //maintain the heap order after removed a patient
        if(size > 1){
            //maintain min heap
            siftDown(0);
        }
    }

    return ss.str();
}

/*
 * return size of the HEAP
 */
int PatientPriorityQueue::Size() {
    return patients.size();
}

/*
 * function to return the number of last patient inserted
 */
int PatientPriorityQueue::getLatestInsertedPatientNumber() {
    return nextPatientNumber;
}

/*
 * private function to update the highest priority code of patient
 * in the system.
 */
void PatientPriorityQueue::updatePriorityCode()  {
    if(patients.size() > 0){
        for(int i = 0; i < (int) patients.size(); i++){
            if(patients[i].getPriorityCode() < highestPriorityCode){
                highestPriorityCode = patients[i].getPriorityCode();
            }
        }
    }
}

/*
 * mean HEAP sift up
 */
void PatientPriorityQueue::siftUp(int index) {
    int parentIndex;
    if(index != 0){
        parentIndex = getParent(index);
        if(patients[parentIndex] > patients[index]){
            Patient tempPatient = patients[parentIndex];
            patients[parentIndex] = patients[index];
            patients[index] = tempPatient;
            siftUp(parentIndex);
        }
    }
}

/*
 * maintain min heap after removed an item
 */
void PatientPriorityQueue::siftDown(int index)  {
    int leftIndex, rightIndex, maxIndex;
    leftIndex = getLeftChild(index);
    rightIndex = getRightChild(index);

    //find minIndex
    if(rightIndex >= size){
        if(leftIndex >= size){
            return;
        }else{
            maxIndex = leftIndex;
        }
    }else{
        if(patients[leftIndex] >= patients[rightIndex] ){
            maxIndex = leftIndex;
        }else{
            maxIndex = rightIndex;
        }
    }

    //swap
    if(patients[index] > patients[maxIndex]){
        Patient tempPatient = patients[maxIndex];
        patients[maxIndex] = patients[index];
        patients[index] = tempPatient;
        siftDown(maxIndex);
    }
}

/*
 * get index for min heap
 */
int PatientPriorityQueue::getParent(int index) const {
    return (index -1)/2;
}

/*
 * get index for min heap
 */
int PatientPriorityQueue::getLeftChild(int index) const {
    return 2 * index + 1;
}

/*
 * get index for min heap
 */
int PatientPriorityQueue::getRightChild(int index) const {
    return 2 * index + 2;
}


#endif //P3X_PATIENTPRIORITYQUEUE_H
