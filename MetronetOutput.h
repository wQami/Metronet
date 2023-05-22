#ifndef METRONETOUTPUT_H
#define METRONETOUTPUT_H

#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>
#include <set>

#include "DesignByContract.h"

#include "Station.h"
#include "Tram.h"
#include "Spoor.h"

using namespace std;

class Tram;
class Station;
class Spoor;

class MetronetOutput {
public:
    /**
     * \page Constructor
     *
    * @brief Construct the MetronetOutput object with the specified filename.
    *
    * \description
    * Construct the Metronet output generator with the given filename, which is loaded last in Metronet.
    *
    * @param Filename The filename to be used.
    */
    explicit MetronetOutput(const string &Filename);
    /*
    Construct the Metronet output generator which needs
    parameter: Filename which is loaded last in Metronet
    */

    /**
    * \page Ouput
    *
    * @brief Writes an Overview File.
    *
    * \description
    * Writes an overview file based on the provided stations and trams.
    *
    * @param stations The vector of stations.
    * @param trams The vector of trams.
    */
    void Overview(const vector<Station*>& stations, const vector<Tram*>& trams);
    /*
    Writes an Overview File
    parameters: Stations and Trams

    REQUIRE(OverviewFile,"Failed to open Overview file.")
    ENSURE(OverviewFile.tellp() != 0, "Overview file is empty.")
    */

    /**
    * \page Ouput
    *
    * @brief Write a Logbook File.
    *
    * \description
    * Write a logbook file.
    */
    void Logbook();
    /*
    Write a Logbook File

    REQUIRE(LogbookFile, "Failed to open Overview file.")
    ENSURE(LogbookFile.tellp() != 0, "Logbook file is empty.")
    */

    /**
    * \page Ouput
    *
    * @brief Write a Position File.
    *
    * \description
    * Write a position file.
    *
    * @param stations The vector of stations.
    * @param trams The vector of trams.
    */
    void Position(const vector<Station*>& stations, const vector<Tram*>& trams);
    /*
    Write a Position File

    REQUIRE(PositionFile, "Failed to open Position file.")
    ENSURE(PositionFile.tellp() != 0, "Position file is empty.")
    */

    /**
    * \page Ouput
    *
    * @brief Write a static information file.
    *
    * \description
    * Write a static information file.
    *
    * @param stations The vector of stations.
    * @param trams The vector of trams.
    * @param runtime The runtime value.
    */
    void Information(const vector<Station*>& stations, const vector<Tram*>& trams, int runtime);
    /*
    Write a static information file

    REQUIRE(InformationFile, "Failed to open Information file.");
    ENSURE(InformationFile.tellp() != 0, "Information file is empty.");
    */

    /**
    * \page Ouput
    *
    * @brief Write an advanced output file.
    *
    * \description
    * Write an advanced output file.
    *
    * @param stations The vector of stations.
    * @param trams The vector of trams.
    */
    void Railnet(const vector<Station*>& stations, const vector<Tram*>& trams);
    /*
    Write an advanced output file

    REQUIRE(RailnetFile, "Failed to open Information file.")
    ENSURE(RailnetFile.tellp() != 0, "Advanced file is empty.")
    */

    /**
    * \page Getters and Setter
    *
    * @brief Get the filename.
    *
    * \description
    * Returns the filename associated with the MetronetOutput object.
    *
    * @return The filename.
    */
    const string &getFilename() const;
    /*
    Get Filename
    */

    /**
    * \page Getters and Setter
    *
    * @brief Set the filename.
    *
    * \description
    * Sets the filename for the MetronetOutput object.
    *
    * @param Filename The new filename to be set.
    */
    void setFilename(const string &Filename);
    /*
    set Filename
    */

    /**
    * \page Getters and Setter
    *
    * @brief Get the log.
    *
    * \description
    * Returns the log associated with the MetronetOutput object.
    *
    * @return The log.
    */
    const string &getLog() const;
    /*
    Get Log
    */

    /**
    * \page Getters and Setter
    *
    * @brief Set the log.
    *
    * \description
    * Sets the log for the MetronetOutput object.
    *
    * @param log The new log to be set.
    */
    void setLog(const string &log);
    /*
    Set Log
    */

    /**
    * \page Getters and Setter
    *
    * @brief Add to the log.
    *
    * \description
    * Appends the provided log string to the existing log.
    *
    * @param log The log string to be added.
    */
    void operator+(string log);
    /*
    Add to log
    */

    /**
    * \page Getters and Setter
    *
    * @brief Get the overview filename.
    *
    * \description
    * Returns the filename for the overview file.
    *
    * @return The overview filename.
    */
    const string &getOverviewFilename() const;
    /*
    Get overviewFilename
    */

    /**
    * \page Getters and Setter
    *
    * @brief Get the info filename.
    *
    * \description
    * Returns the filename for the information file.
    *
    * @return The info filename.
    */
    const string &getInfoFilename() const;
    /*
    Get infoFilename
    */

    /**
    * \page Getters and Setter
    *
    * @brief Get the position filename.
    *
    * \description
    * Returns the filename for the position file.
    *
    * @return The position filename.
    */
    const string &getPositionFilename() const;
    /*
    Get positionFilename
    */

    /**
    * \page Getters and Setter
    *
    * @brief Get the logbook filename.
    *
    * \description
    * Returns the filename for the logbook file.
    *
    * @return The logbook filename.
    */
    const string &getLogbookFilename() const;
    /*
    Get logbookFilename
    */

    /**
    * \page Getters and Setter
    *
    * @brief Get the railnet filename.
    *
    * \description
    * Returns the filename for the railnet file.
    *
    * @return The railnet filename.
    */
    const string &getRailnetFilename() const;
    /*
    Get railnetFilename
    */
private:
    string filename;

    string overviewFilename;
    string infoFilename;
    string positionFilename;
    string logbookFilename;
    string railnetFilename;

    string Log;
};


#endif //METRONETOUTPUT_H
