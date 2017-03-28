#include "habit.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
Habit::Habit() {

}

void Habit::setName(string name) {
            this->name = name;
        }
string Habit::getName() {
            return name;
        }

void Habit::setQuestion(string question) {
            this->question = question;
        }

void Habit::setDescription(string description) {
            this->description = description;
        }

void Habit::setGrace(int grace) {
            this->grace = grace;
        }

void Habit::setStartDate(string startDate) {
    this->startDate = startDate;
}

string Habit::getQuestion() {
            return question;
        }
string Habit::getDescription() {
            return description;
        }
int Habit::getGrace() {
            return grace;
        }
string Habit::getStartDate() {
       return startDate;
}
/*void Habit::setDaysUndone(int daysUndone) {
    this->daysUndone = daysUndone;
}
int Habit::getDaysUndone() {
    return daysUndone;
}*/


