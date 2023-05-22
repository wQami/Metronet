#include "Spoor.h"




//_________________ Construct & Deconstruct _________________//
Spoor::Spoor() {
    Bezoeken = 0;
    bezet = false;
    bezetting = 0;
    empty = true;
}
Spoor::Spoor(int spoorNr, Station *volgende, Station *vorige) : spoorNr(spoorNr), Volgende(volgende), Vorige(vorige) {
    Bezoeken = 0;
    bezet = false;
    bezetting = 0;
    empty = true;
}
Spoor::~Spoor() {}




//_________________ Getters & Setter _________________//
int Spoor::getSpoorNr() const {
    return spoorNr;
}
void Spoor::setSpoorNr(int spoornr) {
    Spoor::spoorNr = spoornr;
}
Station *Spoor::getVolgende() const {
    return Volgende;
}
void Spoor::setVolgende(Station *volgende) {
    Volgende = volgende;
}
Station *Spoor::getVorige() const {
    return Vorige;
}
void Spoor::setVorige(Station *vorige) {
    Vorige = vorige;
}

int Spoor::getBezoeken() const {
    return Bezoeken;
}

void Spoor::setBezoeken(int bezoeken) {
    Bezoeken = bezoeken;
}

void Spoor::incrementBezoeken() {
    Bezoeken++;
}

bool Spoor::isBezet() const {
    return bezet;
}

void Spoor::setBezet(bool Bezet) {
    Spoor::bezet = Bezet;
}

int Spoor::getBezetting() const {
    return bezetting;
}

void Spoor::setBezetting(int Bezetting) {
    Spoor::bezetting = Bezetting;
}

void Spoor::incrementBezetting() {
    bezetting++;
}

bool Spoor::isEmpty() const {
    return empty;
}

void Spoor::setEmpty(bool Empty) {
    Spoor::empty = Empty;
}
