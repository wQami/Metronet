#include "Station.h"




//_________________ Construct & Deconstruct _________________//
Station::Station() {bezoeken = 0;bezet = false;bezetting = 0;}
Station::Station(const string &naam) : Naam(naam){bezoeken = 0;bezet = false;bezetting = 0;}
Station::Station(const string &naam, const vector<Spoor *> &sporen, const string &type) : Naam(naam), Sporen(sporen),type(type) {bezoeken = 0;bezet = false;bezetting = 0;}
Station::~Station() {for (vector<Spoor *>::iterator spoorPtr = Sporen.begin(); spoorPtr != Sporen.end(); ++spoorPtr) {delete *spoorPtr;}}

Metrostation::Metrostation() {}
Metrostation::Metrostation(const string &naam) : Station(naam) {setType("Metrostation");}
Metrostation::Metrostation(const string &naam, const vector<Spoor *> &sporen, const string &type) : Station(naam,sporen,type) {}
Metrostation::~Metrostation() {}

Halte::Halte() {}
Halte::Halte(const string &naam) : Station(naam) {setType("Halte");}
Halte::Halte(const string &naam, const vector<Spoor *> &sporen, const string &type) : Station(naam, sporen, type) {}
Halte::~Halte() {}





//_________________ Simulate _________________//
bool Station::allowed(string tramType) {
    return false;
}
bool Metrostation::allowed(string tramType) {
    return true;
}
bool Halte::allowed(string tramType) {
    return tramType == "PCC";
}
Spoor* Station::getSpoor(int lijn) {
    for (vector<Spoor *>::iterator spoorPtr = Sporen.begin(); spoorPtr != Sporen.end(); ++spoorPtr) {
        if((*spoorPtr)->getSpoorNr() == lijn){
            return *spoorPtr;
        }
    }
    return NULL;
}





//_________________ Input _________________//
bool Station::initializedCorrectly() {
    return !Sporen.empty() && Naam != "" && type != "";
}





//_________________ Output _________________//
void Station::incrementBezoeken() {
    bezoeken++;
}
void Station::incrementBezetting() {
    bezetting++;
}





//_________________ Getters & Setters _________________//
const string &Station::getNaam() const {
    return Naam;
}
void Station::setNaam(const string &naam) {
    Naam = naam;
}
const vector<Spoor *> &Station::getSporen() const {
    return Sporen;
}
void Station::setSporen(const vector<Spoor *> &sporen) {
    Sporen = sporen;
}
const string &Station::getType() const {
    return type;
}
void Station::setType(const string &Type) {
    type = Type;
}
int Station::getBezoeken() const {
    return bezoeken;
}
void Station::setBezoeken(int Bezoeken) {
    Station::bezoeken = Bezoeken;
}
int Station::getBezetting() const {
    return bezetting;
}
void Station::setBezetting(int Bezetting) {
    Station::bezetting = Bezetting;
}
bool Station::isBezet() const {
    return bezet;
}
void Station::setBezet(bool Bezet) {
    Station::bezet = Bezet;
}