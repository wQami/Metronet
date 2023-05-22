#ifndef METRONETSIMULATION_H
#define METRONETSIMULATION_H

#include <string>
#include "Station.h"
#include "Spoor.h"
#include "Tram.h"

#include "DesignByContract.h"

using namespace std;

class MetronetSimulation {
public:
     /**
     * \page Construct
     *
     * @brief Construct a MetronetSimulation object.
     *
     * \description
     * Constructs a MetronetSimulation object.
     */
    MetronetSimulation();
    /*
    Construct a MetronetSimulation
    */

    /**
    * \page Simulation
    *
    * @brief Automate the simulation for a given amount of time.
    *
    * \description
    * This operator automates the simulation for the specified duration.
    *
    * @param tijd The automation time.
    * @return A string representation of the simulation output.
    *
    * @require tijd > 0, "Invalid duration"
    * @require spoor, "Lijn is not allowed on Spoor (check XML file)"
    */
    string operator>>(int tijd);
    /*
    Automate the simulation for a given amount of time
    Parameter: the automation time

    REQUIRE(tijd > 0,"invalid duration")
    REQUIRE(spoor,"lijn is not allowed on Spoor (check XML file)")
    */

    /**
    * \page Simulation
    *
    * @brief Move the desired lijn to the next station.
    *
    * \description
    * This operator moves the tram of the specified lijn to the next station.
    *
    * @param lijn The lijn number.
    * @return A string representation of the simulation output.
    *
    * @require !trams.empty(), "Tram(s) do(es) not exist"
    * @require spoor, "Lijn is not allowed on Spoor (check XML file)"
    */
    string operator>(const int lijn);
    /*
    Moves desired lijn to the next station
    Parameter: lijn number

    REQUIRE(!trams.empty(),"Tram(s) does(do) not exist")
    REQUIRE(spoor,"lijn is not allowed on Spoor (check XML file)")
    */

    /**
    * \page Simulation
    *
    * @brief Move the tram with the specified voertuigNr.
    *
    * \description
    * This operator moves the tram with the specified voertuigNr.
    *
    * @param voertuigNr The voertuigNr of the tram.
    * @return A string representation of the simulation output.
    */
    string operator^(const int voertuigNr);
    /*
    Moves desired voertuig to the next station
    Parameter: voertuig Nr

    REQUIRE(tramWithNr, "Tram does not exist");
    REQUIRE(nextSpoor, "lijn is not allowed on Spoor (check XML file)");
    */

    /**
    * \page Clearing
    *
    * @brief Clear the trams and stations.
    *
    * \description
    * This function clears the trams and stations.
    *
    * @ensure Stations.empty(), "Could not clear Stations"
    * @ensure Trams.empty(), "Could not clear Trams"
    */
    void clear();
    /*
    Clears the Trams and Stations

    ENSURE(Stations.empty(),"Could not clear Stations");
    ENSURE(Trams.empty(),"Could not clear Trams");
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the stations.
    *
    * \description
    * This function sets the stations of the MetronetSimulation.
    *
    * @param stations The vector of stations.
    *
    * @ensure Stations == stations, "System could not set stations"
    */
    void setStations(const vector<Station *> &stations);
    /*
    Sets the Stations

    ENSURE(Stations == stations,"System could not set stations");
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the stations.
    *
    * \description
    * This function returns the vector of stations.
    *
    * @return The vector of stations.
    */
    vector<Station *> getStations() const;
    /*
    Get Stations
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the trams.
    *
    * \description
    * This function sets the trams of the MetronetSimulation.
    *
    * @param trams The vector of trams.
    *
    * @ensure Trams == trams, "System could not set trams"
    */
    void setTrams(const vector<Tram *> &trams);
    /*
    Sets the Trams

    ENSURE(Trams == trams,"System could not set trams");
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the trams.
    *
    * \description
    * This function returns the vector of trams.
    *
    * @return The vector of trams.
    */
    vector<Tram *> getTrams() const;
    /*
    Get Trams
    */

    /**
    * \page Getters & Setters
    *
    * @brief Get the runtime.
    *
    * \description
    * This function returns the runtime of the simulation.
    *
    * @return The runtime.
    */
    int getRuntime() const;
    /*
    Get the runtime
    */

    /**
    * \page Getters & Setters
    *
    * @brief Set the runtime.
    *
    * \description
    * This function sets the runtime of the simulation.
    *
    * @param Runtime The runtime value.
    *
    * @ensure runtime == Runtime, "System could not set runtime"
    */
    void setRuntime(int Runtime);
    /*
    Sets the runtime

    ENSURE(runtime == Runtime,"System could not set runtime");
    */

    /**
    * \page Getters & Setters
    *
    * @brief Add stations to the existing stations.
    *
    * \description
    * This function adds stations to the existing stations in the MetronetSimulation.
    *
    * @param stations The vector of stations to be added.
    *
    * @ensure prevSize + stations.size() == Stations.size(), "System could not add stations"
    */
    void addStations(const vector<Station *> &stations);
    /*
    Sets the Stations

    ENSURE(prevSize + stations.size() == Stations.size(), "System could not add stations")
    */

    /**
    * \page Getters & Setters
    *
    * @brief Add trams to the existing trams.
    *
    * \description
    * This function adds trams to the existing trams in the MetronetSimulation.
    *
    * @param trams The vector of trams to be added.
    *
    * @ensure prevSize + trams.size() == Stations.size(), "System could not add trams"
    */
    void addTrams(const vector<Tram *> &trams);
    /*
    Sets the Stations

    ENSURE(prevSize + trams.size() == Stations.size(), "System could not add Trams")
    */

    /**
    * \page Getters & Setters
    *
    * @brief Find and return a tram with the given voertuig number.
    *
    * \description
    * This function finds and returns a tram with the specified voertuig number.
    *
    * @param voertuigNr The voertuig number of the tram.
    * @return A pointer to the tram.
    */
    Tram* getTramByNr(int voertuigNr);
    /*
    Finds and returns tram with given number
    Parameter: voertuig number
    */

private:
    //______________________________ Collection of Trams and Stations ______________________________//qw
    vector<Tram*> Trams;
    vector<Station*> Stations;
    //______________________________ Collection of Trams and Stations ______________________________//
    int runtime;
    //___________________________________________  Getter ___________________________________________//
    vector<Tram*> getLijnTrams(int lijn);
    /*
    Finds and returns trams with given lijn
    Parameter: lijn number
    */
    Tram* getTramFromStation(int lijn, Station* station);
    /*
    Gets a tram on a given station with a lijn
    Parameter: lijn and station
    */
};


#endif //METRONETSIMULATION_H
