#include "HabitOp.h"
#include "Habit.h"
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <direct.h>
#include <stdio.h>
using namespace std;

HabitOp::HabitOp()
{
}

/*
*                       !!! Failed, reason : something about file streams code prevents something
                            So, you have to manually edit the lines in addHabit and updateHabitFile functions !!!
*   Seems useless but, In case I decided to change the order of attrs in the line or added, removed or modified one of them
*   I won't have to change every line that writes, I'll change it only once
*/
/*void HabitOp::addHabitLine(Habit h, fstream f) {
    f << h.getName() << "*" << h.getStartDate() << "*" << h.getQuestion() << "*" << h.getDescription() << "*" << h.getGrace() << "#" << endl;
}*/

/*
*   Take habit object from the interface
*   add a logFile for that habit
*   append the habit to the dictionary
*/
void HabitOp::addHabit(Habit h) {
    //Creating the log file for the habit (recording days)
    mkdir("logs");
    string fileName = "logs\\" + h.getName();
    fstream f(fileName.c_str(),ios::app | ios::out);
    f.close();
    //Adding the habit to the dictionary
    f.open(dict.c_str(),ios::app | ios::out);
    f << h.getName() << "*" << h.getStartDate() << "*" << h.getQuestion() << "*" << h.getDescription() << "*" << h.getGrace() << "#" << endl;
    f.close();
    //Appending a score record for the habit
    f.open("score", ios::app | ios::out);
    // formula : Name*highestScore*lowestScore*bestInterval*worstInterval*highestInWeek*lowestInWeek*highestInMonth*lowestInMonth#
    // default : Name*-9999999*9999999*0*0*-9999999*9999999*-9999999*9999999#
    f << h.getName() << "*-9999999*9999999*0*0*-9999999*9999999*-9999999*9999999#" << endl;
}

/*
*   function takes the name of the habit and returns the line number of the habit in first of pair (int)
*   and returns the habit object itself second of pair (Habit)
*   if the habit was not found it returns -1 as first
*   !!! remember to overload it to use more options to search !!!
*/
pair<int,Habit> HabitOp::searchAndGetHabit(string habitName) {
    // open the file and search
    cout << "searching for \"" << habitName << "\"" << endl;
    pair<int,Habit> theWanted;
    string fullLine, namePart;
    fstream f(dict.c_str(), ios::in);
    string name, question, description, startDate,graceStr;
    int grace,line = 0;
    bool found = false; // found flag
    while (getline(f,name,'*') && getline(f,startDate,'*') && getline(f,question,'*')
            && getline(f,description,'*') && getline(f,graceStr,'#') && f.get()) {
            line ++;
    // found and assign values to object
        cout << "now at\"" << name  << "\"\n";
            if(name == habitName) {
                    cout << "true" << endl;
                    found = true;
                    Habit amy;
                    stringstream ss(graceStr);
                    ss >> grace;
                    amy.setName(name);
                    amy.setStartDate(startDate);
                    amy.setQuestion(question);
                    amy.setDescription(description);
                    amy.setGrace(grace);
                    theWanted.first = line;
                    theWanted.second = amy;
                    break;
            }
    }
    if (!found) //it's obvious dummy
        theWanted.first = -1;
    return theWanted;
}


/*
*   string : habitName which you can get from selected in list in the Gui
*   newObject : the newObject after editing the old one in the edit interface
*   option : whether to edit or delete -> 1 means delete , other means just edit
*/
void HabitOp::updateHabitFile(string habitName, Habit newObject, int option) {
    ifstream is(dict.c_str());
    ofstream os("tmp");
    pair<int,Habit> found = searchAndGetHabit(habitName);
    string line;
    int number = 0;
    Habit x = found.second;
    cout << "found : " << x.getName() << "\nAt :" << found.first << endl;
    // creating the tmp file with the new edited value
    while (getline(is,line)) {
        ++ number;
        if (number == found.first) {
            if (option == 1) {
                continue;
            }
        else{
            os << newObject.getName() << "*" << newObject.getStartDate() << "*" << newObject.getQuestion() << "*" << newObject.getDescription() << "*" << newObject.getGrace() << "#" << endl;
        }
        }else {
            os << line << endl;
        }
    }
    is.close();
    os.close();

// Sending out dear data back home and delete tmp
    // reversing the process
    os.open(dict.c_str());
    is.open("tmp");
    while (getline(is,line)) {
        os << line << endl;
    }
    os.close();
    is.close();
//removing tmp file, bye bye
    mkdir("tmp");
}

/*
*   Iterates the dict file and collects the names in a vector
*   So you can assign the values of this vector to list items in the Interface
*/

vector<string> HabitOp::loadHabitNames() {
    vector <string> namesList;
    string name, question, description, startDate,graceStr;
    ifstream f(dict.c_str());
     while (getline(f,name,'*') && getline(f,startDate,'*') && getline(f,question,'*')
            && getline(f,description,'*') && getline(f,graceStr,'#') && f.get()) {
            namesList.push_back(name);
        }
    f.close();
    return namesList;
}

bool HabitOp::dictIsEmpty() {
    ifstream f(dict.c_str());
    f.seekg(0,ios::end);
    return f.tellg() == 0 ? true:false;
}
