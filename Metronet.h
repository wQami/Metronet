#ifndef METRONET_H
#define METRONET_H

#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>

#include "tinyxml/tinyxml.h"
#include "DesignByContract.h"

#include "Spoor.h"
#include "Station.h"
#include "Tram.h"
#include "MetronetParser.h"
#include "MetronetOutput.h"
#include "MetronetSimulation.h"

class Metronet {
public:
////_____________________________ Constructing / Initialzing _____________________________////
    Metronet(const vector<Station*> &stations, const vector<Tram*> &trams);
    /*
    Load a premade list of Stations and Trams in Metronet without needing an input file.
    Parameter: list of station and list of trams

    ENSURE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.")
    */
    Metronet();
    /*
    Creates an empty Metronet

    ENSURE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.");
    */
    explicit Metronet(string filename);
    /*
    Load file with given filename into a new metronet
    Parameter: filename

    ENSURE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.")
    */





////__________________________________ Deconstructing  __________________________________////
    void reset();
    /*
    Removes all stations and trams, resets the current time

    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.")
    */
    virtual ~Metronet();
    /*
    deletes the metronet

    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.")
    */





////________________________________________ Input ________________________________________////
    void load(string filename);
    /*
    load file with given filename into this metronet
    Parameter: filename

    REQUIRE(this->properlyInitialized(),"The Metronet is not properly initialized, please try something else.")
    */




    ////___________________________________ Simulation ___________________________________////
    void drive(const int nr);
    /*
    move Tram with nr to move to next station if allowed
    Parameter: voeruigNr

    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.")
    */
    void move(const int lijn);
    /*
    Move desired tramlijn to their next stations if allowed.
    Parameters: lijn number

    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.");
    */
    void run();
    /*
    Move all trams to next station if allowed.

    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.")
    */

    void drive(const int nr, const int tijd);
    /*
    Automate simulation of Tram with nr for a given amount of time
    Parameter: voeruigNr, the automation time

    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.")
    REQUIRE(tijd > 1,"invalid duration")
    */
    void move(const int lijn, const int tijd);
    /*
    Automate the simulation of desired tramlijn for given amount of time.
    Parameters: lijn number, the automation time

    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.")
    REQUIRE(tijd > 1,"invalid duration")
    */
    void run(const int tijd);
    /*
    Automate the simulation for a given amount of time
    Parameter: the automation time

    REQUIRE(this->properlyInitialized(), "The Metronet is not properly initialized, please try something else.")
    REQUIRE(tijd > 1,"invalid duration")
    */





    ////________________________________________ Output ________________________________________////
    void write();
    /*
    Writes an Overview File, a Logbook File and a position File

    REQUIRE(this->properlyInitialized(),"The Metronet is not properly initialized, please try something else.")
    */
    void overview();
    /*
    Writes an Overview File

    REQUIRE(this->properlyInitialized(),"The Metronet is not properly initialized, please try something else.")
    */
    void logbook();
    /*
    Writes a Logbook File

    REQUIRE(this->properlyInitialized(),"The Metronet is not properly initialized, please try something else.")
    */
    void position();
    /*
    Writes a Postion File

    REQUIRE(this->properlyInitialized(),"The Metronet is not properly initialized, please try something else.")
    */
    void information();
    /*
    Write a static Information file

    REQUIRE(this->properlyInitialized(),"The Metronet is not properly initialized, please try something else.")
    */
    void railnet();
    /*
    Write an Advanced file

    REQUIRE(this->properlyInitialized(),"The Metronet is not properly initialized, please try something else.")
    */





private:
    //_______________________________ Input _______________________________//
    MetronetParser input;
    //_______________________________ Output ______________________________//
    MetronetOutput output;
public:
    const MetronetOutput &getOutput() const;

private:
    //____________________________ Simulation _____________________________//
    MetronetSimulation simulation;
    //______________________________ Control ______________________________//
    Metronet* initCheck;
    bool properlyInitialized();
};


#endif //METRONET_H
