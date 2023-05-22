#ifndef METRONETPARSER_H
#define METRONETPARSER_H

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>
#include <map>

#include "tinyxml/tinyxml.h"
#include "DesignByContract.h"

#include "Station.h"
#include "Tram.h"



class MetronetParser {
public:
    /**
    * \page Input
    *
    * @brief Parse an XML file into the Metronet.
    *
    * \description
    * Parses the provided XML file and populates the Metronet with the extracted data,
    * including stations and trams.
    *
    * @param xml The XML content or filename to parse.
    * @param stations A reference to the vector of Station pointers where the parsed stations will be stored.
    * @param trams A reference to the vector of Tram pointers where the parsed trams will be stored.
    */
    void parse(string xml, vector<Station*> &stations,vector<Tram*> &trams);
    /*
    Parse file with given filename into this metronet
    Parameter: filename

    REQUIRE(this->properlyInitialized(),"The Metronet is not properly initialized, please try something else.")
    REQUIRE(successfulLoad, "Could not load file.")
    REQUIRE(metronet, "'Metronet' element not found in file")

    for every Station (in xml):
        REQUIRE(name, "Station is missing 'name' in XML file")
        REQUIRE(type,"Station is missing 'type' in XML file")
        REQUIRE(spoor,"Station is missing at least one 'spoor' in XML file")
        REQUIRE(Type != "Halte" or aantalSporen <= 1, "Halte cannot have more than one track.");
        for every Spoor in Tram in XML:
            REQUIRE(name, "Spoor is missing 'spoorNr' in XML file")
            REQUIRE(type,"Spoor is missing 'volgende' in XML file")
            REQUIRE(spoor,"Spoor is missing 'vorige' in XML file")
            REQUIRE(find(SpoorNrs.begin(), SpoorNrs.end(), Track->getSpoorNr()) == SpoorNrs.end(),"Spoor with certain SpoorNr occurs more than once in station in XML file")

    for every Tram (in xml):
        REQUIRE(lijnNr,"Tram is missing 'lijnNr' in XML file");
        REQUIRE(type,"Tram is missing 'type' in XML file");
        REQUIRE(voertuigNr,"Tram is missing 'voertuigNr' in XML file");
        REQUIRE(beginStation,"Tram is missing 'beginStation' in XML file");
        REQUIRE(BeginStation,"Tram's beginStation does not exist");
        REQUIRE(Type =="PCC" or Type == "Albatros" or Type == "Stadslijner","Tram type is unknown to system");
        if type == PCC:
            REQUIRE(reparatieTijd,"Tram is missing 'reparatieTijd' in XML file");
            REQUIRE(aantalDefecten,"Tram is missing 'defecten' in XML file");
            REQUIRE(reparatieKost,"Tram is missing 'reparatieKost' in XML file");
        REQUIRE(!voertuigWithNr[newTram->getVoertuigNr()], "Tram with the same voertuigNr already exists");
        REQUIRE(hasCorrespondingTrack(BeginStation,newTram),"There is no Spoor beginstation of Tram");

    ENSURE(!stations.empty(),"No stations have been added")
    ENSURE(!trams.empty(),"No trams have been added")
    */


private:
    //____________________________________________ Getter ____________________________________________//
    Station* findOrAddStation(const string& name, const string& type, vector<Station*>& stations);
    /*
    find a Station or add it to the list and return it
    REQUIRE(stationInXml,"'volgende' or 'vorige' on a Spoor of a Station is not specified in XML file");
    */
    Station* getStation(const string& name, vector<Station*>& stations);
    static string stationtypeFromDoc(const string& statName, TiXmlElement* station);
    /*
    REQUIRE(name, "Station is missing 'name' in XML file");
    if station found:
        REQUIRE(type, "Station is missing 'type' in XML file");
    */

    //____________________________________________ XML Check ____________________________________________//
    bool hasCorrespondingTrack(Station* &station, Tram* &tram);
};


#endif //METRONETPARSER_H
