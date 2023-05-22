#include "Tram.h"
#include "MetronetSimulation.h"




//__________ Construct & Deconstruct __________//
Tram::Tram() {}
Tram::Tram(int lijn, const string &type, Station *huidige, int voertuigNr) : Lijn(lijn), type(type), Huidige(huidige),VoertuigNr(voertuigNr) {hasMoved = false;}
Tram::~Tram() {}

Stadslijner::Stadslijner() {}
Stadslijner::Stadslijner(int lijn, const string &type, Station *huidige, int voertuigNr) : Tram(lijn, type, huidige,voertuigNr) {}
Stadslijner::~Stadslijner() {}

Albatros::Albatros(){}
Albatros::Albatros(int lijn, const string &type, Station *huidige, int voertuigNr) : Tram(lijn, type, huidige,voertuigNr) {}
Albatros::~Albatros() {}

PCC::PCC() {}
PCC::PCC(int lijn, const string &type, Station *huidige, int voertuigNr, int reparatieKost, int reparatieTijd, int defectenLimiet) : Tram(lijn, type, huidige, voertuigNr),reparatieKost(reparatieKost),kost(0),reparatieTijd(reparatieTijd),reparatieProgress(0),defecten(0),defectenLimiet(defectenLimiet),inPanne(false) {}
PCC::PCC(int lijn, const string &type, Station *huidige, int voertuigNr) : Tram(lijn, type, huidige, voertuigNr) {}
PCC::~PCC() {}





//_________________ Output _________________//
int Tram::getSnelheid() const {
    return 0;
}
int PCC::getSnelheid() const {
    return 40;
}
int Albatros::getSnelheid() const {
    return 70;
}
int Stadslijner::getSnelheid() const {
    return 70;
}





//___________ Getters and Setters ___________//

// Tram
int Tram::getLijn() const {
    return Lijn;
}
void Tram::setLijn(int lijn) {
    Lijn = lijn;
}
const string &Tram::getType() const {
    return type;
}
void Tram::setType(const string &Type) {
    Tram::type = Type;
}
Station *Tram::getHuidige() const {
    return Huidige;
}
int Tram::getVoertuigNr() const {
    return VoertuigNr;
}
void Tram::setVoertuigNr(int voertuigNr) {
    VoertuigNr = voertuigNr;
}
void Tram::setHuidige(Station *huidige) {
    Huidige = huidige;
}
bool Tram::hasItMoved() const {
    return hasMoved;
}
void Tram::moved(bool HasMoved) {
    Tram::hasMoved = HasMoved;
}
int Tram::getReparatieKost() const {return 0;}
void Tram::setReparatieKost(int reparatieKost) {}
int Tram::getKost() const {return 0;}
void Tram::setKost(int kost) {}
int Tram::getReparatieTijd() const {return 0;}
void Tram::setReparatieTijd(int reparatieTijd) {}
int Tram::getReparatieProgress() const {return 0;}
void Tram::setReparatieProgress(int reparatieProgress) {}
int Tram::getDefecten() const {return 0;}
void Tram::setDefecten(int defecten) {}
int Tram::getDefectenLimiet() const {return 0;}
void Tram::setDefectenLimiet(int defectenLimiet) {}
bool Tram::isInPanne() const {return false;}
void Tram::setInPanne(bool inPanne) {}

// PCC
int PCC::getReparatieKost() const {
    return reparatieKost;
}
void PCC::setReparatieKost(int ReparatieKost) {
    PCC::reparatieKost = ReparatieKost;
}
int PCC::getKost() const {
    return kost;
}
void PCC::setKost(int Kost) {
    PCC::kost = Kost;
}
int PCC::getReparatieTijd() const {
    return reparatieTijd;
}
void PCC::setReparatieTijd(int ReparatieTijd) {
    PCC::reparatieTijd = ReparatieTijd;
}
int PCC::getReparatieProgress() const {
    return reparatieProgress;
}
void PCC::setReparatieProgress(int ReparatieProgress) {
    PCC::reparatieProgress = ReparatieProgress;
}
int PCC::getDefecten() const {
    return defecten;
}
void PCC::setDefecten(int Defecten) {
    PCC::defecten = Defecten;
}
int PCC::getDefectenLimiet() const {
    return defectenLimiet;
}
void PCC::setDefectenLimiet(int DefectenLimiet) {
    PCC::defectenLimiet = DefectenLimiet;
}
bool PCC::isInPanne() const {
    return inPanne;
}
void PCC::setInPanne(bool InPanne) {
    PCC::inPanne = InPanne;
}





//_________________ Simulate _________________//
bool Tram::goTo(Station *volgende, bool nextTramMoved){
    Huidige = volgende;
    return true;
}
bool PCC::goTo(Station *volgende, bool nextTramMoved) {
    // Next Spoor is not empty or
    if(!volgende->getSpoor(getLijn())->isEmpty() or nextTramMoved){
        if(inPanne){
            reparatieProgress++;
            if(reparatieProgress >= reparatieTijd){
                inPanne = false;
                kost+=reparatieKost;
                defecten = 0;
            }
        }
        return false;
    }else if(!inPanne){
        getHuidige()->getSpoor(getLijn())->setEmpty(true);
        volgende->getSpoor(getLijn())->setEmpty(false);
        volgende->getSpoor(getLijn())->incrementBezoeken();
        volgende->incrementBezoeken();
        setHuidige(volgende);
        defecten++;
        if(defecten >= defectenLimiet){
            inPanne = true;
            reparatieProgress = 0;
        }
        return true;
    }else{
        reparatieProgress++;
        if(reparatieProgress >= reparatieTijd) {
            inPanne = false;
            kost += reparatieKost;
            defecten = 0;
        }
        return false;
    }
}
bool Albatros::goTo(Station *volgende, bool nextTramMoved) {
    // Next Spoor is not empty or
    if(!volgende->getSpoor(getLijn())->isEmpty() or nextTramMoved){
        return false;
    }else{
        getHuidige()->getSpoor(getLijn())->setEmpty(true);
        volgende->getSpoor(getLijn())->setEmpty(false);
        volgende->getSpoor(getLijn())->incrementBezoeken();
        volgende->incrementBezoeken();
        setHuidige(volgende);
        return true;
    }
}
bool Stadslijner::goTo(Station *volgende, bool nextTramMoved) {
    // Next Spoor is not empty or
    if (!volgende->getSpoor(getLijn())->isEmpty() or nextTramMoved) {
        return false;
    } else {
        getHuidige()->getSpoor(getLijn())->setEmpty(true);
        volgende->getSpoor(getLijn())->setEmpty(false);
        volgende->getSpoor(getLijn())->incrementBezoeken();
        volgende->incrementBezoeken();
        setHuidige(volgende);
        return true;
    }
}