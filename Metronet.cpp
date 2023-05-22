#include "Metronet.h"





//_____________________________ Constructing / Initialzing _____________________________//
Metronet::Metronet() : output(MetronetOutput("")), initCheck(this){
    ENSURE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.");
}
Metronet::Metronet(const vector<Station*> &stations, const vector<Tram*> &trams) : output(MetronetOutput("Preloaded")), initCheck(this){
    simulation.setStations(stations);
    simulation.setTrams(trams);

    ENSURE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.");
}
Metronet::Metronet(string filename) : output(MetronetOutput(filename)), initCheck(this){
    vector<Station*> Stations;
    vector<Tram*> Trams;
    input.parse(filename, Stations, Trams);
    simulation.setStations(Stations);
    simulation.setTrams(Trams);

    ENSURE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.");
}
bool Metronet::properlyInitialized() {
    return initCheck == this;
}





//__________________________________ Deconstructing  __________________________________//
void Metronet::reset() {
    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.");
    simulation.clear();
}
Metronet::~Metronet() {
    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.");
    reset();
}


//________________________________________ Input ________________________________________//
void Metronet::load(string filename) {
    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.");

    vector<Station*> Stations;
    vector<Tram*> Trams;
    input.parse(filename, Stations, Trams);
    output.setFilename(filename);

    simulation.addStations(Stations);
    simulation.addTrams(Trams);
}





//___________________________________ Simulation ___________________________________//

//// Simulate once ////
void Metronet::drive(const int nr) {
    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.");
    output+(simulation^nr);
}
void Metronet::move(const int lijn){
    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.");
    output+(simulation>lijn);
}
void Metronet::run() {
    int tijd = 1;
    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.");
    output+(simulation>>tijd);
}

//// Simulate for automation time ////
void Metronet::drive(const int nr, const int tijd) {
    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.");
    REQUIRE(tijd > 1,"invalid duration");
    for(int t = 0; t< tijd; t++){
        output+(simulation^nr);
    }
}
void Metronet::move(const int lijn, const int tijd) {
    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.");
    REQUIRE(tijd > 1,"invalid duration");
    for(int t = 0; t< tijd; t++){
        output+(simulation>lijn);
    }
}
void Metronet::run(const int tijd){
    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.");
    REQUIRE(tijd > 1,"invalid duration");
    output+(simulation>>tijd);
}





//_______________________________________ Output _______________________________________//
void Metronet::overview() {
    REQUIRE(this->properlyInitialized(),"The Metronet is not properly initialized, please try something else.");
    output.Overview(simulation.getStations(),simulation.getTrams());
}
void Metronet::logbook(){
    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.");
    output.Logbook();
}
void Metronet::position() {
    REQUIRE(this->properlyInitialized(),"The Metronet is not properly initialized, please try something else.");
    output.Position(simulation.getStations(),simulation.getTrams());
}
void Metronet::information() {
    REQUIRE(this->properlyInitialized(),"The Metronet is not properly initialized, please try something else.");
    output.Information(simulation.getStations(),simulation.getTrams(), simulation.getRuntime());
}
void Metronet::railnet() {
    REQUIRE(this->properlyInitialized(),"The Metronet is not properly initialized, please try something else.");
    output.Railnet(simulation.getStations(),simulation.getTrams());
}
void Metronet::write() {
    REQUIRE(this->properlyInitialized(),"The Metronet is not properly initialized, please try something else.");
    vector<Station*> stations = simulation.getStations();
    vector<Tram*> trams =  simulation.getTrams();
    output.Overview(stations,trams);
    output.Logbook();
    output.Position(stations,trams);
    output.Information(stations,trams, simulation.getRuntime());
    output.Railnet(stations,trams);
}

const MetronetOutput &Metronet::getOutput() const {
    return output;
}








