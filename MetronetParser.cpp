#include "MetronetParser.h"

void MetronetParser::parse(string xml, vector<Station*> &stations, vector<Tram*> &trams){

    // Open document
    TiXmlDocument doc(xml.c_str());
    bool successfulLoad = doc.LoadFile();
    REQUIRE(successfulLoad, "Could not load file.");

    // Load metronet element
    TiXmlElement* metronet = doc.FirstChildElement("METRONET");
    REQUIRE(metronet, "'Metronet' element not found in file");

    // Prepare iterations
    Station* station;Station* Next;Station* Previous;Spoor* Track;
    TiXmlElement* name;TiXmlElement* type;TiXmlElement* spoor;
    TiXmlElement* spoorNr;TiXmlElement* volgende;TiXmlElement* vorige;
    string Type; int aantalSporen;

    // Iterate over stations
    for (TiXmlElement* stat = metronet->FirstChildElement("STATION"); stat; stat = stat->NextSiblingElement("STATION")){

        // Get name, type and first spoor elements out xml file
        name = stat->FirstChildElement("naam");
        type = stat->FirstChildElement("type");
        spoor = stat->FirstChildElement("SPOOR");

        // Preconditions for each Tram
        REQUIRE(name, "Station is missing 'name' in XML file");
        REQUIRE(type,"Station is missing 'type' in XML file");
        REQUIRE(spoor,"Station is missing at least one 'spoor' in XML file");

        // Check Type
        Type = type->FirstChild()->Value();
        REQUIRE(Type =="Metrostation" or Type == "Halte","Station type is unknown to system");

        // Create Station or Add it to stations if it doesn't exist yet
        station = findOrAddStation(name->FirstChild()->Value(), Type, stations);

        // Iterate over Sporen
        vector<Spoor*> sporen;
        vector<int> SpoorNrs;
        aantalSporen = 0;
        for (; spoor; spoor = spoor->NextSiblingElement("SPOOR")){
            aantalSporen++;
            REQUIRE(Type != "Halte" or aantalSporen <= 1, "Halte cannot have more than one track.");


            // Get spoorNr, volgende and vorige elements out xml file
            spoorNr = spoor->FirstChildElement("spoorNr");
            volgende = spoor->FirstChildElement("volgende");
            vorige = spoor->FirstChildElement("vorige");

            // Preconditions for elke spoor
            REQUIRE(spoorNr, "Spoor is missing 'spoorNr' in XML file");
            REQUIRE(volgende,"Spoor is missing 'volgende' in XML file");
            REQUIRE(vorige,"Spoor is missing 'vorige' in XML file");

            // Make new Spoor
            Next = findOrAddStation(volgende->FirstChild()->Value(),
                                    stationtypeFromDoc(volgende->FirstChild()->Value(), metronet) , stations);
            Previous = findOrAddStation(vorige->FirstChild()->Value(),
                                        stationtypeFromDoc(volgende->FirstChild()->Value(), metronet) , stations);
            Track = new Spoor(atoi(spoorNr->GetText()), Next , Previous);

            //Make sure certain Spoor isn't more than once in a station
            REQUIRE(find(SpoorNrs.begin(), SpoorNrs.end(), Track->getSpoorNr()) == SpoorNrs.end(),"Spoor with certain SpoorNr occurs more than once in station in XML file");

            // Add to sporen
            SpoorNrs.push_back(Track->getSpoorNr());
            sporen.push_back(Track);
        }
        station->setSporen(sporen);
    }





    Station* BeginStation;
    Tram* newTram;
    TiXmlElement* lijnNr;
    TiXmlElement* voertuigNr;
    TiXmlElement* beginStation;
    TiXmlElement* aantalDefecten;
    TiXmlElement* reparatieTijd;
    TiXmlElement* reparatieKost;
    map<int,bool> voertuigWithNr;
    // Iterate over trams
    for (TiXmlElement* tram = metronet->FirstChildElement("TRAM"); tram; tram = tram->NextSiblingElement("TRAM")){

        // Get lijnNr, type, voertuigNr and beginstation elements out xml file
        lijnNr = tram->FirstChildElement("lijnNr");
        type = tram->FirstChildElement("type");
        voertuigNr = tram->FirstChildElement("voertuigNr");
        beginStation = tram->FirstChildElement("beginStation");
        reparatieTijd = tram->FirstChildElement("reparatieTijd");
        aantalDefecten = tram->FirstChildElement("aantalDefecten");
        reparatieKost = tram->FirstChildElement("reparatieKost");

        // Preconditions for elke tram in XML
        REQUIRE(lijnNr,"Tram is missing 'lijnNr' in XML file");
        REQUIRE(type,"Tram is missing 'type' in XML file");
        REQUIRE(voertuigNr,"Tram is missing 'voertuigNr' in XML file");
        REQUIRE(beginStation,"Tram is missing 'beginStation' in XML file");

        // Get beginStation and check if it is initialized
        BeginStation = getStation(beginStation->FirstChild()->Value(),stations);
        REQUIRE(BeginStation,"Tram's beginStation does not exist");


        // Get Type and check if it is allowed
        Type = type->FirstChild()->Value();
        REQUIRE(Type =="PCC" or Type == "Albatros" or Type == "Stadslijner","Tram type is unknown to system");

        // Create Tram
        if(Type == "PCC"){
            REQUIRE(reparatieTijd,"Tram is missing 'reparatieTijd' in XML file");
            REQUIRE(aantalDefecten,"Tram is missing 'defecten' in XML file");
            REQUIRE(reparatieKost,"Tram is missing 'reparatieKost' in XML file");
            newTram = new PCC(atoi(lijnNr->GetText()), "PCC", BeginStation, atoi(voertuigNr->GetText()),atoi(reparatieKost->GetText()),atoi(reparatieTijd->GetText()),atoi(aantalDefecten->GetText()));

        }else if(Type == "Albatros"){
            newTram = new Albatros(atoi(lijnNr->GetText()), "Albatros", BeginStation, atoi(voertuigNr->GetText()));
        }else if(Type == "Stadslijner"){
            newTram = new Stadslijner(atoi(lijnNr->GetText()), "Stadslijner", BeginStation, atoi(voertuigNr->GetText()));
        }
        BeginStation->getSpoor(atoi(lijnNr->GetText()))->setEmpty(false);
        trams.push_back(newTram);

        // Make sure there aren't 2 Trams with 1 VoertuigNr and Mark this voertuigNr on this lijn as existing
        REQUIRE(!voertuigWithNr[newTram->getVoertuigNr()], "Tram with the same voertuigNr already exists");
        voertuigWithNr[newTram->getVoertuigNr()] = true;

        // Make Sure begin station has Spoor for the Tram
        REQUIRE(hasCorrespondingTrack(BeginStation,newTram),"There is no Spoor beginstation of Tram");
    }

    // Ensure Elements have been added
    ENSURE(!stations.empty(),"No stations have been added");
    ENSURE(!trams.empty(),"No trams have been added");
}

Station* MetronetParser::findOrAddStation(const string &name, const string& type, vector<Station *> &stations) {
    // Search Station and return it to the datastructure
    for (vector<Station *>::iterator it = stations.begin(); it != stations.end(); ++it) {
        if ((*it)->getNaam() == name){
            return *it;
        }
    }
    // Add the station with the given name to the datastructure
    Station *newStation;
    bool stationInXml = false;
    if(type == "Metrostation"){
        newStation = new Metrostation(name);
    }else if (type == "Halte"){
        newStation = new Halte(name);
    }else{
        REQUIRE(stationInXml,"'volgende' or 'vorige' on a Spoor of a Station is not specified in XML file");
    }
    stations.push_back(newStation);
    return newStation;
}
Station *MetronetParser::getStation(const string &name, vector<Station *> &stations){
    // Search Station
    Station* station = NULL;
    for (vector<Station *>::iterator it = stations.begin(); it != stations.end(); ++it) {
        if ((*it)->getNaam() == name){
            station =  *it;
        }
    }
    return station;
}

bool MetronetParser::hasCorrespondingTrack(Station *&station, Tram *&tram) {
    // Get the sporen of the station
    vector<Spoor*> sporen = station->getSporen();

    // Check if any spoor in the station corresponds to the tram's line
    for (vector<Spoor*>::iterator it = sporen.begin(); it != sporen.end(); ++it) {
        Spoor* spoor = *it;

        if (spoor->getSpoorNr() == tram->getLijn()) {
            return true;
        }
    }
    // No corresponding track was found
    return false;
}

string MetronetParser::stationtypeFromDoc(const string &statName, TiXmlElement *station) {
    string Name;
    TiXmlElement* name;
    TiXmlElement* type;
    for(TiXmlElement* stat = station; stat; stat = stat->NextSiblingElement("STATION")){
        name = stat->FirstChildElement("naam");
        REQUIRE(name, "Station is missing 'name' in XML file");
        Name = name->FirstChild()->Value();
        if(statName == Name){
            type = stat->FirstChildElement("type");
            REQUIRE(type, "Station is missing 'type' in XML file");
            return type->FirstChild()->Value();
        }
    }
    return "";
}

