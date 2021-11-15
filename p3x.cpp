/*
 * name: David Nguyen
 * p3x.cpp file
 * to run patient system
 */

#include <iostream>
#include "Patient.h"
#include "PatientPriorityQueuex.h"
#include <fstream>
#include <string>

using namespace std;


void welcome();
// Prints welcome message.

void goodbye();
// Prints goodbye message.

void help();
// Prints help menu.

bool processLine(string, PatientPriorityQueue &);
// Process the line entered from the user or read from the file.

void addPatientCmd(string, PatientPriorityQueue &);
// Adds the patient to the waiting room.

void peekNextCmd(PatientPriorityQueue &);
// Displays the next patient in the waiting room that will be called.

void removePatientCmd(PatientPriorityQueue &);
// Removes a patient from the waiting room and displays the name on the screen.

void showPatientListCmd(PatientPriorityQueue &);
// Displays the list of patients in the waiting room.

void execCommandsFromFileCmd(string, PatientPriorityQueue &);
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.

string delimitBySpace(string &);
// Delimits (by space) the string from user or file input.

void showHeapSizeCmd(PatientPriorityQueue &);
// Displays size of patient list.

void UpdatePatientPriorityCode(string, PatientPriorityQueue &);
//****************EXTRA CREDIT works**************************
//update specific patient's priority code

void SavePatientList(string, PatientPriorityQueue &);
//*************** Extra CREDIT works***************************

int main() {

    // declare variables
    string line;

    // welcome message
    welcome();

    // process commands
    PatientPriorityQueue priQueue;
    do {
        cout << "\ntriage> ";
        getline(cin, line);
    } while (processLine(line, priQueue));

    // goodbye message
    goodbye();
}

bool processLine(string line, PatientPriorityQueue &priQueue) {
    // get command
    string cmd = delimitBySpace(line);
    if (cmd.length() == 0) {
        cout << "Error: no command given.";
        return false;
    }
    // process user input
    if (cmd == "help")
        help();
    else if (cmd == "add")
        addPatientCmd(line, priQueue);
    else if (cmd == "change") //****EXTRA credit works*********
        UpdatePatientPriorityCode(line, priQueue);
    else if (cmd == "peek")
        peekNextCmd(priQueue);
    else if (cmd == "next")
        removePatientCmd(priQueue);
    else if (cmd == "list")
        showPatientListCmd(priQueue);
    else if (cmd == "load")
        execCommandsFromFileCmd(line, priQueue);
    else if (cmd == "size")
        showHeapSizeCmd(priQueue);
    else if(cmd == "save")
        SavePatientList(line, priQueue);
    else if (cmd == "quit")
        return false;
    else
        cout << "Error: unrecognized command: " << cmd << endl;
    return true;
}

void addPatientCmd(string line, PatientPriorityQueue &priQueue) {
    string priority, name;
    // get priority and name
    priority = delimitBySpace(line);
    if (priority.length() == 0) {
        cout << "Error: no priority code given.\n";
        return;
    }
    name = line;
    if (name.length() == 0) {
        cout << "Error: no patient name given.\n";
        return;
    }

    int code = 0;
    if(priority == "immediate")
        code = 1;
    if(priority == "emergency")
        code = 2;
    if(priority == "urgent")
        code = 3;
    if(priority == "minimal")
        code = 4;

    if(code != 0){
        Patient patient(name, code);
        stringstream ss;
        priQueue.add(patient);
        ss << "Added patient " << '"'<< patient.getName() << '"' << " to the priority system";
        cout << ss.str();
    }else{
        cout << "enter correct priority code"<< endl;
    }
}

/*
 * ********** EXTRA CREDIT WORKS***************************************
 * Update Patient 's priority code
 */
void UpdatePatientPriorityCode(string line, PatientPriorityQueue &priQueue){
    string priority, arrivalNumber;
    // get priority and arrival number
    arrivalNumber = delimitBySpace(line);
    if (arrivalNumber.length() == 0) {
        cout << "Error: no patient id provided.\n";
        return;
    }
    priority = line;
    if (priority.length() == 0) {
        cout << "Error: no priority code given.\n";
        return;
    }

    int code = 0;
    if(priority == "immediate")
        code = 1;
    if(priority == "emergency")
        code = 2;
    if(priority == "urgent")
        code = 3;
    if(priority == "minimal")
        code = 4;
    //convert input arrival number into integer
    int patientNumber = stoi(arrivalNumber);
    string patientName = priQueue.getPatientName(patientNumber);

    if(patientName != ""){
        if(code != 0){
            priQueue.updatePatientPriorityCode(patientNumber, code);
            stringstream ss;
            ss << "Change patient " << '"'<< patientName << '"' <<"'s priority to " << priQueue.getPatientPriorityCode(patientNumber) << endl;
            cout << ss.str();
        }else{
            cout << "enter correct priority code"<< endl;

        }
    }else{
        stringstream ss;
        ss << "Error: no patient with the given id was found " << endl;
        cout << ss.str();
    }
}

/*
 * ********** EXTRA CREDIT WORKS***************************************
 * Save patient list to a text file
 */
void SavePatientList (string filename, PatientPriorityQueue &priQueue){
    stringstream ss;
    fstream fileStream;
    ofstream file;
    ifstream input;
    input.open(filename, ios::app);
    file.open(filename);
    for(int i = 1; i <= priQueue.Size(); i++){
        ss << "add " << priQueue.getPatientPriorityCode(i) << " " << priQueue.getPatientName(i) + "\n";
    }
    string inputLines = ss.str();
    if(input.is_open()){
        file << inputLines;
    }
    input.close();
    file.close();
    cout << "Saved " << priQueue.Size() << " to file " << filename << endl;
}
void showHeapSizeCmd(PatientPriorityQueue &priQueue){
    cout << priQueue.Size() << endl;
}

void peekNextCmd(PatientPriorityQueue &priQueue) {
    string patient = priQueue.peek();
    cout << patient << endl;
}
void removePatientCmd(PatientPriorityQueue &priQueue) {
    cout << priQueue.remove();
}

void showPatientListCmd(PatientPriorityQueue &priQueue) {

    cout << "# patients waiting: " << priQueue.Size() << endl;
    cout << "  Arrival #   Priority Code   Patient Name\n"
         << "+-----------+---------------+--------------+\n";
    cout << priQueue.to_string();
}

void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue) {
    ifstream infile;
    string line;

    // open and read from file
    infile.open(filename);
    if (infile) {
        while (getline(infile, line)) {
            cout << "\ntriage> " << line;
            // process file input
            processLine(line, priQueue);
        }
    } else {
        cout << "Error: could not open file.\n";
    }
    // close file
    infile.close();
}

//string delimitBySpace(string &s) {
string delimitBySpace(string &s) {
    unsigned pos = 0;
    char delimiter = ' ';
    string result = "";

    pos = s.find(delimiter);
    if (pos != string::npos) {
        result = s.substr(0, pos);
        s.erase(0, pos + 1);
    }
    return result;
}

void welcome() {

    cout << "************************************************************"<< endl;
    cout << "*    David 's Extra credit works                           *"<< endl;
    cout << "*                                                          *"<< endl;
    cout << "*    1 - Extra credit: update patient 's priority code     *"<< endl;
    cout << "*    2 - Extra credit: save patient list into a text file  *"<< endl;
    cout << "************************************************************"<< endl;
    
    cout << "************************************************************"<< endl;
    cout << "*    Welcome to patient priority and waiting list system   *"<< endl;
    cout << "*                                                          *"<< endl;
    cout << "*     to learn all commands of the system type 'help'      *"<< endl;
    cout << "*   (if you are running this system on windows machine)    *"<< endl;
    cout << "* then hit 'space' key then hit 'enter'(no space on linux) *"<< endl;
    cout << "*     -because of how the system work, any command:        *"<< endl;
    cout << "*   'help', 'next', 'list' will be required hit space key  *"<< endl;
    cout << "*                 before hit enter key                     *"<< endl;
    cout << "************************************************************"<< endl;
}

void goodbye() {

    exit(0);
}

void help() {
    cout << "add <priority-code> <patient-name>\n"
         << "            Adds the patient to the triage system.\n"
         << "            <priority-code> must be one of the 4 accepted priority codes:\n"
         << "                1. immediate 2. emergency 3. urgent 4. minimal\n"
         << "            <patient-name>: patient's full legal name (may contain spaces)\n"
         << "next        Announces the patient to be seen next. Takes into account the\n"
         << "            type of emergency and the patient's arrival order.\n"
         << "peek        Displays the patient that is next in line, but keeps in queue\n"
         << "list        Displays the list of all patients that are still waiting\n"
         << "            in the order that they have arrived.\n"
         << "load <file> Reads the file and executes the command on each line\n"
         << "help        Displays this menu\n"
         << "quit        Exits the program\n";
}
