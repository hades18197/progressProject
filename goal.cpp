#include "goal.h"
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include "Cons.h"
#include <lav.h>
#include <sstream>
#include "operations.h"

using namespace std;

Goal::Goal()
{

}

int Goal::getId() const {return id;}

void Goal::setId(int value) {id = value;}

int Goal::getType() const {return type;}

void Goal::setType(int value) {type = value;}

int Goal::getScope() const {return scope;}

void Goal::setScope(int value) {scope = value;}

int Goal::getFinalGoal() const {return finalGoal;}

void Goal::setFinalGoal(int value) {finalGoal = value;}

int Goal::getLimit() const {return limit;}

void Goal::setLimit(int value) {limit = value;}

int Goal::getUnitsPerScope() const {return unitsPerScope;}

void Goal::setUnitsPerScope(int value) {unitsPerScope = value;}

int Goal::getCountOffline() const {return countOffline;}

void Goal::setCountOffline(int value) {countOffline = value;}

string Goal::getName() const {return name;}

void Goal::setName(const string &value) {name = value;}

string Goal::getUnit() const {return unit;}

void Goal::setUnit(const string &value) {unit = value;}

string Goal::getStartDate() const {return startDate;}

void Goal::setStartDate(const string &value) {startDate = value;}

string Goal::getColor() const {return color;}

void Goal::setColor(const string &value) {color = value;}

int Goal::loadId(string list) {
    int newId;
    ifstream f(list.c_str());
    string ev = "loaded id = ";
    if(!lav.emptyFile(list)) {
        string line;
        string part;
        while(getline(f,line)){
               stringstream ss(line);
               getline(ss,part,'|');
        }
        newId = op.s2i(part) + 1;
    }
    else {
        newId = 1;
    }
    f.close();
    ev += op.i2s(newId);
    ev += " from file \"" + list;
    ev += "\"";
    lav.logEvent(ev,Cons::EVENT_INFO());
    return newId;
}

void Goal::add() {
    fstream f;
    string dest;
    //Specifying a list file
    if(type == Cons::TYPE_LIMITED()) {
        dest = Cons::LGLIST();
        f.open(Cons::LGLIST(),ios::app|ios::out);
    }else if (type == Cons::TYPE_UNLIMITED()) {
        dest = Cons::LGLIST();
        f.open(Cons::UGLIST(), ios::app | ios::out);
    }
    // place to add courses else if (type == Cons::TYPE_COURSE())

    //Setting the correct Id
    this->id = loadId(dest);

    //Wrtiring to the list file
    f << this->toString() << endl;
    f.close();
    string ev = "added \"" + name;
    ev += "\" to " + dest;
    lav.logEvent(ev,Cons::EVENT_INFO());
}

// Converts a goal object to a line with delimiter (string) that can be added to a file
/////////////*! Attention ! not suitable for courses .. needs to be overrided !*////////////////

string Goal::toString() {
    string objString = "";
    objString += op.i2s(id) + '|';
    objString += name + '|';
    objString += startDate + '|';
    objString += op.i2s(scope) + '|';
    objString += op.i2s(finalGoal) + '|';
    objString += op.i2s(limit) + '|';
    objString += unit + '|';
    objString += op.i2s(unitsPerScope) + '|';
    objString += op.i2s(countOffline) + '|';
    objString += color + '#';
    return objString;
}


/* Description :
*   Fills the current object data with the wanted one,
*   returns true if found, and guess what :D false if not !
*/
bool Goal::searchAndGet(string name, int type) {
//Constructing file full path
    string fileFullPath;
    if(type == Cons::TYPE_LIMITED()) {
        fileFullPath = Cons::LGLIST();
    }
    else if (type == Cons::TYPE_UNLIMITED()) {
        fileFullPath = Cons::UGLIST();
    }
    bool found = false;
    //Preparing log event
    string ev = "Trying to get \"";
    ev += name;
    ev += "\" : ";

    if(!lav.emptyFile(fileFullPath)) {
        ifstream f(fileFullPath.c_str());
        string line;
        while (getline(f,line)) {
            stringstream ss(line);
            string part;
            getline(ss,part,'|');
            getline(ss,part,'|');
            if(part == name) {
                ss.flush();
                stringstream ss2(line);
                string tmp;
                getline(ss2,tmp,'|');
                id = op.s2i(tmp);
                getline(ss2,this->name,'|');
                getline(ss2,startDate,'|');
                getline(ss2,tmp,'|');
                scope = op.s2i(tmp);
                getline(ss2,tmp,'|');
                finalGoal = op.s2i(tmp);
                getline(ss2,tmp,'|');
                limit = op.s2i(tmp);
                getline(ss2,unit,'|');
                getline(ss2,tmp,'|');
                unitsPerScope = op.s2i(tmp);
                getline(ss2,tmp,'|');
                countOffline = op.s2i(tmp);
                getline(ss2,color,'#');
                this->type = type;
                found = true;
                break;
            }
        }

        // The boring logging part :D
        if(found){
            ev += "Sucessful .";
            lav.logEvent(ev,Cons::EVENT_INFO());
        } else {
            ev += "Failed !";
            lav.logEvent(ev,Cons::EVENT_ERROR());
        }
    }else {
        ev += "File is empty !";
        lav.logEvent(ev,Cons::EVENT_ERROR());
    }
    return found;
}

void Goal::clone(Goal &g) {
    this->id = g.id;
    this->name = g.name;
    this->startDate = g.startDate;
    this->scope = g.scope;
    this->finalGoal = g.finalGoal;
    this->limit = g.limit;
    this->unit = g.unit;
    this->unitsPerScope = g.unitsPerScope;
    this->countOffline = g.countOffline;
    this->color = g.color;
    this->type = g.type;
}

void Goal::update(Goal g, int type, int option) {
    //preparing log event string
    string opStr;
    if(option == Cons::OPTION_DELETE()) opStr = "deleting";
    else if(option == Cons::OPTION_UPDATE()) opStr = "updating";

    //reserve the oldName to search with and set object data to the new data
    string oldName = this->name;
    clone(g);

    ofstream newFile(Cons::TMP_FILE());
    string fileFullPath;
    if(type == Cons::TYPE_LIMITED()) fileFullPath = Cons::LGLIST();
    else if(type == Cons::TYPE_UNLIMITED()) fileFullPath = Cons::UGLIST();
    //place to add courses  else if (type == Cons::CLIST())

    if(!lav.emptyFile(fileFullPath)) {
        ifstream theFile(fileFullPath.c_str());
        string line;

        //Writing the temp file
        bool found = false;
        while(getline(theFile, line)) {
            stringstream ss(line);
            string tmp;
            getline(ss,tmp,'|');
            getline(ss,tmp,'|');
            if(tmp == oldName) {
                found = true;
                // To delete or not to delete, that's is the question .
                if(option == Cons::OPTION_UPDATE()) {
                    newFile << toString() << endl;
                }
                else if(option == Cons::OPTION_DELETE()) {
                    continue;
                }
            }
            else {
                newFile << line << endl;
            }
        }
        newFile.close();
        theFile.close();

        //Time to go back home Data
        newFile.open(fileFullPath.c_str());
        theFile.open(Cons::TMP_FILE());
        while (getline(theFile,line)) {
            newFile << line << endl;
        }
        newFile.close();
        theFile.close();
        remove(Cons::TMP_FILE());

        //boring logging part

        string ev = opStr + " \"" + oldName;
        ev += "\" at file \"" + fileFullPath;
        if(found) {
            ev += "\" : Successful .";
            lav.logEvent(ev,Cons::EVENT_INFO());
        }else {
            ev += "\" : Failed ! ,reason : Not Found .";
            lav.logEvent(ev,Cons::EVENT_ERROR());
        }
    } else {
        string ev = opStr + " \"" + oldName;
        ev += "\" at file \"" + fileFullPath;
        ev += "\" : Failed ! ,reason : File is Empty .";
        lav.logEvent(ev,Cons::EVENT_ERROR());
    }
}
