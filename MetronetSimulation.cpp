#include <sstream>
#include "MetronetSimulation.h"
#include "iostream"

using namespace std;


//_________________________ Construct _________________________//
MetronetSimulation::MetronetSimulation() {runtime = 0;}




//_________________________ Simulate _________________________//
string MetronetSimulation::operator>>(int tijd) {

    Station* currentStation = NULL;
    Station* nextAllowedStation = NULL;
    string Log;
    string lijnNr;
    string voertuig;
    Spoor* nextSpoor;
    Tram* nextTram;
    bool nextTramMoved;

    while(tijd > 0){

        //// Time in logbook ////
        ostringstream time;
        time << runtime%24;
        string Time = time.str();

        int i;
        std::istringstream(Time) >> i;

        Time = (i < 10) ? "0" + Time : Time;

        Log += (runtime != 0) ? "\t ╠══════════════╧═══════════════════════╣\n" : "";
        Log += "\t ║\t\t\t\t   "+ Time+":00"+"\t\t\t\t║\n";
        Log += "\t ╠══════════════╤═══════════════════════╣\n";


        //// Move every tram ////
        for(long long unsigned int t = 0; t<Trams.size() ; t++){
            // Get Next Station which is allowed on the Track
            currentStation = Trams[t]->getHuidige();
            nextAllowedStation = currentStation;
            do{
                nextSpoor = nextAllowedStation->getSpoor(Trams[t]->getLijn());
                REQUIRE(nextSpoor, "lijn is not allowed on Spoor (check XML file)");
                nextAllowedStation = nextSpoor->getVolgende();
            }while(!nextAllowedStation->allowed(Trams[t]->getType()));
            nextSpoor = nextAllowedStation->getSpoor(Trams[t]->getLijn());

            // Go to Next Station
            nextTram = getTramFromStation(Trams[t]->getLijn(), nextAllowedStation);
            nextTramMoved = (nextTram) ? nextTram->hasItMoved() : false;
            if(Trams[t]->goTo(nextAllowedStation, nextTramMoved)){
                nextAllowedStation->setBezet(true);
                nextSpoor->setBezet(true);

                // Write Log
                string panne;
                ostringstream LijnNr;
                LijnNr << Trams[t]->getLijn();
                lijnNr = LijnNr.str();
                ostringstream Voertuig;
                Voertuig << Trams[t]->getVoertuigNr();
                voertuig = Voertuig.str();
                if(Trams[t]->getType()== "PCC" and Trams[t]->isInPanne()){
                    panne =  "\tvoertuig " + voertuig + " valt in panne";
                }
                Log += "\t ║ Tram " + lijnNr + " nr " + voertuig + " │ Station " + currentStation->getNaam() + " ► Station " + nextAllowedStation->getNaam() + " ║" + panne + "\n";
            }
            Trams[t]->moved(true);
        }
        for(long long unsigned int t = 0; t<Trams.size() ; t++){
            Trams[t]->moved(false);
        }

        //// Bezettingsgraad ////
        for(long long unsigned int s = 0; s<Stations.size() ; s++) {
            currentStation = Stations[s];
            if(currentStation->isBezet()){
                currentStation->setBezet(false);
                currentStation->incrementBezetting();
                for(long long unsigned int sp = 0; sp < currentStation->getSporen().size(); sp++){
                    nextSpoor = currentStation->getSporen()[sp];
                    if(nextSpoor->isBezet()){
                        nextSpoor->setBezet(false);
                        nextSpoor->incrementBezetting();
                    }
                }
            }
        }
        runtime++;
        tijd--;
    }
    return Log;
}



string MetronetSimulation::operator>(const int lijn) {
    vector<Tram*> trams = getLijnTrams(lijn);
    REQUIRE(!trams.empty(),"Tram(s) does(do) not exist");
    Station* currentStation = NULL;
    Station* nextAllowedStation = NULL;
    Spoor* nextSpoor;
    Tram* nextTram;
    bool nextTramMoved;
    string lijnNr;
    string voertuig;

    //// Time in logbook ////
    ostringstream time;
    time << runtime%24;
    string Time = time.str();
    int i;
    std::istringstream(Time) >> i;

    Time = (i < 10) ? "0" + Time : Time;
    string Log = (runtime != 0) ? "\t ╠══════════════╧═══════════════════════╣\n" : "";
    Log += "\t ║\t\t\t\t   "+ Time+":00"+"\t\t\t\t║\n";
    Log += "\t ╠══════════════╤═══════════════════════╣\n";

    //// Move every tram with lijn ////
    for(long long unsigned int t = 0; t<trams.size() ; t++){
        currentStation = trams[t]->getHuidige();
        nextAllowedStation = currentStation;

        // Get Next Station which is allowed on the Track
        do{
            nextSpoor = nextAllowedStation->getSpoor(trams[t]->getLijn());
            REQUIRE(nextSpoor, "lijn is not allowed on Spoor (check XML file)");
            nextAllowedStation = nextSpoor->getVolgende();
        }while(!nextAllowedStation->allowed(trams[t]->getType()));
        nextSpoor = nextAllowedStation->getSpoor(trams[t]->getLijn());

        // Go to Next Station
        nextTram = getTramFromStation(trams[t]->getLijn(), nextAllowedStation);
        nextTramMoved = (nextTram) ? nextTram->hasItMoved() : false;
        if(trams[t]->goTo(nextAllowedStation, nextTramMoved)){
            nextAllowedStation->setBezet(true);
            nextSpoor->setBezet(true);

            // Write Log
            string panne;
            ostringstream LijnNr;
            LijnNr << trams[t]->getLijn();
            lijnNr = LijnNr.str();
            ostringstream Voertuig;
            Voertuig << trams[t]->getVoertuigNr();
            voertuig = Voertuig.str();
            if(trams[t]->getType()== "PCC" and trams[t]->isInPanne()){
                panne =  "\tvoertuig " + voertuig + " valt in panne";
            }
            Log += "\t ║ Tram " + lijnNr + " nr " + voertuig + " │ Station " + currentStation->getNaam() + " ► Station " + nextAllowedStation->getNaam() + " ║" + panne + "\n";
        }
        trams[t]->moved(true);
    }
    for(long long unsigned int t = 0; t<trams.size() ; t++){
        trams[t]->moved(false);
    }

    //// Bezettingsgraad ////
    for(long long unsigned int s = 0; s<Stations.size() ; s++) {
        currentStation = Stations[s];
        if(currentStation->isBezet()){
            currentStation->setBezet(false);
            currentStation->incrementBezetting();
            for(long long unsigned int sp = 0; sp < currentStation->getSporen().size(); sp++){
                nextSpoor = currentStation->getSporen()[sp];
                if(nextSpoor->isBezet()){
                    nextSpoor->setBezet(false);
                    nextSpoor->incrementBezetting();
                }
            }
        }
    }
    runtime++;
    return Log;
}

string MetronetSimulation::operator^(const int voertuigNr) {
    Tram* tramWithNr = getTramByNr(voertuigNr);
    REQUIRE(tramWithNr, "Tram does not exist");
    Station* currentStation = NULL;
    Station* nextAllowedStation = NULL;
    Spoor* nextSpoor;
    Tram* nextTram;
    bool moved;
    string lijnNr;
    string voertuig;


    ostringstream time;
    time << runtime%24;
    string Time = time.str();
    int i;
    std::istringstream(Time) >> i;

    Time = (runtime < 10) ? "0" + Time : Time;
    string Log = (i != 0) ? "\t ╠══════════════╧═══════════════════════╣\n" : "";
    Log += "\t ║\t\t\t\t   "+ Time+":00"+"\t\t\t\t║\n";
    Log += "\t ╠══════════════╤═══════════════════════╣\n";

    currentStation = tramWithNr->getHuidige();
    nextAllowedStation = currentStation;

    // Get Next Station which is allowed on the Track
    do{
        nextSpoor = nextAllowedStation->getSpoor(tramWithNr->getLijn());
        REQUIRE(nextSpoor, "lijn is not allowed on Spoor (check XML file)");
        nextAllowedStation = nextSpoor->getVolgende();
    }while(!nextAllowedStation->allowed(tramWithNr->getType()));
    nextSpoor = nextAllowedStation->getSpoor(tramWithNr->getLijn());

    // Go to Next Station
    nextTram = getTramFromStation(tramWithNr->getLijn(), nextAllowedStation);
    moved = (nextTram) ? nextTram->hasItMoved() : false;
    if(tramWithNr->goTo(nextAllowedStation, moved)){
        //// Bezettingsgraad ////
        nextAllowedStation->incrementBezetting();
        nextSpoor->incrementBezetting();

        // Write Log
        string panne;
        ostringstream LijnNr;
        LijnNr << tramWithNr->getLijn();
        lijnNr = LijnNr.str();
        ostringstream Voertuig;
        Voertuig << tramWithNr->getVoertuigNr();
        voertuig = Voertuig.str();
        if(tramWithNr->getType()== "PCC" and tramWithNr->isInPanne()){
            panne =  "\tvoertuig " + voertuig + " valt in panne";
        }
        Log += "\t ║ Tram " + lijnNr + " nr " + voertuig + " │ Station " + currentStation->getNaam() + " ► Station " + nextAllowedStation->getNaam() + " ║" + panne + "\n";
    }
    runtime++;
    return Log;
}



//_________________________ Clearing _________________________//
void MetronetSimulation::clear() {
    for(long long unsigned int t = 0; t < Trams.size() ; t++){
        delete Trams[t];
    }
    Trams.clear();
    for(long long unsigned int t = 0; t < Stations.size() ; t++){
        delete Stations[t];
    }
    Stations.clear();
    runtime = 0;

    ENSURE(Stations.empty(),"Could not clear Stations");
    ENSURE(Trams.empty(),"Could not clear Trams");
}




//_________________________ Getters & Setters _________________________//
vector<Tram *> MetronetSimulation::getLijnTrams(int lijn) {
    vector<Tram*> trams;
    for(long long unsigned int t = 0; t < Trams.size() ; t++){
        if(Trams[t]->getLijn() == lijn){
            trams.push_back(Trams[t]);
        }
    }
    return trams;
}
Tram *MetronetSimulation::getTramByNr(int voertuigNr) {
    for(long long unsigned int i = 0; i < Trams.size(); i++){
        if(Trams[i]->getVoertuigNr() == voertuigNr){
            return Trams[i];
        }
    }
    return NULL;
}
vector<Tram *> MetronetSimulation::getTrams() const {
    return Trams;
}
void MetronetSimulation::setTrams(const vector<Tram *> &trams) {
    Trams = trams;
    ENSURE(Trams == trams,"System could not set trams");
}
void MetronetSimulation::setStations(const vector<Station *> &stations) {
    Stations = stations;
    ENSURE(Stations == stations,"System could not set stations");
}
vector<Station *> MetronetSimulation::getStations() const {
    return Stations;
}
int MetronetSimulation::getRuntime() const {
    return runtime;
}
void MetronetSimulation::setRuntime(int Runtime) {
    MetronetSimulation::runtime = Runtime;
    ENSURE(runtime == Runtime,"System could not set runtime");
}

Tram *MetronetSimulation::getTramFromStation(int lijn, Station *station) {
    vector<Tram*> trams = getLijnTrams(lijn);
    for(long long unsigned int t = 0; t < trams.size() ; t++){
        if(trams[t]->getHuidige() == station){
            return trams[t];
        }
    }
    return NULL;
}

void MetronetSimulation::addStations(const vector<Station *> &stations){
    int prevSize = Stations.size();
    Stations.insert(Stations.end(), stations.begin(), stations.end());
    ENSURE(prevSize + stations.size() == Stations.size(), "System could not add stations");
}

void MetronetSimulation::addTrams(const vector<Tram *> &trams) {
    int prevSize = Trams.size();
    Trams.insert(Trams.end(), trams.begin(), trams.end());
    ENSURE(prevSize + trams.size() == Stations.size(), "System could not add Trams");
}



